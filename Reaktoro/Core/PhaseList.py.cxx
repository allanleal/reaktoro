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
#include <Reaktoro/Core/PhaseList.hpp>
#include <Reaktoro/Core/Species.hpp>
using namespace Reaktoro;

void exportPhaseList(py::module& m)
{
    auto __getitem__ = [](const PhaseList& self, Index i)
    {
        return self[i];
    };

    py::class_<PhaseList>(m, "PhaseList")
        .def(py::init<>())
        .def(py::init<const Vec<Phase>&>())
        .def("append", &PhaseList::append)
        .def("data", &PhaseList::data)
        .def("size", &PhaseList::size)
        .def("find", &PhaseList::find)
        .def("findWithName", &PhaseList::findWithName)
        .def("findWithSpecies", py::overload_cast<Index>(&PhaseList::findWithSpecies, py::const_))
        .def("findWithSpecies", py::overload_cast<const String&>(&PhaseList::findWithSpecies, py::const_))
        .def("findWithAggregateState", &PhaseList::findWithAggregateState)
        .def("findWithStateOfMatter", &PhaseList::findWithStateOfMatter)
        .def("index", &PhaseList::index)
        .def("indexWithName", &PhaseList::indexWithName)
        .def("indexWithSpecies", py::overload_cast<Index>(&PhaseList::indexWithSpecies, py::const_))
        .def("indexWithSpecies", py::overload_cast<const String&>(&PhaseList::indexWithSpecies, py::const_))
        .def("indexWithAggregateState", &PhaseList::indexWithAggregateState)
        .def("indexWithStateOfMatter", &PhaseList::indexWithStateOfMatter)
        .def("withNames", &PhaseList::withNames)
        .def("withStateOfMatter", &PhaseList::withStateOfMatter)
        .def("withAggregateState", &PhaseList::withAggregateState)
        .def("numSpeciesUntilPhase", &PhaseList::numSpeciesUntilPhase)
        .def("__getitem__", __getitem__, py::return_value_policy::reference_internal)
        ;
}
