// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2020 Allan Leal
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

// pybind11 includes
#include <pybind11/pybind11.h>
namespace py = pybind11;

// Reaktoro includes
#include <Reaktoro/Optimization/OptimumOptions.hpp>

namespace Reaktoro {

void exportOptimumOptions(py::module& m)
{
    py::enum_<StepMode>(m, "StepMode")
        .value("Conservative", StepMode::Conservative)
        .value("Aggressive", StepMode::Aggressive)
        ;

    py::class_<OptimumParamsActNewton>(m, "OptimumParamsActNewton")
        .def(py::init<>())
        .def_readwrite("threshold", &OptimumParamsActNewton::threshold)
        ;

    py::class_<OptimumParamsIpNewton>(m, "OptimumParamsIpNewton")
        .def(py::init<>())
        .def_readwrite("mu", &OptimumParamsIpNewton::mu)
        .def_readwrite("tau", &OptimumParamsIpNewton::tau)
        .def_readwrite("step", &OptimumParamsIpNewton::step)
        ;

    py::class_<OptimumParamsIpActive>(m, "OptimumParamsIpActive")
        .def(py::init<>())
        .def_readwrite("epsilon", &OptimumParamsIpActive::epsilon)
        .def_readwrite("tau", &OptimumParamsIpActive::tau)
        ;

    py::class_<OptimumParamsIpAction>(m, "OptimumParamsIpAction")
        .def(py::init<>())
        .def_readwrite("mu", &OptimumParamsIpAction::mu)
        .def_readwrite("tau", &OptimumParamsIpAction::tau)
        .def_readwrite("step", &OptimumParamsIpAction::step)
        ;

    py::class_<OptimumParamsIpOpt>(m, "OptimumParamsIpOpt")
        .def(py::init<>())
        .def_readwrite("mu", &OptimumParamsIpOpt::mu)
        .def_readwrite("delta", &OptimumParamsIpOpt::delta)
        .def_readwrite("eta_phi", &OptimumParamsIpOpt::eta_phi)
        .def_readwrite("gamma_alpha", &OptimumParamsIpOpt::gamma_alpha)
        .def_readwrite("gamma_phi", &OptimumParamsIpOpt::gamma_phi)
        .def_readwrite("gamma_theta", &OptimumParamsIpOpt::gamma_theta)
        .def_readwrite("kappa_epsilon", &OptimumParamsIpOpt::kappa_epsilon)
        .def_readwrite("kappa_mu", &OptimumParamsIpOpt::kappa_mu)
        .def_readwrite("kappa_sigma", &OptimumParamsIpOpt::kappa_sigma)
        .def_readwrite("kappa_soc", &OptimumParamsIpOpt::kappa_soc)
        .def_readwrite("s_phi", &OptimumParamsIpOpt::s_phi)
        .def_readwrite("s_theta", &OptimumParamsIpOpt::s_theta)
        .def_readwrite("tau_min", &OptimumParamsIpOpt::tau_min)
        .def_readwrite("theta_mu", &OptimumParamsIpOpt::theta_mu)
        .def_readwrite("max_iters_soc", &OptimumParamsIpOpt::max_iters_soc)
        .def_readwrite("soc", &OptimumParamsIpOpt::soc)
        .def_readwrite("mux", &OptimumParamsIpOpt::mux)
        .def_readwrite("scaling", &OptimumParamsIpOpt::scaling)
        ;

    py::class_<OptimumParamsKarpov>(m, "OptimumParamsKarpov")
        .def(py::init<>())
        .def_readwrite("line_search_max_iterations", &OptimumParamsKarpov::line_search_max_iterations)
        .def_readwrite("line_search_wolfe", &OptimumParamsKarpov::line_search_wolfe)
        .def_readwrite("tau_feasible", &OptimumParamsKarpov::tau_feasible)
        .def_readwrite("tau_descent", &OptimumParamsKarpov::tau_descent)
        .def_readwrite("feasibility_tolerance", &OptimumParamsKarpov::feasibility_tolerance)
        .def_readwrite("negative_dual_tolerance", &OptimumParamsKarpov::negative_dual_tolerance)
        .def_readwrite("active_to_inactive", &OptimumParamsKarpov::active_to_inactive)
        .def_readwrite("use_kkt_solver", &OptimumParamsKarpov::use_kkt_solver)
        ;

    py::class_<OptimumOutputOptions, OutputterOptions>(m, "OptimumOutput")
        .def(py::init<>())
        .def_readwrite("xprefix", &OptimumOutputOptions::xprefix)
        .def_readwrite("yprefix", &OptimumOutputOptions::yprefix)
        .def_readwrite("zprefix", &OptimumOutputOptions::zprefix)
        .def_readwrite("xnames", &OptimumOutputOptions::xnames)
        .def_readwrite("ynames", &OptimumOutputOptions::ynames)
        .def_readwrite("znames", &OptimumOutputOptions::znames)
        ;

    py::class_<RegularizerOptions>(m, "RegularizerOptions")
        .def(py::init<>())
        .def_readwrite("echelonize", &RegularizerOptions::echelonize)
        .def_readwrite("max_denominator", &RegularizerOptions::max_denominator)
        ;

    py::class_<OptimumParamsRegularization, RegularizerOptions>(m, "OptimumParamsRegularization")
        .def(py::init<>())
        .def_readwrite("delta", &OptimumParamsRegularization::delta)
        .def_readwrite("gamma", &OptimumParamsRegularization::gamma)
        ;

    py::class_<OptimumOptions>(m, "OptimumOptions")
        .def(py::init<>())
        .def_readwrite("tolerance", &OptimumOptions::tolerance)
        .def_readwrite("tolerancex", &OptimumOptions::tolerancex)
        .def_readwrite("tolerancef", &OptimumOptions::tolerancef)
        .def_readwrite("tolerance_linear_constraints", &OptimumOptions::tolerance_linear_constraints)
        .def_readwrite("max_iterations", &OptimumOptions::max_iterations)
        .def_readwrite("output", &OptimumOptions::output)
        .def_readwrite("actnewton", &OptimumOptions::actnewton)
        .def_readwrite("ipaction", &OptimumOptions::ipaction)
        .def_readwrite("ipopt", &OptimumOptions::ipopt)
        .def_readwrite("ipnewton", &OptimumOptions::ipnewton)
        .def_readwrite("ipactive", &OptimumOptions::ipactive)
        .def_readwrite("karpov", &OptimumOptions::karpov)
        .def_readwrite("regularization", &OptimumOptions::regularization)
        ;
}

} // namespace Reaktoro
