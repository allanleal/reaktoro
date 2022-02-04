// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2018 Allan Leal
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
#include <Reaktoro/Thermodynamics/Common/StateOfMatter.hpp>

namespace Reaktoro {

// Forward declarations
struct WaterThermoState;
struct WaterHelmholtzState;

/// Calculate the thermodynamic state of water using the Haar--Gallagher--Kell (1984) equation of state.
/// **References:**
/// - Haar, L., Gallagher, J. S., Kell, G. S. (1984). NBS/NRC Steam Tables: Thermodynamic and
///   Transport Properties and Computer Program for Vapor and Liquid States of Water in SI Units.
///   New York: Hemisphere Publishing Corporation.
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @return The thermodynamic state of water
/// @see WaterThermoState
auto waterThermoStateHGK(Temperature T, Pressure P, StateOfMatter stateofmatter) -> WaterThermoState;

/// Calculate the thermodynamic state of water using the Wagner and Pruss (1995) equation of state.
/// **References:**
/// - Wagner, W., Pruss, A. (1999). The IAPWS Formulation 1995 for the Thermodynamic Properties of
///   Ordinary Water Substance for General and Scientific Use. Journal of Physical and Chemical
///   Reference Data, 31(2), 387. [doi](http://doi.org/10.1063/1.1461829)
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @return The thermodynamic state of water
/// @see WaterThermoState
auto waterThermoStateWagnerPruss(Temperature T, Pressure P, StateOfMatter stateofmatter) -> WaterThermoState;

/// Calculate the thermodynamic state of water.
/// This is a general method that uses the Helmholtz free energy state
/// of water, as an instance of WaterHelmholtzState, to completely
/// resolve its thermodynamic state.
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @param whs The Helmholtz free energy state of water
/// @return The thermodynamic state of water
/// @see WaterHelmholtzState, WaterThermoState
auto waterThermoState(Temperature T, Pressure P, const WaterHelmholtzState& whs) -> WaterThermoState;

} // namespace Reaktoro
