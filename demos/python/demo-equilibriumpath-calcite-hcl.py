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

editor = ChemicalEditor()
editor.addAqueousPhase("H O Ca C Cl")
editor.addMineralPhase("Calcite")

system = ChemicalSystem(editor)

problem1 = EquilibriumProblem(system)
problem1.setTemperature(30.0, "celsius")
problem1.setPressure(1.0, "bar")
problem1.add("H2O", 1, "kg")
problem1.add("CaCO3", 1, "g")

problem2 = EquilibriumProblem(system)
problem2.setTemperature(30.0, "celsius")
problem2.setPressure(1.0, "bar")
problem2.add("H2O", 1, "kg")
problem2.add("CaCO3", 1, "g")
problem2.add("HCl", 1, "mmol")

state1 = equilibrate(problem1)
state2 = equilibrate(problem2)

path = EquilibriumPath(system)

plot1 = path.plot()
plot1.x("elementAmount(Cl units=mmol)")
plot1.y("pH")
plot1.xlabel("HCl [mmol]")
plot1.ylabel("pH")
plot1.showlegend(False)

plot2 = path.plot()
plot2.x("elementAmount(Cl units=mmol)")
plot2.y("elementMolality(Ca units=mmolal)", "Ca")
plot2.xlabel("HCl [mmol]")
plot2.ylabel("Concentration [mmolal]")
plot2.legend("right center")

plot3 = path.plot()
plot3.x("elementAmount(Cl units=mmol)")
plot3.y("speciesMolality(CO2(aq) units=mmolal)", "CO2(aq)")
plot3.y("speciesMolality(CO3-- units=mmolal)", "CO3--")
plot3.xlabel("HCl [mmol]")
plot3.ylabel("Concentration [mmolal]")
plot3.legend("right top")

plot4 = path.plot()
plot4.x("elementAmount(Cl units=mmol)")
plot4.y("speciesMass(Calcite units=g)", "Calcite")
plot4.xlabel("HCl [mmol]")
plot4.ylabel("Mass [g]")

output = path.output()
output.filename("result.txt")
output.add("elementAmount(Cl units=mmol)", "Cl [mmol]")
output.add("elementMolality(Ca units=mmolal)", "Ca [mmolal]")
output.add("pH")
output.add("speciesMass(Calcite units=g)")

path.solve(state1, state2)
