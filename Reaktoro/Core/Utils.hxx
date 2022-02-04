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

// C++ includes
namespace Reaktoro {

template<typename NamedValues>
auto names(const NamedValues& values) -> std::vector<std::string>
{
    std::vector<std::string> names;
    names.reserve(values.size());
    for(const auto& entry : values)
        names.push_back(entry.name());
    return names;
}

template<typename SpeciesValues>
auto charges(const SpeciesValues& species) -> VectorXr
{
    VectorXr charges(species.size());
    for(unsigned i = 0; i < species.size(); ++i)
        charges[i] = species[i].charge();
    return charges;
}

template<typename SpeciesValues>
auto molarMasses(const SpeciesValues& species) -> VectorXr
{
    VectorXr molar_masses(species.size());
    for(unsigned i = 0; i < species.size(); ++i)
        molar_masses[i] = species[i].molarMass();
    return molar_masses;
}

} // namespace Reaktoro
