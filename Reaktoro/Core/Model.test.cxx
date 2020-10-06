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
#include <Reaktoro/Core/Model.hpp>
using namespace Reaktoro;

template<typename T>
constexpr auto into(T& var) -> T& { return var; }

const auto check_evaluation = [](auto a, auto b, auto A, auto B, auto factor, auto model)
{
    REQUIRE( model.initialized() );

    auto res = model(a, b);

    const auto xres = A*a*a + B*b*b + 2*a*b*A*B; // xres is expected(res)

    CHECK( res == Approx(xres) );

    model.apply(into(res), a, b); // res should become factor*xres depending on the use of evaluator or calculator

    CHECK( res == Approx(factor * xres) );
};

const auto check_params_update_and_evaluation = [](auto a, auto b, auto Anew, auto Bnew, auto factor, auto model)
{
    Params params;
    params.set("A", Anew);
    params.set("B", Bnew);

    model = model.withParams(params);

    check_evaluation(a, b, Anew, Bnew, factor, model);
};

TEST_CASE("Testing Model class", "[Model]")
{
    const auto a = 4.0;
    const auto b = 5.0;

    const auto A = 2.0;
    const auto B = 3.0;

    const auto Anew = 7.0;
    const auto Bnew = 9.0;

    SECTION("Testing constructor Model()")
    {
        Model<real(real)> model;

        CHECK( model.initialized() == false );
    }

    SECTION("Testing constructor Model(const ModelCreator&, const Params&)")
    {
        auto creatorfn = [](const Params& params)
        {
            const real A = params.get("A");
            const real B = params.get("B");

            return [=](real& res, real a, real b)
            {
                res += A*a*a + B*b*b + 2*a*b*A*B;
            };
        };

        Params params;
        params.set("A", A);
        params.set("B", B);

        Model<real(real, real)> model(creatorfn, params);

        CHECK( real(model.params().get("A")) == A );
        CHECK( real(model.params().get("B")) == B );

        const auto factor = 2.0;

        WHEN("Checking evaluation with initial params")
        {
            check_evaluation(a, b, A, B, factor, model);
        }

        WHEN("Checking evaluation with updated params")
        {
            check_params_update_and_evaluation(a, b, Anew, Bnew, factor, model);
        }
    }

    SECTION("Testing constructor Model(const ModelEvaluator&)")
    {
        auto evalfn = [=](real& res, real a, real b)
        {
            res += A*a*a + B*b*b + 2*a*b*A*B;
        };

        Model<real(real, real)> model(evalfn);

        const auto factor = 2.0;

        WHEN("Checking evaluation with initial params")
        {
            check_evaluation(a, b, A, B, factor, model);
        }

        WHEN("Checking evaluation with updated params")
        {
            Params params;
            params.set("A", Anew);
            params.set("B", Bnew);

            model = model.withParams(params);

            check_evaluation(a, b, A, B, factor, model);

            // Note: In above check, initial A and B are used.
            // This is because the used Model constructor does
            // not use a ModelCreator function that knows how
            // to update the ModelEvaluator function with changes
            // in parameters. Does, changing the parameters in this
            // model function object produces the exact same evaluator.
        }
    }

    SECTION("Testing constructor Model(const ModelCalculator&)")
    {
        auto calcfn = [=](real a, real b) -> real
        {
            return A*a*a + B*b*b + 2*a*b*A*B;
        };

        Model<real(real, real)> model(calcfn);

        const auto factor = 1.0;

        WHEN("Checking evaluation with initial params")
        {
            check_evaluation(a, b, A, B, factor, model);
        }

        WHEN("Checking evaluation with updated params")
        {
            Params params;
            params.set("A", Anew);
            params.set("B", Bnew);

            model = model.withParams(params);

            check_evaluation(a, b, A, B, factor, model);

            // Note: In above check, initial A and B are used.
            // This is because the used Model constructor does
            // not use a ModelCreator function that knows how
            // to update the ModelEvaluator function with changes
            // in parameters. Does, changing the parameters in this
            // model function object produces the exact same evaluator.
        }
    }

    SECTION("Testing static member method Model::Constant")
    {
        auto model = Model<real(real, real)>::Constant(11.0, "MyConstant");

        CHECK( real(model.params().get("MyConstant")) == 11.0 );

        CHECK( model(a, b) == 11.0 );

        real res = 10.0;

        model.apply(into(res), a, b);

        CHECK( res == 11.0 );
    }
}
