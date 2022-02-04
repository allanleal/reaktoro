// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2021 Allan Leal
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
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
namespace py = pybind11;

// Reaktoro includes
#include <Reaktoro/Core/ChemicalSystem.hpp>
using namespace Reaktoro;

PYBIND11_MAKE_OPAQUE(ArrayXr);
PYBIND11_MAKE_OPAQUE(ArrayXrRef);
PYBIND11_MAKE_OPAQUE(ArrayXrConstRef);
PYBIND11_MAKE_OPAQUE(VectorXr);
PYBIND11_MAKE_OPAQUE(VectorXrRef);
PYBIND11_MAKE_OPAQUE(VectorXrConstRef);

void exportChemicalSystem(py::module& m)
{
    py::class_<ChemicalSystem>(m, "ChemicalSystem")
        .def(py::init<>())
        .def(py::init<const Phases&>())
        .def(py::init<const Database&, const Vec<Phase>&>())
        .def("database", &ChemicalSystem::database)
        .def("element", &ChemicalSystem::element)
        .def("elements", &ChemicalSystem::elements)
        .def("species", py::overload_cast<>(&ChemicalSystem::species, py::const_), py::return_value_policy::reference_internal)
        .def("species", py::overload_cast<Index>(&ChemicalSystem::species, py::const_), py::return_value_policy::reference_internal)
        .def("phase", &ChemicalSystem::phase)
        .def("phases", &ChemicalSystem::phases)
        .def("formulaMatrix", &ChemicalSystem::formulaMatrix)
        ;
}
