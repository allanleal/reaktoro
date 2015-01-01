// Reaktor is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <functional>

// Reaktor includes
#include <Reaktor/Common/Matrix.hpp>

namespace Reaktor {

/// A type that describes the functional signature of an objective function
/// @param x The vector of primal variables
/// @return The objective function evaluated at `x`
using ObjectiveFunction = std::function<double(const Vector& x)>;

/// A type that describes the functional signature of the gradient of an objective function
/// @param x The vector of primal variables
/// @return The gradient vector of the objective function evaluated at `x`
using ObjectiveGradFunction = std::function<Vector(const Vector& x)>;

/// A type that describes the functional signature of the Hessian matrix of an objective function
/// @param x The vector of primal variables
/// @return The Hessian matrix of the objective function evaluated at `x`
using ObjectiveHessianFunction = std::function<Matrix(const Vector& x)>;

/// A type that describes the functional signature of the diagonal Hessian matrix of an objective function
/// @param x The vector of primal variables
/// @return The diagonal Hessian matrix of the objective function evaluated at `x`
using ObjectiveDiagonalHessianFunction = std::function<Vector(const Vector& x)>;

/// A type that describes the functional signature of the inverse of the Hessian matrix of an objective function
/// @param x The vector of primal variables
/// @param g The gradient of the objective function evaluated at `x`
/// @return The inverse of the Hessian matrix of the objective function evaluated at `x`
using ObjectiveInverseHessianFunction = std::function<Matrix(const Vector& x, const Vector& g)>;

/// A type that describes the functional signature of a constraint function
/// @param x The vector of primal variables
/// @return The constraint function evaluated at `x`
using ConstraintFunction = std::function<Vector(const Vector& x)>;

/// A type that describes the functional signature of the gradient of an objective function
/// @param x The vector of primal variables
/// @return The gradient matrix of the constraint function evaluated at `x`
using ConstraintGradFunction = std::function<Matrix(const Vector& x)>;

/// A type to describe the possible schemes for the representation of the Hessian function
enum class HessianScheme
{
    Regular = 0, Diagonal = 1, Inverse = 2,
};

/// A type that describes the definition of an optimisation problem
class OptimumProblem
{
public:

    /// Construct a OptimumProblem instance
    /// @param num_variables The number of primal variables
    /// @param num_constraints The number of equality constraints
    OptimumProblem(unsigned num_variables, unsigned num_constraints);

    /// Set the objective function
    /// @param f The objective function
    auto setObjective(const ObjectiveFunction& f) -> void;

    /// Set the gradient function of the objective function
    /// @param g The gradient function of the objective function
    auto setObjectiveGrad(const ObjectiveGradFunction& g) -> void;

    /// Set the Hessian function of the objective function
    /// @param H The Hessian function of the objective function
    auto setObjectiveHessian(const ObjectiveHessianFunction& H) -> void;

    /// Set the diagonal Hessian function of the objective function
    /// @param diagH The diagonal Hessian function of the objective function
    auto setObjectiveDiagonalHessian(const ObjectiveDiagonalHessianFunction& diagH) -> void;

    /// Set the inverse Hessian function of the objective function
    /// @param invH The inverse Hessian function of the objective function
    auto setObjectiveInverseHessian(const ObjectiveInverseHessianFunction& invH) -> void;

    /// Set the equality constraint function
    /// @param h The equality constraint function
    auto setConstraint(const ConstraintFunction& h) -> void;

    /// Set the gradient function of the equality constraint function
    /// @param A The gradient function of the equality constraint function
    auto setConstraintGrad(const ConstraintGradFunction& A) -> void;

    /// Set the lower bounds of the optimisation problem
    /// @param l The lower bounds of the primal variables
    auto setLowerBounds(const Vector& lower) -> void;

    /// Set the lower bounds of the optimisation problem
    /// @param l The lower bounds of the primal variables
    auto setLowerBounds(double lower) -> void;

    /// Set the lower bounds of the optimisation problem
    /// @param u The upper bounds of the primal variables
    auto setUpperBounds(const Vector& upper) -> void;

    /// Set the lower bounds of the optimisation problem
    /// @param u The upper bounds of the primal variables
    auto setUpperBounds(double upper) -> void;

    /// Get the number of variables in the optimisation problem
    auto numVariables() const -> unsigned;

    /// Get the number of equality constraints in the optimisation problem
    auto numConstraints() const -> unsigned;

    /// Get the lower bounds of the optimisation problem
    auto lowerBounds() const -> const Vector&;

    /// Get the upper bounds of the optimisation problem
    auto upperBounds() const -> const Vector&;

    /// Evaluate the objective function at `x`
    /// @param x The vector of primal variables
    auto objective(const Vector& x) const -> double;

    /// Evaluate the gradient function of the objective function at `x`
    /// @param x The vector of primal variables
    auto objectiveGrad(const Vector& x) const -> Vector;

    /// Evaluate the Hessian function of the objective function at `x`
    /// @param x The vector of primal variables
    auto objectiveHessian(const Vector& x) const -> Matrix;

    /// Evaluate the diagonal Hessian function of the objective function at `x`
    /// @param x The vector of primal variables
    auto objectiveDiagonalHessian(const Vector& x) const -> Vector;

    /// Evaluate the inverse function of the Hessian of the objective function at `x`
    /// @param x The vector of primal variables
    /// @param g The gradient of the objective function evaluated at `x`
    auto objectiveInverseHessian(const Vector& x, const Vector& g) const -> Matrix;

    /// Evaluate the equality constraint function at `x`
    /// @param x The vector of primal variables
    auto constraint(const Vector& x) const -> Vector;

    /// Evaluate the gradient of the equality constraint function at `x`
    /// @param x The vector of primal variables
    auto constraintGrad(const Vector& x) const -> Matrix;

    /// Return the scheme for the Hessian representation of the objective function
    auto hessianScheme() const -> HessianScheme;

private:
    /// The number of primal variables
    unsigned n;

    /// The number of equality constraints
    unsigned m;

    /// The objective function
    ObjectiveFunction f;

    /// The gradient function of the objective function
    ObjectiveGradFunction g;

    /// The Hessian function of the objective function
    ObjectiveHessianFunction H;

    /// The diagonal Hessian function of the objective function
    ObjectiveDiagonalHessianFunction diagH;

    /// The inverse function of the Hessian of the objective function
    ObjectiveInverseHessianFunction invH;

    /// The scheme for the Hessian representation of the objective function
    HessianScheme hessian_scheme;

    /// The equality constraint function
    ConstraintFunction h;

    /// The gradient function of the equality constraint function
    ConstraintGradFunction A;

    /// The lower bound vector of the inequality constraints in the optimisation problem
    Vector l;

    /// The upper bound vector of the inequality constraints in the optimisation problem
    Vector u;
};

} // namespace Reaktor
