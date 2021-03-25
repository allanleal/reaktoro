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

#include "YAML.hpp"

namespace Reaktoro {

yaml::yaml()
: YAML::Node()
{}

yaml::yaml(const char* input)
: YAML::Node(YAML::Load(input))
{}

yaml::yaml(const std::string& input)
: YAML::Node(YAML::Load(input))
{}

yaml::yaml(std::istream& input)
: YAML::Node(YAML::Load(input))
{}

yaml::yaml(const Node& node)
: YAML::Node(node)
{}

auto yaml::at(const std::string& key) const -> yaml
{
    auto child = (*this)[key];
    errorif(!child, "Could not get YAML node with key ", key, " .");
    return child;
}

} // namespace Reaktoro
