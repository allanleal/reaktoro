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

#include "Params.hpp"

// Reaktoro includes
#include <Reaktoro/Common/Algorithms.hpp>
#include <Reaktoro/Common/Exception.hpp>

namespace Reaktoro {

Params::Params()
{}

auto Params::append(const Param& param) -> Param&
{
    m_data.push_back(param);
    return m_data.back();
}

auto Params::append(const String& id, const real& value) -> Param&
{
    return append( Param(value).id(id) );
}

auto Params::size() const -> Index
{
    return m_data.size();
}

auto Params::operator[](Index i) -> Param&
{
    return m_data[i];
}

auto Params::operator[](Index i) const -> const Param&
{
    return m_data[i];
}

auto Params::find(const String& id) const -> Index
{
    return indexfn(m_data, RKT_LAMBDA(x, x.id() == id));
}

auto Params::index(const String& id) const -> Index
{
    const auto idx = indexfn(m_data, RKT_LAMBDA(x, x.id() == id));
    errorif(idx >= m_data.size(), "Could not find a parameter with "
        "id `", id, "` in this Params object.");
    return idx;
}

auto Params::get(const String& id) -> Param&
{
    return m_data[index(id)];
}

auto Params::get(const String& id) const -> const Param&
{
    return m_data[index(id)];
}

auto Params::exists(const String& id) const -> bool
{
    return containsfn(m_data, RKT_LAMBDA(x, x.id() == id));
}

} // namespace Reaktoro
