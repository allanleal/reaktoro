// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2021 Allan Leal
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

#include "ActivityModel.hpp"

// Reaktoro includes
#include "ActivityModel.hpp"

namespace Reaktoro {

auto chain(const Vec<ActivityModel>& models) -> ActivityModel
{
    ActivityModel chained_model = [=](const SpeciesList& species)
    {
        const Vec<ActivityPropsFn> activity_props_fns = vectorize(models, RKT_LAMBDA(model, model(species)));

        ActivityPropsFn chained_activity_props_fn = [=](ActivityPropsRef props, ActivityArgs args)
        {
            for(const auto& fn : activity_props_fns)
                fn(props, args);
        };

        return chained_activity_props_fn;
    };

    return chained_model;
}

auto chain(const ActivityModel& model) -> ActivityModel
{
    return model;
}

} // namespace Reaktoro
