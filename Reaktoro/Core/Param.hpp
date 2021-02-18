// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2020 Allan Leal
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
#include <limits>

// Reaktoro includes
#include <Reaktoro/Common/Exception.hpp>
#include <Reaktoro/Common/TraitsUtils.hpp>
#include <Reaktoro/Common/Types.hpp>

namespace Reaktoro {

/// A type used to represent the value of a parameter and its lower and upper bounds.
class Param
{
public:
    /// Construct a default Param object.
    Param();

    /// Construct a Param object with given value.
    Param(const real& val);

    /// Construct a Param object with given value.
    template<typename T, EnableIf<isArithmetic<T>>...>
    Param(const T& val) : Param(real(val)) {}

    /// Set the value of the parameter.
    auto value(const real& val) -> Param&;

    /// Return the value of the parameter.
    auto value() const -> const real&;

    /// Set the value of the parameter.
    auto name(String name) -> Param&;

    /// Return the value of the parameter.
    auto name() const -> const String&;

    /// Set the lower bound of the parameter.
    auto lowerbound(double val) -> Param&;

    /// Return the lower bound of the parameter.
    auto lowerbound() const -> double;

    /// Set the upper bound of the parameter.
    auto upperbound(double val) -> Param&;

    /// Return the upper bound of the parameter.
    auto upperbound() const -> double;

    /// Set the parameter to constant or non-constant modes.
    auto isconst(bool val) -> Param&;

    /// Return true if the parameter is constant.
    auto isconst() const -> bool;

    /// Assign a real value to this parameter value.
    auto operator=(const real& val) -> Param&;

    /// Convert this Param object into its value type.
    operator const real&() const;

    /// Return a Param object that represents a constant parameter.
    static auto Constant(const real& val) -> Param;

private:
    struct Impl;

    SharedPtr<Impl> pimpl;
};

} // namespace Reaktoro
