# Reaktoro is a unified framework for modeling chemically reactive systems.
#
# Copyright © 2014-2022 Allan Leal
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.


from reaktoro import *


def testSurface():

    surface = Surface()

    surface = surface.withName("AqueousPhase:GaseousPhase")
    assert surface.name() == "AqueousPhase:GaseousPhase"

    surface = surface.withPhaseNames("AqueousPhase", "GaseousPhase")
    assert surface.phaseNames() == ("AqueousPhase","GaseousPhase")

    surface = surface.withPhaseIndices(0, 1)
    assert surface.phaseIndices() == (0, 1)

    other = Surface("SomeName")
    other = other.withPhaseNames("GaseousPhase", "AqueousPhase")
    other = other.withPhaseIndices(1, 0)
    assert surface.equivalent(other)

    another = Surface("SomeName", "GaseousPhase", 1, "AqueousPhase", 0)
    assert surface.equivalent(another)
