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

// C++ includes
#include <cmath>

// Reaktoro includes
#include <Reaktoro/Common/Types.hpp>
#include <Reaktoro/Core/ActivityProps.hpp>
#include <Reaktoro/Core/SpeciesList.hpp>

namespace Reaktoro {

/// The type for functions that construct an ActivityModel for a phase.
/// @param species The species in the phase.
using ActivityModelGenerator = Fn<ActivityModel(const SpeciesList& species)>;

// TODO: Rename this ActivityModel type by ActivityModelGenerator
// TODO: Use the name ActivityModel instead of ActivityModel.
// TODO: Use Model type to define ActivityModel.
// TODO: Define these chain methods for Model type.

/// Return an activity model resulting from chaining other activity models.
auto chain(const Vec<ActivityModelGenerator>& models) -> ActivityModelGenerator;

/// Return an activity model resulting from chaining other activity models.
auto chain(const ActivityModelGenerator& model) -> ActivityModelGenerator;

/// Return an activity model resulting from chaining other activity models.
template<typename... Models>
auto chain(const ActivityModelGenerator& model, const Models&... models) -> ActivityModelGenerator
{
    Vec<ActivityModelGenerator> vec = {model, models...};
    return chain(vec);
}

} // namespace Reaktoro
