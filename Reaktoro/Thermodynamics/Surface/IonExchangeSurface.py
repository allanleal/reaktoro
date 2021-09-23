# Reaktoro is a unified framework for modeling chemically reactive systems.
#
# Copyright © 2014-2021 Allan Leal
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
import pytest


def testActivityModelIonExchage():

    db = PhreeqcDatabase("phreeqc.dat")

    # Expected species: AlOHX2 AlX3 BaX2 CaX2 CdX2 CuX2 FeX2 KX LiX MgX2 MnX2 NH4X NaX PbX2 SrX2 ZnX2
    species = db.species().withAggregateState(AggregateState.IonExchange)

    # Create the aqueous mixture
    surface = IonExchangeSurface(species)

    # The numbers of exchanger's equivalents for exchange species
    ze = surface.ze()

    assert ze[0]  == 0 # X-
    assert ze[1]  == 2 # AlOHX2
    assert ze[2]  == 3 # AlX3
    assert ze[3]  == 2 # BaX2
    assert ze[4]  == 2 # CaX2
    assert ze[5]  == 2 # CdX2
    assert ze[6]  == 2 # CuX2
    assert ze[7]  == 2 # FeX2
    assert ze[8]  == 1 # KX
    assert ze[9]  == 1 # LiX
    assert ze[10] == 2 # MgX2
    assert ze[11] == 2 # MnX2
    assert ze[12] == 1 # NH4X
    assert ze[13] == 1 # NaX
    assert ze[14] == 2 # PbX2
    assert ze[15] == 2 # SrX2
    assert ze[16] == 2 # ZnX2

    # The numbers of exchanger's equivalents for exchange species
    idx_exchager = surface.indexExchanger()
    idx_exchange = surface.indicesExchange()

    expected_exchanger_index = 0 # exchanger is assumed to be on the first place
    expected_exchange_indices = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]

    assert idx_exchager == expected_exchanger_index
    assert idx_exchange == expected_exchange_indices

