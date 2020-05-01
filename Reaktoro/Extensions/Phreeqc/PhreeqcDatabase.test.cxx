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

// Catch includes
#include <catch2/catch.hpp>

// Reaktoro includes
#include <Reaktoro/Extensions/Phreeqc/PhreeqcDatabase.hpp>
using namespace Reaktoro;



#include <iostream>
#include <iomanip>
using namespace std;

/// Return the contents in the `phreeqc.dat` database as a string.
auto databaseContentsPhreeqc() -> String;

/// Return the contents in the `pitzer.dat` database as a string.
auto databaseContentsPitzer() -> String;

TEST_CASE("Testing PhreeqcDatabase", "[PhreeqcDatabase]")
{
    PhreeqcDatabase db(databaseContentsPhreeqc());

    // SECTION("Check some selected elements are present")
    // {
    //     REQUIRE_NOTHROW( db.elements().index("H")  );
    //     REQUIRE_NOTHROW( db.elements().index("C")  );
    //     REQUIRE_NOTHROW( db.elements().index("O")  );
    //     REQUIRE_NOTHROW( db.elements().index("Na") );
    //     REQUIRE_NOTHROW( db.elements().index("Cl") );
    //     REQUIRE_NOTHROW( db.elements().index("K")  );
    //     REQUIRE_NOTHROW( db.elements().index("Ca") );
    //     REQUIRE_NOTHROW( db.elements().index("Mg") );
    //     REQUIRE_NOTHROW( db.elements().index("Si") );
    //     REQUIRE_NOTHROW( db.elements().index("Fe") );
    // }

    // SECTION("Check some selected species are present")
    // {
    //     REQUIRE_NOTHROW( db.species().index("H2O")         );
    //     REQUIRE_NOTHROW( db.species().index("H+")          );
    //     REQUIRE_NOTHROW( db.species().index("CO3-2")       );
    //     REQUIRE_NOTHROW( db.species().index("Calcite")     );
    //     REQUIRE_NOTHROW( db.species().index("Quartz")      );
    //     REQUIRE_NOTHROW( db.species().index("CO2(g)")      );
    //     REQUIRE_NOTHROW( db.species().index("NaX")         );
    //     REQUIRE_NOTHROW( db.species().index("X-")          );
    //     REQUIRE_NOTHROW( db.species().index("Hfo_sOHCa+2") );
    // }



}

//=================================================================================================
// AUXILIARY FUNCTIONS
//=================================================================================================

auto databaseContentsPhreeqc() -> String
{
    return R"xyz(
# PHREEQC.DAT for calculating pressure dependence of reactions, with
#   molal volumina of aqueous species and of minerals, and
#   critical temperatures and pressures of gases used in Peng-Robinson's EOS.
# Details are given at the end of this file.

SOLUTION_MASTER_SPECIES
#
#element	species	alk	gfw_formula	element_gfw
#
H		H+	-1.0	H		1.008
H(0)		H2	0	H
H(1)		H+	-1.0	0
E		e-	0	0.0		0
O		H2O	0	O		16.0
O(0)		O2	0	O
O(-2)		H2O	0	0
Ca		Ca+2	0	Ca		40.08
Mg		Mg+2	0	Mg		24.312
Na		Na+	0	Na		22.9898
K		K+	0	K		39.102
Fe		Fe+2	0	Fe		55.847
Fe(+2)		Fe+2	0	Fe
Fe(+3)		Fe+3	-2.0	Fe
Mn		Mn+2	0	Mn		54.938
Mn(+2)		Mn+2	0	Mn
Mn(+3)		Mn+3	0	Mn
Al		Al+3	0	Al		26.9815
Ba		Ba+2	0	Ba		137.34
Sr		Sr+2	0	Sr		87.62
Si		H4SiO4	0	SiO2		28.0843
Cl		Cl-	0	Cl		35.453
C		CO3-2	2.0	HCO3		12.0111
C(+4)		CO3-2	2.0	HCO3
C(-4)		CH4	0	CH4
Alkalinity	CO3-2	1.0	Ca0.5(CO3)0.5	50.05
S		SO4-2	0	SO4		32.064
S(6)		SO4-2	0	SO4
S(-2)		HS-	1.0	S
N		NO3-	0	N		14.0067
N(+5)		NO3-	0	N
N(+3)		NO2-	0	N
N(0)		N2	0	N
N(-3)	        NH4+	0	N		14.0067
#Amm		AmmH+	0	AmmH		17.0
B		H3BO3	0	B		10.81
P		PO4-3	2.0	P		30.9738
F		F-	0	F		18.9984
Li		Li+	0	Li		6.939
Br		Br-	0	Br		79.904
Zn		Zn+2	0	Zn		65.37
Cd		Cd+2	0	Cd		112.4
Pb		Pb+2	0	Pb		207.19
Cu		Cu+2	0	Cu		63.546
Cu(+2)		Cu+2	0	Cu
Cu(+1)		Cu+1	0	Cu
# redox-uncoupled gases
Hdg		Hdg	0	Hdg		2.016 # H2 gas
Oxg		Oxg	0	Oxg		32 # O2 gas
Mtg		Mtg	0	Mtg		16.032 # CH4 gas
Sg		H2Sg	1.0	H2Sg		34.08
Ntg		Ntg	0	Ntg		28.0134 # N2 gas

SOLUTION_SPECIES
H+ = H+
	-gamma	9.0	0

	-dw	 9.31e-9
e- = e-
H2O = H2O
Ca+2 = Ca+2
	-gamma	5.0	0.1650
	-dw	 0.793e-9
	-Vm  -0.3456  -7.252  6.149  -2.479  1.239  5  1.60  -57.1  -6.12e-3  1 # ref. 1
Mg+2 = Mg+2
	-gamma	5.5	0.20
	-dw	 0.705e-9
	-Vm  -1.410  -8.6  11.13  -2.39  1.332  5.5  1.29  -32.9  -5.86e-3  1 # ref. 1
Na+ = Na+
	-gamma	4.0	 0.075
	-gamma	4.08 0.082 # halite solubility
	-dw	 1.33e-9
	-Vm   2.28  -4.38  -4.1  -0.586  0.09  4  0.3  52  -3.33e-3  0.566 # ref. 1
# for calculating densities (rho) when I > 3...
	# -Vm   2.28  -4.38  -4.1  -0.586  0.09  4  0.3  52  -3.33e-3  0.45
K+ = K+
	-gamma	3.5	0.015
	-dw	 1.96e-9
	-Vm  3.322  -1.473  6.534  -2.712  9.06e-2  3.5  0  29.7  0  1 # ref. 1
Fe+2 = Fe+2
	-gamma	6.0	0
	-dw	 0.719e-9

	-Vm  -0.3255  -9.687  1.536  -2.379  0.3033  6  -4.21e-2  39.7  0  1 # ref. 1
Mn+2 = Mn+2
	-gamma	6.0	0
	-dw	 0.688e-9

	-Vm  -1.10  -8.03  4.08  -2.45  1.4  6  8.07  0  -1.51e-2  0.118 # ref. 2
Al+3 = Al+3
	-gamma	9.0	0
	-dw	 0.559e-9
	-Vm   -2.28  -17.1  10.9  -2.07  2.87  9  0  0  5.5e-3  1 # ref. 2 and Barta and Hepler, 1986, Can. J.C. 64, 353.
Ba+2 = Ba+2
	-gamma  5.0  0
	-gamma	4.0  0.153 # Barite solubility
	-dw 0.848e-9
	-Vm  2.063  -10.06  1.9534  -2.36  0.4218  5  1.58  -12.03  -8.35e-3  1 # ref. 1
Sr+2 = Sr+2
	-gamma	5.260	0.121
	-dw	 0.794e-9
	-Vm  -1.57e-2  -10.15  10.18  -2.36  0.860  5.26  0.859  -27.0  -4.1e-3  1.97 # ref. 1
H4SiO4 = H4SiO4
	-dw	 1.10e-9
	-Vm  10.5  1.7  20  -2.7  0.1291 # supcrt + 2*H2O in a1
Cl- = Cl-
	-gamma	3.5	  0.015
	-gamma	3.63  0.017 # cf. pitzer.dat
	-dw	 2.03e-9
	-Vm  4.465  4.801  4.325  -2.847  1.748  0  -0.331  20.16  0  1 # ref. 1
CO3-2 = CO3-2
	-gamma	5.4	0
	-dw	 0.955e-9
	-Vm  5.95  0  0  -5.67  6.85  0  1.37  106  -0.0343  1 # ref. 1
SO4-2 = SO4-2
	-gamma	5.0	-0.04
	-dw	 1.07e-9
	-Vm  8.0  2.3  -46.04  6.245  3.82  0  0  0  0  1 # ref. 1
NO3- = NO3-
	-gamma	3.0	0
	-dw	 1.9e-9
	-Vm  6.32  6.78  0  -3.06  0.346  0  0.93  0  -0.012  1 # ref. 1
#AmmH+ = AmmH+
#	-gamma	2.5	0
#	-dw	 1.98e-9
#	-Vm  4.837  2.345  5.522  -2.88 1.096  3  -1.456  75.0  7.17e-3  1 # ref. 1
H3BO3 = H3BO3
	-dw	1.1e-9
	-Vm 7.0643  8.8547  3.5844  -3.1451 -.2000  # supcrt
PO4-3 = PO4-3
	-gamma	4.0	0
	-dw	 0.612e-9
	-Vm   1.24  -9.07  9.31  -2.4  5.61  0  0  0  -1.41e-2  1 # ref. 2
F- = F-
	-gamma	3.5	0
	-dw	 1.46e-9
	-Vm   0.928  1.36  6.27  -2.84  1.84  0  0  -0.318  0  1 # ref. 2
Li+ = Li+
	-gamma	6.0	0
	-dw	 1.03e-9
	-Vm  -0.419  -0.069  13.16  -2.78  0.416  0  0.296  -12.4  -2.74e-3  1.26 # ref. 2 and Ellis, 1968, J. Chem. Soc. A, 1138
Br- = Br-
	-gamma	3.0	0
	-dw	 2.01e-9
	-Vm   6.72  2.85  4.21  -3.14  1.38  0  -9.56e-2  7.08  -1.56e-3  1 # ref. 2
Zn+2 = Zn+2
	-gamma	5.0	0
	-dw	 0.715e-9
	-Vm  -1.96  -10.4  14.3  -2.35  1.46  5  -1.43  24  1.67e-2  1.11 # ref. 2
Cd+2 = Cd+2
	-dw	 0.717e-9
	-Vm   1.63  -10.7  1.01  -2.34  1.47  5  0  0  0  1 # ref. 2
Pb+2 = Pb+2
	-dw	 0.945e-9
	-Vm  -.0051  -7.7939  8.8134  -2.4568  1.0788 4.5 # supcrt
Cu+2 = Cu+2
	-gamma	6.0	0
	-dw	 0.733e-9
	-Vm   -1.13  -10.5  7.29  -2.35  1.61  6  9.78e-2  0  3.42e-3  1 # ref. 2
# redox-uncoupled gases
Hdg = Hdg # H2
	-dw	 5.13e-9
	-Vm 6.52  0.78  0.12 # supcrt
Oxg = Oxg # O2
	-dw	 2.35e-9
	-Vm  5.7889  6.3536  3.2528  -3.0417  -0.3943 # supcrt
Mtg = Mtg # CH4
	-dw	 1.85e-9

	-Vm 7.7 # CH4 solubility, 25-100C, 1-700atm
Ntg = Ntg # N2
	-dw	 1.96e-9
	-Vm 7 # Pray et al., 1952, IEC 44. 1146
H2Sg = H2Sg # H2S
	-dw	 2.1e-9
	-Vm  7.81  2.96  -0.46 # supcrt
# aqueous species
H2O = OH- + H+
	-analytic  293.29227  0.1360833  -10576.913  -123.73158  0  -6.996455e-5
	-gamma	3.5	0
	-dw	 5.27e-9
	-Vm  -9.66  28.5  80.0 -22.9 1.89 0 1.09 0 0 1 # ref. 1
2 H2O = O2 + 4 H+ + 4 e-
	-log_k	-86.08
	-delta_h 134.79 kcal
	-dw	 2.35e-9
	-Vm  5.7889  6.3536  3.2528  -3.0417  -0.3943 # supcrt
2 H+ + 2 e- = H2
	-log_k	-3.15
	-delta_h -1.759 kcal
	-dw	 5.13e-9
	-Vm 6.52  0.78  0.12 # supcrt
CO3-2 + H+ = HCO3-
	-log_k	10.329
	-delta_h -3.561	kcal
	-analytic	107.8871	0.03252849	-5151.79	-38.92561	563713.9
	-gamma	5.4	0
	-dw	 1.18e-9
	-Vm  8.472  0  -11.5  0  1.56  0  0  146  3.16e-3  1 # ref. 1
CO3-2 + 2 H+ = CO2 + H2O
	-log_k	16.681
	-delta_h -5.738	kcal
	-analytic	464.1965	0.09344813	-26986.16	-165.75951	2248628.9
	-dw	 1.92e-9
	-Vm   7.29  0.92  2.07  -1.23  -1.60 # ref. 1 + McBride et al. 2015, JCED 60, 171
2CO2 = (CO2)2 # activity correction for CO2 solubility at high P, T
	-log_k -1.8
	-analytical_expression  8.68  -0.0103  -2190
	-Vm   14.58  1.84  4.14  -2.46  -3.20
CO3-2 + 10 H+ + 8 e- = CH4 + 3 H2O
	-log_k	41.071
	-delta_h -61.039 kcal
	-dw	 1.85e-9
	-Vm   9.01  -1.11  0  -1.85  -1.50 # ref. 1 + Hnedkovsky et al., 1996, JCT 28, 125
SO4-2 + H+ = HSO4-
	-log_k	1.988
	-delta_h 3.85	kcal
	-analytic	-56.889	0.006473	2307.9	19.8858
	-dw	 1.33e-9
	-Vm 8.2 9.2590  2.1108  -3.1618 1.1748  0 -0.3 15 0 1 # ref. 1
HS- = S-2 + H+
	-log_k	-12.918
	-delta_h 12.1	kcal
	-gamma	5.0	0
	-dw	 0.731e-9
SO4-2 + 9 H+ + 8 e- = HS- + 4 H2O
	-log_k	33.65
	-delta_h -60.140 kcal
	-gamma	3.5	0
	-dw	 1.73e-9
	-Vm  5.0119  4.9799  3.4765  -2.9849  1.4410 # supcrt
HS- + H+ = H2S
	-log_k	6.994
	-delta_h -5.30	kcal
	-analytical  -11.17  0.02386  3279.0
	-dw	 2.1e-9
	-Vm  7.81  2.96  -0.46 # supcrt
H2Sg = HSg- + H+
	-log_k	-6.994
	-delta_h 5.30	kcal
	-analytical  11.17  -0.02386  -3279.0
	-dw	 2.1e-9
	-Vm  5.0119  4.9799  3.4765  -2.9849  1.4410 # supcrt
NO3- + 2 H+ + 2 e- = NO2- + H2O
	-log_k	28.570
	-delta_h -43.760 kcal
	-gamma	3.0	0
	-dw	 1.91e-9
	-Vm  5.5864  5.8590  3.4472  -3.0212  1.1847 # supcrt
2 NO3- + 12 H+ + 10 e- = N2 + 6 H2O
	-log_k	207.08
	-delta_h -312.130	kcal
	-dw	 1.96e-9
	-Vm 7 # Pray et al., 1952, IEC 44. 1146
NO3- + 10 H+ + 8 e- = NH4+ + 3 H2O
	-log_k	119.077
	-delta_h -187.055	kcal
	-gamma	2.5	0
	-dw	 1.98e-9
	-Vm  4.837  2.345  5.522  -2.88 1.096  3  -1.456  75.0  7.17e-3  1 # ref. 1

#AmmH+ = Amm + H+
NH4+ = NH3 + H+
	-log_k	-9.252
	-delta_h 12.48	kcal
	-analytic  0.6322  -0.001225  -2835.76
	-dw	 2.28e-9
	-Vm   6.69  2.8  3.58  -2.88  1.43 # ref. 2
#NO3- + 10 H+ + 8 e- = AmmH+ + 3 H2O
#	-log_k	119.077
#	-delta_h -187.055	kcal
#	-gamma	2.5	0
#	-Vm  4.837  2.345  5.522  -2.88 1.096  3  -1.456  75.0  7.17e-3  1 # ref. 1

#AmmH+ + SO4-2 = AmmHSO4-
NH4+ + SO4-2 = NH4SO4-
	-log_k	1.11
	-Vm   14.0  0  -35.2  0  0  0  12.3  0  -0.141  1 # ref. 2
H3BO3 = H2BO3- + H+
	-log_k	-9.24
	-delta_h 3.224	kcal
H3BO3 + F- = BF(OH)3-
	-log_k	-0.4
	-delta_h 1.850	kcal
H3BO3 + 2 F- + H+ = BF2(OH)2- + H2O
	-log_k	7.63
	-delta_h 1.618	kcal
H3BO3 + 2 H+ + 3 F- = BF3OH- + 2 H2O
	-log_k	13.67
	-delta_h -1.614	kcal
H3BO3 + 3 H+ + 4 F- = BF4- + 3 H2O
	-log_k	20.28
	-delta_h -1.846	kcal
PO4-3 + H+ = HPO4-2
	-log_k	12.346
	-delta_h -3.530	kcal
	-gamma	5.0	0
	-dw	0.69e-9
	-Vm   3.52  1.09  8.39  -2.82  3.34  0  0  0  0  1 # ref. 2
PO4-3 + 2 H+ = H2PO4-
	-log_k	19.553
	-delta_h -4.520	kcal
	-gamma	5.4	0
	-dw	 0.846e-9
	-Vm   5.58  8.06  12.2  -3.11  1.3  0  0  0  1.62e-2  1 # ref. 2
PO4-3 + 3H+ = H3PO4
	log_k	21.721 # log_k and delta_h from minteq.v4.dat, NIST46.3
	delta_h	-10.1	kJ
	-Vm   7.47  12.4  6.29  -3.29  0 # ref. 2
H+ + F- = HF
	-log_k	3.18
	-delta_h 3.18	kcal
	-analytic	-2.033	0.012645	429.01
	-Vm  3.4753  .7042  5.4732  -2.8081  -.0007 # supcrt
H+ + 2 F- = HF2-
	-log_k	3.76
	-delta_h 4.550	kcal
	-Vm  5.2263  4.9797  3.7928  -2.9849  1.2934 # supcrt
Ca+2 + H2O = CaOH+ + H+
	-log_k	-12.78
Ca+2 + CO3-2 = CaCO3
	-log_k	3.224
	-delta_h 3.545	kcal
	-analytic	-1228.732	-0.299440	35512.75	485.818
	-dw 4.46e-10	# complexes: calc'd with the Pikal formula
	-Vm  -.2430  -8.3748  9.0417  -2.4328  -.0300 # supcrt
Ca+2 + CO3-2 + H+ = CaHCO3+
	-log_k	11.435
	-delta_h -0.871	kcal
	-analytic	1317.0071	0.34546894	-39916.84	-517.70761	563713.9
	-gamma	6.0	0
	-dw 5.06e-10
	-Vm  3.1911  .0104  5.7459  -2.7794  .3084 5.4 # supcrt
Ca+2 + SO4-2 = CaSO4
	-log_k	2.25
	-delta_h 1.325	kcal
	-dw 4.71e-10
	-Vm  2.7910  -.9666  6.1300  -2.7390  -.0010 # supcrt
Ca+2 + HSO4- = CaHSO4+
	-log_k	  1.08
Ca+2 + PO4-3 = CaPO4-
	-log_k	6.459
	-delta_h 3.10	kcal
	-gamma  5.4  0.0
Ca+2 + HPO4-2 = CaHPO4
	-log_k	2.739
	-delta_h 3.3 kcal
Ca+2 + H2PO4- = CaH2PO4+
	-log_k	1.408
	-delta_h 3.4 kcal
	-gamma  5.4  0.0
# Ca+2 + F- = CaF+
	# -log_k	0.94
	# -delta_h 4.120	kcal
	# -gamma  5.5  0.0
	# -Vm  .9846  -5.3773  7.8635  -2.5567  .6911 5.5 # supcrt
Mg+2 + H2O = MgOH+ + H+
	-log_k	-11.44
	-delta_h 15.952 kcal
	-gamma	6.5	0
Mg+2 + CO3-2 = MgCO3
	-log_k	2.98
	-delta_h 2.713	kcal
	-analytic	0.9910	0.00667
	-dw 4.21e-10
	-Vm  -.5837  -9.2067  9.3687  -2.3984  -.0300 # supcrt
Mg+2 + H+ + CO3-2 = MgHCO3+
	-log_k	11.399
	-delta_h -2.771	kcal
	-analytic	48.6721	0.03252849	-2614.335	-18.00263	563713.9
	-gamma	4.0	0
	-dw 4.78e-10
	-Vm  2.7171  -1.1469  6.2008  -2.7316  .5985 4 # supcrt
Mg+2 + SO4-2 = MgSO4
	-log_k	2.37
	-delta_h 4.550	kcal
	-dw 4.45e-10
	-Vm  2.4  -0.97  6.1  -2.74  # est'd
Mg+2 + PO4-3 = MgPO4-
	-log_k	6.589
	-delta_h 3.10	kcal
	-gamma	5.4	0
Mg+2 + HPO4-2 = MgHPO4
	-log_k	2.87
	-delta_h 3.3 kcal
Mg+2 + H2PO4- = MgH2PO4+
	-log_k	1.513
	-delta_h 3.4 kcal
	-gamma	5.4	0
Mg+2 + F- = MgF+
	-log_k	1.82
	-delta_h 3.20	kcal
	-gamma	4.5	0
	-Vm  .6494  -6.1958  8.1852  -2.5229  .9706 4.5 # supcrt
Na+ + OH- = NaOH
	-log_k	-10 # remove this complex
Na+ + CO3-2 = NaCO3-
	-log_k	1.27
	-delta_h 8.91 kcal
	-dw 5.85e-10
	-Vm  3.89  -8.23e-4  20  -9.44  3.02  9.05e-3  3.07  0  0.0233  1 # ref. 1
Na+ + HCO3- = NaHCO3
	-log_k  -0.25
	-delta_h  -1 kcal
	-dw 6.73e-10
	-Vm  0.431 # ref. 1
Na+ + SO4-2 = NaSO4-
	-log_k	0.7
	-delta_h 1.120	kcal
	-gamma	5.4	0
	-dw 6.18e-10
	-Vm  1e-5  16.4  -0.0678  -1.05  4.14  0  6.86  0  0.0242  0.53 # ref. 1
Na+ + HPO4-2 = NaHPO4-
	-log_k	0.29
	-gamma	5.4	0
	-Vm    5.2  8.1  13  -3  0.9  0  0  1.62e-2  1 # ref. 2
Na+ + F- = NaF
	-log_k	-0.24
	-Vm  2.7483  -1.0708  6.1709  -2.7347  -.030 # supcrt
K+ + SO4-2 = KSO4-
	-log_k	0.85
	-delta_h 2.250	kcal
	-analytical  3.106  0.0  -673.6
	-gamma	5.4	0
	-dw 7.46e-10
	-Vm  6.8  7.06 3.0   -2.07  1.1  0  0  0  0  1 # ref. 1
K+ + HPO4-2 = KHPO4-
	-log_k	0.29
	-gamma	5.4	0
	-Vm   5.4  8.1  19  -3.1  0.7  0  0  0  1.62e-2  1 # ref. 2
Fe+2 + H2O = FeOH+ + H+
	-log_k	-9.5
	-delta_h 13.20	kcal
	-gamma	5.0	0
Fe+2 + 3H2O = Fe(OH)3- + 3H+
	-log_k -31.0
	-delta_h 30.3 kcal
	-gamma  5.0 0
Fe+2 + Cl- = FeCl+
	-log_k	0.14
Fe+2 + CO3-2 = FeCO3
	-log_k	4.38
Fe+2 + HCO3- = FeHCO3+
	-log_k	2.0
Fe+2 + SO4-2 = FeSO4
	-log_k	2.25
	-delta_h 3.230	kcal
	-Vm   -13  0  123 # ref. 2
Fe+2 + HSO4- = FeHSO4+
	-log_k	1.08
Fe+2 + 2HS- = Fe(HS)2
	-log_k	8.95
Fe+2 + 3HS- = Fe(HS)3-
	-log_k	10.987
Fe+2 + HPO4-2 = FeHPO4
	-log_k	3.6
Fe+2 + H2PO4- = FeH2PO4+
	-log_k	2.7
	-gamma	5.4	0
Fe+2 + F- = FeF+
	-log_k	1.0
Fe+2 = Fe+3 + e-
	-log_k	-13.02
	-delta_h 9.680	kcal
	-gamma	9.0	0
Fe+3 + H2O = FeOH+2 + H+
	-log_k	-2.19
	-delta_h 10.4	kcal
	-gamma	5.0	0
Fe+3 + 2 H2O = Fe(OH)2+ + 2 H+
	-log_k	-5.67
	-delta_h 17.1	kcal
	-gamma	5.4	0
Fe+3 + 3 H2O = Fe(OH)3 + 3 H+
	-log_k	-12.56
	-delta_h 24.8	kcal
Fe+3 + 4 H2O = Fe(OH)4- + 4 H+
	-log_k	-21.6
	-delta_h 31.9	kcal
	-gamma	5.4	0
Fe+2 + 2H2O = Fe(OH)2 + 2H+
	-log_k  -20.57
	-delta_h 28.565 kcal
2 Fe+3 + 2 H2O = Fe2(OH)2+4 + 2 H+
	-log_k	-2.95
	-delta_h 13.5	kcal
3 Fe+3 + 4 H2O = Fe3(OH)4+5 + 4 H+
	-log_k	-6.3
	-delta_h 14.3	kcal
Fe+3 + Cl- = FeCl+2
	-log_k	1.48
	-delta_h 5.6	kcal
	-gamma	5.0	0
Fe+3 + 2 Cl- = FeCl2+
	-log_k	2.13
	-gamma	5.0	0
Fe+3 + 3 Cl- = FeCl3
	-log_k	1.13
Fe+3 + SO4-2 = FeSO4+
	-log_k	4.04
	-delta_h 3.91	kcal
	-gamma	5.0	0
Fe+3 + HSO4- = FeHSO4+2
	-log_k	2.48
Fe+3 + 2 SO4-2 = Fe(SO4)2-
	-log_k	5.38
	-delta_h 4.60	kcal
Fe+3 + HPO4-2 = FeHPO4+
	-log_k	5.43
	-delta_h 5.76	kcal
	-gamma	5.0	0
Fe+3 + H2PO4- = FeH2PO4+2
	-log_k	5.43
	-gamma	5.4	0
Fe+3 + F- = FeF+2
	-log_k	6.2
	-delta_h 2.7	kcal
	-gamma	5.0	0
Fe+3 + 2 F- = FeF2+
	-log_k	10.8
	-delta_h 4.8	kcal
	-gamma	5.0	0
Fe+3 + 3 F- = FeF3
	-log_k	14.0
	-delta_h 5.4	kcal
Mn+2 + H2O = MnOH+ + H+
	-log_k	-10.59
	-delta_h 14.40	kcal
	-gamma	5.0	0
Mn+2 + 3H2O = Mn(OH)3- + 3H+
	-log_k  -34.8
	-gamma	5.0	0
Mn+2 + Cl- = MnCl+
	-log_k	0.61
	-gamma	5.0	0
	-Vm   7.25  -1.08  -25.8  -2.73  3.99  5  0  0  0  1 # ref. 2
Mn+2 + 2 Cl- = MnCl2
	-log_k	0.25
	-Vm   1e-5  0  144 # ref. 2
Mn+2 + 3 Cl- = MnCl3-
	-log_k	-0.31
	-gamma	5.0	0
	-Vm   11.8  0  0  0  2.4  0  0  0  3.6e-2  1 # ref. 2
Mn+2 + CO3-2 = MnCO3
	-log_k	4.9
Mn+2 + HCO3- = MnHCO3+
	-log_k	1.95
	-gamma	5.0	0
Mn+2 + SO4-2 = MnSO4
	-log_k	2.25
	-delta_h 3.370	kcal
	-Vm  -1.31  -1.83  62.3  -2.7 # ref. 2
Mn+2 + 2 NO3- = Mn(NO3)2
	-log_k	0.6
	-delta_h -0.396	kcal
	-Vm  6.16  0  29.4  0  0.9 # ref. 2
Mn+2 + F- = MnF+
	-log_k	0.84
	-gamma	5.0	0
Mn+2 = Mn+3 + e-
	-log_k	-25.51
	-delta_h 25.80	kcal
	-gamma	9.0	0
Al+3 + H2O = AlOH+2 + H+
	-log_k	-5.0
	-delta_h 11.49	kcal
	-analytic	-38.253	0.0	-656.27	14.327
	-gamma	5.4	0
	-Vm   -1.46  -11.4  10.2  -2.31  1.67  5.4  0  0  0  1  # ref. 2 and Barta and Hepler, 1986, Can. J. Chem. 64, 353.
Al+3 + 2 H2O = Al(OH)2+ + 2 H+
	-log_k	-10.1
	-delta_h 26.90	kcal
	-gamma	5.4	0
	-analytic	88.50	0.0	-9391.6	-27.121
Al+3 + 3 H2O = Al(OH)3 + 3 H+
	-log_k	-16.9
	-delta_h 39.89	kcal
	-analytic	226.374	0.0	-18247.8	-73.597
Al+3 + 4 H2O = Al(OH)4- + 4 H+
	-log_k	-22.7
	-delta_h 42.30	kcal
	-analytic	51.578	0.0	-11168.9	-14.865
	-gamma	4.5	0
Al+3 + SO4-2 = AlSO4+
	-log_k	3.5
	-delta_h 2.29 kcal
	-gamma	4.5	0
Al+3 + 2SO4-2 = Al(SO4)2-
	-log_k	5.0
	-delta_h 3.11 kcal
	-gamma	4.5	0
Al+3 + HSO4- = AlHSO4+2
	-log_k	0.46
Al+3 + F- = AlF+2
	-log_k	7.0
	-delta_h 1.060	kcal
	-gamma	5.4	0
Al+3 + 2 F- = AlF2+
	-log_k	12.7
	-delta_h 1.980	kcal
	-gamma	5.4	0
Al+3 + 3 F- = AlF3
	-log_k	16.8
	-delta_h 2.160	kcal
Al+3 + 4 F- = AlF4-
	-log_k	19.4
	-delta_h 2.20	kcal
	-gamma	4.5	0
# Al+3 + 5 F- = AlF5-2
	# log_k	20.6
	# delta_h 1.840	kcal
# Al+3 + 6 F- = AlF6-3
	# log_k	20.6
	# delta_h -1.670	kcal
H4SiO4 = H3SiO4- + H+
	-log_k	-9.83
	-delta_h 6.12	kcal
	-analytic	-302.3724	-0.050698	15669.69	108.18466	-1119669.0
	-gamma	4	0
	-Vm  7.94  1.0881  5.3224  -2.8240  1.4767 # supcrt + H2O in a1
H4SiO4 = H2SiO4-2 + 2 H+
	-log_k	-23.0
	-delta_h 17.6	kcal
	-analytic	-294.0184	-0.072650	11204.49	108.18466	-1119669.0
	-gamma	5.4	0
H4SiO4 + 4 H+ + 6 F- = SiF6-2 + 4 H2O
	-log_k	30.18
	-delta_h -16.260	kcal
	-gamma	5.0	0
	-Vm  8.5311  13.0492  .6211  -3.3185  2.7716 # supcrt
Ba+2 + H2O = BaOH+ + H+
	-log_k	-13.47
	-gamma	5.0	0
Ba+2 + CO3-2 = BaCO3
	-log_k	2.71
	-delta_h 3.55	kcal
	-analytic	0.113	0.008721
	-Vm  .2907  -7.0717  8.5295  -2.4867  -.0300 # supcrt
Ba+2 + HCO3- = BaHCO3+
	-log_k	0.982
	-delta_h 5.56 kcal
	-analytic	-3.0938	0.013669
Ba+2 + SO4-2 = BaSO4
	-log_k	2.7
Sr+2 + H2O = SrOH+ + H+
	-log_k	-13.29
	-gamma	5.0	0
Sr+2 + CO3-2 + H+ = SrHCO3+
	-log_k	11.509
	-delta_h 2.489	kcal
	-analytic	104.6391	0.04739549	-5151.79	-38.92561	563713.9
	-gamma	5.4	0
Sr+2 + CO3-2 = SrCO3
	-log_k	2.81
	-delta_h 5.22	kcal
	-analytic	-1.019	0.012826
	-Vm  -.1787  -8.2177  8.9799  -2.4393  -.0300 # supcrt
Sr+2 + SO4-2 = SrSO4
	-log_k	2.29
	-delta_h 2.08	kcal
	-Vm  6.7910  -.9666  6.1300  -2.7390  -.0010 # celestite solubility
Li+ + SO4-2 = LiSO4-
	-log_k	0.64
	-gamma	5.0	0
Cu+2 + e- = Cu+
	-log_k	2.72
	-delta_h 1.65	kcal
	-gamma	2.5	0
Cu+ + 2Cl- = CuCl2-
	-log_k	  5.50
	-delta_h -0.42 kcal
	-gamma  4.0  0
Cu+ + 3Cl- = CuCl3-2
	-log_k	  5.70
	-delta_h 0.26 kcal
	-gamma  5.0  0.0
Cu+2 + CO3-2 = CuCO3
	-log_k	  6.73
Cu+2 + 2CO3-2 = Cu(CO3)2-2
	-log_k	  9.83
Cu+2 + HCO3- = CuHCO3+
	-log_k	  2.7
Cu+2 + Cl- = CuCl+
	-log_k	  0.43
	-delta_h 8.65 kcal
	-gamma  4.0  0
	-Vm   -4.19  0  30.4  0  0  4  0  0  1.94e-2  1 # ref. 2
Cu+2 + 2Cl- = CuCl2
	-log_k	  0.16
	-delta_h 10.56 kcal
	-Vm   26.8  0  -136 # ref. 2
Cu+2 + 3Cl- = CuCl3-
	-log_k	  -2.29
	-delta_h 13.69 kcal
	-gamma  4.0  0
Cu+2 + 4Cl- = CuCl4-2
	-log_k	  -4.59
	-delta_h 17.78 kcal
	-gamma  5.0  0
Cu+2 + F- = CuF+
	-log_k	  1.26
	-delta_h 1.62 kcal
Cu+2 + H2O = CuOH+ + H+
	-log_k	-8.0
	-gamma	4.0	0
Cu+2 + 2 H2O = Cu(OH)2 + 2 H+
	-log_k	-13.68
Cu+2 + 3 H2O = Cu(OH)3- + 3 H+
	-log_k	-26.9
Cu+2 + 4 H2O = Cu(OH)4-2 + 4 H+
	-log_k	-39.6
2Cu+2 + 2H2O = Cu2(OH)2+2 + 2H+
	-log_k  -10.359
	-delta_h 17.539 kcal
	-analytical  2.497  0.0  -3833.0
Cu+2 + SO4-2 = CuSO4
	-log_k	2.31
	-delta_h 1.220	kcal
	-Vm   5.21  0  -14.6 # ref. 2
Cu+2 + 3HS- = Cu(HS)3-
	-log_k  25.9
Zn+2 + H2O = ZnOH+ + H+
	-log_k	-8.96
	-delta_h 13.4 kcal
Zn+2 + 2 H2O = Zn(OH)2 + 2 H+
	-log_k	-16.9
Zn+2 + 3 H2O = Zn(OH)3- + 3 H+
	-log_k	-28.4
Zn+2 + 4 H2O = Zn(OH)4-2 + 4 H+
	-log_k	-41.2
Zn+2 + Cl- = ZnCl+
	-log_k	0.43
	-delta_h 7.79 kcal
	-gamma  4.0  0
	-Vm   14.8  -3.91  -105.7  -2.62  0.203  4  0  0  -5.05e-2  1 # ref. 2
Zn+2 + 2 Cl- = ZnCl2
	-log_k	0.45
	-delta_h 8.5 kcal
	-Vm   -10.1  4.57  241  -2.97  -1e-3 # ref. 2
Zn+2 + 3Cl- = ZnCl3-
	-log_k	0.5
	-delta_h 9.56 kcal
	-gamma  4.0  0
	-Vm   0.772  15.5  -0.349  -3.42  1.25  0  -7.77  0  0  1 # ref. 2
Zn+2 + 4Cl- = ZnCl4-2
	-log_k	0.2
	-delta_h 10.96 kcal
	-gamma  5.0  0
	-Vm   28.42  28  -5.26  -3.94  2.67  0  0  0  4.62e-2 1 # ref. 2
Zn+2 + H2O + Cl- = ZnOHCl + H+
	-log_k  -7.48
Zn+2 + 2HS- = Zn(HS)2
	-log_k  14.94
Zn+2 + 3HS- = Zn(HS)3-
	-log_k  16.1
Zn+2 + CO3-2 = ZnCO3
	-log_k	5.3
Zn+2 + 2CO3-2 = Zn(CO3)2-2
	-log_k	9.63
Zn+2 + HCO3- = ZnHCO3+
	-log_k	2.1
Zn+2 + SO4-2 = ZnSO4
	-log_k	2.37
	-delta_h 1.36 kcal
	-Vm   2.51  0  18.8 # ref. 2
Zn+2 + 2SO4-2 = Zn(SO4)2-2
	-log_k	3.28
	-Vm    10.9  0  -98.7  0  0  0  24  0 -0.236  1 # ref. 2
Zn+2 + Br- = ZnBr+
	-log_k  -0.58
Zn+2 + 2Br- = ZnBr2
	-log_k  -0.98
Zn+2 + F- = ZnF+
	-log_k  1.15
	-delta_h 2.22 kcal
Cd+2 + H2O = CdOH+ + H+
	-log_k	-10.08
	-delta_h 13.1 kcal
Cd+2 + 2 H2O = Cd(OH)2 + 2 H+
	-log_k	-20.35
Cd+2 + 3 H2O = Cd(OH)3- + 3 H+
	-log_k	-33.3
Cd+2 + 4 H2O = Cd(OH)4-2 + 4 H+
	-log_k	-47.35
2Cd+2 + H2O = Cd2OH+3 + H+
	-log_k  -9.39
	-delta_h 10.9 kcal
Cd+2 + H2O + Cl- = CdOHCl + H+
	-log_k  -7.404
	-delta_h 4.355 kcal
Cd+2 + NO3- = CdNO3+
	-log_k  0.4
	-delta_h -5.2 kcal
	-Vm   5.95  0  -1.11  0  2.67  7  0  0  1.53e-2  1 # ref. 2
Cd+2 + Cl- = CdCl+
	-log_k	1.98
	-delta_h 0.59 kcal
	-Vm   5.69  0  -30.2  0  0  6  0  0  0.112  1 # ref. 2
Cd+2 + 2 Cl- = CdCl2
	-log_k	2.6
	-delta_h 1.24 kcal
	-Vm   5.53 # ref. 2
Cd+2 + 3 Cl- = CdCl3-
	-log_k	2.4
	-delta_h 3.9 kcal
	-Vm   4.6  0  83.9  0  0  0  0  0  0  1 # ref. 2
Cd+2 + CO3-2 = CdCO3
	-log_k	2.9
Cd+2 + 2CO3-2 = Cd(CO3)2-2
	-log_k	6.4
Cd+2 + HCO3- = CdHCO3+
	-log_k	1.5
Cd+2 + SO4-2 = CdSO4
	-log_k	2.46
	-delta_h 1.08 kcal
	-Vm   10.4  0  57.9 # ref. 2
Cd+2 + 2SO4-2 = Cd(SO4)2-2
	-log_k	3.5
	-Vm   -6.29  0  -93  0  9.5  7  0  0  0  1 # ref. 2
Cd+2 + Br- = CdBr+
	-log_k  2.17
	-delta_h -0.81 kcal
Cd+2 + 2Br- = CdBr2
	-log_k  2.9
Cd+2 + F- = CdF+
	-log_k  1.1
Cd+2 + 2F- = CdF2
	-log_k  1.5
Cd+2 + HS- = CdHS+
	-log_k  10.17
Cd+2 + 2HS- = Cd(HS)2
	-log_k  16.53
Cd+2 + 3HS- = Cd(HS)3-
	-log_k  18.71
Cd+2 + 4HS- = Cd(HS)4-2
	-log_k  20.9
Pb+2 + H2O = PbOH+ + H+
	-log_k	-7.71
Pb+2 + 2 H2O = Pb(OH)2 + 2 H+
	-log_k	-17.12
Pb+2 + 3 H2O = Pb(OH)3- + 3 H+
	-log_k	-28.06
Pb+2 + 4 H2O = Pb(OH)4-2 + 4 H+
	-log_k	-39.7
2 Pb+2 + H2O = Pb2OH+3 + H+
	-log_k	-6.36
Pb+2 + Cl- = PbCl+
	-log_k	1.6
	-delta_h 4.38 kcal
	-Vm  2.8934  -.7165  6.0316  -2.7494  .1281 6 # supcrt
Pb+2 + 2 Cl- = PbCl2
	-log_k	1.8
	-delta_h 1.08 kcal
	-Vm  6.5402  8.1879  2.5318  -3.1175  -.0300 # supcrt
Pb+2 + 3 Cl- = PbCl3-
	-log_k	1.7
	-delta_h 2.17 kcal
	-Vm  11.0396  19.1743  -1.7863  -3.5717  .7356 # supcrt
Pb+2 + 4 Cl- = PbCl4-2
	-log_k	1.38
	-delta_h 3.53 kcal
	-Vm  16.4150  32.2997  -6.9452  -4.1143  2.3118 # supcrt
Pb+2 + CO3-2 = PbCO3
	-log_k	7.24
Pb+2 + 2 CO3-2 = Pb(CO3)2-2
	-log_k	10.64
Pb+2 + HCO3- = PbHCO3+
	-log_k	2.9
Pb+2 + SO4-2 = PbSO4
	-log_k	2.75
Pb+2 + 2 SO4-2 = Pb(SO4)2-2
	-log_k	3.47
Pb+2 + 2HS- = Pb(HS)2
	-log_k  15.27
Pb+2 + 3HS- = Pb(HS)3-
	-log_k  16.57
3Pb+2 + 4H2O = Pb3(OH)4+2 + 4H+
	-log_k  -23.88
	-delta_h 26.5 kcal
Pb+2 + NO3- = PbNO3+
	-log_k	1.17
Pb+2 + Br- = PbBr+
	-log_k  1.77
	-delta_h 2.88 kcal
Pb+2 + 2Br- = PbBr2
	-log_k  1.44
Pb+2 + F- = PbF+
	-log_k  1.25
Pb+2 + 2F- = PbF2
	-log_k  2.56
Pb+2 + 3F- = PbF3-
	-log_k  3.42
Pb+2 + 4F- = PbF4-2
	-log_k  3.1

PHASES
Calcite
	CaCO3 = CO3-2 + Ca+2
	-log_k	-8.48
	-delta_h -2.297 kcal
	-analytic	-171.9065	-0.077993	2839.319	71.595
	-Vm 36.9 cm3/mol # MW (100.09 g/mol) / rho (2.71 g/cm3)
Aragonite
	CaCO3 = CO3-2 + Ca+2
	-log_k	-8.336
	-delta_h -2.589 kcal
	-analytic	-171.9773	-0.077993	2903.293	71.595
	-Vm 34.04
Dolomite
	CaMg(CO3)2 = Ca+2 + Mg+2 + 2 CO3-2
	-log_k	-17.09
	-delta_h  -9.436 kcal
	-Vm 64.5
Siderite
	FeCO3 = Fe+2 + CO3-2
	-log_k	-10.89
	-delta_h  -2.480 kcal
	-Vm 29.2
Rhodochrosite
	MnCO3 = Mn+2 + CO3-2
	-log_k	-11.13
	-delta_h  -1.430 kcal
	-Vm 31.1
Strontianite
	SrCO3 = Sr+2 + CO3-2
	-log_k	-9.271
	-delta_h -0.400 kcal
	-analytic	155.0305	0.0	-7239.594	-56.58638
	-Vm 39.69
Witherite
	BaCO3 = Ba+2 + CO3-2
	-log_k	-8.562
	-delta_h  0.703 kcal
	-analytic	607.642	0.121098	-20011.25	-236.4948
	-Vm 46
Gypsum
	CaSO4:2H2O = Ca+2 + SO4-2 + 2 H2O
	-log_k	-4.58
	-delta_h -0.109 kcal
	-analytic	68.2401	0.0	-3221.51	-25.0627

	-Vm 73.9 # 172.18 / 2.33  (Vm H2O = 13.9 cm3/mol)
Anhydrite
	CaSO4 = Ca+2 + SO4-2
	-log_k	-4.36
	-delta_h -1.710 kcal
	-analytic  84.90  0  -3135.12  -31.79 # 50 - 160oC, 1 - 1e3 atm, anhydrite dissolution, Blount and Dickson, 1973, Am. Mineral. 58, 323.
	-Vm 46.1 # 136.14 / 2.95
Celestite
	SrSO4 = Sr+2 + SO4-2
	-log_k	-6.63
	-delta_h -4.037 kcal
#	-analytic	-14805.9622	-2.4660924	756968.533	5436.3588	-40553604.0
	-analytic  -7.14 6.11e-3  75 0 0 -1.79e-5  # Howell et al., 1992, JCED 37, 464.
	-Vm 46.4
Barite
	BaSO4 = Ba+2 + SO4-2
	-log_k	-9.97
	-delta_h  6.35 kcal
	-analytical_expression  -282.43  -8.972e-2  5822  113.08 # Blount 1977; Templeton, 1960
	-Vm 52.9
Hydroxyapatite
	Ca5(PO4)3OH + 4 H+ = H2O + 3 HPO4-2 + 5 Ca+2
	-log_k	 -3.421
	-delta_h -36.155 kcal
	-Vm 128.9
Fluorite
	CaF2 = Ca+2 + 2 F-
	-log_k	-10.6
	-delta_h   4.69 kcal
	-analytic	66.348	0.0	-4298.2	-25.271
	-Vm 15.7
SiO2(a)
	SiO2 + 2 H2O = H4SiO4
	-log_k	-2.71
	-delta_h  3.340 kcal
	-analytic	-0.26	0.0	-731.0
Chalcedony
	SiO2 + 2 H2O = H4SiO4
	-log_k	-3.55
	-delta_h  4.720 kcal
	-analytic	-0.09	0.0	-1032.0
	-Vm 23.1
Quartz
	SiO2 + 2 H2O = H4SiO4
	-log_k	-3.98
	-delta_h  5.990 kcal
	-analytic	0.41	0.0	-1309.0
	-Vm 22.67
Gibbsite
	Al(OH)3 + 3 H+ = Al+3 + 3 H2O
	-log_k	  8.11
	-delta_h -22.800 kcal
Al(OH)3(a)
	Al(OH)3 + 3 H+ = Al+3 + 3 H2O
	-log_k	 10.8
	-delta_h -26.500 kcal
Kaolinite
	Al2Si2O5(OH)4 + 6 H+ = H2O + 2 H4SiO4 + 2 Al+3
	-log_k	  7.435
	-delta_h -35.300 kcal
Albite
	NaAlSi3O8 + 8 H2O = Na+ + Al(OH)4- + 3 H4SiO4
	-log_k	-18.002
	-delta_h 25.896 kcal
Anorthite
	CaAl2Si2O8 + 8 H2O = Ca+2 + 2 Al(OH)4- + 2 H4SiO4
	-log_k	-19.714
	-delta_h 11.580 kcal
K-feldspar
	KAlSi3O8 + 8 H2O = K+ + Al(OH)4- + 3 H4SiO4
	-log_k	-20.573
	-delta_h 30.820	kcal
K-mica
	KAl3Si3O10(OH)2 + 10 H+ = K+ + 3 Al+3 + 3 H4SiO4
	-log_k	12.703
	-delta_h -59.376 kcal
Chlorite(14A)
	Mg5Al2Si3O10(OH)8 + 16H+ = 5Mg+2 + 2Al+3 + 3H4SiO4 + 6H2O
	-log_k	68.38
	-delta_h -151.494 kcal
Ca-Montmorillonite
	Ca0.165Al2.33Si3.67O10(OH)2 + 12 H2O = 0.165Ca+2 + 2.33 Al(OH)4- + 3.67 H4SiO4 + 2 H+
	-log_k	-45.027
	-delta_h 58.373	kcal
Talc
	Mg3Si4O10(OH)2 + 4 H2O + 6 H+ = 3 Mg+2 + 4 H4SiO4
	-log_k	21.399
	-delta_h -46.352 kcal
Illite
	K0.6Mg0.25Al2.3Si3.5O10(OH)2 + 11.2H2O = 0.6K+ + 0.25Mg+2 + 2.3Al(OH)4- + 3.5H4SiO4 + 1.2H+
	-log_k	-40.267
	-delta_h 54.684 kcal
Chrysotile
	Mg3Si2O5(OH)4 + 6 H+ = H2O + 2 H4SiO4 + 3 Mg+2
	-log_k	32.2
	-delta_h -46.800 kcal
	-analytic	13.248	0.0	10217.1	-6.1894
Sepiolite
	Mg2Si3O7.5OH:3H2O + 4 H+ + 0.5H2O = 2 Mg+2 + 3 H4SiO4
	-log_k	15.760
	-delta_h -10.700 kcal
Sepiolite(d)
	Mg2Si3O7.5OH:3H2O + 4 H+ + 0.5H2O = 2 Mg+2 + 3 H4SiO4
	-log_k	18.66
Hematite
	Fe2O3 + 6 H+ = 2 Fe+3 + 3 H2O
	-log_k	-4.008
	-delta_h -30.845 kcal
Goethite
	FeOOH + 3 H+ = Fe+3 + 2 H2O
	-log_k	-1.0
	-delta_h	 -14.48 kcal
Fe(OH)3(a)
	Fe(OH)3 + 3 H+ = Fe+3 + 3 H2O
	-log_k	4.891
Pyrite
	FeS2 + 2 H+ + 2 e- = Fe+2 + 2 HS-
	-log_k	-18.479
	-delta_h 11.300 kcal
FeS(ppt)
	FeS + H+ = Fe+2 + HS-
	-log_k	-3.915
Mackinawite
	FeS + H+ = Fe+2 + HS-
	-log_k	-4.648
Sulfur
	S + 2H+ + 2e- = H2S
	-log_k	4.882
	-delta_h -9.5 kcal
Vivianite
	Fe3(PO4)2:8H2O = 3 Fe+2 + 2 PO4-3 + 8 H2O
	-log_k	-36.0
Pyrolusite	# H2O added for surface calc's
	MnO2:H2O + 4 H+ + 2 e- = Mn+2 + 3 H2O
	-log_k	41.38
	-delta_h -65.110 kcal
Hausmannite
	Mn3O4 + 8 H+ + 2 e- = 3 Mn+2 + 4 H2O
	-log_k	61.03
	-delta_h -100.640 kcal
Manganite
	MnOOH + 3 H+ + e- = Mn+2 + 2 H2O
	-log_k	25.34
Pyrochroite
	Mn(OH)2 + 2 H+ = Mn+2 + 2 H2O
	-log_k	15.2
Halite
	NaCl  =  Cl- + Na+
	log_k	  1.570
	-delta_h  1.37
	#-analytic -713.4616   -.1201241   37302.21    262.4583    -2106915.
	-Vm 27.1
Sylvite
	KCl  = K+ + Cl-
	log_k	   0.900
	-delta_h  8.5
	# -analytic     3.984     0.0	 -919.55
	Vm 37.5
CO2(g)
	CO2 = CO2
	-log_k	-1.468
	-delta_h -4.776 kcal
	-analytic   10.5624  -2.3547e-2  -3972.8  0  5.8746e5  1.9194e-5
	-T_c  304.2 # critical T, K
	-P_c   72.86 # critical P, atm
	-Omega 0.225 # acentric factor
H2O(g)
	H2O = H2O
	-log_k  1.506; delta_h -44.03 kJ
	-T_c  647.3
	-P_c  217.60
	-Omega 0.344
	-analytic   -16.5066 -2.0013E-3  2710.7  3.7646  0 2.24E-6

# Gases from LLNL...
O2(g)
	O2 = O2
	-log_k   -2.8983
	-analytic -7.5001 7.8981e-3 0.0 0.0 2.0027e5

	-T_c  154.6
	-P_c   49.80
	-Omega 0.021
H2(g)
	H2 = H2
	-log_k	   -3.1050
	-delta_h -4.184  kJ
	-analytic   -9.3114    4.6473e-3   -49.335    1.4341    1.2815e5

	-T_c  33.2
	-P_c   12.80
	-Omega -0.225
N2(g)
	N2 = N2
	-log_k		 -3.1864
	-analytic -58.453 1.818e-3  3199  17.909 -27460

	-T_c  126.2
	-P_c   33.50
	-Omega 0.039
H2S(g)
	H2S  =  H+ + HS-
	-log_k	   -7.9759
	-analytic -97.354 -3.1576e-2 1.8285e3 37.44 28.56

	-T_c  373.2
	-P_c  88.20
	-Omega 0.1
CH4(g)
	CH4 = CH4
	-log_k	   -2.8502
	-analytic   10.44  -7.65e-3  -6669  0  1.014e6 # CH4 solubilities 25 - 100C
	-T_c  190.6
	-P_c   45.40
	-Omega 0.008
#Amm(g)
#	Amm = Amm
NH3(g)
	NH3 = NH3
	-log_k	   1.7966
	-analytic -18.758 3.3670e-4 2.5113e3 4.8619 39.192

	-T_c  405.6
	-P_c   111.3
	-Omega 0.25
# redox-uncoupled gases
Oxg(g)
	Oxg = Oxg
	-analytic -7.5001 7.8981e-3 0.0 0.0 2.0027e5
	-T_c  154.6 ; -P_c   49.80 ; -Omega 0.021
Hdg(g)
	Hdg = Hdg
	-analytic   -9.3114    4.6473e-3   -49.335    1.4341    1.2815e5
	-T_c  33.2 ; -P_c   12.80 ; -Omega -0.225
Ntg(g)
	Ntg = Ntg
	-analytic -58.453 1.81800e-3  3199  17.909 -27460
	T_c  126.2 ; -P_c   33.50 ; -Omega 0.039
Mtg(g)
	Mtg = Mtg
	-log_k -2.8
	-analytic   10.44  -7.65e-3  -6669  0  1.014e6 # CH4 solubilities 25 - 100C
	-T_c  190.6 ; -P_c   45.40 ; -Omega 0.008
H2Sg(g)
	H2Sg  =  H+ + HSg-
	-analytic -97.354 -3.1576e-2 1.8285e3 37.44 28.56
	-T_c  373.2 ; -P_c  88.20 ; -Omega 0.1
Melanterite
	FeSO4:7H2O = 7 H2O + Fe+2 + SO4-2
	-log_k	-2.209
	-delta_h 4.910	kcal
	-analytic	1.447	-0.004153	0.0	0.0	-214949.0
Alunite
	KAl3(SO4)2(OH)6 + 6 H+ = K+ + 3 Al+3 + 2 SO4-2 + 6H2O
	-log_k	-1.4
	-delta_h -50.250 kcal
Jarosite-K
	KFe3(SO4)2(OH)6 + 6 H+ = 3 Fe+3 + 6 H2O + K+ + 2 SO4-2
	-log_k	-9.21
	-delta_h -31.280 kcal
Zn(OH)2(e)
	Zn(OH)2 + 2 H+ = Zn+2 + 2 H2O
	-log_k	11.5
Smithsonite
	ZnCO3 = Zn+2 + CO3-2
	-log_k	-10.0
	-delta_h -4.36	kcal
Sphalerite
	ZnS + H+ = Zn+2 + HS-
	-log_k	-11.618
	-delta_h 8.250	kcal
Willemite	289
	Zn2SiO4 + 4H+ = 2Zn+2 + H4SiO4
	-log_k	15.33
	-delta_h -33.37	kcal
Cd(OH)2
	Cd(OH)2 + 2 H+ = Cd+2 + 2 H2O
	-log_k	13.65
Otavite	315
	CdCO3 = Cd+2 + CO3-2
	-log_k	-12.1
	-delta_h -0.019	kcal
CdSiO3	328
	CdSiO3 + H2O + 2H+ = Cd+2 + H4SiO4
	-log_k	9.06
	-delta_h -16.63	kcal
CdSO4	329
	CdSO4 = Cd+2 + SO4-2
	-log_k	-0.1
	-delta_h -14.74	kcal
Cerrusite	365
	PbCO3 = Pb+2 + CO3-2
	-log_k	-13.13
	-delta_h 4.86	kcal
Anglesite	384
	PbSO4 = Pb+2 + SO4-2
	-log_k	-7.79
	-delta_h 2.15	kcal
Pb(OH)2	389
	Pb(OH)2 + 2H+ = Pb+2 + 2H2O
	-log_k	8.15
	-delta_h -13.99	kcal

EXCHANGE_MASTER_SPECIES
	X	X-
EXCHANGE_SPECIES
	X- = X-
	-log_k	0.0

	Na+ + X- = NaX
	-log_k	0.0
	-gamma	4.08 0.082

	K+ + X- = KX
	-log_k	0.7
	-gamma	3.5	0.015
	-delta_h  -4.3	# Jardine & Sparks, 1984

	Li+ + X- = LiX
	-log_k	-0.08
	-gamma	6.0	0
	-delta_h  1.4	# Merriam & Thomas, 1956

# !!!!!
#	H+ + X- = HX
#	-log_k	1.0
#	-gamma	9.0	0

#	AmmH+ + X- = AmmHX
	NH4+ + X- = NH4X
	-log_k	0.6
	-gamma	2.5	0
	-delta_h  -2.4	# Laudelout et al., 1968

	Ca+2 + 2X- = CaX2
	-log_k	0.8
	-gamma	5.0	0.165
	-delta_h  7.2    # Van Bladel & Gheyl, 1980

	Mg+2 + 2X- = MgX2
	-log_k	0.6
	-gamma	5.5	0.2
	-delta_h  7.4	# Laudelout et al., 1968

	Sr+2 + 2X- = SrX2
	-log_k	0.91
	-gamma	5.26	0.121
	-delta_h  5.5	# Laudelout et al., 1968

	Ba+2 + 2X- = BaX2
	-log_k	0.91
	-gamma	4.0  0.153
	-delta_h  4.5	# Laudelout et al., 1968

	Mn+2 + 2X- = MnX2
	-log_k	0.52
	-gamma	6.0	0

	Fe+2 + 2X- = FeX2
	-log_k	0.44
	-gamma	6.0	0

	Cu+2 + 2X- = CuX2
	-log_k	0.6
	-gamma	6.0	0

	Zn+2 + 2X- = ZnX2
	-log_k	0.8
	-gamma	5.0	0

	Cd+2 + 2X- = CdX2
	-log_k	0.8
	-gamma 0.0  0

	Pb+2 + 2X- = PbX2
	-log_k	1.05
	-gamma 0.0  0

	Al+3 + 3X- = AlX3
	-log_k	0.41
	-gamma	9.0	0

	AlOH+2 + 2X- = AlOHX2
	-log_k	0.89
	-gamma	0.0	0

SURFACE_MASTER_SPECIES
	Hfo_s	Hfo_sOH
	Hfo_w	Hfo_wOH
SURFACE_SPECIES
# All surface data from
# Dzombak and Morel, 1990
#
#
# Acid-base data from table 5.7
#
# strong binding site--Hfo_s,

	Hfo_sOH = Hfo_sOH
	-log_k	0

	Hfo_sOH	+ H+ = Hfo_sOH2+
	-log_k	7.29	# = pKa1,int

	Hfo_sOH = Hfo_sO- + H+
	-log_k	-8.93	# = -pKa2,int

# weak binding site--Hfo_w

	Hfo_wOH = Hfo_wOH
	-log_k	0

	Hfo_wOH	+ H+ = Hfo_wOH2+
	-log_k	7.29	# = pKa1,int

	Hfo_wOH = Hfo_wO- + H+
	-log_k	-8.93	# = -pKa2,int
###############################################
# CATIONS #
###############################################
#
# Cations from table 10.1 or 10.5
#
# Calcium
	Hfo_sOH + Ca+2 = Hfo_sOHCa+2
	-log_k	4.97

	Hfo_wOH + Ca+2 = Hfo_wOCa+ + H+
	-log_k -5.85
# Strontium
	Hfo_sOH + Sr+2 = Hfo_sOHSr+2
	-log_k	5.01

	Hfo_wOH + Sr+2 = Hfo_wOSr+ + H+
	-log_k -6.58

	Hfo_wOH + Sr+2 + H2O = Hfo_wOSrOH + 2H+
	-log_k -17.6
# Barium
	Hfo_sOH + Ba+2 = Hfo_sOHBa+2
	-log_k	5.46

	Hfo_wOH + Ba+2 = Hfo_wOBa+ + H+
	-log_k	-7.2	# table 10.5
#
# Cations from table 10.2
#
# Cadmium
	Hfo_sOH + Cd+2 = Hfo_sOCd+ + H+
	-log_k	0.47

	Hfo_wOH + Cd+2 = Hfo_wOCd+ + H+
	-log_k	-2.91
# Zinc
	Hfo_sOH + Zn+2 = Hfo_sOZn+ + H+
	-log_k	0.99

	Hfo_wOH + Zn+2 = Hfo_wOZn+ + H+
	-log_k	-1.99
# Copper
	Hfo_sOH + Cu+2 = Hfo_sOCu+ + H+
	-log_k	2.89

	Hfo_wOH + Cu+2 = Hfo_wOCu+ + H+
	-log_k	0.6	# table 10.5
# Lead
	Hfo_sOH + Pb+2 = Hfo_sOPb+ + H+
	-log_k	4.65

	Hfo_wOH + Pb+2 = Hfo_wOPb+ + H+
	-log_k	0.3	# table 10.5
#
# Derived constants table 10.5
#
# Magnesium
	Hfo_wOH + Mg+2 = Hfo_wOMg+ + H+
	-log_k -4.6
# Manganese
	Hfo_sOH + Mn+2 = Hfo_sOMn+ + H+
	-log_k	-0.4	# table 10.5

	Hfo_wOH + Mn+2 = Hfo_wOMn+ + H+
	-log_k -3.5	# table 10.5
# Iron, strong site: Appelo, Van der Weiden, Tournassat & Charlet, EST 36, 3096
	Hfo_sOH + Fe+2 = Hfo_sOFe+ + H+
	-log_k	-0.95
# Iron, weak site: Liger et al., GCA 63, 2939, re-optimized for D&M
	Hfo_wOH + Fe+2 = Hfo_wOFe+ + H+
	-log_k -2.98

	Hfo_wOH + Fe+2 + H2O = Hfo_wOFeOH + 2H+
	-log_k -11.55
###############################################
# ANIONS #
###############################################
#
# Anions from table 10.6
#
# Phosphate
	Hfo_wOH + PO4-3 + 3H+ = Hfo_wH2PO4 + H2O
	-log_k	31.29

	Hfo_wOH + PO4-3 + 2H+ = Hfo_wHPO4- + H2O
	-log_k	25.39

	Hfo_wOH + PO4-3 + H+ = Hfo_wPO4-2 + H2O
	-log_k	17.72
#
# Anions from table 10.7
#
# Borate
	Hfo_wOH + H3BO3 = Hfo_wH2BO3 + H2O
	-log_k	0.62
#
# Anions from table 10.8
#
# Sulfate
	Hfo_wOH + SO4-2 + H+ = Hfo_wSO4- + H2O
	-log_k	7.78

	Hfo_wOH + SO4-2 = Hfo_wOHSO4-2
	-log_k	0.79
#
# Derived constants table 10.10
#
	Hfo_wOH + F- + H+ = Hfo_wF + H2O
	-log_k	8.7

	Hfo_wOH + F- = Hfo_wOHF-
	-log_k	1.6
#
# Carbonate: Van Geen et al., 1994 reoptimized for D&M model
#
	Hfo_wOH + CO3-2 + H+ = Hfo_wCO3- + H2O
	-log_k	12.56

	Hfo_wOH + CO3-2 + 2H+= Hfo_wHCO3 + H2O
	-log_k	20.62

RATES

###########
#Quartz
###########
#
#######
# Example of quartz kinetic rates block:
#	KINETICS
#	Quartz
#		-m0  158.8	    # 90 % Qu
#		-parms 0.146  1.5
#		-step 3.1536e8 in 10
#		-tol 1e-12

Quartz
  -start
1  REM  Specific rate k from Rimstidt and Barnes, 1980, GCA 44,1683
2  REM  k = 10^-13.7 mol/m2/s (25 C), Ea = 90 kJ/mol
3  REM  sp. rate * parm(2) due to salts (Dove and Rimstidt, MSA Rev. 29, 259)
4  REM  PARM(1) = Specific area of Quartz, m^2/mol Quartz
5  REM  PARM(2) = salt correction: (1 + 1.5 * c_Na (mM)), < 35

10 dif_temp = 1/TK - 1/298
20 pk_w = 13.7 + 4700.4 * dif_temp
40 moles = PARM(1) * M0 * PARM(2) * (M/M0)^0.67 * 10^-pk_w * (1 -  SR("Quartz"))
#			 Integrate...
50 SAVE moles * TIME
  -end

###########
#K-feldspar
###########
#
# Sverdrup and Warfvinge, 1995, Estimating field weathering rates
# using laboratory kinetics: Reviews in mineralogy and geochemistry,
# vol. 31, p. 485-541.
#
# As described in:
# Appelo and Postma, 2005, Geochemistry, groundwater
# and pollution, 2nd Edition: A.A. Balkema Publishers,
# p. 162-163 and 395-399.
#
# Assume soil is 10% K-feldspar by mass in 1 mm spheres (radius 0.5 mm)
# Assume density of rock and Kspar is 2600 kg/m^3 = 2.6 kg/L
# GFW Kspar 0.278 kg/mol
#
# Moles of Kspar per liter pore space calculation:
#   Mass of rock per liter pore space = 0.7*2.6/0.3       = 6.07     kg rock/L pore space
#   Mass of Kspar per liter pore space 6.07x0.1           = 0.607    kg Kspar/L pore space
#   Moles of Kspar per liter pore space 0.607/0.278       = 2.18     mol Kspar/L pore space
#
# Specific area calculation:
#   Volume of sphere 4/3 x pi x r^3                       = 5.24e-13 m^3 Kspar/sphere
#   Mass of sphere 2600 x 5.24e-13                        = 1.36e-9  kg Kspar/sphere
#   Moles of Kspar in sphere 1.36e-9/0.278                = 4.90e-9  mol Kspar/sphere
#   Surface area of one sphere 4 x pi x r^2               = 3.14e-8  m^2/sphere
#   Specific area of K-feldspar in sphere 3.14e-8/4.90e-9 = 6.41 m^2/mol Kspar
#
#
# Example of KINETICS data block for K-feldspar rate:
#       KINETICS 1
#       K-feldspar
#               -m0 2.18            # 10% Kspar, 0.1 mm cubes
#               -m  2.18            # Moles per L pore space
#               -parms 6.41  0.1    # m^2/mol Kspar, fraction adjusts lab rate to field rate
#               -time 1.5 year in 40

K-feldspar
 -start
1   REM Sverdrup and Warfvinge, 1995, mol m^-2 s^-1
2   REM PARM(1) = Specific area of Kspar m^2/mol Kspar
3   REM PARM(2) = Adjusts lab rate to field rate
4   REM temp corr: from A&P, p. 162. E (kJ/mol) / R / 2.303 = H in H*(1/T-1/281)
5   REM K-Feldspar parameters
10  DATA 11.7, 0.5, 4e-6, 0.4, 500e-6, 0.15, 14.5, 0.14, 0.15, 13.1, 0.3
20  RESTORE 10
30  READ pK_H, n_H, lim_Al, x_Al, lim_BC, x_BC, pK_H2O, z_Al, z_BC, pK_OH, o_OH
40  DATA 3500, 2000, 2500, 2000
50  RESTORE 40
60  READ e_H, e_H2O, e_OH, e_CO2
70  pk_CO2 = 13
80  n_CO2 = 0.6
100 REM Generic rate follows
110 dif_temp = 1/TK - 1/281
120 BC       = ACT("Na+") + ACT("K+") + ACT("Mg+2") + ACT("Ca+2")
130 REM rate by H+
140 pk_H     = pk_H + e_H * dif_temp
150 rate_H   = 10^-pk_H * ACT("H+")^n_H / ((1 + ACT("Al+3") / lim_Al)^x_Al * (1 + BC / lim_BC)^x_BC)
160 REM rate by hydrolysis
170 pk_H2O   = pk_H2O + e_H2O * dif_temp
180 rate_H2O = 10^-pk_H2O / ((1 + ACT("Al+3") / lim_Al)^z_Al * (1 + BC / lim_BC)^z_BC)
190 REM rate by OH-
200 pk_OH    = pk_OH + e_OH * dif_temp
210 rate_OH  = 10^-pk_OH * ACT("OH-")^o_OH
220 REM rate by CO2
230 pk_CO2   = pk_CO2 + e_CO2 * dif_temp
240 rate_CO2 = 10^-pk_CO2 * (SR("CO2(g)"))^n_CO2
250 rate     = rate_H + rate_H2O + rate_OH + rate_CO2
260 area     = PARM(1) * M0 *(M/M0)^0.67
270 rate     = PARM(2) * area * rate * (1-SR("K-feldspar"))
280 moles    = rate * TIME
290 SAVE moles
 -end


###########
#Albite
###########
#
# Sverdrup and Warfvinge, 1995, Estimating field weathering rates
# using laboratory kinetics: Reviews in mineralogy and geochemistry,
# vol. 31, p. 485-541.
#
# As described in:
# Appelo and Postma, 2005, Geochemistry, groundwater
# and pollution, 2nd Edition: A.A. Balkema Publishers,
# p. 162-163 and 395-399.
#
# Example of KINETICS data block for Albite rate:
#       KINETICS 1
#       Albite
#               -m0 0.46            # 2% Albite, 0.1 mm cubes
#               -m  0.46            # Moles per L pore space
#               -parms 6.04  0.1    # m^2/mol Albite, fraction adjusts lab rate to field rate
#               -time 1.5 year in 40
#
# Assume soil is 2% Albite by mass in 1 mm spheres (radius 0.5 mm)
# Assume density of rock and Albite is 2600 kg/m^3 = 2.6 kg/L
# GFW Albite 0.262 kg/mol
#
# Moles of Albite per liter pore space calculation:
#   Mass of rock per liter pore space = 0.7*2.6/0.3       = 6.07     kg rock/L pore space
#   Mass of Albite per liter pore space 6.07x0.02         = 0.121    kg Albite/L pore space
#   Moles of Albite per liter pore space 0.607/0.262      = 0.46     mol Albite/L pore space
#
# Specific area calculation:
#   Volume of sphere 4/3 x pi x r^3                       = 5.24e-13 m^3 Albite/sphere
#   Mass of sphere 2600 x 5.24e-13                        = 1.36e-9  kg Albite/sphere
#   Moles of Albite in sphere 1.36e-9/0.278               = 5.20e-9  mol Albite/sphere
#   Surface area of one sphere 4 x pi x r^2               = 3.14e-8  m^2/sphere
#   Specific area of Albite in sphere 3.14e-8/4.90e-9     = 6.04 m^2/mol Albite

Albite
 -start
1   REM Sverdrup and Warfvinge, 1995, mol m^-2 s^-1
2   REM PARM(1) = Specific area of Albite m^2/mol Albite
3   REM PARM(2) = Adjusts lab rate to field rate
4   REM temp corr: from A&P, p. 162. E (kJ/mol) / R / 2.303 = H in H*(1/T-1/281)
5   REM Albite parameters
10  DATA 11.5, 0.5, 4e-6, 0.4, 500e-6, 0.2, 13.7, 0.14, 0.15, 11.8, 0.3
20  RESTORE 10
30  READ pK_H, n_H, lim_Al, x_Al, lim_BC, x_BC, pK_H2O, z_Al, z_BC, pK_OH, o_OH
40  DATA 3500, 2000, 2500, 2000
50  RESTORE 40
60  READ e_H, e_H2O, e_OH, e_CO2
70  pk_CO2 = 13
80  n_CO2 = 0.6
100 REM Generic rate follows
110 dif_temp = 1/TK - 1/281
120 BC       = ACT("Na+") + ACT("K+") + ACT("Mg+2") + ACT("Ca+2")
130 REM rate by H+
140 pk_H     = pk_H + e_H * dif_temp
150 rate_H   = 10^-pk_H * ACT("H+")^n_H / ((1 + ACT("Al+3") / lim_Al)^x_Al * (1 + BC / lim_BC)^x_BC)
160 REM rate by hydrolysis
170 pk_H2O   = pk_H2O + e_H2O * dif_temp
180 rate_H2O = 10^-pk_H2O / ((1 + ACT("Al+3") / lim_Al)^z_Al * (1 + BC / lim_BC)^z_BC)
190 REM rate by OH-
200 pk_OH    = pk_OH + e_OH * dif_temp
210 rate_OH  = 10^-pk_OH * ACT("OH-")^o_OH
220 REM rate by CO2
230 pk_CO2   = pk_CO2 + e_CO2 * dif_temp
240 rate_CO2 = 10^-pk_CO2 * (SR("CO2(g)"))^n_CO2
250 rate     = rate_H + rate_H2O + rate_OH + rate_CO2
260 area     = PARM(1) * M0 *(M/M0)^0.67
270 rate     = PARM(2) * area * rate * (1-SR("Albite"))
280 moles    = rate * TIME
290 SAVE moles
 -end

########
#Calcite
########
# Example of KINETICS data block for calcite rate,
#   in mmol/cm2/s, Plummer et al., 1978, AJS 278, 179; Appelo et al., AG 13, 257.
# KINETICS 1
# Calcite
# -tol   1e-8
# -m0    3.e-3
# -m     3.e-3
# -parms 1.67e5   0.6  # cm^2/mol calcite, exp factor
# -time  1 day

Calcite
   -start
1   REM   PARM(1) = specific surface area of calcite, cm^2/mol calcite
2   REM   PARM(2) = exponent for M/M0

10  si_cc = SI("Calcite")
20  IF (M <= 0  and si_cc < 0) THEN GOTO 200
30  k1 = 10^(0.198 - 444.0 / TK )
40  k2 = 10^(2.84 - 2177.0 /TK )
50  IF TC <= 25 THEN k3 = 10^(-5.86 - 317.0 / TK)
60  IF TC > 25 THEN k3 = 10^(-1.1 - 1737.0 / TK )
70  t = 1
80  IF M0 > 0 THEN t = M/M0
90  IF t = 0 THEN t = 1
100 area = PARM(1) * M0 * t^PARM(2)
110 rate = area * (k1 * ACT("H+") + k2 * ACT("CO2") + k3 * ACT("H2O"))
120 rate = rate * (1 - 10^(2/3*si_cc))
130 moles = rate * 0.001 * TIME # convert from mmol to mol
200 SAVE moles
   -end

#######
#Pyrite
#######
#
# Williamson, M.A. and Rimstidt, J.D., 1994,
# Geochimica et Cosmochimica Acta, v. 58, p. 5443-5454,
# rate equation is mol m^-2 s^-1.
#
# Example of KINETICS data block for pyrite rate:
#       KINETICS 1
#       Pyrite
#               -tol    1e-8
#               -m0     5.e-4
#               -m      5.e-4
#               -parms  0.3     0.67     .5      -0.11
#               -time 1 day in 10
Pyrite
  -start
1   REM        Williamson and Rimstidt, 1994
2   REM        PARM(1) = log10(specific area), log10(m^2 per mole pyrite)
3   REM        PARM(2) = exp for (M/M0)
4   REM        PARM(3) = exp for O2
5   REM        PARM(4) = exp for H+

10  REM Dissolution in presence of DO
20  if (M <= 0) THEN GOTO 200
30  if (SI("Pyrite") >= 0) THEN GOTO 200
40  log_rate = -8.19 + PARM(3)*LM("O2") + PARM(4)*LM("H+")
50  log_area = PARM(1) + LOG10(M0) + PARM(2)*LOG10(M/M0)
60  moles = 10^(log_area + log_rate) * TIME
200 SAVE moles
  -end

##########
#Organic_C
##########
#
# Example of KINETICS data block for SOC (sediment organic carbon):
#       KINETICS 1
#       Organic_C
#               -formula C
#               -tol    1e-8
#               -m      5e-3   # SOC in mol
#               -time 30 year in 15
Organic_C
 -start
1   REM      Additive Monod kinetics for SOC (sediment organic carbon)
2   REM      Electron acceptors: O2, NO3, and SO4

10  if (M <= 0) THEN GOTO 200
20  mO2   = MOL("O2")
30  mNO3  = TOT("N(5)")
40  mSO4  = TOT("S(6)")
50  k_O2  = 1.57e-9    # 1/sec
60  k_NO3 = 1.67e-11   # 1/sec
70  k_SO4 = 1.e-13     # 1/sec
80  rate  = k_O2 * mO2/(2.94e-4 + mO2)
90  rate  = rate + k_NO3 * mNO3/(1.55e-4 + mNO3)
100 rate  = rate + k_SO4 * mSO4/(1.e-4 + mSO4)
110 moles = rate * M * (M/M0) * TIME
200 SAVE moles
 -end

###########
#Pyrolusite
###########
#
# Postma, D. and Appelo, C.A.J., 2000, GCA, vol. 64, pp. 1237-1247.
# Rate equation given as mol L^-1 s^-1
#
# Example of KINETICS data block for Pyrolusite
#       KINETICS 1-12
#       Pyrolusite
#               -tol    1.e-7
#               -m0     0.1
#               -m      0.1
#               -time 0.5 day in 10
Pyrolusite
  -start
10  if (M <= 0) THEN GOTO 200
20  sr_pl = SR("Pyrolusite")
30  if (sr_pl > 1) THEN GOTO 100
40  REM sr_pl <= 1, undersaturated
50  Fe_t = TOT("Fe(2)")
60  if Fe_t < 1e-8 then goto 200
70  moles = 6.98e-5 * Fe_t  * (M/M0)^0.67 * TIME * (1 - sr_pl)
80  GOTO 200
100 REM sr_pl > 1, supersaturated
110 moles = 2e-3 * 6.98e-5 * (1 - sr_pl) * TIME
200 SAVE moles * SOLN_VOL
  -end
END

# For the reaction aA + bB = cC + dD,
#   with delta_v = c*Vm(C) + d*Vm(D) - a*Vm(A) - b*Vm(B),
# PHREEQC adds the pressure term to log_k: -= delta_v * (P - 1) / (2.3RT).
#   Vm(A) is volume of A, cm3/mol, P is pressure, atm, R is the gas constant, T is Kelvin.
# Gas-pressures and fugacity coefficients are calculated with Peng-Robinson's EOS.
#   Binary interaction coefficients from Soreide and Whitson, 1992, FPE 77, 217 are
#    hard-coded in calc_PR():
#    kij    CH4    CO2    H2S    N2
#    H2O    0.49   0.19   0.19   0.49
# =============================================================================================
# The molar volumes of solids are entered with
#                         -Vm vm cm3/mol
#    vm is the molar volume, cm3/mol (default), but dm3/mol and m3/mol are permitted.
# Data for minerals' vm (= MW (g/mol) / rho (g/cm3)) are defined using rho from
#   Deer, Howie and Zussman, The rock-forming minerals, Longman.
#                           --------------------
# Temperature- and pressure-dependent volumina of aqueous species are calculated with a Redlich-
#   type equation (cf. Redlich and Meyer, Chem. Rev. 64, 221), from parameters entered with
#                        -Vm a1 a2 a3 a4 W a0 i1 i2 i3 i4
# The volume (cm3/mol) is
#    Vm(T, pb, I) = 41.84 * (a1 * 0.1 + a2 * 100 / (2600 + pb)  + a3 / (T - 228) +
#                            a4 * 1e4 / (2600 + pb) / (T - 228) - W * QBrn)
#                   + z^2 / 2 * Av * f(I^0.5)
#                   + (i1 + i2 / (T - 228) + i3 * (T - 228)) * I^i4
#   Volumina at I = 0 are obtained using supcrt92 formulas (Johnson et al., 1992, CG 18, 899).
#   41.84 transforms cal/bar/mol into cm3/mol.
#   pb is pressure in bar.
#   W * QBrn is the energy of solvation, calculated from W and the pressure dependence of the

#     Born equation.
#   z is charge of the solute species.
#   Av is the Debye-Hckel limiting slope.
#   a0 is the ion-size parameter in the extended Debye-Hckel equation:
#     f(I^0.5) = I^0.5) / (1 + a0 * DH_B * I^0.5),
#     a0 = -gamma x for cations, = 0 for anions.
# For details, consult ref. 1.
#
# ref. 1: Appelo, Parkhurst and Post, 2014. Geochim. Cosmochim. Acta 125, 4967.
# ref. 2: Procedures from ref. 1 using data compiled by Lalibert, 2009, J. Chem. Eng. Data 54, 1725.
#
#
# =============================================================================================
# It remains the responsibility of the user to check the calculated results, for example with
#   measured solubilities as a function of (P, T).
)xyz";
}

auto databaseContentsPitzer() -> String
{
    return R"xyz(
# Pitzer.DAT for calculating pressure dependence of reactions
#   and temperature dependence to 200 C. With
#   molal volumina of aqueous species and of minerals, and
#   critical temperatures and pressures of gases used in Peng-Robinson's EOS.
# Details are given at the end of this file.
SOLUTION_MASTER_SPECIES
Alkalinity	CO3-2	 1	Ca0.5(CO3)0.5	50.05
B		B(OH)3	 0	B		10.81
Ba		Ba+2	 0	Ba		137.33
Br		Br-	 0	Br		79.904
C		CO3-2	 2	HCO3		12.0111
C(4)		CO3-2	 2	HCO3		12.0111
Ca		Ca+2	 0	Ca		40.08
Cl		Cl-	 0	Cl		35.453
E		e-	 0	0.0		0.0
Fe		Fe+2	 0	Fe		55.847
H		H+	-1	H		1.008
H(1)		H+	-1	0.0
K		K+	 0	K		39.0983
Li		Li+	 0	Li		6.941
Mg		Mg+2	 0	Mg		24.305
Mn		Mn+2	 0	Mn		54.938
Na		Na+	 0	Na		22.9898
O		H2O	 0	O		16.00
O(-2)		H2O	 0	0.0
S		SO4-2	 0	SO4		32.064
S(6)		SO4-2	 0	SO4
Si		H4SiO4	 0	SiO2		28.0843
Sr		Sr+2	 0	Sr		87.62
# redox-uncoupled gases
Hdg		Hdg	 0	Hdg		2.016 # H2 gas
Oxg		Oxg	 0	Oxg		32 # Oxygen gas
Mtg		Mtg	 0.0	Mtg		16.032 # CH4 gas
Sg		H2Sg	 1.0	H2Sg		34.08
Ntg		Ntg	 0	Ntg		28.0134 # N2 gas

SOLUTION_SPECIES
H+ = H+
	-dw	 9.31e-9
e- = e-
H2O = H2O
Li+ = Li+
	-dw	 1.03e-9
	-Vm  -0.419  -0.069  13.16  -2.78  0.416  0  0.296  -12.4  -2.74e-3  1.26 # ref. 2 and Ellis, 1968, J. Chem. Soc. A, 1138
Na+ = Na+
	-dw	 1.33e-9
	-Vm   2.28  -4.38  -4.1  -0.586  0.09  4  0.3  52  -3.33e-3  0.566 # ref. 1
# for calculating densities (rho) when I > 3...
	# -Vm   2.28  -4.38  -4.1  -0.586  0.09  4  0.3  52  -3.33e-3  0.45
K+ = K+
	-dw	 1.96e-9
	-Vm  3.322  -1.473  6.534  -2.712  9.06e-2  3.5  0  29.70  0  1 # ref. 1
Mg+2 = Mg+2
	-dw	 0.705e-9
	-Vm  -1.410  -8.6  11.13  -2.39  1.332  5.5  1.29  -32.9  -5.86e-3  1 # ref. 1
Ca+2 = Ca+2
	-dw	 0.793e-9
	-Vm  -0.3456  -7.252  6.149  -2.479  1.239  5  1.60  -57.1  -6.12e-3  1 # ref. 1
Sr+2 = Sr+2
	-dw	 0.794e-9
	-Vm  -1.57e-2  -10.15  10.18  -2.36  0.860  5.26  0.859  -27.0  -4.1e-3  1.97 # ref. 1
Ba+2 = Ba+2
	-dw	 0.848e-9
	-Vm  2.063  -10.06  1.9534  -2.36  0.4218  5  1.58  -12.03  -8.35e-3  1 # ref. 1
Mn+2 = Mn+2
	-dw	 0.688e-9
	-Vm  -1.10  -8.03  4.08  -2.45  1.4  6  8.07  0  -1.51e-2  0.118 # ref. 2
Fe+2 = Fe+2
	-dw	 0.719e-9
	-Vm  -0.3255  -9.687  1.536  -2.379  0.3033  6  -4.21e-2  39.7  0  1 # ref. 1
Cl- = Cl-
	-dw	 2.03e-9
	-Vm  4.465  4.801  4.325  -2.847  1.748  0  -0.331  20.16  0  1 # ref. 1
CO3-2 = CO3-2
	-dw	 0.955e-9
	-Vm  4.91  0  0  -5.41  4.76  0  0.386  89.7  -1.57e-2  1 # ref. 1
SO4-2 = SO4-2
	-dw	 1.07e-9
	-Vm  -7.77  43.17  141.1  -42.45  3.794  0  4.97  26.5  -5.77e-2  0.45 # ref. 1
B(OH)3 = B(OH)3
	-dw	1.1e-9
	-Vm 7.0643   8.8547   3.5844   -3.1451 -.2000  # supcrt
Br- = Br-
	-dw	 2.01e-9
	-Vm   7.05  3.95  2.03  -3.14  2.07  0  -0.983  39.9  4.05e-3  1 # ref. 2
H4SiO4 = H4SiO4
	-dw  1.10e-9
	-Vm  10.5  1.7  20  -2.7  0.1291 # supcrt + 2*H2O in a1
# redox-uncoupled gases
Hdg = Hdg # H2
	-dw	 5.13e-9
	-Vm 6.52  0.78  0.12 # supcrt
Oxg = Oxg # O2
	-dw	 2.35e-9
	-Vm   5.7889  6.3536  3.2528  -3.0417   -0.3943 # supcrt
Mtg = Mtg # CH4
	-dw   1.85e-9
	-Vm   9.01  -1.11  0  -1.85  -1.50 # ref. 1 + Hnedkovsky et al., 1996, JCT 28, 125
Ntg = Ntg # N2
	-dw	 1.96e-9
	-Vm 7 # Pray et al., 1952, IEC 44. 1146
H2Sg = H2Sg # H2S
	-dw	 2.1e-9
	-Vm  7.81  2.96  -0.46 # supcrt
# aqueous species
H2O = OH- + H+
	-analytic  293.29227  0.1360833  -10576.913  -123.73158  0  -6.996455e-5
	-dw	 5.27e-9
	-Vm  -9.66  28.5  80.0 -22.9 1.89 0 1.09 0 0 1 # ref. 1
CO3-2 + H+ = HCO3-
	log_k	   10.3393
	delta_h -3.561  kcal
	-analytic    107.8975    0.03252849  -5151.79   -38.92561    563713.9
	-dw	 1.18e-9
	-Vm  8.54  0  -11.7  0  1.6  0  0  116  0  1 # ref. 1
CO3-2 + 2 H+ = CO2 + H2O
	log_k	   16.6767
	delta_h	 -5.738  kcal
	-analytic    464.1965    0.09344813  -26986.16	-165.75951   2248628.9
	-dw	 1.92e-9
	-Vm   7.29  0.92  2.07  -1.23  -1.60 # ref. 1 + McBride et al. 2015, JCED 60, 171
SO4-2 + H+ = HSO4-
	log_k	   1.979
	delta_h 4.91    kcal
	-analytic   -5.3585   0.0183412   557.2461
	-dw	 1.33e-9
	-Vm 8.2 9.2590   2.1108   -3.1618 1.1748  0 -0.3 15 0 1 # ref. 1
H2Sg = HSg- + H+
	log_k	-6.994
	delta_h 5.30	kcal
	-analytical  11.17   -0.02386  -3279.0
	-dw	 2.1e-9
	-Vm 5.0119   4.9799   3.4765   -2.9849 1.4410 # supcrt
B(OH)3 + H2O = B(OH)4- + H+
	log_k	   -9.239
	delta_h 0   kcal
3B(OH)3 = B3O3(OH)4- + 2H2O + H+
	log_k	   -7.528
	delta_h 0   kcal
4B(OH)3 = B4O5(OH)4-2 + 3H2O + 2H+
	log_k	   -16.134
	delta_h 0   kcal
Ca+2 + B(OH)3 + H2O = CaB(OH)4+ + H+
	log_k	   -7.589
	delta_h 0   kcal
Mg+2 + B(OH)3 + H2O = MgB(OH)4+ + H+
	log_k	   -7.840
	delta_h 0   kcal
# Ca+2 + CO3-2 = CaCO3
	# log_k	   3.151
	# delta_h 3.547   kcal
	# -analytic    -1228.806   -0.299440    35512.75   485.818
	# -dw 4.46e-10	# complexes: calc'd with the Pikal formula
	# -Vm  -.2430   -8.3748   9.0417   -2.4328  -.0300 # supcrt
Mg+2 + H2O = MgOH+ + H+
	log_k	   -11.809
	delta_h 15.419 kcal
Mg+2 + CO3-2 = MgCO3
	log_k	   2.928
	delta_h 2.535   kcal
	-analytic	-32.225   0.0	  1093.486    12.72433
	-dw 4.21e-10
	-Vm  -.5837   -9.2067   9.3687   -2.3984  -.0300 # supcrt
H4SiO4 = H3SiO4- + H+
	-log_k  -9.83; -delta_h 6.12 kcal
	-analytic	-302.3724	-0.050698	15669.69	108.18466	-1119669.0
	-Vm  7.94  1.0881  5.3224  -2.8240  1.4767 # supcrt + H2O in a1
H4SiO4 = H2SiO4-2 + 2 H+
	-log_k  -23.0;  -delta_h 17.6 kcal
	-analytic	-294.0184	-0.072650	11204.49	108.18466	-1119669.0

PHASES
Akermanite
	Ca2MgSi2O7 + 6 H+  =  Mg+2 + 2 Ca+2 + 2 H4SiO4 - H2O # llnl.dat
	log_k	   45.23
	-delta_H	-289	kJ/mol
	Vm 92.6
Anhydrite
	CaSO4 = Ca+2 + SO4-2
	log_k   -4.362
	-analytical_expression  5.009  -2.21e-2  -796.4 # ref. 3
	-Vm 46.1 # 136.14 / 2.95
Anthophyllite
	Mg7Si8O22(OH)2 + 14 H+  =  7 Mg+2 - 8 H2O + 8 H4SiO4 # llnl.dat
	log_k	   66.80
	-delta_H	-483	kJ/mol
	Vm 269
Antigorite
	Mg48Si34O85(OH)62 + 96 H+  =  34 H4SiO4 + 48 Mg+2 + 11 H2O # llnl.dat
	log_k	   477.19
	-delta_H	-3364	kJ/mol
	Vm 1745
Aragonite
	CaCO3 = CO3-2 + Ca+2
	log_k   -8.336
	delta_h -2.589 kcal
	-analytic     -171.8607   -.077993    2903.293    71.595
	-Vm 34.04
Arcanite
	K2SO4  =  SO4-2 + 2 K+
	log_k   -1.776; -delta_h 5 kcal
	-analytical_expression   674.142  0.30423  -18037  -280.236  0  -1.44055e-4 # ref. 3
	# Note, the Linke and Seidell data may give subsaturation in other xpt's, SI = -0.06
	-Vm 65.5
Artinite
	Mg2CO3(OH)2:3H2O + 3 H+  =  HCO3- + 2 Mg+2 + 5 H2O # llnl.dat
	log_k	   19.66
	-delta_H	-130	kJ/mol
	Vm 97.4
Barite
	BaSO4 = Ba+2 + SO4-2
	log_k  -9.97; delta_h  6.35 kcal
	-analytical_expression  -282.43  -8.972e-2  5822  113.08 # ref. 3
	-Vm 52.9
Bischofite
	MgCl2:6H2O  =  Mg+2 + 2 Cl- + 6 H2O
	log_k	   4.455
	-analytical_expression  7.526  -1.114e-2  115.7 # ref. 3
	Vm 127.1
Bloedite
	Na2Mg(SO4)2:4H2O  = Mg++ + 2 Na+ + 2 SO4-- + 4 H2O
	log_k	   -2.347
	-delta_H	0	     # Not possible to calculate enthalpy of reaction	Bloedite
	Vm 147
Brucite
	Mg(OH)2  = Mg++ + 2 OH-
	log_k	   -10.88
	-delta_H	4.85    kcal/mol
	Vm 24.6
Burkeite
	Na6CO3(SO4)2  = CO3-2 + 2 SO4-- + 6 Na+
	log_k	   -0.772
	Vm 152
Calcite
	CaCO3 = CO3-2 + Ca+2
	log_k	   -8.406
	delta_h -2.297 kcal
	-analytic   -237.04  -0.1077  0  102.25  6.79e5 # ref. 3 + data from Ellis, 1959, Plummer and Busenberg, 1982
	-Vm 36.9
Carnallite
	KMgCl3:6H2O  =  K+ + Mg+2 + 3Cl- + 6H2O
	log_k  4.35; -delta_h 1.17
	-analytical_expression  24.06  -3.11e-2  -3.09e3 # ref. 3
	Vm 173.7
Celestite
	SrSO4 = Sr+2 + SO4-2
	log_k	   -6.630
	-analytic  -7.14 6.11E-03  75 0 0 -1.79E-05  # ref. 3
	-Vm 46.4
Chalcedony
	SiO2 + 2 H2O = H4SiO4
	-log_k  -3.55;  -delta_h  4.720 kcal
	-Vm 23.1
Chrysotile
	Mg3Si2O5(OH)4 + 6 H+ = H2O + 2 H4SiO4 + 3 Mg+2 # phreeqc.dat
	-log_k	32.2
	-delta_h -46.800 kcal
	-analytic	13.248	0.0	10217.1	-6.1894
	-Vm 110
Diopside
	CaMgSi2O6 + 4 H+  =  Ca+2 + Mg+2 - 2 H2O + 2 H4SiO4 # llnl.dat
	log_k	   20.96
	-delta_H	-134	kJ/mol
	Vm 67.2
Dolomite
	CaMg(CO3)2 = Ca+2 + Mg+2 + 2 CO3-2
	log_k	   -17.083
	delta_h -9.436 kcal
	-Vm 64.5
Enstatite
	MgSiO3 + 2 H+  = - H2O + Mg+2 + H4SiO4 # llnl.dat
	log_k	   11.33
	-delta_H	-83	kJ/mol
	Vm 31.3
Epsomite
	MgSO4:7H2O  =  Mg+2 + SO4-2 + 7 H2O
	log_k	   -1.881
	-analytical_expression  4.479  -6.99e-3  -1.265e3 # ref. 3
	Vm 147
Forsterite
	Mg2SiO4 + 4 H+  =  H4SiO4 + 2 Mg+2 # llnl.dat
	log_k	   27.86
	-delta_H	-206	kJ/mol
	Vm 43.7
Gaylussite
	CaNa2(CO3)2:5H2O = Ca+2 + 2 CO3-2 + 2 Na+ + 5 H2O
	log_k	   -9.421
Glaserite
	NaK3(SO4)2 =  Na+ + 3K+ + 2SO4-2
	log_k   -3.803;  -delta_h 25
	-Vm 123
Glauberite
	Na2Ca(SO4)2  =  Ca+2 + 2 Na+ + 2 SO4-2
	log_k	   -5.31
	-analytical_expression  218.142  0  -9285  -77.735 # ref. 3
	Vm 100.4
Goergeyite
	K2Ca5(SO4)6H2O = 2K+ + 5Ca+2 + 6SO4-2 + H2O
	log_k -29.5
	-analytical_expression  1056.787  0  -52300  -368.06 # ref. 3
	-Vm  295.9
Gypsum
	CaSO4:2H2O = Ca+2 + SO4-2 + 2 H2O
	-log_k	-4.58;  -delta_h -0.109 kcal
	-analytical_expression  82.381  0  -3804.5  -29.9952 # ref. 3
	-Vm 73.9
Halite
	NaCl  =  Cl- + Na+
	log_k	   1.570
	-analytical_expression 159.605  8.4294e-2  -3975.6  -66.857  0  -4.9364e-5 # ref. 3
	-Vm 27.1
Hexahydrite
	MgSO4:6H2O  =  Mg+2 + SO4-2 + 6 H2O
	log_k	   -1.635
	-analytical_expression  -0.733  -2.80e-3  -8.57e-3 # ref. 3
	Vm 132
Huntite
	CaMg3(CO3)4 + 4 H+  =  Ca+2 + 3 Mg+2 + 4 HCO3- # llnl.dat
	log_k	   10.30
	-analytical_expression  -1.145e3  -3.249e-1  3.941e4  4.526e2
	Vm 130.8
Kainite
	KMgClSO4:3H2O  =  Cl- + K+ + Mg+2 + SO4-2 + 3 H2O
	log_k	   -0.193
Kalicinite
	KHCO3  =  K+ + H+ + CO3-2
	log_k	   -9.94 # Harvie et al., 1984
Kieserite
	MgSO4:H2O  =  Mg+2 + SO4-2 + H2O
	log_k	   -0.123
	-analytical_expression  47.24  -0.12077  -5.356e3  0  0  7.272e-5 # ref. 3
	Vm 53.8
Labile_S
	Na4Ca(SO4)3:2H2O = 4Na+ + Ca+2 + 3SO4-2 + 2H2O
	log_k	   -5.672
Leonhardite
	MgSO4:4H2O = Mg+2 + SO4-2 + 4H2O
	log_k	   -0.887
Leonite
	K2Mg(SO4)2:4H2O  =  Mg+2 + 2 K+ + 2 SO4-2 + 4 H2O
	log_k	   -3.979
Magnesite
	MgCO3 =  CO3-2 + Mg+2
	log_k	  -7.834
	delta_h	-6.169
	Vm 28.3
MgCl2_2H2O
	MgCl2:2H2O  =  Mg+2 + 2 Cl- + 2 H2O
	-analytical_expression  -10.273  0  7.403e3 # ref. 3
MgCl2_4H2O
	MgCl2:4H2O  =  Mg+2 + 2 Cl- + 4 H2O
	-analytical_expression  12.98  -2.013e-2 # ref. 3
Mirabilite
	Na2SO4:10H2O  =  SO4-2 + 2 Na+ + 10 H2O
	-analytical_expression  -301.9326  -0.16232  0  141.078 # ref. 3
	Vm 216
Misenite
	K8H6(SO4)7  =  6 H+ + 7 SO4-2 + 8 K+
	log_k	   -10.806
Nahcolite
	NaHCO3  =  CO3-2 + H+ + Na+
	log_k	   -10.742
	Vm 38.0
Natron
	Na2CO3:10H2O = CO3-2 + 2 Na+ + 10 H2O
	log_k	   -0.825
Nesquehonite
	MgCO3:3H2O =  CO3-2 + Mg+2 + 3 H2O
	log_k	   -5.167
Pentahydrite
	MgSO4:5H2O  =  Mg+2 + SO4-2 + 5 H2O
	log_k	   -1.285
Pirssonite
	Na2Ca(CO3)2:2H2O = 2Na+ + Ca+2 + 2CO3-2 + 2 H2O
	log_k	   -9.234
Polyhalite
	K2MgCa2(SO4)4:2H2O  = 2K+ +  Mg+2 + 2 Ca+2 + 4SO4-2 + 2 H2O
	log_k	   -13.744
	Vm 218
Portlandite
	Ca(OH)2 =  Ca+2 + 2 OH-
	log_k	   -5.190
Quartz
	SiO2 + 2 H2O = H4SiO4
	-log_k  -3.98;  -delta_h  5.990 kcal
	-Vm 22.67
Schoenite
	K2Mg(SO4)2:6H2O  =  2K+ + Mg+2 + 2 SO4-2 + 6H2O
	log_k	   -4.328
Sepiolite(d)
	Mg2Si3O7.5OH:3H2O + 4 H+ + 0.5H2O = 2 Mg+2 + 3 H4SiO4 # phreeqc.dat
	-log_k	18.66
	-Vm 162
Sepiolite
	Mg2Si3O7.5OH:3H2O + 4 H+ + 0.5H2O = 2 Mg+2 + 3 H4SiO4 # phreeqc.dat
	-log_k	15.760
	-delta_h -10.700 kcal
	-Vm 154
SiO2(a)
	SiO2 + 2 H2O = H4SiO4
	-log_k  -2.71;  -delta_h  3.340 kcal
	-analytic  20.42  3.107e-3  -1492  -7.68 # ref. 3
	-Vm 25.7
Sylvite
	KCl  = K+ + Cl-
	log_k   0.90;  -delta_h 8
	-analytical_expression  -50.571  9.8815e-2  1.3135e4  0  -1.3754e6  -7.393e-5 # ref. 3
	Vm 37.5
Syngenite
	K2Ca(SO4)2:H2O  =  2K+ + Ca+2 + 2SO4-2 + H2O
	log_k    -6.43;  -delta_h   -32.65 # ref. 3
	-Vm  127.3
Talc
	Mg3Si4O10(OH)2 + 4 H2O + 6 H+ = 3 Mg+2 + 4 H4SiO4 # phreeqc.dat
	-log_k	21.399
	-delta_h -46.352 kcal
	-Vm 140
Thenardite
	Na2SO4 = 2 Na+ + SO4-2
	-analytical_expression  57.185  8.6024e-2  0  -30.8341  0  -7.6905e-5 # ref. 3
	-Vm 52.9
Trona
	Na3H(CO3)2:2H2O =  3 Na+ + H+ + 2CO3-2 + 2H2O
	log_k	   -11.384
	Vm 106
Borax
	Na2(B4O5(OH)4):8H2O + 2 H+  =  4 B(OH)3 + 2 Na+ +  5 H2O
	log_k	   12.464
	Vm 223
Boric_acid,s
	B(OH)3  =  B(OH)3
	log_k	   -0.030
KB5O8:4H2O
	KB5O8:4H2O + 3H2O + H+ = 5B(OH)3 + K+
	log_k	   4.671
K2B4O7:4H2O
	K2B4O7:4H2O + H2O + 2H+ = 4B(OH)3 + 2K+
	log_k	   13.906
NaBO2:4H2O
	NaBO2:4H2O + H+ = B(OH)3 + Na+ + 3H2O
	log_k	   9.568
NaB5O8:5H2O
	NaB5O8:5H2O + 2H2O + H+ = 5B(OH)3 + Na+
	log_k	   5.895
Teepleite
	Na2B(OH)4Cl + H+ = B(OH)3 + 2Na+ + Cl- + H2O
	log_k	   10.840
CO2(g)
	CO2 = CO2
	log_k	-1.468
	delta_h -4.776 kcal
	-analytic   10.5624  -2.3547e-2  -3972.8  0  5.8746e5  1.9194e-5
	-T_c  304.2 # critical T, K
	-P_c   72.80 # critical P, atm
	-Omega 0.225 # acentric factor
H2O(g)
	H2O = H2O
	log_k  1.506; delta_h -44.03 kJ
	-T_c  647.3 # critical T, K
	-P_c  217.60 # critical P, atm
	-Omega 0.344 #  acentric factor
	-analytic   -16.5066 -2.0013E-3  2710.7  3.7646  0 2.24E-6
# redox-uncoupled gases
Oxg(g)
	Oxg = Oxg
	-analytic -7.5001 7.8981e-003 0.0 0.0 2.0027e+005
	T_c  154.6 ; -P_c   49.80 ; -Omega 0.021
Hdg(g)
	Hdg = Hdg
	-analytic   -9.3114e+000    4.6473e-003   -4.9335e+001    1.4341e+000    1.2815e+005
	-T_c  33.2 ; -P_c   12.80 ; -Omega -0.225
Ntg(g)
	Ntg = Ntg
	-analytic -58.453 1.81800E-03  3199  17.909 -27460
	T_c  126.2 ; -P_c   33.50 ; -Omega 0.039
Mtg(g)
	Mtg = Mtg
	-analytic   10.44  -7.65e-3  -6669  0  1.014e6 # CH4 solubilities 25 - 100C
	T_c  190.6 ; -P_c   45.40 ; -Omega 0.008
H2Sg(g)
	H2Sg  =  H+ + HSg-
	-analytic -9.7354e+001 -3.1576e-002 1.8285e+003 3.7440e+001 2.8560e+001
	T_c  373.2 ; -P_c  88.20 ; -Omega 0.1
PITZER
-B0
  B(OH)4-     K+      0.035
  B(OH)4-     Na+    -0.0427
  B3O3(OH)4-  K+     -0.13
  B3O3(OH)4-  Na+    -0.056
  B4O5(OH)4-2 K+     -0.022
  B4O5(OH)4-2 Na+    -0.11
  Ba+2      Br-       0.31455       0           0          -0.33825E-3
  Ba+2      Cl-       0.5268        0           0           0         0     4.75e4  # ref. 3
  Ba+2      OH-       0.17175
  Br-       H+        0.1960        0           0          -2.049E-4
  Br-       K+        0.0569        0           0           7.39E-4
  Br-       Li+       0.1748        0           0          -1.819E-4
  Br-       Mg+2      0.4327        0           0          -5.625E-5
  Br-       Na+       0.0973        0           0           7.692E-4
  Br-       Sr+2      0.331125      0           0          -0.32775E-3
  Ca+2      Br-       0.3816        0           0          -5.2275E-4
  Ca+2      Cl-       0.3159        0           0          -3.27e-4   1.4e-7       # ref. 3
  Ca+2      HCO3-     0.4
  Ca+2      HSO4-     0.2145
  Ca+2      OH-      -0.1747
  Ca+2      SO4-2     0      # ref. 3
  CaB(OH)4+   Cl-     0.12
  Cl-       Fe+2      0.335925
  Cl-       H+        0.1775        0           0          -3.081E-4
  Cl-       K+        0.04808    -758.48       -4.7062      0.010072   -3.7599e-6  # ref. 3
  Cl-       Li+       0.1494        0           0          -1.685E-4
  Cl-       Mg+2      0.351         0           0          -9.32e-4   5.94e-7      # ref. 3
  Cl-       MgB(OH)4+  0.16
  Cl-       MgOH+    -0.1
  Cl-       Mn+2      0.327225
  Cl-       Na+       7.534e-2   9598.4        35.48     -5.8731e-2   1.798e-5   -5e5  # ref. 3
  Cl-       Sr+2      0.2858        0           0           0.717E-3
  CO3-2     K+        0.1488        0           0           1.788E-3
  CO3-2     Na+       0.0399        0           0           1.79E-3
  Fe+2      HSO4-     0.4273
  Fe+2      SO4-2     0.2568
  H+        HSO4-     0.2065
  H+        SO4-2     0.0298
  HCO3-     K+        0.0296        0           0           0.996E-3
  HCO3-     Mg+2      0.329
  HCO3-     Na+      -0.018  # ref. 3 + new -analytic for calcite
  HCO3-     Sr+2      0.12
  HSO4-     K+       -0.0003
  HSO4-     Mg+2      0.4746
  HSO4-     Na+       0.0454
  K+        OH-       0.1298
  K+        SO4-2     3.17e-2       0           0           9.28e-4               # ref. 3
  Li+       OH-       0.015
  Li+       SO4-2     0.136275      0           0           0.5055E-3
  Mg+2      SO4-2     0.2135     -951           0          -2.34e-2   2.28e-5     # ref. 3
  Mn+2      SO4-2     0.2065
  Na+       OH-       0.0864        0           0           7.00E-4
  Na+       SO4-2     2.73e-2      0          -5.8         9.89e-3  0          -1.563e5 # ref. 3
  SO4-2     Sr+2      0.200         0           0          -2.9E-3
-B1
  B(OH)4-   K+        0.14
  B(OH)4-   Na+       0.089
  B3O3(OH)4-  Na+    -0.910
  B4O5(OH)4-2 Na+    -0.40
  Ba+2      Br-       1.56975       0           0           6.78E-3
  Ba+2      Cl-       0.687         0           0           1.417e-2              # ref. 3
  Ba+2      OH-       1.2
  Br-       H+        0.3564        0           0           4.467E-4
  Br-       K+        0.2212        0           0           17.40E-4
  Br-       Li+       0.2547        0           0           6.636E-4
  Br-       Mg+2      1.753         0           0           3.8625E-3
  Br-       Na+       0.2791        0           0           10.79E-4
  Br-       Sr+2      1.7115        0           0           6.5325E-3
  Ca+2      Br-       1.613         0           0           6.0375E-3
  Ca+2      Cl-       1.614         0           0           7.63e-3    -8.19e-7   # ref. 3
  Ca+2      HCO3-     2.977 # ref. 3 + new -analytic for calcite
  Ca+2      HSO4-     2.53
  Ca+2      OH-      -0.2303
  Ca+2      SO4-2     3.546         0           0           5.77e-3               # ref. 3
  Cl-       Fe+2      1.53225
  Cl-       H+        0.2945        0           0           1.419E-4
  Cl-       K+        0.2168        0          -6.895       2.262e-2   -9.293e-6  -1e5  # ref. 3
  Cl-       Li+       0.3074        0           0           5.366E-4
  Cl-       Mg+2      1.65          0           0          -1.09e-2     2.60e-5   # ref. 3
  Cl-       MgOH+     1.658
  Cl-       Mn+2      1.55025
  Cl-       Na+       0.2769        1.377e4    46.8        -6.9512e-2   2e-5      -7.4823e5  # ref. 3
  Cl-       Sr+2      1.667         0           0           2.8425E-3
  CO3-2     K+        1.43          0           0           2.051E-3
  CO3-2     Na+       1.389         0           0           2.05E-3
  Fe+2      HSO4-     3.48
  Fe+2      SO4-2     3.063
  H+        HSO4-     0.5556
  HCO3-     K+        0.25          0           0           1.104E-3              # ref. 3
  HCO3-     Mg+2      0.6072
  HCO3-     Na+       0     # ref. 3 + new -analytic for calcite
  HSO4-     K+        0.1735
  HSO4-     Mg+2      1.729
  HSO4-     Na+       0.398
  K+        OH-       0.32
  K+        SO4-2     0.756        -1.514e4   -80.3         0.1091                # ref. 3
  Li+       OH-       0.14
  Li+       SO4-2     1.2705        0           0           1.41E-3
  Mg+2      SO4-2     3.367        -5.78e3      0          -1.48e-1   1.576e-4    # ref. 3
  Mn+2      SO4-2     2.9511
  Na+       OH-       0.253         0           0           1.34E-4
  Na+       SO4-2     0.956         2.663e3     0           1.158e-2   0         -3.194e5   # ref. 3
  SO4-2     Sr+2      3.1973        0           0          27e-3
-B2
  Ca+2      Cl-      -1.13          0           0        -0.0476                  # ref. 3
  Ca+2      OH-      -5.72
  Ca+2      SO4-2   -59.3           0           0        -0.443       -3.96e-6    # ref. 3
  Fe+2      SO4-2   -42.0
  HCO3-     Na+       8.22          0           0        -0.049                   # ref. 3 + new -analytic for calcite
  Mg+2      SO4-2   -32.45          0          -3.236e3  21.812       -1.8859e-2  # ref. 3
  Mn+2      SO4-2   -40.0
  SO4-2     Sr+2    -54.24          0           0          -0.42
-C0
  B(OH)4-   Na+       0.0114
  Ba+2      Br-      -0.0159576
  Ba+2      Cl-      -0.143      -114.5  # ref. 3
  Br-       Ca+2     -0.00257
  Br-       H+        0.00827       0           0        -5.685E-5
  Br-       K+       -0.00180       0           0        -7.004E-5
  Br-       Li+       0.0053        0           0        -2.813E-5
  Br-       Mg+2      0.00312
  Br-       Na+       0.00116       0           0        -9.30E-5
  Br-       Sr+2      0.00122506
  Ca+2      Cl-       1.4e-4      -57          -0.098    -7.83e-4      7.18e-7    # ref. 3
  Ca+2      SO4-2     0.114  # ref. 3
  Cl-       Fe+2     -0.00860725
  Cl-       H+        0.0008        0           0         6.213E-5
  Cl-       K+       -7.88e-4     91.27        0.58643  -1.298e-3     4.9567e-7  # ref. 3
  Cl-       Li+       0.00359       0           0        -4.520E-5
  Cl-       Mg+2      0.00651       0  0       -2.50e-4   2.418e-7                # ref. 3
  Cl-       Mn+2     -0.0204972
  Cl-       Na+       1.48e-3    -120.5        -0.2081    0            1.166e-7  11121  # ref. 3
  Cl-       Sr+2     -0.00130
  CO3-2     K+       -0.0015
  CO3-2     Na+       0.0044
  Fe+2      SO4-2     0.0209
  H+        SO4-2     0.0438
  HCO3-     K+       -0.008
  K+        OH-       0.0041
  K+        SO4-2     8.18e-3    -625          -3.30      4.06e-3                 # ref. 3
  Li+       SO4-2    -0.00399338    0           0        -2.33345e-4
  Mg+2      SO4-2     2.875e-2      0          -2.084     1.1428e-2   -8.228e-6   # ref. 3
  Mn+2      SO4-2     0.01636
  Na+       OH-       0.0044        0           0       -18.94E-5
  Na+       SO4-2     3.418e-3   -384           0        -8.451e-4     0        5.177e4  # ref. 3
-THETA
  B(OH)4-   Cl-      -0.065
  B(OH)4-   SO4-2    -0.012
  B3O3(OH)4-  Cl-     0.12
  B3O3(OH)4-  HCO3-  -0.10
  B3O3(OH)4-  SO4-2   0.10
  B4O5(OH)4-2  Cl-    0.074
  B4O5(OH)4-2  HCO3- -0.087
  B4O5(OH)4-2  SO4-2  0.12
  Ba+2      Na+       0.07   # ref. 3
  Br-       OH-      -0.065
  Ca+2      H+        0.092
  Ca+2      K+       -5.35e-3       0           0         3.08e-4               # ref. 3
  Ca+2      Mg+2      0.007
  Ca+2      Na+       9.22e-2       0           0        -4.29e-4      1.21e-6  # ref. 3
  Cl-       CO3-2    -0.02
  Cl-       HCO3-     0.03
  Cl-       HSO4-    -0.006
  Cl-       OH-      -0.05
  Cl-       SO4-2     0.03   # ref. 3
  CO3-2     OH-       0.1
  CO3-2     SO4-2     0.02
  H+        K+        0.005
  H+        Mg+2      0.1
  H+        Na+       0.036
  HCO3-     CO3-2    -0.04
  HCO3-     SO4-2     0.01
  K+        Na+      -0.012
  Mg+2      Na+       0.07
  Na+       Sr+2      0.051
  OH-       SO4-2    -0.013
-LAMDA
  B(OH)3    Cl-       0.091
  B(OH)3    K+       -0.14
  B(OH)3    Na+      -0.097
  B(OH)3    SO4-2     0.018
  B3O3(OH)4-  B(OH)3 -0.20
  Ca+2      CO2       0.183
  Ca+2      H4SiO4    0.238    # ref. 3
  Cl-       CO2      -0.005
  CO2       CO2      -1.34e-2   348   0.803 # new VM("CO2"), CO2 solubilities at high P, 0 - 150C
  CO2       HSO4-    -0.003
  CO2       K+        0.051
  CO2       Mg+2      0.183
  CO2       Na+       0.085
  CO2       SO4-2     0.075    # Rumpf and Maurer, 1993.
  H4SiO4    K+        0.0298   # ref. 3
  H4SiO4    Li+       0.143    # ref. 3
  H4SiO4    Mg+2      0.238  -1788   -9.023  0.0103    # ref. 3
  H4SiO4    Na+       0.0566    75.3  0.115            # ref. 3
  H4SiO4    SO4-2    -0.085      0    0.28  -8.25e-4   # ref. 3
-ZETA
  B(OH)3    Cl-       H+        -0.0102
  B(OH)3    Na+       SO4-2      0.046
  Cl-       H4SiO4    K+        -0.0153  # ref. 3
  Cl-       H4SiO4    Li+       -0.0196  # ref. 3
  CO2       Na+       SO4-2     -0.015
-PSI
  B(OH)4-     Cl-     Na+       -0.0073
  B3O3(OH)4-  Cl-     Na+       -0.024
  B4O5(OH)4-2 Cl-     Na+        0.026
  Br-       K+        Na+       -0.0022
  Br-       K+        OH-       -0.014
  Br-       Na+       H+        -0.012
  Br-       Na+       OH-       -0.018
  Ca+2      Cl-       H+        -0.015
  Ca+2      Cl-       K+        -0.025
  Ca+2      Cl-       Mg+2      -0.012
  Ca+2      Cl-       Na+       -1.48e-2  0    0  -5.2e-6       # ref. 3
  Ca+2      Cl-       OH-       -0.025
  Ca+2      Cl-       SO4-2     -0.122    0    0  -1.21e-3      # ref. 3
  Ca+2      K+        SO4-2     -0.0365                         # ref. 3
  Ca+2      Mg+2      SO4-2      0.024
  Ca+2      Na+       SO4-2     -0.055  17.2                    # ref. 3
  Cl-       Br-       K+         0
  Cl-       CO3-2     K+         0.004
  Cl-       CO3-2     Na+        0.0085
  Cl-       H+        K+        -0.011
  Cl-       H+        Mg+2      -0.011
  Cl-       H+        Na+       -0.004
  Cl-       HCO3-     Mg+2      -0.096
  Cl-       HCO3-     Na+        0                              # ref. 3 + new -analytic for calcite
  Cl-       HSO4-     H+         0.013
  Cl-       HSO4-     Na+       -0.006
  Cl-       K+        Mg+2      -0.022  -14.27                  # ref. 3
  Cl-       K+        Na+       -0.0015   0    0   1.8e-5       # ref. 3
  Cl-       K+        OH-       -0.006
  Cl-       K+        SO4-2     -1e-3                           # ref. 3
  Cl-       Mg+2      MgOH+      0.028
  Cl-       Mg+2      Na+       -0.012   -9.51 # ref. 3
  Cl-       Mg+2      SO4-2     -0.008   32.63 # ref. 3
  Cl-       Na+       OH-       -0.006
  Cl-       Na+       SO4-2      0             # ref. 3
  Cl-       Na+       Sr+2      -0.0021
  CO3-2     HCO3-     K+         0.012
  CO3-2     HCO3-     Na+        0.002
  CO3-2     K+        Na+        0.003
  CO3-2     K+        OH-       -0.01
  CO3-2     K+        SO4-2     -0.009
  CO3-2     Na+       OH-       -0.017
  CO3-2     Na+       SO4-2     -0.005
  H+        HSO4-     K+        -0.0265
  H+        HSO4-     Mg+2      -0.0178
  H+        HSO4-     Na+       -0.0129
  H+        K+        Br-       -0.021
  H+        K+        SO4-2      0.197
  HCO3-     K+        Na+       -0.003
  HCO3-     Mg+2      SO4-2     -0.161
  HCO3-     Na+       SO4-2     -0.005
  HSO4-     K+        SO4-2     -0.0677
  HSO4-     Mg+2      SO4-2     -0.0425
  HSO4-     Na+       SO4-2     -0.0094
  K+        Mg+2      SO4-2     -0.048
  K+        Na+       SO4-2     -0.010
  K+        OH-       SO4-2     -0.050
  Mg+2      Na+       SO4-2     -0.015
  Na+       OH-       SO4-2     -0.009
EXCHANGE_MASTER_SPECIES
	X       X-
EXCHANGE_SPECIES
	X- = X-
	log_k	   0.0

	Na+ + X- = NaX
	log_k   0.0

	K+ + X- = KX
	log_k   0.7
	delta_h  -4.3   # Jardine & Sparks, 1984

	Li+ + X- = LiX
	log_k   -0.08
	delta_h  1.4    # Merriam & Thomas, 1956

	Ca+2 + 2X- = CaX2
	log_k   0.8
	delta_h  7.2    # Van Bladel & Gheyl, 1980

	Mg+2 + 2X- = MgX2
	log_k   0.6
	delta_h  7.4    # Laudelout et al., 1968

	Sr+2 + 2X- = SrX2
	log_k   0.91
	delta_h  5.5    # Laudelout et al., 1968

	Ba+2 + 2X- = BaX2
	log_k   0.91
	delta_h  4.5    # Laudelout et al., 1968

	Mn+2 + 2X- = MnX2
	log_k   0.52

	Fe+2 + 2X- = FeX2
	log_k   0.44

SURFACE_MASTER_SPECIES
	Hfo_s  Hfo_sOH
	Hfo_w  Hfo_wOH
SURFACE_SPECIES
#   All surface data from
#   Dzombak and Morel, 1990
#
#
#   Acid-base data from table 5.7
#
#   strong binding site--Hfo_s,

	Hfo_sOH = Hfo_sOH
	log_k  0.0

	Hfo_sOH  + H+ = Hfo_sOH2+
	log_k  7.29    # = pKa1,int

	Hfo_sOH = Hfo_sO- + H+
	log_k  -8.93   # = -pKa2,int

#   weak binding site--Hfo_w

	Hfo_wOH = Hfo_wOH
	log_k  0.0

	Hfo_wOH  + H+ = Hfo_wOH2+
	log_k  7.29    # = pKa1,int

	Hfo_wOH = Hfo_wO- + H+
	log_k  -8.93   # = -pKa2,int

###############################################
#	     CATIONS			 #
###############################################
#
#   Cations from table 10.1 or 10.5
#
#   Calcium
	Hfo_sOH + Ca+2 = Hfo_sOHCa+2
	log_k  4.97

	Hfo_wOH + Ca+2 = Hfo_wOCa+ + H+
	log_k -5.85
#   Strontium
	Hfo_sOH + Sr+2 = Hfo_sOHSr+2
	log_k  5.01

	Hfo_wOH + Sr+2 = Hfo_wOSr+ + H+
	log_k -6.58

	Hfo_wOH + Sr+2 + H2O = Hfo_wOSrOH + 2H+
	log_k -17.60
#   Barium
	Hfo_sOH + Ba+2 = Hfo_sOHBa+2
	log_k  5.46

	Hfo_wOH + Ba+2 = Hfo_wOBa+ + H+
	log_k  -7.2		     # table 10.5
#
#   Derived constants table 10.5
#
#   Magnesium
	Hfo_wOH + Mg+2 = Hfo_wOMg+ + H+
	log_k -4.6
#   Manganese
	Hfo_sOH + Mn+2 = Hfo_sOMn+ + H+
	log_k  -0.4		     # table 10.5

	Hfo_wOH + Mn+2 = Hfo_wOMn+ + H+
	log_k -3.5		      # table 10.5
# Iron
#	Hfo_sOH + Fe+2 = Hfo_sOFe+ + H+
#	log_k   0.7     # LFER using table 10.5

#	Hfo_wOH + Fe+2 = Hfo_wOFe+ + H+
#	log_k -2.5      # LFER using table 10.5

# Iron, strong site: Appelo, Van der Weiden, Tournassat & Charlet, subm.
	 Hfo_sOH + Fe+2 = Hfo_sOFe+ + H+
	 log_k   -0.95
# Iron, weak site: Liger et al., GCA 63, 2939, re-optimized for D&M
	 Hfo_wOH + Fe+2 = Hfo_wOFe+ + H+
	 log_k -2.98

	 Hfo_wOH + Fe+2 + H2O = Hfo_wOFeOH + 2H+
	 log_k -11.55

###############################################
#	     ANIONS			  #
###############################################
#
#   Anions from table 10.6
#
#
#   Anions from table 10.7
#
#   Borate
	Hfo_wOH + B(OH)3 = Hfo_wH2BO3 + H2O
	log_k   0.62
#
#   Anions from table 10.8
#
#   Sulfate
	Hfo_wOH + SO4-2 + H+ = Hfo_wSO4- + H2O
	log_k   7.78

	Hfo_wOH + SO4-2 = Hfo_wOHSO4-2
	log_k   0.79
#
# Carbonate: Van Geen et al., 1994 reoptimized for HFO
# 0.15 g HFO/L has 0.344 mM sites == 2 g of Van Geen's Goethite/L
#
#	Hfo_wOH + CO3-2 + H+ = Hfo_wCO3- + H2O
#	log_k   12.56
#
#	Hfo_wOH + CO3-2 + 2H+= Hfo_wHCO3 + H2O
#	log_k   20.62


END
MEAN GAM
CaCl2
CaSO4
CaCO3
Ca(OH)2
MgCl2
MgSO4
MgCO3
Mg(OH)2
NaCl
Na2SO4
NaHCO3
Na2CO3
NaOH
KCl
K2SO4
KHCO3
K2CO3
KOH
HCl
H2SO4
HBr

END

# For the reaction aA + bB = cC + dD,
#   with delta_v = c*Vm(C) + d*Vm(D) - a*Vm(A) - b*Vm(B),
# PHREEQC adds the pressure term to log_k: -= delta_v * (P - 1) / (2.3RT).
#   Vm(A) is volume of A, cm3/mol, P is pressure, atm, R is the gas constant, T is Kelvin.
# Gas-pressures and fugacity coefficients are calculated with Peng-Robinson's EOS.
#   Binary interaction coefficients from Soreide and Whitson, 1992, FPE 77, 217 are
#    hard-coded in calc_PR():
#    kij    CH4    CO2    H2S    N2
#    H2O    0.49   0.19   0.19   0.49
# =============================================================================================
# The molar volumes of solids are entered with
#                         -Vm vm cm3/mol
#    vm is the molar volume, cm3/mol (default), but dm3/mol and m3/mol are permitted.
# Data for minerals' vm (= MW (g/mol) / rho (g/cm3)) are defined using rho from
#   Deer, Howie and Zussman, The rock-forming minerals, Longman.
#                           --------------------
# Temperature- and pressure-dependent volumina of aqueous species are calculated with a Redlich-
#   type equation (cf. Redlich and Meyer, Chem. Rev. 64, 221), from parameters entered with
#                        -Vm a1 a2 a3 a4 W a0 i1 i2 i3 i4
# The volume (cm3/mol) is
#    Vm(T, pb, I) = 41.84 * (a1 * 0.1 + a2 * 100 / (2600 + pb)  + a3 / (T - 228) +
#                            a4 * 1e4 / (2600 + pb) / (T - 228) - W * QBrn)
#                   + z^2 / 2 * Av * f(I^0.5)
#                   + (i1 + i2 / (T - 228) + i3 * (T - 228)) * I^i4
#   Volumina at I = 0 are obtained using supcrt92 formulas (Johnson et al., 1992, CG 18, 899).
#   41.84 transforms cal/bar/mol into cm3/mol.
#   pb is pressure in bar.
#   W * QBrn is the energy of solvation, QBrn is the pressure dependence of the Born equation,
#     W is fitted on measured solution densities.
#   z is charge of the solute species.
#   Av is the Debye-Hckel limiting slope (DH_AV in PHREEQC basic).
#   a0 is the ion-size parameter in the extended Debye-Hckel equation:
#     f(I^0.5) = I^0.5 / (1 + a0 * DH_B * I^0.5),
#     a0 = -gamma x for cations, = 0 for anions.
# For details, consult ref. 1.
#
# ref. 1: Appelo, Parkhurst and Post, 2014. Geochim. Cosmochim. Acta 125, 4967.
# ref. 2: Procedures from ref. 1 using data compiled by Lalibert, 2009, J. Chem. Eng. Data 54, 1725.
# ref. 3: Appelo, 2015, Appl. Geochem. 55, 6271.
#                 http://www.hydrochemistry.eu/pub/pitzer_db/appendix.zip contains example files
#                 for the high P,T Pitzer model and improvements for Calcite.
#
# =============================================================================================
# It remains the responsibility of the user to check the calculated results, for example with
#   measured solubilities as a function of (P, T).
)xyz";
}