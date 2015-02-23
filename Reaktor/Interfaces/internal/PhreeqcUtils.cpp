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

#include "PhreeqcUtils.hpp"

// Phreeqc includes
#define protected public
#include <Reaktor/phreeqc/Phreeqc.h>
#include <Reaktor/phreeqc/GasPhase.h>

namespace Reaktor {

const double gram_to_kilogram = 1e-3;
const double kilogram_to_gram = 1e+3;
const double pascal_to_atm = 9.86923267e-6;
const double atm_to_pascal = 1/pascal_to_atm;

auto loadDatabase(Phreeqc& phreeqc, std::string filename) -> void
{
    std::istream* db_cookie = new std::ifstream(filename, std::ios_base::in);
    int errors = phreeqc.do_initialize();
    if(errors != 0) throw std::runtime_error("Error after call to `do_initialize` from Phreeqc instance.");
    phreeqc.Get_phrq_io()->push_istream(db_cookie);
    errors = phreeqc.read_database();
    phreeqc.Get_phrq_io()->clear_istream();
    phreeqc.Get_phrq_io()->Set_error_ostream(&std::cout);
    if(errors != 0) throw std::runtime_error("Error loading the database file in the Phreeqc instance.");
}

auto loadScript(Phreeqc& phreeqc, std::string filename) -> void
{
    std::istream* in_cookie = new std::ifstream(filename, std::ios_base::in);
    phreeqc.Get_phrq_io()->push_istream(in_cookie);
    int errors = phreeqc.run_simulations();
    phreeqc.Get_phrq_io()->clear_istream();
    if(errors != 0) throw std::runtime_error("Error when running the simulation with the Phreeqc instance.");
}

auto findElement(Phreeqc& phreeqc, std::string name) -> element*
{
    for(int i = 0; i < phreeqc.count_elements; ++i)
        if(phreeqc.elements[i]->name == name)
            return phreeqc.elements[i];
    return nullptr;
}

auto findSpecies(Phreeqc& phreeqc, std::string name) -> species*
{
    return phreeqc.s_search(name.c_str());
}

auto findPhase(Phreeqc& phreeqc, std::string name) -> phase*
{
    for(int i = 0; i < phreeqc.count_phases; ++i)
        if(phreeqc.phases[i]->name == name)
            return phreeqc.phases[i];
    return nullptr;
}

auto getElementsInSpecies(const species* s) -> std::map<element*, double>
{
    std::map<element*, double> elements;
    for(auto iter = s->next_elt; iter->elt != NULL; iter++)
        elements.emplace(iter->elt, iter->coef);
    return elements;
}

auto getElementsInPhase(const phase* p) -> std::map<element*, double>
{
    std::map<element*, double> elements;
    for(auto iter = p->next_elt; iter->elt != NULL; iter++)
        elements.emplace(iter->elt, iter->coef);
    return elements;
}

// Return the reaction equation of a species defined by the names of
// the species and their stoichiometries.
// An empty equation is returned in case the given species is a primary species.
auto getReactionEquation(const species* s) -> std::map<std::string, double>
{
    std::map<std::string, double> equation;

    // Check if there is any reaction defined by this species
    if(s->rxn_x)
    {
        // Iterate over all reactants
        for(auto iter = s->rxn_x->token; iter->name != NULL; iter++)
            equation.emplace(iter->name, iter->coef);

        // Check if the reaction is defined by only one species
        if(equation.size() <= 1)
            equation.clear();
    }

    return equation;
}

// Return the reaction equation of a phase defined by the names of
// the species and their stoichiometries.
auto getReactionEquation(const phase* p) -> std::map<std::string, double>
{
    std::map<std::string, double> equation;
    for(auto iter = p->rxn_x->token; iter->name != NULL; iter++)
        equation.emplace(iter->name, iter->coef);
    return equation;
}

auto numElementAtomsInSpecies(std::string element, const species* s) -> double
{
    for(auto x : getElementsInSpecies(s))
        if(x.first->name == element)
            return x.second;
    return 0.0;
}

auto numElementAtomsInPhase(std::string element, const phase* p) -> double
{
    for(auto x : getElementsInPhase(p))
        if(x.first->name == element)
            return x.second;
    return 0.0;
}

auto collectAqueousSpecies(Phreeqc& phreeqc) -> std::vector<species*>
{
    std::set<species*> aqueous_species;
    for(int i = 0; i < phreeqc.count_s; ++i)
    {
        // Check if the species is considered in the model
        if(phreeqc.s[i]->in)
        {
            aqueous_species.insert(phreeqc.s[i]);

            // Add the reactants in the reaction defined by this species
            for(auto pair : getReactionEquation(phreeqc.s[i]))
                aqueous_species.insert(findSpecies(phreeqc, pair.first));
        }
    }

    return {aqueous_species.begin(), aqueous_species.end()};
}

auto collectSecondarySpecies(Phreeqc& phreeqc) -> std::vector<species*>
{
    std::vector<species*> secondary_species;
    for(species* s : collectAqueousSpecies(phreeqc))
        if(getReactionEquation(s).size())
            secondary_species.push_back(s);

    return secondary_species;
}

auto collectGaseousSpecies(Phreeqc& phreeqc) -> std::vector<phase*>
{
    std::vector<phase*> gaseous_species;
    for(const auto& pair : phreeqc.Rxn_gas_phase_map)
    {
        const cxxGasPhase& gas_phase = pair.second;
        for(const cxxGasComp& component : gas_phase.Get_gas_comps())
            gaseous_species.push_back(findPhase(phreeqc, component.Get_phase_name()));
    }
    return gaseous_species;
}

auto collectMineralSpecies(Phreeqc& phreeqc) -> std::vector<phase*>
{
    auto is_mineral = [](phase* p)
    {
        std::string name(p->name);
        const bool is_in = p->in;
        const bool is_solid = p->type == SOLID;
        const bool is_not_gas = name.find("(g)") > name.size();
        return is_in and is_solid and is_not_gas;
    };

    std::vector<phase*> pure_minerals;
    for(int i = 0; i < phreeqc.count_phases; ++i)
        if(is_mineral(phreeqc.phases[i]))
            pure_minerals.push_back(phreeqc.phases[i]);
    return pure_minerals;
}

auto index(std::string name, const std::vector<species*>& pointers) -> unsigned
{
    auto compare = [=](species* entry) { return entry->name == name; };
    return std::find_if(pointers.begin(), pointers.end(), compare) - pointers.begin();
}

auto index(std::string name, const std::vector<phase*>& pointers) -> unsigned
{
    auto compare = [=](phase* entry) { return entry->name == name; };
    return std::find_if(pointers.begin(), pointers.end(), compare) - pointers.begin();
}

} // namespace Reaktor
