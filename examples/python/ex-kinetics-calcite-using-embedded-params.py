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
from reaktplot import *


db = SupcrtDatabase("supcrtbl")

solution = AqueousPhase("H2O(aq) H+ OH- Ca+2 HCO3- CO3-2 CO2(aq)")
solution.set(ActivityModelDavies())

calcite = MineralPhase("Calcite")

phases = Phases(db)
phases.add(solution)
phases.add(calcite)

params = Params.embedded("PalandriKharaka.yaml")

reactions = MineralReactions("Calcite")
reactions.setRateModel(ReactionRateModelPalandriKharaka(params))

system = ChemicalSystem(phases, reactions)

state = ChemicalState(system)
state.set("H2O(aq)", 1.0, "kg")
state.set("Calcite", 2.71, "g")  # equivalent to a cube of calcite of 1 cm3
state.surfaceArea("Calcite", 6.0, "cm2")  # equivalent to the surface area of a 1cm3 cube

aprops = AqueousProps(system)

solver = KineticsSolver(system)

table = Table()

dt = 2.0  # time step (in seconds)

for i in range(501):

    result = solver.solve(state, dt)

    assert result.succeeded(), f"Calculation did not succeed at time step #{i}."

    aprops.update(state.props())

    table.column("Timestep") << i
    table.column("Time")     << i*dt / 60.0  # from seconds to minute
    table.column("Calcite")  << state.props().speciesMass("Calcite") * 1000.0  # from kg to g
    table.column("Ca+2")     << aprops.speciesMolality("Ca+2")
    table.column("HCO3-")    << aprops.speciesMolality("HCO3-")
    table.column("CO3-2")    << aprops.speciesMolality("CO3-2")
    table.column("CO2(aq)")  << aprops.speciesMolality("CO2(aq)")
    table.column("pH")       << aprops.pH()

table.save("ex-kinetics-calcite-using-embedded-params.txt")

fig1 = Figure()
fig1.title("AQUEOUS SPECIES CONCENTRATIONS OVER TIME")
fig1.xaxisTitle("Time [minute]")
fig1.yaxisTitle("Concentration [molal]")
fig1.drawLine(table["Time"], table["Ca+2"], "Ca+2")
fig1.drawLine(table["Time"], table["HCO3-"], "HCO3-")
fig1.drawLine(table["Time"], table["CO3-2"], "CO3-2")
fig1.drawLine(table["Time"], table["CO2(aq)"], "CO2(aq)")
fig1.yaxisScaleLog()
fig1.show()
fig1.save("ex-kinetics-calcite-using-embedded-params-fig1.pdf")

fig2 = Figure()
fig2.title("CALCITE MASS OVER TIME")
fig2.xaxisTitle("Time [minute]")
fig2.yaxisTitle("Mass [g]")
fig2.drawLine(table["Time"], table["Calcite"], "Calcite")
fig2.show()
fig2.save("ex-kinetics-calcite-using-embedded-params-fig2.pdf")

fig3 = Figure()
fig3.title("PH OVER TIME")
fig3.xaxisTitle("Time [minute]")
fig3.yaxisTitle("pH")
fig3.drawLine(table["Time"], table["pH"], "pH")
fig3.show()
fig3.save("ex-kinetics-calcite-using-embedded-params-fig3.pdf")
