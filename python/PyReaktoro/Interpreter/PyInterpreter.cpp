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
#include <pybind11/stl.h>
namespace py = pybind11;

// Reaktoro includes
#include <Reaktoro/Interpreter/Interpreter.hpp>
#include <Reaktoro/Core/ChemicalSystem.hpp>
#include <Reaktoro/Core/ChemicalState.hpp>

namespace Reaktoro {

void exportInterpreter(py::module& m)
{
    py::class_<Interpreter>(m, "Interpreter")
        .def(py::init<>())
        .def("executeJsonString", &Interpreter::executeJsonString)
        .def("executeJsonFile", &Interpreter::executeJsonFile)
        .def("system", &Interpreter::system, py::return_value_policy::reference_internal)
        .def("states", &Interpreter::states, py::return_value_policy::reference_internal)
        .def("state", &Interpreter::state, py::return_value_policy::reference_internal)
        ;
}

} // namespace Reaktoro
