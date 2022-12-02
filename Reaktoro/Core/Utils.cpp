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

#include "Utils.hpp"

// Reaktoro includes
#include <Reaktoro/Common/Algorithms.hpp>
#include <Reaktoro/Common/Exception.hpp>
#include <Reaktoro/Common/Units.hpp>
#include <Reaktoro/Core/ChemicalFormula.hpp>
#include <Reaktoro/Core/ChemicalSystem.hpp>
#include <Reaktoro/Core/ElementList.hpp>
#include <Reaktoro/Core/Phase.hpp>
#include <Reaktoro/Core/PhaseList.hpp>
#include <Reaktoro/Core/Reaction.hpp>
#include <Reaktoro/Core/ReactionList.hpp>
#include <Reaktoro/Core/SpeciesList.hpp>
#include <Reaktoro/Core/Surface.hpp>
#include <Reaktoro/Core/SurfaceList.hpp>

namespace Reaktoro {
namespace detail {

//=================================================================================================
// AUXILIARY METHODS RELATED TO SPECIES AMOUNTS
//=================================================================================================

auto molarMasses(SpeciesList const& species) -> ArrayXd
{
    ArrayXd molar_masses(species.size());
    transform(species, molar_masses, [](auto&& s) { return s.molarMass(); });
    return molar_masses;
}

auto computeSpeciesAmount(ChemicalSystem const& system, Index ispecies, real value, Chars unit) -> real
{
    if(strcmp(unit, "mol") == 0)
        return value;

    if(units::convertible(unit, "kg"))
    {
        const auto molarmass = system.species(ispecies).molarMass(); // in kg/mol
        value = units::convert(value, unit, "kg"); // from some mass unit to kg
        return value / molarmass; // from kg to mol
    }
    else if(units::convertible(unit, "mol"))
        return units::convert(value, unit, "mol"); // from some amount unit to mol
    else errorif("Provided unit `", unit, "` should be convertible to mol or kg.");

    return {};
}

//=================================================================================================
// AUXILIARY INDEX RESOLUTION METHODS FOR ELEMENTS
//=================================================================================================

auto resolveElementIndexAux(ElementList const& elementlist, Index index) -> Index { return index; }
auto resolveElementIndexAux(ElementList const& elementlist, int index) -> Index { return index; }
auto resolveElementIndexAux(ElementList const& elementlist, String const& symbol) -> Index { return elementlist.find(symbol); }

auto resolveElementIndex(ElementList const& elementlist, StringOrIndex const& element) -> Index
{
    return std::visit([&](auto&& arg) { return resolveElementIndexAux(elementlist, arg); }, element);
}

auto resolveElementIndexOrRaiseError(ElementList const& elementlist, StringOrIndex const& element, String const& errormsg) -> Index
{
    const auto idx = resolveElementIndex(elementlist, element);
    errorifnot(idx < elementlist.size(), errormsg);
    return idx;
}

auto resolveElementIndex(ChemicalSystem const& system, StringOrIndex const& element) -> Index { return resolveElementIndex(system.elements(), element); }
auto resolveElementIndex(Phase const& phase, StringOrIndex const& element) -> Index { return resolveElementIndex(phase.elements(), element); }
auto resolveElementIndexOrRaiseError(ChemicalSystem const& system, StringOrIndex const& element, String const& errormsg) -> Index { return resolveElementIndex(system.elements(), element); }
auto resolveElementIndexOrRaiseError(Phase const& phase, StringOrIndex const& element, String const& errormsg) -> Index { return resolveElementIndex(phase.elements(), element); }

//=================================================================================================
// AUXILIARY INDEX RESOLUTION METHODS FOR SPECIES
//=================================================================================================

auto resolveSpeciesIndexAux(SpeciesList const& specieslist, Index index) -> Index { return index; }
auto resolveSpeciesIndexAux(SpeciesList const& specieslist, int index) -> Index { return index; }
auto resolveSpeciesIndexAux(SpeciesList const& specieslist, String const& name) -> Index { return specieslist.find(name); }

auto resolveSpeciesIndex(SpeciesList const& specieslist, StringOrIndex const& species) -> Index
{
    return std::visit([&](auto&& arg) { return resolveSpeciesIndexAux(specieslist, arg); }, species);
}

auto resolveSpeciesIndexOrRaiseError(SpeciesList const& specieslist, StringOrIndex const& species, String const& errormsg) -> Index
{
    const auto idx = resolveSpeciesIndex(specieslist, species);
    errorifnot(idx < specieslist.size(), errormsg);
    return idx;
}

auto resolveSpeciesIndex(ChemicalSystem const& system, StringOrIndex const& species) -> Index { return resolveSpeciesIndex(system.species(), species); }
auto resolveSpeciesIndex(Phase const& phase, StringOrIndex const& species) -> Index { return resolveSpeciesIndex(phase.species(), species); }
auto resolveSpeciesIndexOrRaiseError(ChemicalSystem const& system, StringOrIndex const& species, String const& errormsg) -> Index { return resolveSpeciesIndex(system.species(), species); }
auto resolveSpeciesIndexOrRaiseError(Phase const& phase, StringOrIndex const& species, String const& errormsg) -> Index { return resolveSpeciesIndex(phase.species(), species); }

//=================================================================================================
// AUXILIARY INDEX RESOLUTION METHODS FOR PHASES
//=================================================================================================

auto resolvePhaseIndexAux(PhaseList const& phaselist, Index index) -> Index { return index; }
auto resolvePhaseIndexAux(PhaseList const& phaselist, int index) -> Index { return index; }
auto resolvePhaseIndexAux(PhaseList const& phaselist, String const& name) -> Index { return phaselist.find(name); }

auto resolvePhaseIndex(PhaseList const& phaselist, StringOrIndex const& phase) -> Index
{
    return std::visit([&](auto&& arg) { return resolvePhaseIndexAux(phaselist, arg); }, phase);
}

auto resolvePhaseIndexOrRaiseError(PhaseList const& phaselist, StringOrIndex const& phase, String const& errormsg) -> Index
{
    const auto idx = resolvePhaseIndex(phaselist, phase);
    errorifnot(idx < phaselist.size(), errormsg);
    return idx;
}

auto resolvePhaseIndex(ChemicalSystem const& system, StringOrIndex const& phase) -> Index { return resolvePhaseIndex(system.phases(), phase); }
auto resolvePhaseIndexOrRaiseError(ChemicalSystem const& system, StringOrIndex const& phase, String const& errormsg) -> Index { return resolvePhaseIndex(system.phases(), phase); }

//=================================================================================================
// AUXILIARY INDEX RESOLUTION METHODS FOR REACTIONS
//=================================================================================================

auto resolveReactionIndexAux(ReactionList const& reactionlist, Index index) -> Index { return index; }
auto resolveReactionIndexAux(ReactionList const& reactionlist, int index) -> Index { return index; }
auto resolveReactionIndexAux(ReactionList const& reactionlist, String const& name) -> Index { return reactionlist.find(name); }

auto resolveReactionIndex(ReactionList const& reactionlist, StringOrIndex const& reaction) -> Index
{
    return std::visit([&](auto&& arg) { return resolveReactionIndexAux(reactionlist, arg); }, reaction);
}

auto resolveReactionIndexOrRaiseError(ReactionList const& reactionlist, StringOrIndex const& reaction, String const& errormsg) -> Index
{
    const auto idx = resolveReactionIndex(reactionlist, reaction);
    errorifnot(idx < reactionlist.size(), errormsg);
    return idx;
}

auto resolveReactionIndex(ChemicalSystem const& system, StringOrIndex const& reaction) -> Index { return resolveReactionIndex(system.reactions(), reaction); }
auto resolveReactionIndexOrRaiseError(ChemicalSystem const& system, StringOrIndex const& reaction, String const& errormsg) -> Index { return resolveReactionIndex(system.reactions(), reaction); }

//=================================================================================================
// AUXILIARY INDEX RESOLUTION METHODS FOR SURFACES
//=================================================================================================

auto resolveSurfaceIndexAux(SurfaceList const& surfacelist, Index index) -> Index { return index; }
auto resolveSurfaceIndexAux(SurfaceList const& surfacelist, int index) -> Index { return index; }
auto resolveSurfaceIndexAux(SurfaceList const& surfacelist, String const& name) -> Index { return surfacelist.find(name); }

auto resolveSurfaceIndex(SurfaceList const& surfacelist, StringOrIndex const& surface) -> Index
{
    return std::visit([&](auto&& arg) { return resolveSurfaceIndexAux(surfacelist, arg); }, surface);
}

auto resolveSurfaceIndexOrRaiseError(SurfaceList const& surfacelist, StringOrIndex const& surface, String const& errormsg) -> Index
{
    const auto idx = resolveSurfaceIndex(surfacelist, surface);
    errorifnot(idx < surfacelist.size(), errormsg);
    return idx;
}

auto resolveSurfaceIndex(ChemicalSystem const& system, StringOrIndex const& surface) -> Index { return resolveSurfaceIndex(system.surfaces(), surface); }
auto resolveSurfaceIndexOrRaiseError(ChemicalSystem const& system, StringOrIndex const& surface, String const& errormsg) -> Index { return resolveSurfaceIndex(system.surfaces(), surface); }

//=================================================================================================
// AUXILIARY FORMULA MATRIX/VECTOR METHODS
//=================================================================================================

auto assembleFormulaVector(ChemicalFormula const& substance, ElementList const& elements) -> VectorXd
{
    const auto num_elements = elements.size();
    const auto num_components = num_elements + 1;
    VectorXd A(num_components);
    for(auto j = 0; j < num_elements; ++j)
        A[j] = substance.coefficient(elements[j].symbol());
    A[num_elements] = substance.charge();
    return A;
}

auto assembleFormulaMatrix(SpeciesList const& species, ElementList const& elements) -> MatrixXd
{
    const auto num_elements = elements.size();
    const auto num_components = num_elements + 1;
    const auto num_species = species.size();
    MatrixXd A(num_components, num_species);
    for(auto i = 0; i < num_elements; ++i)
        for(auto j = 0; j < num_species; ++j)
            A(i, j) = species[j].elements().coefficient(elements[i].symbol());
    for(auto j = 0; j < num_species; ++j)
        A(num_elements, j) = species[j].charge();
    return A;
}

auto assembleStoichiometricMatrix(ReactionList const& reactions, SpeciesList const& species) -> MatrixXd
{
    const auto num_species = species.size();
    const auto num_reactions = reactions.size();
    MatrixXd S(num_species, num_reactions);
    for(auto i = 0; i < num_species; ++i)
        for(auto j = 0; j < num_reactions; ++j)
            S(i, j) = reactions[j].equation().coefficient(species[i].name());
    return S;
}

//=================================================================================================
// AUXILIARY EXTRACT NAME METHODS
//=================================================================================================

auto extractNames(SpeciesList const& list) -> Strings
{
    return vectorize(list, RKT_LAMBDA(x, x.name()));
}

auto extractNames(ElementList const& list) -> Strings
{
    return vectorize(list, RKT_LAMBDA(x, x.name()));
}

auto extractNames(PhaseList const& list) -> Strings
{
    return vectorize(list, RKT_LAMBDA(x, x.name()));
}

//=================================================================================================
// AUXILIARY METHODS FOR IDENTIFICATION OF REACTIVE INTERPHASE SURFACES
//=================================================================================================

auto determineReactingPhaseInterfacesInReaction(const Reaction& reaction, const PhaseList& phases) -> Pairs<Index, Index>
{
    Indices iphases;
    for(auto const& species : reaction.equation().species())
    {
        const auto iphase = phases.findWithSpecies(species.name());
        if(iphase < phases.size())
            iphases.push_back(iphase);
    }

    errorif(iphases.empty(), "Could not determine the phases that participate in the given reaction. No species in the reaction exist in the phases.");

    iphases = unique(iphases);

    // When a reaction is defined with just one species (such as a mineral-aqueous reaction in which only the mineral is needed because
    // the reactions among the aqueous species are modeled using an equilibrium) create a phase surface with duplicate phase indices.
    if(reaction.equation().size() == 1)
        return { {iphases.front(), iphases.front()} };

    // Skip if the reaction contains only species from a same phase (i.e., homogeneous reaction)
    if(iphases.size() == 1)
        return {};

    Pairs<Index, Index> surfaces;

    for(auto i = 0; i < iphases.size(); ++i)
        for(auto j = i + 1; j < iphases.size(); ++j)
            surfaces.push_back({ iphases[i], iphases[j] });

    return surfaces;
}

auto determineReactingPhaseInterfacesInReactions(const Vec<Reaction>& reactions, const PhaseList& phases) -> Pairs<Index, Index>
{
    Pairs<Index, Index> result;
    for(auto const& reaction : reactions)
        result = merge(result, determineReactingPhaseInterfacesInReaction(reaction, phases));
    return result;
}

auto createSurfacesForReactingPhaseInterfacesInReactions(const Vec<Reaction>& reactions, const PhaseList& phases) -> Vec<Surface>
{
    auto const pairs = determineReactingPhaseInterfacesInReactions(reactions, phases);

    // The auxiliary function to create Surface objects from phase indices
    auto createSurface = [&](Index iphase1, Index iphase2)
    {
        auto const nphase1 = phases[iphase1].name();
        auto const nphase2 = phases[iphase2].name();
        auto const surfacename = iphase1 == iphase2 ? nphase1 : nphase1 + ":" + nphase2; // e.g., AqueousPhase:GaseousPhase, AqueousPhase:Calcite, Calcite:Calcite is reduced to just Calcite
        return Surface(surfacename).withAreaModel([](ChemicalProps const&) { return 0.0; });
    };

    return vectorize(pairs, RKT_LAMBDA(x, createSurface(x.first, x.second)));
}

} // namespace detail
} // namespace Reaktoro
