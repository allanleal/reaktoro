// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright © 2014-2022 Allan Leal
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#include "EquilibriumSolver.hpp"

// Optima includes
#include <Optima/Options.hpp>
#include <Optima/Problem.hpp>
#include <Optima/Result.hpp>
#include <Optima/Sensitivity.hpp>
#include <Optima/Solver.hpp>
#include <Optima/State.hpp>

// Reaktoro includes
#include <Reaktoro/Common/ArrayStream.hpp>
#include <Reaktoro/Common/Constants.hpp>
#include <Reaktoro/Common/Exception.hpp>
#include <Reaktoro/Core/ChemicalState.hpp>
#include <Reaktoro/Core/ChemicalSystem.hpp>
#include <Reaktoro/Equilibrium/EquilibriumConditions.hpp>
#include <Reaktoro/Equilibrium/EquilibriumDims.hpp>
#include <Reaktoro/Equilibrium/EquilibriumOptions.hpp>
#include <Reaktoro/Equilibrium/EquilibriumProps.hpp>
#include <Reaktoro/Equilibrium/EquilibriumRestrictions.hpp>
#include <Reaktoro/Equilibrium/EquilibriumResult.hpp>
#include <Reaktoro/Equilibrium/EquilibriumSensitivity.hpp>
#include <Reaktoro/Equilibrium/EquilibriumSetup.hpp>
#include <Reaktoro/Equilibrium/EquilibriumSpecs.hpp>

namespace Reaktoro {

struct EquilibriumSolver::Impl
{
    /// The chemical system associated with this equilibrium solver.
    const ChemicalSystem system;

    /// The chemical equilibrium specifications associated with this equilibrium solver.
    const EquilibriumSpecs specs;

    /// The dimensions of the variables and constraints in the equilibrium specifications.
    const EquilibriumDims dims;

    /// The auxiliary equilibrium restrictions used whenever none are given.
    const EquilibriumRestrictions restrictions;

    /// The auxiliary equilibrium conditions used whenever none are given.
    EquilibriumConditions conditions;

    // The equilibrium problem setup for the equilibrium solver.
    EquilibriumSetup setup;

    /// The options of the equilibrium solver.
    EquilibriumOptions options;

    /// The dimensions of the variables and constraints in the optimization problem.
    Optima::Dims optdims;

    /// The optimization problem to be configured for a chemical equilibrium calculation.
    Optima::Problem optproblem;

    /// The optimization state of the calculation.
    Optima::State optstate;

    /// The optimization sensitivity of the calculation.
    Optima::Sensitivity optsensitivity;

    /// The solver for the optimization calculations.
    Optima::Solver optsolver;

    /// The result of the equilibrium calculation
    EquilibriumResult result;

    /// The array stream used to clean up autodiff seed values from the last ChemicalProps update step.
    ArrayStream<double> stream;

    /// Construct a Impl instance with given EquilibriumConditions object.
    Impl(const EquilibriumSpecs& specs)
    : system(specs.system()), specs(specs), dims(specs), restrictions(system), conditions(specs), setup(specs)
    {
        // Initialize the equilibrium solver with the default options
        setOptions(options);
    }

    /// Set the options of the equilibrium solver.
    auto setOptions(EquilibriumOptions const& opts) -> void
    {
        // Update the options of the equilibrium calculation
        options = opts;

        // Pass along the options used for the calculation to EquilibriumSetup object
        setup.setOptions(options);

        // Ensure some options have proper values
        error(options.epsilon <= 0, "EquilibriumOptions::epsilon cannot be zero or negative.");

        // Initialize the names of the primal and dual variables
        if(options.optima.output.active)
        {
            // Define some auxiliary references to the variables names
            auto& xnames = options.optima.output.xnames;

            // Initialize the names of the variables corresponding to the species
            for(auto species : system.species())
                xnames.push_back("n[" + species.name() + "]");

            // Initialize the names of the variables corresponding to the implicit titrants
            for(auto titrant : specs.namesTitrantsImplicit())
                xnames.push_back(titrant);
        }

        // Pass along the options used for the calculation to Optima::Solver object
        optsolver.setOptions(options.optima);
    }

    /// Update the optimization problem before a new equilibrium calculation.
    auto updateOptProblem(ChemicalState const& state0, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0)
    {
        // The input variables for the equilibrium calculation
        const VectorXr w = conditions.inputValuesGetOrCompute(state0);

        // Create the Optima::Dims object with dimension info of the optimization problem
        optdims = Optima::Dims();
        optdims.x  = dims.Nx;
        optdims.p  = dims.Np;
        optdims.be = dims.Nc;
        optdims.c  = dims.Nw + dims.Nc; // c' = (w, c) where w are the input variables and c are the amounts of components

        // Recreate a new Optima::Problem problem (TODO: Avoid recreation of Optima::Problem object for each equilibrium calculation)
        optproblem = Optima::Problem(optdims);

        // Set the resources function in the Optima::Problem object
        optproblem.r = [=](VectorXdConstRef x, VectorXdConstRef p, VectorXdConstRef c, Optima::ObjectiveOptions fopts, Optima::ConstraintOptions hopts, Optima::ConstraintOptions vopts) mutable
        {
            setup.update(x, p, w);

            if(fopts.eval.fxc || vopts.eval.ddc)
                setup.assembleChemicalPropsJacobianBegin();

            if(fopts.eval.fxx || vopts.eval.ddx)
                setup.updateGradX(fopts.ibasicvars);
            if(fopts.eval.fxp || vopts.eval.ddp)
                setup.updateGradP();
            if(fopts.eval.fxc || vopts.eval.ddc)
                setup.updateGradW();

            if(fopts.eval.fxc || vopts.eval.ddc)
                setup.assembleChemicalPropsJacobianEnd();
        };

        // Set the objective function in the Optima::Problem object
        optproblem.f = [=](Optima::ObjectiveResultRef res, VectorXdConstRef x, VectorXdConstRef p, VectorXdConstRef c, Optima::ObjectiveOptions opts) mutable
        {
            res.f = setup.getGibbsEnergy();
            res.fx = setup.getGibbsGradX();

            if(opts.eval.fxx)
                res.fxx = setup.getGibbsHessianX();

            if(opts.eval.fxp)
                res.fxp = setup.getGibbsHessianP();

            if(opts.eval.fxc)
                res.fxc = setup.getGibbsHessianC();

            res.fxx4basicvars = setup.usingPartiallyExactDerivatives();
            res.diagfxx = setup.usingDiagonalApproxDerivatives();

            res.succeeded = true;
        };

        // Set the external constraint function in the Optima::Problem object
        optproblem.v = [=](Optima::ConstraintResultRef res, VectorXdConstRef x, VectorXdConstRef p, VectorXdConstRef c, Optima::ConstraintOptions opts) mutable
        {
            res.val = setup.getConstraintResiduals();

            if(opts.eval.ddx)
                res.ddx = setup.getConstraintResidualsGradX();

            if(opts.eval.ddp)
                res.ddp = setup.getConstraintResidualsGradP();

            if(opts.eval.ddc)
                res.ddc = setup.getConstraintResidualsGradC();

            res.succeeded = true;
        };

        // Set the coefficient matrices Aex and Aep of the linear equality constraints
        optproblem.Aex = setup.Aex();
        optproblem.Aep = setup.Aep();

        /// Set the right-hand side vector be of the linear equality constraints.
        optproblem.be = c0.size() ? c0 : conditions.initialComponentAmountsGetOrCompute(state0);

        // Set the lower and upper bounds of the species amounts
        optproblem.xlower = setup.assembleLowerBoundsVector(restrictions, state0);
        optproblem.xupper = setup.assembleUpperBoundsVector(restrictions, state0);

        // Set the lower and upper bounds of the *p* control variables
        optproblem.plower = conditions.lowerBoundsControlVariablesP();
        optproblem.pupper = conditions.upperBoundsControlVariablesP();

        // Set the values of the input variables for sensitivity derivatives (due to the use of Param, a wrapper to a shared pointer, the actual values of c here are not important, because the Param objects are embedded in the models)
        optproblem.c = zeros(optdims.c);

        // Set the Jacobian matrix d(be)/dc = [d(be)/dw d(be)/db]
        // The left Nw x Nb block is zero. The right Nb x Nb block is identity!
        optproblem.bec.setZero();
        optproblem.bec.rightCols(dims.Nc).diagonal().setOnes();
    }

    /// Update the initial state variables before the new equilibrium calculation.
    auto updateOptState(ChemicalState const& state0)
    {
        // Allocate memory if needed
        if((optstate.dims.x != dims.Nx) || (!result.optima.succeeded))
            optstate = Optima::State(optdims);

        // Set species amounts in x = (n, q) to that from the chemical state
        optstate.x.head(dims.Nn) = state0.speciesAmounts();

        // Set delta variables in q to zero (i.e., the amount of an implicit titrant to add/remove)
        optstate.x.tail(dims.Nq).fill(0.0);

        // Set delta variables in p to zero (i.e., the amount of an explicit titrant to add/remove, temperature and/or pressure increase/decrease)
        optstate.p.fill(0.0);

        // TODO: Instead of using T and P as unknown, use dT and dP, so this is block of code is not needed!
        if(specs.isTemperatureUnknown())
        {
            optstate.p[0] = state0.temperature();
            if(specs.isPressureUnknown())
                optstate.p[1] = state0.pressure();
        }
        else if(specs.isPressureUnknown())
            optstate.p[0] = state0.pressure();
    }

    /// Update the chemical state object with computed optimization state.
    auto updateChemicalState(ChemicalState& state, EquilibriumConditions const& conditions)
    {
        // Update the ChemicalProps object in state
        auto& props = state.props();
        props = setup.chemicalProps();

        // TODO: In Optima, make sure check for convergence does not compute
        // any derivatives. Use F.updateSkipJacobian(u) instead of F.update(u)
        // in method MasterSolver::Impl::stepping. Once this is implemented,
        // there will be no need for this method, because the chemical
        // properties will be clean of derivatives (i.e., autodiff seed values
        // will be zero). Once this is done, the next step of cleaning up such
        // seed values can be removed.

        // Make sure the derivative information in the underlying chemical
        // properties of the system are zeroed out!
        ArrayStream<double> stream;
        props.serialize(stream);
        props.deserialize(stream);

        // Update other state variables in the ChemicalState object
        state.setTemperature(props.temperature());
        state.setPressure(props.pressure());
        state.setSpeciesAmounts(optstate.x.head(dims.Nn));
        state.equilibrium().setInputNames(conditions.inputNames());
        state.equilibrium().setInputValues(conditions.inputValues());
        state.equilibrium().setInitialComponentAmounts(optproblem.be);
        state.equilibrium().setOptimaState(optstate);
    }

    /// Update the equilibrium sensitivity object with computed optimization sensitivity.
    auto updateEquilibriumSensitivity(EquilibriumSensitivity& sensitivity)
    {
        auto const& Nn = dims.Nn;
        auto const& Nc = dims.Nc;
        auto const& Nq = dims.Nq;
        auto const& Nw = dims.Nw;
        auto const& xc = optsensitivity.xc;
        auto const& pc = optsensitivity.pc;

        auto const& props = setup.equilibriumProps();

        const auto dndw = xc.topLeftCorner(Nn, Nw);
        const auto dqdw = xc.bottomLeftCorner(Nq, Nw);
        const auto dpdw = pc.leftCols(Nw);
        const auto dndc = xc.topRightCorner(Nn, Nc);
        const auto dqdc = xc.bottomRightCorner(Nq, Nc);
        const auto dpdc = pc.rightCols(Nc);
        const auto dudn = props.dudn();
        const auto dudp = props.dudp();
        const auto dudw = props.dudw();

        sensitivity.initialize(specs);
        sensitivity.dndw(dndw);
        sensitivity.dqdw(dqdw);
        sensitivity.dpdw(dpdw);
        sensitivity.dndc(dndc);
        sensitivity.dqdc(dqdc);
        sensitivity.dpdc(dpdc);
        sensitivity.dudw(dudw + dudn*dndw + dudp*dpdw);
        sensitivity.dudc(dudn*dndc + dudp*dpdc);
    }

    auto solve(ChemicalState& state) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, conditions, restrictions);
    }

    auto solve(ChemicalState& state, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, conditions, restrictions);
    }

    auto solve(ChemicalState& state, EquilibriumConditions const& conditions) -> EquilibriumResult
    {
        return solve(state, conditions, restrictions);
    }

    auto solve(ChemicalState& state, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
    {
        return solve(state, conditions, restrictions, ArrayXd{});
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, sensitivity, conditions, restrictions, ArrayXd{});
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, sensitivity, conditions, restrictions, ArrayXd{});
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions) -> EquilibriumResult
    {
        return solve(state, sensitivity, conditions, restrictions, ArrayXd{});
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
    {
        return solve(state, conditions, restrictions, ArrayXd{});
    }

    auto solve(ChemicalState& state, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, conditions, restrictions, c0);
    }

    auto solve(ChemicalState& state, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, conditions, restrictions, c0);
    }

    auto solve(ChemicalState& state, EquilibriumConditions const& conditions, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        return solve(state, conditions, restrictions, c0);
    }

    auto solve(ChemicalState& state, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        updateOptProblem(state, conditions, restrictions, c0);
        updateOptState(state);

        result.optima = optsolver.solve(optproblem, optstate);

        updateChemicalState(state, conditions);

        return result;
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, sensitivity, conditions, restrictions, c0);
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        conditions.temperature(state.temperature());
        conditions.pressure(state.pressure());
        conditions.surfaceAreas(state.surfaceAreas());
        return solve(state, sensitivity, conditions, restrictions, c0);
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        return solve(state, sensitivity, conditions, restrictions, c0);
    }

    auto solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
    {
        EquilibriumResult result;

        updateOptProblem(state, conditions, restrictions, c0);
        updateOptState(state);

        result.optima = optsolver.solve(optproblem, optstate, optsensitivity);

        updateChemicalState(state, conditions);
        updateEquilibriumSensitivity(sensitivity);

        return result;
    }
};

EquilibriumSolver::EquilibriumSolver(ChemicalSystem const& system)
: pimpl(new Impl(EquilibriumSpecs::TP(system)))
{}

EquilibriumSolver::EquilibriumSolver(EquilibriumSpecs const& specs)
: pimpl(new Impl(specs))
{}

EquilibriumSolver::EquilibriumSolver(EquilibriumSolver const& other)
: pimpl(new Impl(*other.pimpl))
{}

EquilibriumSolver::~EquilibriumSolver()
{}

auto EquilibriumSolver::operator=(EquilibriumSolver other) -> EquilibriumSolver&
{
    pimpl = std::move(other.pimpl);
    return *this;
}

auto EquilibriumSolver::solve(ChemicalState& state) -> EquilibriumResult
{
    return pimpl->solve(state);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
{
    return pimpl->solve(state, restrictions);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumConditions const& conditions) -> EquilibriumResult
{
    return pimpl->solve(state, conditions);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
{
    return pimpl->solve(state, conditions, restrictions);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity, restrictions);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity, conditions);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity, conditions, restrictions);
}

auto EquilibriumSolver::solve(ChemicalState& state, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, c0);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, restrictions, c0);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumConditions const& conditions, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, conditions, c0);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, conditions, restrictions, c0);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity, c0);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity, restrictions, c0);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity, conditions, c0);
}

auto EquilibriumSolver::solve(ChemicalState& state, EquilibriumSensitivity& sensitivity, EquilibriumConditions const& conditions, EquilibriumRestrictions const& restrictions, ArrayXdConstRef const& c0) -> EquilibriumResult
{
    return pimpl->solve(state, sensitivity, conditions, restrictions, c0);
}

auto EquilibriumSolver::setOptions(EquilibriumOptions const& options) -> void
{
    pimpl->setOptions(options);
}

} // namespace Reaktoro
