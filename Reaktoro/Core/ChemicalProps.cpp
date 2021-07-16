// Reaktoro is a unified framework for modeling chemically reactive phases.
//
// Copyright © 2014-2021 Allan Leal
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

#include "ChemicalProps.hpp"

// cpp-tabulate includes
#include <tabulate/table.hpp>
using namespace tabulate;

// Reaktoro includes
#include <Reaktoro/Common/Algorithms.hpp>
#include <Reaktoro/Core/ChemicalPropsPhase.hpp>
#include <Reaktoro/Core/ChemicalState.hpp>

namespace Reaktoro {

struct ChemicalProps::Impl
{
    /// The chemical system associated with these chemical properties.
    ChemicalSystem system;

    /// The temperature of the system (in K).
    real T = 0.0;

    /// The pressure of the system (in Pa).
    real P = 0.0;

    /// The temperatures of each phase (in K).
    ArrayXr Ts;

    /// The pressures of each phase (in Pa).
    ArrayXr Ps;

    /// The amounts of each species in the system (in mol).
    ArrayXr n;

    /// The sum of species amounts in each phase of the system (in mol).
    ArrayXr nsum;

    /// The mole fractions of the species in the system (in mol/mol).
    ArrayXr x;

    /// The standard molar Gibbs energies of formation of the species in the system (in J/mol).
    ArrayXr G0;

    /// The standard molar enthalpies of formation of the species in the system (in J/mol).
    ArrayXr H0;

    /// The standard molar volumes of the species in the system (in m3/mol).
    ArrayXr V0;

    /// The standard molar isobaric heat capacities of the species in the system (in J/(mol·K)).
    ArrayXr Cp0;

    /// The standard molar isochoric heat capacities of the species in the system (in J/(mol·K)).
    ArrayXr Cv0;

    /// The excess molar volume of each phase in the system (in m3/mol).
    ArrayXr Vex;

    /// The temperature derivative at constant pressure of the excess molar volume of each phase in the system (in m3/(mol*K)).
    ArrayXr VexT;

    /// The pressure derivative at constant temperature of the excess molar volume of each phase in the system (in m3/(mol*Pa)).
    ArrayXr VexP;

    /// The excess molar Gibbs energy of each phase in the system (in J/mol).
    ArrayXr Gex;

    /// The excess molar enthalpy of each phase in the system (in J/mol).
    ArrayXr Hex;

    /// The excess molar isobaric heat capacity of each phase in the system (in J/(mol*K)).
    ArrayXr Cpex;

    /// The excess molar isochoric heat capacity of each phase in the system (in J/(mol*K)).
    ArrayXr Cvex;

    /// The activity coefficients (natural log) of the species in the system.
    ArrayXr ln_g;

    /// The activities (natural log) of the species in the system.
    ArrayXr ln_a;

    /// The chemical potentials of the species in the system.
    ArrayXr u;

    /// Construct a ChemicalProps::Impl object.
    Impl(const ChemicalSystem& system)
    : system(system)
    {
        const auto numspecies = system.species().size();
        const auto numphases = system.phases().size();

        Ts   = ArrayXr::Zero(numphases);
        Ps   = ArrayXr::Zero(numphases);
        n    = ArrayXr::Zero(numspecies);
        nsum = ArrayXr::Zero(numphases);
        x    = ArrayXr::Zero(numspecies);
        G0   = ArrayXr::Zero(numspecies);
        H0   = ArrayXr::Zero(numspecies);
        V0   = ArrayXr::Zero(numspecies);
        Cp0  = ArrayXr::Zero(numspecies);
        Cv0  = ArrayXr::Zero(numspecies);
        Vex  = ArrayXr::Zero(numphases);
        VexT = ArrayXr::Zero(numphases);
        VexP = ArrayXr::Zero(numphases);
        Gex  = ArrayXr::Zero(numphases);
        Hex  = ArrayXr::Zero(numphases);
        Cpex = ArrayXr::Zero(numphases);
        Cvex = ArrayXr::Zero(numphases);
        ln_g = ArrayXr::Zero(numspecies);
        ln_a = ArrayXr::Zero(numspecies);
        u    = ArrayXr::Zero(numspecies);
    }

    /// Construct a ChemicalProps::Impl object.
    Impl(const ChemicalState& state)
    : Impl(state.system())
    {
        update(state);
    }

    /// Update the chemical properties of the chemical system.
    auto update(const ChemicalState& state) -> void
    {
        const auto& T = state.temperature();
        const auto& P = state.pressure();
        const auto& n = state.speciesAmounts();
        update(T, P, n);
    }

    /// Update the chemical properties of the chemical system.
    auto update(const real& T, const real& P, ArrayXrConstRef n) -> void
    {
        this->T = T;
        this->P = P;
        const auto numphases = system.phases().size();
        auto offset = 0;
        for(auto i = 0; i < numphases; ++i)
        {
            const auto size = system.phase(i).species().size();
            const auto np = n.segment(offset, size);
            phaseProps(i).update(T, P, np);
            offset += size;
        }
    }

    /// Update the chemical properties of the system with serialized data.
    template<typename Array>
    auto update(const Array& data) -> void
    {
        ArraySerialization::deserialize(data, T, P, Ts, Ps, n, nsum, x, G0, H0, V0, Cp0, Cv0, Vex, VexT, VexP, Gex, Hex, Cpex, Cvex, ln_g, ln_a, u);
    }

    /// Update the chemical properties of the chemical system using ideal activity models.
    auto updateIdeal(const ChemicalState& state) -> void
    {
        const auto& T = state.temperature();
        const auto& P = state.pressure();
        const auto& n = state.speciesAmounts();
        updateIdeal(T, P, n);
    }

    /// Update the chemical properties of the chemical system using ideal activity models.
    auto updateIdeal(const real& T, const real& P, ArrayXrConstRef n) -> void
    {
        this->T = T;
        this->P = P;
        const auto numphases = system.phases().size();
        auto offset = 0;
        for(auto i = 0; i < numphases; ++i)
        {
            const auto size = system.phase(i).species().size();
            const auto np = n.segment(offset, size);
            phaseProps(i).updateIdeal(T, P, np);
            offset += size;
        }
    }

    /// Serialize the chemical properties into the array stream @p stream.
    template<typename Type>
    auto serialize(ArrayStream<Type>& stream) const -> void
    {
        stream.from(T, P, Ts, Ps, n, nsum, x, G0, H0, V0, Cp0, Cv0, Vex, VexT, VexP, Gex, Hex, Cpex, Cvex, ln_g, ln_a, u);
    }

    /// Update the chemical properties of the system using the array stream @p stream.
    template<typename Type>
    auto deserialize(const ArrayStream<Type>& stream) -> void
    {
        stream.to(T, P, Ts, Ps, n, nsum, x, G0, H0, V0, Cp0, Cv0, Vex, VexT, VexP, Gex, Hex, Cpex, Cvex, ln_g, ln_a, u);
    }

    /// Return the chemical properties of a phase with given index.
    auto phaseProps(Index idx) -> ChemicalPropsPhaseRef
    {
        const auto phase = system.phase(idx);
        const auto begin = system.phases().numSpeciesUntilPhase(idx);
        const auto size = phase.species().size();

        return ChemicalPropsPhaseRef(phase, {
            Ts[idx],
            Ps[idx],
            n.segment(begin, size),
            nsum[idx],
            x.segment(begin, size),
            G0.segment(begin, size),
            H0.segment(begin, size),
            V0.segment(begin, size),
            Cp0.segment(begin, size),
            Cv0.segment(begin, size),
            Vex[idx],
            VexT[idx],
            VexP[idx],
            Gex[idx],
            Hex[idx],
            Cpex[idx],
            Cvex[idx],
            ln_g.segment(begin, size),
            ln_a.segment(begin, size),
            u.segment(begin, size)
        });
    }
};

ChemicalProps::ChemicalProps(const ChemicalSystem& system)
: pimpl(new Impl(system))
{}

ChemicalProps::ChemicalProps(const ChemicalState& state)
: pimpl(new Impl(state))
{}

ChemicalProps::ChemicalProps(const ChemicalProps& other)
: pimpl(new Impl(*other.pimpl))
{}

ChemicalProps::~ChemicalProps()
{}

auto ChemicalProps::operator=(ChemicalProps other) -> ChemicalProps&
{
    pimpl = std::move(other.pimpl);
    return *this;
}

auto ChemicalProps::update(const ChemicalState& state) -> void
{
    pimpl->update(state);
}

auto ChemicalProps::update(const real& T, const real& P, ArrayXrConstRef n) -> void
{
    pimpl->update(T, P, n);
}

auto ChemicalProps::update(ArrayXrConstRef u) -> void
{
    pimpl->update(u);
}

auto ChemicalProps::update(ArrayXdConstRef u) -> void
{
    pimpl->update(u);
}

auto ChemicalProps::updateIdeal(const ChemicalState& state) -> void
{
    pimpl->updateIdeal(state);
}

auto ChemicalProps::updateIdeal(const real& T, const real& P, ArrayXrConstRef n) -> void
{
    pimpl->updateIdeal(T, P, n);
}

auto ChemicalProps::serialize(ArrayStream<real>& stream) const -> void
{
    pimpl->serialize(stream);
}

auto ChemicalProps::deserialize(const ArrayStream<real>& stream) -> void
{
    pimpl->deserialize(stream);
}

auto ChemicalProps::system() const -> const ChemicalSystem&
{
    return pimpl->system;
}

auto ChemicalProps::phaseProps(Index idx) const -> ChemicalPropsPhaseConstRef
{
    return pimpl->phaseProps(idx);
}

auto ChemicalProps::temperature() const -> const real&
{
    return pimpl->T;
}

auto ChemicalProps::pressure() const -> const real&
{
    return pimpl->P;
}

auto ChemicalProps::speciesAmounts() const -> ArrayXrConstRef
{
    return pimpl->n;
}

auto ChemicalProps::moleFractions() const -> ArrayXrConstRef
{
    return pimpl->x;
}

auto ChemicalProps::lnActivityCoefficients() const -> ArrayXrConstRef
{
    return pimpl->ln_g;
}

auto ChemicalProps::lnActivities() const -> ArrayXrConstRef
{
    return pimpl->ln_a;
}

auto ChemicalProps::chemicalPotentials() const -> ArrayXrConstRef
{
    return pimpl->u;
}

auto ChemicalProps::standardVolumes() const -> ArrayXrConstRef
{
    return pimpl->V0;
}

auto ChemicalProps::standardGibbsEnergies() const -> ArrayXrConstRef
{
    return pimpl->G0;
}

auto ChemicalProps::standardEnthalpies() const -> ArrayXrConstRef
{
    return pimpl->H0;
}

auto ChemicalProps::standardEntropies() const -> ArrayXr
{
    return (pimpl->H0 - pimpl->G0)/pimpl->T; // from G0 = H0 - T*S0
}

auto ChemicalProps::standardInternalEnergies() const -> ArrayXr
{
    return pimpl->H0 - pimpl->P * pimpl->V0; // from H0 = U0 + P*V0
}

auto ChemicalProps::standardHelmholtzEnergies() const -> ArrayXr
{
    return pimpl->G0 - pimpl->P * pimpl->V0; // from A0 = U0 - T*S0 = (H0 - P*V0) + (G0 - H0) = G0 - P*V0
}

auto ChemicalProps::standardHeatCapacitiesConstP() const -> ArrayXrConstRef
{
    return pimpl->Cp0;
}

auto ChemicalProps::standardHeatCapacitiesConstV() const -> ArrayXrConstRef
{
    return pimpl->Cv0;
}

auto ChemicalProps::amount() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).amount(); });
}

auto ChemicalProps::mass() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).mass(); });
}

auto ChemicalProps::volume() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).volume(); });
}

auto ChemicalProps::gibbsEnergy() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).gibbsEnergy(); });
}

auto ChemicalProps::enthalpy() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).enthalpy(); });
}

auto ChemicalProps::entropy() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).entropy(); });
}

auto ChemicalProps::internalEnergy() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).internalEnergy(); });
}

auto ChemicalProps::helmholtzEnergy() const -> real
{
    const auto iend = system().phases().size();
    return Reaktoro::sum(iend, [&](auto i) { return phaseProps(i).helmholtzEnergy(); });
}

ChemicalProps::operator VectorXr() const
{
    ArrayStream<real> stream;
    pimpl->serialize(stream);
    return stream.data();
}

ChemicalProps::operator VectorXd() const
{
    ArrayStream<double> stream;
    pimpl->serialize(stream);
    return stream.data();
}

auto operator<<(std::ostream& out, const ChemicalProps& props) -> std::ostream&
{
    const auto species = props.system().species();
    const auto n   = props.speciesAmounts();
    const auto x   = props.moleFractions();
    const auto lng = props.lnActivityCoefficients();
    const auto lna = props.lnActivities();
    const auto mu  = props.chemicalPotentials();
    const auto G0  = props.standardGibbsEnergies();
    const auto H0  = props.standardEnthalpies();
    const auto V0  = props.standardVolumes();
    const auto S0  = props.standardEntropies();
    const auto U0  = props.standardInternalEnergies();
    const auto A0  = props.standardHelmholtzEnergies();
    const auto Cp0 = props.standardHeatCapacitiesConstP();
    const auto Cv0 = props.standardHeatCapacitiesConstV();

    Table table;
    table.add_row({ "Property", "Value", "Unit" });
    table.add_row({ "Temperature", str(props.temperature()), "K" });
    table.add_row({ "Pressure", str(props.pressure()), "Pa" });
    table.add_row({ "Volume", str(props.volume()), "m3" });
    table.add_row({ "Gibbs Energy", str(props.gibbsEnergy()), "J" });
    table.add_row({ "Enthalpy", str(props.enthalpy()), "J" });
    table.add_row({ "Entropy", str(props.entropy()), "J/K" });
    table.add_row({ "Internal Energy", str(props.internalEnergy()), "J" });
    table.add_row({ "Helmholtz Energy", str(props.helmholtzEnergy()), "J" });

    table.add_row({ "Amount" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(n[i]), "mol" });
    table.add_row({ "Mole Fraction", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(x[i]), "mol/mol" });
    table.add_row({ "Activity Coefficient", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(exp(lng[i])), "-" });
    table.add_row({ "Activity", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(exp(lna[i])), "-" });
    table.add_row({ "lg(Activity)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(lna[i]/ln10), "-" });
    table.add_row({ "ln(Activity)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(lna[i]), "-" });
    table.add_row({ "Chemical Potential", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(mu[i]), "J/mol" });
    table.add_row({ "Standard Volume", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(V0[i]), "m3/mol" });
    table.add_row({ "Standard Gibbs Energy (formation)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(G0[i]), "J/mol" });
    table.add_row({ "Standard Enthalpy (formation)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(H0[i]), "J/mol" });
    table.add_row({ "Standard Entropy (formation)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(S0[i]), "J/(mol*K)" });
    table.add_row({ "Standard Internal Energy (formation)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(U0[i]), "J/mol" });
    table.add_row({ "Standard Helmholtz Energy (formation)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(A0[i]), "J/mol" });
    table.add_row({ "Standard Heat Capacity (constant P)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(Cp0[i]), "J/(mol*K)" });
    table.add_row({ "Standard Heat Capacity (constant V)", "", "" }); for(auto i = 0; i < n.size(); ++i) table.add_row({ ":: " + species[i].name(), str(Cv0[i]), "J/(mol*K)" });

    auto i = 0;
    for(auto& row : table)
    {
        if(i >= 2)  // apply from the third row
            table[i].format()
                .border_top("")
                .column_separator("")
                .corner_top_left("")
                .corner_top_right("");
        i += 1;
    }

    table.row(0).format().font_style({FontStyle::bold});  // Bold face for header
    table.column(1).format().font_align(FontAlign::right); // Value column with right alignment
    table.column(2).format().font_align(FontAlign::right); // Unit column with right alignment

    out << table;
    return out;
}

} // namespace Reaktoro
