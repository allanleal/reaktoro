# Reaktoro is a unified framework for modeling chemically reactive systems.
#
# Copyright (C) 2014-2020 Allan Leal
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

db = DebyeHuckelParams()
db.setPHREEQC()

editor = ChemicalEditor()
editor.addAqueousPhase("H2O NaCl CaCl2 CO2") \
    .setChemicalModelDebyeHuckel(db)

system = ChemicalSystem(editor)

problem1 = EquilibriumProblem(system)
problem1.add("H2O", 1, "kg")

problem2 = EquilibriumProblem(system)
problem2.add("H2O", 1, "kg")
problem2.add("NaCl", 0.1, "mol")
problem2.add("CaCl2", 0.5, "mol")
problem2.add("CO2", 0.2, "mol")

state1 = equilibrate(problem1)
state2 = equilibrate(problem2)

path = EquilibriumPath(system)

plot = path.plot()
plot.x("ionicStrength")
plot.y("activityCoefficient(Na+)", "Na+")
plot.y("activityCoefficient(Cl-)", "Cl-")
plot.y("activityCoefficient(Ca++)", "Ca++")
plot.ylabel("Activity Coefficient")
plot.xlabel("I [molal]")
path.solve(state1, state2)
