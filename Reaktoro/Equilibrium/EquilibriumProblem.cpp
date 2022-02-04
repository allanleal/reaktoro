// // Reaktoro is a unified framework for modeling chemically reactive systems.
// //
// // Copyright (C) 2014-2020 Allan Leal
// //
// // This library is free software; you can redistribute it and/or
// // modify it under the terms of the GNU Lesser General Public
// // License as published by the Free Software Foundation; either
// // version 2.1 of the License, or (at your option) any later version.
// //
// // This library is distributed in the hope that it will be useful,
// // but WITHOUT ANY WARRANTY; without even the implied warranty of
// // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// // Lesser General Public License for more details.
// //
// // You should have received a copy of the GNU Lesser General Public License
// // along with this library. If not, see <http://www.gnu.org/licenses/>.

// #include "EquilibriumProblem.hpp"

// // C++ includes
// #include <memory>

// // Reaktoro includes
// #include <Reaktoro/Common/Exception.hpp>
// #include <Reaktoro/Common/Units.hpp>
// #include <Reaktoro/Core/ChemicalState.hpp>
// #include <Reaktoro/Core/ChemicalSystem.hpp>
// #include <Reaktoro/Core/Element.hpp>
// #include <Reaktoro/Core/Partition.hpp>
// #include <Reaktoro/Core/Species.hpp>
// #include <Reaktoro/Core/Utils.hpp>
// #include <Reaktoro/Math/MathUtils.hpp>

// namespace Reaktoro {
// namespace {

// /// Throw a non-amount or non-mass error if units no compatible
// auto errorNonAmountOrMassUnits(std::string units) -> void
// {
//     Exception exception;
//     exception.error << "Cannot set the amount of a species or element.";
//     exception.reason << "The provided units `" << units << "` is not convertible to units of amount or mass (e.g., mol and g).";
//     RaiseError(exception);
// }

// } // namespace

// struct EquilibriumProblem::Impl
// {
//     /// The reference to the ChemicalSystem instance
//     ChemicalSystem system;

//     /// The reference to the Partition instance
//     Partition partition;

//     /// The temperature for the equilibrium problem (in units of K)
//     double T;

//     /// The pressure for the equilibrium problem (in units of Pa)
//     double P;

//     /// The amounts of the elements for the equilibrium problem (in units of mol)
//     VectorXr b;

//     /// Construct a EquilibriumProblem::Impl instance
//     Impl(const Partition& partition)
//     : system(partition.system()), T(298.15), P(1.0e+5), partition(partition)
//     {
//         // Initialize the amounts of the elements
//         b = zeros(system.elements().size());
//     }

//     /// Set the partition of the chemical system
//     auto setPartition(const Partition& part) -> void
//     {
//         partition = part;
//     }
// };

// EquilibriumProblem::EquilibriumProblem(const ChemicalSystem& system)
// : pimpl(new Impl(Partition(system)))
// {}

// EquilibriumProblem::EquilibriumProblem(const Partition& partition)
// : pimpl(new Impl(partition))
// {}

// EquilibriumProblem::EquilibriumProblem(const EquilibriumProblem& other)
// : pimpl(new Impl(*other.pimpl))
// {}

// EquilibriumProblem::~EquilibriumProblem()
// {}

// auto EquilibriumProblem::operator=(EquilibriumProblem other) -> EquilibriumProblem&
// {
//     pimpl = std::move(other.pimpl);
//     return *this;
// }

// auto EquilibriumProblem::setPartition(const Partition& partition) -> EquilibriumProblem&
// {
//     pimpl->setPartition(partition);
//     return *this;
// }

// auto EquilibriumProblem::setTemperature(double val) -> EquilibriumProblem&
// {
//     Assert(val > 0.0, "Cannot set temperature of the equilibrium problem.",
//         "Given value must be positive.");
//     pimpl->T = val;
//     return *this;
// }

// auto EquilibriumProblem::setTemperature(double val, std::string units) -> EquilibriumProblem&
// {
//     return setTemperature(units::convert(val, units, "kelvin"));
// }

// auto EquilibriumProblem::setPressure(double val) -> EquilibriumProblem&
// {
//     Assert(val > 0.0, "Cannot set pressure of the equilibrium problem.",
//         "Given value must be positive.");
//     pimpl->P = val;
//     return *this;
// }

// auto EquilibriumProblem::setPressure(double val, std::string units) -> EquilibriumProblem&
// {
//     return setPressure(units::convert(val, units, "pascal"));
// }

// auto EquilibriumProblem::setElementAmounts(VectorXrConstRef b) -> EquilibriumProblem&
// {
//     Assert(pimpl->b.size() == b.size(),
//         "Could not set the initial mole amounts of the elements.",
//         "Dimension mismatch between given vector of values and number of elements.");
//     pimpl->b = b;
//     return *this;
// }

// auto EquilibriumProblem::setElementAmounts(double amount) -> EquilibriumProblem&
// {
//     pimpl->b.fill(amount);
//     return *this;
// }

// auto EquilibriumProblem::setElementAmount(Index ielement, double amount) -> EquilibriumProblem&
// {
//     Assert(ielement < system().numElements(),
//         "Could not set the initial mole amount of the given element.",
//         "Dimension mismatch between given vector of values and number of elements.");
//     pimpl->b[ielement] = amount;
//     return *this;
// }

// auto EquilibriumProblem::setElementAmount(std::string element, double amount) -> EquilibriumProblem&
// {
//     Index ielement = system().indexElement(element);
//     Assert(ielement < system().numElements(),
//         "Could not set the initial mole amount of the given element `" + element + "`.",
//         "The chemical system was not initialized with this element.");
//     pimpl->b[ielement] = amount;
//     return *this;
// }

// auto EquilibriumProblem::setElectricalCharge(double amount) -> EquilibriumProblem&
// {
//     return setElementAmount("Z", amount);
// }

// auto EquilibriumProblem::add(std::string name, double amount, std::string units) -> EquilibriumProblem&
// {
//     if(system().indexSpecies(name) < system().species().size())
//         return addSpecies(name, amount, units);
//     return addCompound(name, amount, units);
// }

// auto EquilibriumProblem::add(const ChemicalState& state) -> EquilibriumProblem&
// {
//     return addState(state);
// }

// auto EquilibriumProblem::addCompound(std::string name, double amount, std::string units) -> EquilibriumProblem&
// {
//     double molar_amount = 0.0;

//     if(units::convertible(units, "mol"))
//     {
//         molar_amount = units::convert(amount, units, "mol");
//     }
//     else if(units::convertible(units, "kg"))
//     {
//         const double mass = units::convert(amount, units, "kg");
//         const double molar_mass = molarMass(name);
//         molar_amount = mass / molar_mass;
//     }
//     else errorNonAmountOrMassUnits(units);

//     for(const auto& pair : elements(name))
//     {
//         const auto element = pair.first;
//         const auto coeffficient = pair.second;
//         const auto ielement = system().indexElement(element);
//         Assert(ielement < system().numElements(),
//             "Cannot add the compound `" + name + "` to the equilibrium problem.",
//             "This compound has element `" + element + "`, which is not present in the chemical system. "
//             "Please note that this error can happen if this element is present in different valence state. "
//             "In such case, check if there is a chemical species with same chemical formula, "
//             "and use its name instead (e.g., instead of SiO2, use Quartz).");
//         pimpl->b[ielement] += coeffficient * molar_amount;
//     }

//     return *this;
// }

// auto EquilibriumProblem::addSpecies(std::string name, double amount, std::string units) -> EquilibriumProblem&
// {
//     double molar_amount = 0.0;

//     const Species& species = system().species(name);

//     if(units::convertible(units, "mol"))
//     {
//         molar_amount = units::convert(amount, units, "mol");
//     }
//     else if(units::convertible(units, "kg"))
//     {
//         const double mass = units::convert(amount, units, "kg");
//         const double molar_mass = species.molarMass();
//         molar_amount = mass / molar_mass;
//     }
//     else errorNonAmountOrMassUnits(units);

//     for(const auto& pair : species.elements())
//     {
//         const auto element = pair.first.name();
//         const auto coeffficient = pair.second;
//         const auto ielement = system().indexElement(element);
//         pimpl->b[ielement] += coeffficient * molar_amount;
//     }

//     return *this;
// }

// auto EquilibriumProblem::addState(const ChemicalState& state) -> EquilibriumProblem&
// {
//     const Indices ies = pimpl->partition.indicesEquilibriumSpecies();
//     pimpl->b += state.elementAmountsInSpecies(ies);
//     return *this;
// }

// auto EquilibriumProblem::system() const -> const ChemicalSystem&
// {
//     return pimpl->system;
// }

// auto EquilibriumProblem::partition() const -> const Partition&
// {
//     return pimpl->partition;
// }

// auto EquilibriumProblem::temperature() const -> double
// {
//     return pimpl->T;
// }

// auto EquilibriumProblem::pressure() const -> double
// {
//     return pimpl->P;
// }

// auto EquilibriumProblem::elementAmounts() const -> VectorXrConstRef
// {
//     return pimpl->b;
// }

// } // namespace Reaktoro
