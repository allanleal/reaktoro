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

#include "EquilibriumSpecs.hpp"

// Reaktoro includes
#include <Reaktoro/Common/Algorithms.hpp>
#include <Reaktoro/Common/Constants.hpp>
#include <Reaktoro/Common/Exception.hpp>
#include <Reaktoro/Common/Units.hpp>
#include <Reaktoro/Core/ChemicalProps.hpp>
#include <Reaktoro/Core/ChemicalState.hpp>
#include <Reaktoro/Core/Utils.hpp>

namespace Reaktoro {
namespace {

/// Return a Species object in a Database with given formula and aggregate state
auto getSpecies(Database const& db, String const& formula, AggregateState aggstate) -> Species
{
    const auto selected = db.speciesWithAggregateState(aggstate);
    const auto idx = selected.findWithFormula(formula);
    if(idx < selected.size()) return selected[idx];
    else return Species();
}

/// Return a Species object in a Database with given formula and aqueous aggregate state.
auto getAqueousSpecies(Database const& db, String const& formula) -> Species
{
    return getSpecies(db, formula, AggregateState::Aqueous);
}

/// Return a Species object in a Database with given formula and gaseous aggregate state.
auto getGaseousSpecies(Database const& db, String const& formula) -> Species
{
    return getSpecies(db, formula, AggregateState::Gas);
}

} // namespace

EquilibriumSpecs::EquilibriumSpecs(ChemicalSystem const& system)
: m_system(system)
{
    // By default, start with T and P as unknown *p* control variables.
    addControlVariableP({ "T" });
    addControlVariableP({ "P" });
}

//=================================================================================================
//
// METHODS TO SPECIFY THERMODYNAMIC CONSTRAINTS
//
//=================================================================================================

auto EquilibriumSpecs::temperature() -> void
{
    addInput("T");
    const auto idx = indexControlVariableTemperature();
    assert(idx < pvars.size());
    pvars.erase(pvars.begin() + idx); // remove the existing *p* control variable for temperature
    unknownT = false;
}

auto EquilibriumSpecs::pressure() -> void
{
    addInput("P");
    const auto idx = indexControlVariablePressure();
    assert(idx < pvars.size());
    pvars.erase(pvars.begin() + idx); // remove the existing *p* control variable for pressure
    unknownP = false;
}

auto EquilibriumSpecs::volume() -> void
{
    ConstraintEquation constraint;
    constraint.id = "volume";
    const auto idx = addInput("V");
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().volume() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::internalEnergy() -> void
{
    ConstraintEquation constraint;
    constraint.id = "internalEnergy";
    const auto idx = addInput("U");
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().internalEnergy() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::enthalpy() -> void
{
    ConstraintEquation constraint;
    constraint.id = "enthalpy";
    const auto idx = addInput("H");
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().enthalpy() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::gibbsEnergy() -> void
{
    ConstraintEquation constraint;
    constraint.id = "gibbsEnergy";
    const auto idx = addInput("G");
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().gibbsEnergy() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::helmholtzEnergy() -> void
{
    ConstraintEquation constraint;
    constraint.id = "helmholtzEnergy";
    const auto idx = addInput("A");
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().helmholtzEnergy() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::entropy() -> void
{
    ConstraintEquation constraint;
    constraint.id = "entropy";
    const auto idx = addInput("S");
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().entropy() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::charge() -> void
{
    ConstraintEquation constraint;
    constraint.id = "charge";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().charge() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::elementAmount(StringOrIndex const& element) -> void
{
    const auto ielement = detail::resolveElementIndex(m_system, element);
    const auto elementsymbol = m_system.element(ielement).symbol();
    ConstraintEquation constraint;
    constraint.id = "elementAmount[" + elementsymbol + "]";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().elementAmount(ielement) - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::elementAmountInPhase(StringOrIndex const& element, StringOrIndex const& phase) -> void
{
    const auto ielement = detail::resolveElementIndex(m_system, element);
    const auto iphase = detail::resolvePhaseIndex(m_system, phase);
    const auto elementsymbol = m_system.element(ielement).symbol();
    const auto phasename = m_system.phase(iphase).name();
    ConstraintEquation constraint;
    constraint.id = "elementAmountInPhase[" + elementsymbol + "][" + phasename + "]";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().elementAmountInPhase(ielement, iphase) - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::elementMass(StringOrIndex const& element) -> void
{
    const auto ielement = detail::resolveElementIndex(m_system, element);
    const auto elementsymbol = m_system.element(ielement).symbol();
    ConstraintEquation constraint;
    constraint.id = "elementMass[" + elementsymbol + "]";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().elementMass(ielement) - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::elementMassInPhase(StringOrIndex const& element, StringOrIndex const& phase) -> void
{
    const auto ielement = detail::resolveElementIndex(m_system, element);
    const auto iphase = detail::resolvePhaseIndex(m_system, phase);
    const auto elementsymbol = m_system.element(ielement).symbol();
    const auto phasename = m_system.phase(iphase).name();
    ConstraintEquation constraint;
    constraint.id = "elementMassInPhase[" + elementsymbol + "][" + phasename + "]";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().elementMassInPhase(ielement, iphase) - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::phaseAmount(StringOrIndex const& phase) -> void
{
    const auto iphase = detail::resolvePhaseIndex(m_system, phase);
    const auto phasename = m_system.phase(iphase).name();
    ConstraintEquation constraint;
    constraint.id = "phaseAmount[" + phasename + "]";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().phaseProps(iphase).amount() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::phaseMass(StringOrIndex const& phase) -> void
{
    const auto iphase = detail::resolvePhaseIndex(m_system, phase);
    const auto phasename = m_system.phase(iphase).name();
    ConstraintEquation constraint;
    constraint.id = "phaseMass[" + phasename + "]";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().phaseProps(iphase).mass() - w[idx];
    };
    addConstraint(constraint);
}

auto EquilibriumSpecs::phaseVolume(StringOrIndex const& phase) -> void
{
    const auto iphase = detail::resolvePhaseIndex(m_system, phase);
    const auto phasename = m_system.phase(iphase).name();
    ConstraintEquation constraint;
    constraint.id = "phaseVolume[" + phasename + "]";
    const auto idx = addInput(constraint.id);
    constraint.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return state.props().phaseProps(iphase).volume() - w[idx];
    };
    addConstraint(constraint);
}

//=================================================================================================
//
// METHODS TO SPECIFY CHEMICAL POTENTIAL CONSTRAINTS
//
//=================================================================================================

auto EquilibriumSpecs::chemicalPotential(String substance) -> void
{
    const auto pid = "u[" + substance + "]";
    const auto idx = addInput(pid);
    ControlVariableQ qvar;
    qvar.name = "[" + substance + "]";
    qvar.substance = substance;
    qvar.id = pid;
    qvar.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return w[idx];
    };
    addControlVariableQ(qvar);
}

auto EquilibriumSpecs::lnActivity(Species const& species) -> void
{
    const auto pid = "ln(a[" + species.name() + "])";
    const auto idx = addInput(pid);
    ControlVariableQ qvar;
    qvar.name = "[" + species.name() + "]";
    qvar.substance = species.formula();
    qvar.id = pid;
    qvar.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        auto const& T = state.temperature();
        auto const& P = state.pressure();
        auto const& R = universalGasConstant;
        const auto u0 = species.standardThermoProps(T, P).G0;
        return u0 + R*T*w[idx];
    };
    addControlVariableQ(qvar);
}

auto EquilibriumSpecs::lnActivity(String name) -> void
{
    const auto specieslist = m_system.database().species();
    const auto idx = specieslist.findWithName(name);
    errorif(idx >= specieslist.size(),
        "Could not impose an activity constraint for species with name `", name, "` "
        "because it is not in the database.");
    const auto species = specieslist[idx];
    lnActivity(species);
}

auto EquilibriumSpecs::lgActivity(String name) -> void
{
    lnActivity(name);
}

auto EquilibriumSpecs::activity(String name) -> void
{
    lnActivity(name);
}

auto EquilibriumSpecs::fugacity(String gas) -> void
{
    const auto species = getGaseousSpecies(m_system.database(), gas);
    errorif(species.name().empty(),
        "Could not impose the fugacity constraint for gas `", gas, "` because "
        "there is no gaseous species in the database with this chemical formula.");
    const auto pid = "f[" + gas + "]";
    const auto idx = addInput(pid);
    ControlVariableQ qvar;
    qvar.name = "[" + species.name() + "]";
    qvar.substance = species.formula();
    qvar.id = pid;
    qvar.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        auto const& T = state.temperature();
        auto const& P = state.pressure();
        auto const& R = universalGasConstant;
        const auto u0 = species.standardThermoProps(T, P).G0;
        return u0 + R*T*log(w[idx]);
    };
    addControlVariableQ(qvar);
}

auto EquilibriumSpecs::pH() -> void
{
    const auto species = getAqueousSpecies(m_system.database(), "H+");
    errorif(species.name().empty(),
        "Could not impose pH constraint because the database has "
        "no aqueous species with chemical formula `H+`.");
    const auto pid = "pH";
    const auto idx = addInput(pid);
    ControlVariableQ qvar;
    qvar.name = "[H+]";
    qvar.substance = "H+";
    qvar.id = pid;
    qvar.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        auto const& T = state.temperature();
        auto const& P = state.pressure();
        auto const& R = universalGasConstant;
        const auto u0 = species.standardThermoProps(T, P).G0;
        const auto pH = w[idx];
        return u0 + R*T*(-pH*ln10);
    };
    addControlVariableQ(qvar);
}

auto EquilibriumSpecs::pMg() -> void
{
    const auto species = getAqueousSpecies(m_system.database(), "Mg+2");
    errorif(species.name().empty(),
        "Could not impose pMg constraint because the database has "
        "no aqueous species with chemical formula `Mg+2`.");
    const auto pid = "pMg";
    const auto idx = addInput(pid);
    ControlVariableQ qvar;
    qvar.name = "[Mg+2]";
    qvar.substance = "Mg+2";
    qvar.id = pid;
    qvar.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        auto const& T  = state.temperature();
        auto const& P  = state.pressure();
        auto const& R  = universalGasConstant;
        const auto u0  = species.standardThermoProps(T, P).G0;
        const auto pMg = w[idx];
        return u0 + R*T*(-pMg*ln10);
    };
    addControlVariableQ(qvar);
}

auto EquilibriumSpecs::pE() -> void
{
    const auto idx = addInput("pE");
    ControlVariableQ qvar;
    qvar.name = "[e-]";
    qvar.substance = ChemicalFormula("e-");
    qvar.id = "pE";
    qvar.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        auto const& T = state.temperature();
        auto const& R = universalGasConstant;
        const auto pE = w[idx];
        return R*T*(-pE*ln10);
    };
    addControlVariableQ(qvar);
}

auto EquilibriumSpecs::Eh() -> void
{
    const auto F = faradayConstant; // in C/mol
    const auto idx = addInput("Eh");
    ControlVariableQ qvar;
    qvar.name = "[e-]";
    qvar.substance = ChemicalFormula("e-");
    qvar.id = "Eh";
    qvar.fn = [=](ChemicalState const& state, VectorXrConstRef w)
    {
        return -F * w[idx]; // in J/mol (chemical potential of electron)
    };
    addControlVariableQ(qvar);
}

//=================================================================================================
//
// METHODS TO SPECIFY HOW THE CHEMICAL SYSTEM IS OPEN
//
//=================================================================================================

auto EquilibriumSpecs::openTo(ChemicalFormula const& substance) -> void
{
    addUnknownTitrantAmount(substance);
}

//=================================================================================================
//
// METHODS TO SPECIFY ADDITIONAL UNKNOWNS
//
//=================================================================================================

auto EquilibriumSpecs::addUnknownTitrantAmount(ChemicalFormula const& substance) -> void
{
    ControlVariableP pvar;
    pvar.name = "[" + substance.str() + "]";
    pvar.substance = substance;
    addControlVariableP(pvar);
}

auto EquilibriumSpecs::addUnknownChemicalPotential(String const& species) -> void
{
    errorif(contains(species_with_unknown_chemical_potentials, species), "Cannot add an unknown for the chemical potential of ", species, " because this has already been done directly or indirectly.");
    species_with_unknown_chemical_potentials.push_back(species);
    const auto ispecies = m_system.species().index(species);
    ControlVariableP pvar;
    pvar.name = "u[" + species + "]";
    pvar.ispecies = ispecies;
    pvar.fn = [=](ChemicalState const& state, real const& pk) -> real
    {
        return pk;
    };
    addControlVariableP(pvar);
}

auto EquilibriumSpecs::addUnknownStandardChemicalPotential(String const& species) -> void
{
    errorif(contains(species_with_unknown_chemical_potentials, species), "Cannot add an unknown for the standard chemical potential of ", species, " because this has already been done directly or indirectly.");
    species_with_unknown_chemical_potentials.push_back(species);
    const auto ispecies = m_system.species().index(species);
    ControlVariableP pvar;
    pvar.name = "u0[" + species + "]";
    pvar.ispecies = ispecies;
    pvar.fn = [=](ChemicalState const& state, real const& pk) -> real
    {
        auto const& props = state.props();
        auto const& T = props.temperature();
        auto const& lnai = props.speciesActivityLn(ispecies);
        auto const& R = universalGasConstant;
        return pk + R*T*lnai;
    };
    addControlVariableP(pvar);
}

auto EquilibriumSpecs::addUnknownActivity(String const& species) -> void
{
    errorif(contains(species_with_unknown_chemical_potentials, species), "Cannot add an unknown for the activity of ", species, " because this has already been done directly or indirectly.");
    species_with_unknown_chemical_potentials.push_back(species);
    const auto ispecies = m_system.species().index(species);
    ControlVariableP pvar;
    pvar.name = "a[" + species + "]";
    pvar.ispecies = ispecies;
    pvar.fn = [=](ChemicalState const& state, real const& pk) -> real
    {
        auto const& props = state.props();
        auto const& T = props.temperature();
        auto const& G0 = props.speciesStandardGibbsEnergy(ispecies);
        auto const& R = universalGasConstant;
        return G0 + R*T*log(pk);
    };
    addControlVariableP(pvar);
}

auto EquilibriumSpecs::addUnknownActivityCoefficient(String const& species) -> void
{
    errorif(contains(species_with_unknown_chemical_potentials, species), "Cannot add an unknown for the activity coefficient of ", species, " because this has already been done directly or indirectly.");
    species_with_unknown_chemical_potentials.push_back(species);
    const auto ispecies = m_system.species().index(species);
    ControlVariableP pvar;
    pvar.name = "g[" + species + "]";
    pvar.ispecies = ispecies;
    pvar.fn = [=](ChemicalState const& state, real const& pk) -> real
    {
        auto const& props = state.props();
        auto const& T = props.temperature();
        auto const& G0 = props.speciesStandardGibbsEnergy(ispecies);
        auto const& lnci = props.speciesConcentrationLn(ispecies);
        auto const& R = universalGasConstant;
        return G0 + R*T*(lnci + log(pk));
    };
    addControlVariableP(pvar);
}

//=================================================================================================
//
// METHODS TO GET THE NUMBER OF INTRODUCED CONSTRAINTS, PARAMETERS, AND CONTROL VARIABLES
//
//=================================================================================================

auto EquilibriumSpecs::numInputs() const -> Index
{
    return m_inputs.size();
}

auto EquilibriumSpecs::numParams() const -> Index
{
    return m_params.size();
}

auto EquilibriumSpecs::numControlVariables() const -> Index
{
    return numControlVariablesQ() + numControlVariablesP();
}

auto EquilibriumSpecs::numControlVariablesP() const -> Index
{
    return pvars.size();
}

auto EquilibriumSpecs::numControlVariablesQ() const -> Index
{
    return qvars.size();
}

auto EquilibriumSpecs::numTitrants() const -> Index
{
    return titrants_explicit.size() + titrants_implicit.size();
}

auto EquilibriumSpecs::numTitrantsExplicit() const -> Index
{
    return titrants_explicit.size();
}

auto EquilibriumSpecs::numTitrantsImplicit() const -> Index
{
    return titrants_implicit.size();
}

auto EquilibriumSpecs::numConstraints() const -> Index
{
    return econstraints.size() + rconstraints.size() + qvars.size();
}

//=================================================================================================
//
// METHODS TO GET THE NAMES OF INTRODUCED CONSTRAINTS, PARAMETERS, AND CONTROL VARIABLES
//
//=================================================================================================

auto EquilibriumSpecs::namesInputs() const -> Strings
{
    return m_inputs;
}

auto EquilibriumSpecs::namesParams() const -> Strings
{
    return vectorize(m_params, RKT_LAMBDA(x, x.id()));
}

auto EquilibriumSpecs::namesControlVariables() const -> Strings
{
    return concatenate(namesControlVariablesP(), namesControlVariablesQ());
}

auto EquilibriumSpecs::namesControlVariablesP() const -> Strings
{
    return vectorize(pvars, RKT_LAMBDA(x, x.name));
}

auto EquilibriumSpecs::namesControlVariablesQ() const -> Strings
{
    return vectorize(qvars, RKT_LAMBDA(x, x.name));
}

auto EquilibriumSpecs::namesTitrants() const -> Strings
{
    return concatenate(namesTitrantsExplicit(), namesTitrantsImplicit());
}

auto EquilibriumSpecs::namesTitrantsExplicit() const -> Strings
{
    return vectorize(titrants_explicit, RKT_LAMBDA(x, "[" + x.str() + "]"));
}

auto EquilibriumSpecs::namesTitrantsImplicit() const -> Strings
{
    return vectorize(titrants_implicit, RKT_LAMBDA(x, "[" + x.str() + "]"));
}

auto EquilibriumSpecs::namesConstraints() const -> Strings
{
    Strings names = vectorize(econstraints, RKT_LAMBDA(x, x.id));
    names = concatenate(names, vectorize(qvars, RKT_LAMBDA(x, x.id)));
    names = concatenate(names, vectorize(rconstraints, RKT_LAMBDA(x, x.id)));
    return names;
}

//=================================================================================================
//
// METHODS TO ADD CONSTRAINTS AND PARAMETERS
//
//=================================================================================================

auto EquilibriumSpecs::addControlVariableQ(ControlVariableQ const& qvar) -> void
{
    errorif(qvar.name.empty(), "Could not add *q* control variable because its name is empty.");
    errorif(containsfn(qvars, RKT_LAMBDA(x, x.name == qvar.name)), "Could not add *q* control variable with name `", qvar.name, "` because another *q* control variable has already been added with same name.");
    errorif(qvar.fn == nullptr, "Could not add *q* control variable with name `", qvar.name, "` because its chemical potential function is empty.");
    throwErrorIfTitrantHasBeenRegistered(qvar.substance);
    titrants_implicit.push_back(qvar.substance);
    qvars.push_back(qvar);
}

auto EquilibriumSpecs::addControlVariableP(ControlVariableP const& pvar) -> void
{
    const auto Nn = m_system.species().size();
    errorif(pvar.name.empty(), "Could not add *p* control variable because its name is empty.");
    errorif(containsfn(pvars, RKT_LAMBDA(x, x.name == pvar.name)), "Could not add *p* control variable with name `", pvar.name, "` because another *p* control variable has already been added with same name.");
    errorif(pvar.ispecies < Nn && pvar.fn == nullptr, "Could not add *p* control variable with name `", pvar.name, "` because the chemical potential function is missing.");
    errorif(pvar.ispecies >= Nn && pvar.fn, "Could not add *p* control variable with name `", pvar.name, "` because the index of the species whose chemical potential is unknown is missing (index value is ", pvar.ispecies, ", but number of species is ", Nn, ").");
    if(pvar.substance.str().size())
    {
        throwErrorIfTitrantHasBeenRegistered(pvar.substance);
        titrants_explicit.push_back(pvar.substance);
    }
    pvars.push_back(pvar);
}

auto EquilibriumSpecs::addConstraint(ConstraintEquation const& constraint) -> void
{
    const auto constraint_has_same_id = containsfn(econstraints, RKT_LAMBDA(x, x.id == constraint.id));
    errorif(constraint_has_same_id, "Cannot impose a new equation constraint with same id (", constraint.id, ").");
    errorif(constraint.id.empty(), "An equation constraint cannot have an empty id.");
    errorif(!constraint.fn, "The equation constraint with id `", constraint.id, " should not have an empty function.");
    econstraints.push_back(constraint);
}

auto EquilibriumSpecs::addReactivityConstraint(ReactivityConstraint const& constraint) -> void
{
    const auto constraint_has_same_id = containsfn(rconstraints, RKT_LAMBDA(x, x.id == constraint.id));
    errorif(constraint_has_same_id, "Cannot impose a new reactivity constraint with same id (", constraint.id, ").");
    errorif(constraint.id.empty(), "A reactivity constraint cannot have an empty id.");
    errorif(constraint.Kn.size() != m_system.species().size(), "The `Kn` vector in the reactivity constraint with id `", constraint.id, " has size ", constraint.Kn.size(), " which should be equal to the number of species in the chemical system, ", m_system.species().size(), ".");
    errorif(constraint.Kn.cwiseAbs().minCoeff() == 0, "The `Kn` vector in the reactivity constraint with id `", constraint.id, " should not be entirely composed of zeros.", constraint.Kn.size(), " which should be equal to the number of species in the chemical system, ", m_system.species().size(), ".");
    errorif(constraint.Kp.size() > 0 && constraint.Kp.size() != pvars.size(), "The `Kp` vector in the reactivity constraint with id `", constraint.id, " has non-zero size ", constraint.Kp.size(), " which should be equal to the number of p control variables, ", pvars.size(), ".");
    rconstraints.push_back(constraint);
}

auto EquilibriumSpecs::addInput(String const& var) -> Index
{
    errorif(contains(m_inputs, var), "Could not add input variable with id `", var, "` to the "
        "list of input variables for the equilibrium problem because "
        "another input already exists with same id.");
    m_inputs.push_back(var);
    return m_inputs.size() - 1; // the index of the just added input variable
}

auto EquilibriumSpecs::addInput(Param const& param) -> Index
{
    const auto idx = addInput(param.id());
    m_params.push_back(param);
    m_params_idxs.push_back(idx);
    return idx;
}

//=================================================================================================
//
// MISCELLANEOUS METHODS
//
//=================================================================================================

auto EquilibriumSpecs::system() const -> ChemicalSystem const&
{
    return m_system;
}

auto EquilibriumSpecs::inputs() const -> Strings const&
{
    return m_inputs;
}

auto EquilibriumSpecs::params() const -> const Vec<Param>&
{
    return m_params;
}

auto EquilibriumSpecs::indicesParams() const -> const Vec<Index>&
{
    return m_params_idxs;
}

auto EquilibriumSpecs::isTemperatureUnknown() const -> bool
{
    return unknownT;
}

auto EquilibriumSpecs::isPressureUnknown() const -> bool
{
    return unknownP;
}

auto EquilibriumSpecs::indexControlVariableTemperature() const -> Index
{
    return unknownT ? 0 : -1;
}

auto EquilibriumSpecs::indexControlVariablePressure() const -> Index
{
    return unknownP ? (unknownT ? 1 : 0) : -1;
}

auto EquilibriumSpecs::controlVariablesQ() const -> const Vec<ControlVariableQ>&
{
    return qvars;
}

auto EquilibriumSpecs::controlVariablesP() const -> const Vec<ControlVariableP>&
{
    return pvars;
}

auto EquilibriumSpecs::titrants() const -> Vec<ChemicalFormula>
{
    return concatenate(titrants_explicit, titrants_implicit);
}

auto EquilibriumSpecs::titrantsExplicit() const -> Vec<ChemicalFormula>
{
    return titrants_explicit;
}

auto EquilibriumSpecs::titrantsImplicit() const -> Vec<ChemicalFormula>
{
    return titrants_implicit;
}

auto EquilibriumSpecs::equationConstraints() const -> Vec<ConstraintEquation> const&
{
    return econstraints;
}

auto EquilibriumSpecs::reactivityConstraints() const -> Vec<ReactivityConstraint> const&
{
    return rconstraints;
}

//=================================================================================================
//
// PRIVATE METHODS
//
//=================================================================================================

auto EquilibriumSpecs::throwErrorIfTitrantHasBeenRegistered(ChemicalFormula const& substance) const -> void
{
    const auto already_an_explicit_titrant = containsfn(titrants_explicit, RKT_LAMBDA(x, x.equivalent(substance)));
    errorif(already_an_explicit_titrant, "Cannot specify again that the chemical system is open to substance ", substance.str(), ". "
        "You have already explicitly specified that the chemical system is open to this substance.");
    const auto idx = indexfn(titrants_implicit, RKT_LAMBDA(x, x.equivalent(substance)));
    const auto already_an_implicit_titrant = idx < titrants_implicit.size();
    errorif(already_an_implicit_titrant, "Cannot specify again that the chemical system is open to substance ", substance.str(), ". "
        "You have implicitly specified that the chemical system is open to this substance when imposing a chemical potential constraint for it.");
}

} // namespace Reaktoro
