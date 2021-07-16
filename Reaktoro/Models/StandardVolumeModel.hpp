// Reaktoro is a unified framework for modeling chemically reactive systems.
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

#pragma once

// Reaktoro includes
#include <Reaktoro/Core/Model.hpp>

namespace Reaktoro {

/// The function type for calculation of standard volume of a product species in a formation reaction.
/// @param T The temperature for the calculation (in K)
/// @param P The pressure for the calculation (in Pa)
/// @return The standard molar volume of the product species
using StandardVolumeModel = Model<real(real T, real P)>;

} // namespace Reaktoro
