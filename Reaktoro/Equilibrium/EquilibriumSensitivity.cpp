// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright © 2014-2022 Allan Leal
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

#include "EquilibriumSensitivity.hpp"

// Reaktoro includes
#include <Reaktoro/Equilibrium/EquilibriumDims.hpp>

namespace Reaktoro {

EquilibriumSensitivity::EquilibriumSensitivity()
{}

EquilibriumSensitivity::EquilibriumSensitivity(EquilibriumSpecs const& specs)
{
    initialize(specs);
}

auto EquilibriumSensitivity::initialize(EquilibriumSpecs const& specs) -> void
{
    msystem = specs.system();
    minputs = specs.inputs();

    const EquilibriumDims dims(specs);

    const auto Nw = dims.Nw;
    const auto Nn = dims.Nn;
    const auto Np = dims.Np;
    const auto Nq = dims.Nq;
    const auto Nb = dims.Nb;

    mdndw.resize(Nn, Nw);
    mdpdw.resize(Np, Nw);
    mdqdw.resize(Nq, Nw);
    mdndb.resize(Nn, Nb);
    mdpdb.resize(Np, Nb);
    mdqdb.resize(Nq, Nb);
}

auto EquilibriumSensitivity::dndw(String const& wid) const -> VectorXdConstRef
{
    const auto idx = index(minputs, wid);
    return mdndw.col(idx);
}

auto EquilibriumSensitivity::dndw(Param const& param) const -> VectorXdConstRef
{
    return dndw(param.id());
}

auto EquilibriumSensitivity::dndw() const -> MatrixXdConstRef
{
    return mdndw;
}

auto EquilibriumSensitivity::dndw(MatrixXdConstRef data) -> void
{
    errorif(mdndw.rows() != data.rows(), "Mismatch number of rows in call to EquilibriumSensitivity::dndw(MatrixXdConstRef).");
    errorif(mdndw.cols() != data.cols(), "Mismatch number of cols in call to EquilibriumSensitivity::dndw(MatrixXdConstRef).");
    mdndw = data;
}

auto EquilibriumSensitivity::dpdw(String const& wid) const -> VectorXdConstRef
{
    const auto idx = index(minputs, wid);
    return mdpdw.col(idx);
}

auto EquilibriumSensitivity::dpdw(Param const& param) const -> VectorXdConstRef
{
    return dpdw(param.id());
}

auto EquilibriumSensitivity::dpdw() const -> MatrixXdConstRef
{
    return mdpdw;
}

auto EquilibriumSensitivity::dpdw(MatrixXdConstRef data) -> void
{
    errorif(mdpdw.rows() != data.rows(), "Mismatch number of rows in call to EquilibriumSensitivity::dpdw(MatrixXdConstRef).");
    errorif(mdpdw.cols() != data.cols(), "Mismatch number of cols in call to EquilibriumSensitivity::dpdw(MatrixXdConstRef).");
    mdpdw = data;
}

auto EquilibriumSensitivity::dqdw(String const& wid) const -> VectorXdConstRef
{
    const auto idx = index(minputs, wid);
    return mdqdw.col(idx);
}

auto EquilibriumSensitivity::dqdw(Param const& param) const -> VectorXdConstRef
{
    return dqdw(param.id());
}

auto EquilibriumSensitivity::dqdw() const -> MatrixXdConstRef
{
    return mdqdw;
}

auto EquilibriumSensitivity::dqdw(MatrixXdConstRef data) -> void
{
    errorif(mdqdw.rows() != data.rows(), "Mismatch number of rows in call to EquilibriumSensitivity::dqdw(MatrixXdConstRef).");
    errorif(mdqdw.cols() != data.cols(), "Mismatch number of cols in call to EquilibriumSensitivity::dqdw(MatrixXdConstRef).");
    mdqdw = data;
}

auto EquilibriumSensitivity::dndb() const -> MatrixXdConstRef
{
    return mdndb;
}

auto EquilibriumSensitivity::dndb(MatrixXdConstRef data) -> void
{
    errorif(mdndb.rows() != data.rows(), "Mismatch number of rows in call to EquilibriumSensitivity::dndb(MatrixXdConstRef).");
    errorif(mdndb.cols() != data.cols(), "Mismatch number of cols in call to EquilibriumSensitivity::dndb(MatrixXdConstRef).");
    mdndb = data;
}

auto EquilibriumSensitivity::dpdb() const -> MatrixXdConstRef
{
    return mdpdb;
}

auto EquilibriumSensitivity::dpdb(MatrixXdConstRef data) -> void
{
    errorif(mdpdb.rows() != data.rows(), "Mismatch number of rows in call to EquilibriumSensitivity::dpdb(MatrixXdConstRef).");
    errorif(mdpdb.cols() != data.cols(), "Mismatch number of cols in call to EquilibriumSensitivity::dpdb(MatrixXdConstRef).");
    mdpdb = data;
}

auto EquilibriumSensitivity::dqdb() const -> MatrixXdConstRef
{
    return mdqdb;
}

auto EquilibriumSensitivity::dqdb(MatrixXdConstRef data) -> void
{
    errorif(mdqdb.rows() != data.rows(), "Mismatch number of rows in call to EquilibriumSensitivity::dqdb(MatrixXdConstRef).");
    errorif(mdqdb.cols() != data.cols(), "Mismatch number of cols in call to EquilibriumSensitivity::dqdb(MatrixXdConstRef).");
    mdqdb = data;
}

auto EquilibriumSensitivity::dudw() const -> MatrixXdConstRef
{
    return mdudw;
}

auto EquilibriumSensitivity::dudb() const -> MatrixXdConstRef
{
    return mdudb;
}

auto EquilibriumSensitivity::dudw(MatrixXdConstRef data) -> void
{
    mdudw = data;
}

auto EquilibriumSensitivity::dudb(MatrixXdConstRef data) -> void
{
    mdudb = data;
}

} // namespace Reaktoro
