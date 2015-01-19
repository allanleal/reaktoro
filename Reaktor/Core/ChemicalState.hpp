// Reaktor is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <memory>
#include <string>

// Reaktor includes
#include <Reaktor/Common/Matrix.hpp>

namespace Reaktor {

// Forward declarations
class ChemicalSystem;
class Partition;

/// Provides a computational representation of the state of a multiphase chemical system.
/// The chemical state of a multiphase system is defined by its temperature @f$(T)@f$,
/// pressure @f$(P)@f$, and molar composition @f$(\mathbf{n})@f$.
///
/// **Usage**
///
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// // Create a ChemicalState instance, where system is a ChemicalSystem instance
/// ChemicalState state(system);
///
/// // Set the temperature and pressure states
/// state.setTemperature(60.0, "celsius");
/// state.setPressure(  180.0, "bar");
///
/// // Set the amount of some species
/// state.set( "H2O(l)",  1.0, "kg");
/// state.set(    "Na+",  1.0, "mol");
/// state.set(    "Cl-",  1.0, "mol");
/// state.set("CO2(aq)",  0.5, "mol");
/// state.set("Calcite", 10.0, "g");
///
/// // Output the chemical state instance
/// std::cout << state << std::endl;
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// @see ChemicalSystem
/// @ingroup Core
class ChemicalState
{
public:
    /// Construct a ChemicalState instance
    /// @param system The chemical system instance
    explicit ChemicalState(const ChemicalSystem& system);

    /// Construct a ChemicalState instance with given partition
    /// @param system The chemical system instance
    /// @param partition The partition of the chemical system
    ChemicalState(const ChemicalSystem& system, const Partition& partition);

    /// Construct a copy of a ChemicalState instance
    ChemicalState(const ChemicalState& other);

    /// Destroy the instance
    virtual ~ChemicalState();

    /// Assign a ChemicalState instance to this instance
    auto operator=(ChemicalState other) -> ChemicalState&;

    /// Set the temperature of the chemical state (in units of K)
    auto setTemperature(double val) const -> void;

    /// Set the temperature of the chemical state with given units
    auto setTemperature(double val, std::string units) const -> void;

    /// Set the pressure of the chemical state (in units of Pa)
    auto setPressure(double val) const -> void;

    /// Set the pressure of the chemical state with given units
    auto setPressure(double val, std::string units) const -> void;

    /// Set the amount of a species
    /// @param index The index of the species
    /// @param amount The amount of the species (in units of mol)
    auto set(unsigned index, double amount) -> void;

    /// Set the amount of a species
    /// @param species The name of the species
    /// @param amount The amount of the species (in units of mol)
    auto set(std::string species, double amount) -> void;

    /// Set the amount of a species
    /// @param index The index of the species
    /// @param amount The amount of the species
    /// @param units The units of the amount (must be convertible to either mol or gram)
    auto set(unsigned index, double amount, std::string units) -> void;

    /// Set the amount of a species
    /// @param species The name of the species
    /// @param amount The amount of the species
    /// @param units The units of the amount (must be convertible to either mol or gram)
    auto set(std::string species, double amount, std::string units) -> void;

    /// Set the equilibrium state of the chemical system
    /// @param ne The amounts of equilibrium species (in units of mol)
    /// @param ye The multipliers with respect to the balance constraints (in units of J/mol)
    /// @param ze The multipliers with respect to the bound constraints (in units of J/mol)
    auto setEquilibrium(const Vector& ne, const Vector& ye, const Vector& ze) -> void;

    /// Set the kinetic state of the chemical system
    /// @param nk The amounts of kinetic species (in units of mol)
    auto setKinetic(const Vector& nk) -> void;

    /// Get the temperature of the chemical state (in units of K)
    auto temperature() const -> double;

    /// Get the pressure of the chemical state (in units of Pa)
    auto pressure() const -> double;

    /// Get the molar amounts of the chemical species (in units of mol)
    auto n() const -> const Vector&;

    /// Get the molar amounts of the equilibrium species (in units of mol)
    auto ne() const -> MatrixViewRows<Vector>;

    /// Get the molar amounts of the kinetic species (in units of mol)
    auto nk() const -> MatrixViewRows<Vector>;

    /// Get the molar amounts of the chemical elements (in units of mol)
    auto b() const -> Vector;

    /// Get the molar amounts of the equilibrium elements (in units of mol)
    auto be() const -> Vector;

    /// Get the molar amounts of the kinetic elements (in units of mol)
    auto bk() const -> Vector;

    /// Get the multipliers with respect to the balance constraints (in units of J/mol)
    auto ye() const -> const Vector&;

    /// Get the multipliers with respect to the bound constraints (in units of J/mol)
    auto ze() const -> const Vector&;

    /// Get the molar amount of a chemical species (in units of mol)
    /// @param index The index of the species
    auto n(unsigned index) const -> double;

    /// Get the molar amount of a chemical species (in units of mol)
    /// @param name The name of the species
    auto n(std::string name) const -> double;

    /// Get the molar amounts of the species in a phase (in units of mol)
    /// @param index The index of the phase
    /// @return The molar amounts of the species in the phase
    auto nphase(unsigned index) const -> Vector;

    /// Get the molar amounts of the species in a phase (in units of mol)
    /// @param name The name of the phase
    /// @return The molar amounts of the species in the phase
    auto nphase(std::string name) const -> Vector;

    /// Get the molar amount of an element (in units of mol)
    /// @param index The index of the element
    auto b(unsigned index) const -> double;

    /// Get the molar amount of an element (in units of mol)
    /// @param name The name of the element
    auto b(std::string name) const -> double;

    /// Get the molar amount of an element in a given phase (in units of mol)
    /// @param ielement The index of the element
    /// @param iphase The index of the phase
    auto b(unsigned ielement, unsigned iphase) const -> double;

    /// Get the molar amount of an element in a given phase (in units of mol)
    /// @param element The name of the element
    /// @param phase The name of the phase
    auto b(std::string element, std::string phase) const -> double;

    /// Get the molar amount of an element in the equilibrium partition (in units of mol)
    /// @param index The index of the element
    auto be(unsigned index) const -> double;

    /// Get the molar amount of an element in the equilibrium partition (in units of mol)
    /// @param name The name of the element
    auto be(std::string name) const -> double;

    /// Get the molar amount of an element in the kinetic partition (in units of mol)
    /// @param index The index of the element
    auto bk(unsigned index) const -> double;

    /// Get the molar amount of an element in the kinetic partition (in units of mol)
    /// @param name The name of the element
    auto bk(std::string name) const -> double;

    /// Get the amount of a chemical species with given units
    /// @param index The index of the species
    /// @param units The units of the species amount
    auto amount(unsigned index, std::string units) const -> double;

    /// Get the amount of a chemical species with given units
    /// @param name The name of the species
    /// @param units The units of the species amount
    auto amount(std::string name, std::string units) const -> double;

    /// Get the chemical system instance
    auto system() const -> const ChemicalSystem&;

    /// Get the partition of the chemical system
    auto partition() const -> const Partition&;

private:
    struct Impl;

    std::unique_ptr<Impl> pimpl;
};

/// Outputs a @ref ChemicalState instance
auto operator<<(std::ostream& out, const ChemicalState& state) -> std::ostream&;

} // namespace Reaktor
