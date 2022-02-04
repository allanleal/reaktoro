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

#pragma once

// Reaktoro includes
#include <Reaktoro/Common/Real.hpp>

namespace Reaktoro {

// Forward declarations
struct SpeciesElectroState;
struct SpeciesThermoState;
struct SupcrtblParamsAqueousSoluteHKF;
struct SupcrtblParamsAqueousSolventHKF;
struct SupcrtblParamsFluidHollandPowell;
struct SupcrtblParamsMineralHollandPowell;
struct SupcrtblParamsMineralHollandPowell;
struct WaterElectroState;
struct WaterThermoState;

/// Calculate the standard thermodynamic properties of a aqueous solvent water using HKF model.
auto supcrtblStandardThermoPropsSolventHKF(real T, real P, const SupcrtblParamsAqueousSolventHKF& params, const WaterThermoState& wts) -> SpeciesThermoState;

/// Calculate the standard thermodynamic properties of a aqueous solutes using HKF model.
auto supcrtblStandardThermoPropsSoluteHKF(real T, real P, const SupcrtblParamsAqueousSoluteHKF& params, const SpeciesElectroState& aes, const WaterElectroState& wes) -> SpeciesThermoState;

/// Calculate the standard thermodynamic properties of a gas/liquid using Holland and Powell (2011) model.
auto supcrtblStandardThermoPropsFluidHollandPowell(real T, real P, const SupcrtblParamsFluidHollandPowell& params) -> SpeciesThermoState;

/// Calculate the standard thermodynamic properties of a mineral without phase transition using Holland and Powell (2011) model.
auto supcrtblStandardThermoPropsMineralHollandPowell(real T, real P, const SupcrtblParamsMineralHollandPowell& params) -> SpeciesThermoState;

// /// Calculate the standard thermodynamic properties of a mineral with phase transition using Holland and Powell (2011) model and Landau theory.
// auto supcrtblStandardThermoPropsMineralHollandPowellLandau(real T, real P, const SupcrtblParamsMineralHollandPowellLandau& params) -> SpeciesThermoState;

} // namespace Reaktoro
