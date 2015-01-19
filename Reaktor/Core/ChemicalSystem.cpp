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

#include "ChemicalSystem.hpp"

namespace Reaktor {

struct ChemicalSystem::Impl
{
    /// The data used to construct the chemical system
    ChemicalSystemData data;

    /// The list of species in the chemical system
    std::vector<Species> species;

    /// The list of elements in the chemical system
    std::vector<Element> elements;

    Impl()
    {}

    Impl(const ChemicalSystemData& data)
    : data(data),
      species(collectSpecies(data.phases)),
      elements(elements(species))
    {
    }
};

ChemicalSystem::ChemicalSystem()
: pimpl(new Impl())
{}

ChemicalSystem::ChemicalSystem(const ChemicalSystemData& data)
: pimpl(new Impl(data))
{}

auto ChemicalSystem::elements() const -> const std::vector<Element>&
{
    return pimpl->elements;
}

auto ChemicalSystem::species() const -> const std::vector<Species>&
{
    return pimpl->species;
}

auto ChemicalSystem::phases() const -> const std::vector<Phase>&
{
    return pimpl->data.phases;
}

auto ChemicalSystem::element(Index index) const -> const Element&
{
    return elements()[index];
}

auto ChemicalSystem::element(std::string name) const -> const Element&
{
    return element(indexElement(name));
}

auto ChemicalSystem::species(Index index) const -> const Species&
{
    return species()[index];
}

auto ChemicalSystem::species(std::string name) const -> const Species&
{
    return species(indexSpecies(name));
}

auto ChemicalSystem::phase(Index index) const -> const Phase&
{
    return phases()[index];
}

auto ChemicalSystem::phase(std::string name) const -> const Phase&
{
    return phase(indexPhase(name));
}

auto ChemicalSystem::indexElement(std::string name) const -> Index
{
    return index(name, elements());
}

auto ChemicalSystem::indexSpecies(std::string name) const -> Index
{
    return index(name, species());
}

auto ChemicalSystem::indexPhase(std::string name) const -> Index
{
    return index(name, phases());
}

auto ChemicalSystem::offset(Index iphase) const -> unsigned
{
    unsigned counter = 0;
    for(unsigned i = 0; i < iphase-1; ++i)
        counter += phase(i).species().size();
    return counter;
}

auto ChemicalSystem::gibbsEnergies(double T, double P) const -> ThermoVector
{
    return pimpl->data.gibbs_energies(T, P);
}

auto ChemicalSystem::enthalpies(double T, double P) const -> ThermoVector
{
    return pimpl->data.enthalpies(T, P);
}

auto ChemicalSystem::helmholtzEnergies(double T, double P) const -> ThermoVector
{
    return pimpl->data.helmholtz_energies(T, P);
}

auto ChemicalSystem::entropies(double T, double P) const -> ThermoVector
{
    return pimpl->data.entropies(T, P);
}

auto ChemicalSystem::volumes(double T, double P) const -> ThermoVector
{
    return pimpl->data.volumes(T, P);
}

auto ChemicalSystem::internalEnergies(double T, double P) const -> ThermoVector
{
    return pimpl->data.internal_energies(T, P);
}

auto ChemicalSystem::heatCapacitiesCp(double T, double P) const -> ThermoVector
{
    return pimpl->data.heat_capacities_cp(T, P);
}

auto ChemicalSystem::concentrations(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.concentrations(T, P, n);
}

auto ChemicalSystem::lnActivityCoefficients(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.ln_activity_coefficients(T, P, n);
}

auto ChemicalSystem::lnActivities(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.ln_activities(T, P, n);
}

auto ChemicalSystem::chemicalPotentials(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.chemical_potentials(T, P, n);
}

auto ChemicalSystem::densities(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.densities(T, P, n);
}

auto formulaMatrix(const ChemicalSystem& system) -> Matrix
{
    const auto& elements = system.elements();
    const auto& species = system.species();
    const auto& num_elements = elements.size();
    const auto& num_species = species.size();
    Matrix W(num_elements, num_species);
    for(unsigned i = 0; i < num_species; ++i)
        for(unsigned j = 0; j < num_elements; ++j)
            W(j, i) = atoms(elements[j], species[i]);
    return W;
}

auto balanceMatrix(const ChemicalSystem& system) -> Matrix
{
    const unsigned num_elements = system.elements().size();
    const unsigned num_species = system.species().size();
    const Matrix W = formulaMatrix(system);
    const Vector z = charges(system.species());
    Matrix A(num_elements + 1, num_species);
    A << W, z.transpose();
    return A;
}

} // namespace Reaktor
