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

#include "StandardThermoModelConstant.hpp"

// Reaktoro includes
#include <Reaktoro/Serialization/Models.YAML.hpp>

namespace Reaktoro {

/// Return a Params object containing all Param objects in @p params.
auto extractParams(const StandardThermoModelParamsConstant& params) -> Params
{
    const auto& [G0, H0, V0, Cp0, Cv0] = params;
    return {G0, H0, V0, Cp0, Cv0};
}

/// Return a ModelSerializer for given model parameters in @p params.
auto createModelSerializer(const StandardThermoModelParamsConstant& params) -> ModelSerializer
{
    return [=]()
    {
        yaml node;
        node["Constant"] = params;
        return node;
    };
}

auto StandardThermoModelConstant(const StandardThermoModelParamsConstant& params) -> StandardThermoModel
{
    auto evalfn = [=](StandardThermoProps& props, real T, real P)
    {
        auto& [G0, H0, V0, Cp0, Cv0] = props;

        G0  = params.G0;
        H0  = params.H0;
        V0  = params.V0;
        Cp0 = params.Cp0;
        Cv0 = params.Cv0;
    };

    return StandardThermoModel(evalfn, extractParams(params), createModelSerializer(params));
}

} // namespace Reaktoro
