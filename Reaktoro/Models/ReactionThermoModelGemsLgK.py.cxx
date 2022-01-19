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

// pybind11 includes
#include <Reaktoro/pybind11.hxx>

// Reaktoro includes
#include <Reaktoro/Models/ReactionThermoModelGemsLgK.hpp>
using namespace Reaktoro;

void exportReactionThermoModelGemsLgK(py::module& m)
{
    py::class_<ReactionThermoModelParamsGemsLgK>(m, "ReactionThermoModelParamsGemsLgK")
        .def_readwrite("A0", &ReactionThermoModelParamsGemsLgK::A0)
        .def_readwrite("A1", &ReactionThermoModelParamsGemsLgK::A1)
        .def_readwrite("A2", &ReactionThermoModelParamsGemsLgK::A2)
        .def_readwrite("A3", &ReactionThermoModelParamsGemsLgK::A3)
        .def_readwrite("A4", &ReactionThermoModelParamsGemsLgK::A4)
        .def_readwrite("A5", &ReactionThermoModelParamsGemsLgK::A5)
        .def_readwrite("A6", &ReactionThermoModelParamsGemsLgK::A6)
        .def_readwrite("Pr", &ReactionThermoModelParamsGemsLgK::Pr)
        ;

    m.def("ReactionThermoModelGemsLgK", ReactionThermoModelGemsLgK);
}
