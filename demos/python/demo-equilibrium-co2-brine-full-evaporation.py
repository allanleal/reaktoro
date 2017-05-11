# Reaktoro is a unified framework for modeling chemically reactive systems.
#
# Copyright (C) 2014-2015 Allan Leal
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.


# FIXME - This demo runs, but it is now failing to converge


from reaktoro import *

editor = ChemicalEditor()
    editor.addAqueousPhase(["H2O(l)", "H+", "OH-", "Na+", "Cl-", "HCO3-", "CO2(aq)", "CO3--", "Ca++"]) \
        .setChemicalModelDebyeHuckel() \
        .setActivityModelDrummondCO2()
    editor.addGaseousPhase(["CO2(g)", "H2O(g)"]) \
        .setChemicalModelSpycherPruessEnnis()
    editor.addMineralPhase("Calcite");
    editor.addMineralPhase("Halite");

system = ChemicalSystem(editor)
reactions = ReactionSystem(editor)

problem = EquilibriumProblem(system)
problem.add("H2O", 1, "kg")
problem.add("NaCl", 1, "mol")
problem.add("CaCO3", 10, "mol")
problem.add("CO2", 200, "kg")

options = EquilibriumOptions()
options.optimum.output.active = True
options.epsilon = 1e-50

state = equilibrate(problem, options)

