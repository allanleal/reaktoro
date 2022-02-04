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
#include <Reaktoro/Common/StringList.hpp>
#include <Reaktoro/Core/ChemicalSystem.hpp>
#include <Reaktoro/Extensions/Interfaces/Phreeqc.hpp>
#include <Reaktoro/Extensions/Interfaces/PhreeqcEditor.hpp>

namespace Reaktoro {

auto exportPhreeqcEditor(py::module& m) -> void
{
    py::class_<PhreeqcEditor>(m, "PhreeqcEditor")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def("setDatabase", &PhreeqcEditor::setDatabase)
        .def("setAqueousPhase", &PhreeqcEditor::setAqueousPhase)
        .def("setGaseousPhase", &PhreeqcEditor::setGaseousPhase)
        .def("setMineralPhases", &PhreeqcEditor::setMineralPhases)
        ;
}

} // namespace Reaktoro
