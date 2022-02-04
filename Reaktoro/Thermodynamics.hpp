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

#pragma once

#include <Reaktoro/Thermodynamics/Activity/AqueousActivityModel.hpp>
#include <Reaktoro/Thermodynamics/Activity/AqueousActivityModelDrummondCO2.hpp>
#include <Reaktoro/Thermodynamics/Activity/AqueousActivityModelDuanSunCO2.hpp>
#include <Reaktoro/Thermodynamics/Activity/AqueousActivityModelRumpfCO2.hpp>
#include <Reaktoro/Thermodynamics/Activity/AqueousActivityModelSetschenow.hpp>
#include <Reaktoro/Thermodynamics/Core/ChemicalEditor.hpp>
#include <Reaktoro/Thermodynamics/Core/Thermo.hpp>
#include <Reaktoro/Thermodynamics/EOS/CubicEOS.hpp>
#include <Reaktoro/Thermodynamics/Mixtures/AqueousMixture.hpp>
#include <Reaktoro/Thermodynamics/Mixtures/GeneralMixture.hpp>
#include <Reaktoro/Thermodynamics/Models/AqueousChemicalModelDebyeHuckel.hpp>
#include <Reaktoro/Thermodynamics/Models/AqueousChemicalModelHKF.hpp>
#include <Reaktoro/Thermodynamics/Models/AqueousChemicalModelIdeal.hpp>
#include <Reaktoro/Thermodynamics/Models/AqueousChemicalModelPitzerHMW.hpp>
#include <Reaktoro/Thermodynamics/Models/GaseousChemicalModelCubicEOS.hpp>
#include <Reaktoro/Thermodynamics/Models/GaseousChemicalModelIdeal.hpp>
#include <Reaktoro/Thermodynamics/Models/GaseousChemicalModelSpycherPruessEnnis.hpp>
#include <Reaktoro/Thermodynamics/Models/GaseousChemicalModelSpycherReed.hpp>
#include <Reaktoro/Thermodynamics/Models/MineralChemicalModelIdeal.hpp>
#include <Reaktoro/Thermodynamics/Models/MineralChemicalModelRedlichKister.hpp>
#include <Reaktoro/Thermodynamics/Models/PhaseChemicalModel.hpp>
#include <Reaktoro/Thermodynamics/Models/PhaseThermoModel.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesElectroState.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesElectroStateHKF.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesThermoState.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesThermoStateHKF.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesElectroState.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesElectroStateHKF.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesThermoState.hpp>
#include <Reaktoro/Thermodynamics/Models/SpeciesThermoStateHKF.hpp>
#include <Reaktoro/Thermodynamics/Phases/AqueousPhase.hpp>
#include <Reaktoro/Thermodynamics/Phases/GaseousPhase.hpp>
#include <Reaktoro/Thermodynamics/Phases/MineralPhase.hpp>
#include <Reaktoro/Extensions/Geochemistry/MineralCatalyst.hpp>
#include <Reaktoro/Extensions/Geochemistry/MineralMechanism.hpp>
#include <Reaktoro/Extensions/Geochemistry/MineralReaction.hpp>
#include <Reaktoro/Extensions/Water/WaterConstants.hpp>
#include <Reaktoro/Extensions/Water/WaterElectroState.hpp>
#include <Reaktoro/Extensions/Water/WaterElectroStateJohnsonNorton.hpp>
#include <Reaktoro/Extensions/Water/WaterHelmholtzState.hpp>
#include <Reaktoro/Extensions/Water/WaterHelmholtzStateHGK.hpp>
#include <Reaktoro/Extensions/Water/WaterHelmholtzStateWagnerPruss.hpp>
#include <Reaktoro/Extensions/Water/WaterThermoState.hpp>
#include <Reaktoro/Extensions/Water/WaterThermoStateUtils.hpp>
#include <Reaktoro/Extensions/Water/WaterUtils.hpp>
