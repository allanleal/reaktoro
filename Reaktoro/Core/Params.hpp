// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright © 2014-2021 Allan Leal
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

#pragma once

// Reaktoro includes
#include <Reaktoro/Common/Matrix.hpp>
#include <Reaktoro/Common/Types.hpp>
#include <Reaktoro/Core/Param.hpp>

namespace Reaktoro {

// using Vec<Param> = Vec<Param>;

// /// The class used to store and retrieve model parameters.
// /// @ingroup Core
// class Vec<Param>
// {
// public:
//     /// Construct a default Vec<Param> instance.
//     Vec<Param>();

//     /// Construct a default Vec<Param> instance.
//     Vec<Param>(const std::initializer_list<Param>& params);

//     /// Return a deep copy of this Vec<Param> object.
//     auto clone() const -> Vec<Param>;

//     /// Append a new parameter to the list of parameters.
//     auto append(const Param& param) -> Param&;

//     /// Append a new parameter to the list of parameters with given @p id and @p value.
//     auto append(const String& id, const real& value) -> Param&;

//     /// Resize this container of parameters.
//     auto resize(Index size) -> void;

//     /// Return the number of parameters.
//     auto size() const -> Index;

//     /// Return the parameter with given index.
//     auto operator[](Index i) -> Param&;

//     /// Return the parameter with given index.
//     auto operator[](Index i) const -> const Param&;

//     /// Return the parameter with given identifier.
//     /// @warning A runtime error is thrown if there is no parameter with identifier @p id.
//     auto operator[](const String& id) -> Param&;

//     /// Return the parameter with given identifier.
//     /// @warning A runtime error is thrown if there is no parameter with identifier @p id.
//     auto operator[](const String& id) const -> const Param&;

//     /// Return the index of the first parameter with given identifier or the number of parameters if not found.
//     auto find(const String& id) const -> Index;

//     /// Return the index of the first parameter with given identifier or throw a runtime error if not found.
//     auto index(const String& id) const -> Index;

//     /// Return the first parameter with given identifier or throw a runtime error if not found.
//     auto get(const String& id) -> Param&;

//     /// Return the first parameter with given identifier or throw a runtime error if not found.
//     auto get(const String& id) const -> const Param&;

//     /// Return true if a parameter exists with given identifier.
//     auto exists(const String& id) const -> bool;

//     /// Return the container of parameters.
//     auto data() const -> const Vec<Param>&;

//     /// Convert this Vec<Param> object into a VectorXr object.
//     operator VectorXr() const;

//     /// Convert this Vec<Param> object into a VectorXd object.
//     operator VectorXd() const;

// private:
//     Vec<Param> m_data;

// public:
//     /// Construct an Vec<Param> object with given begin and end iterators.
//     template<typename InputIterator>
//     Vec<Param>(InputIterator begin, InputIterator end) : m_data(begin, end) {}

//     /// Return begin const iterator of this Vec<Param> instance (for STL compatibility reasons).
//     auto begin() const { return m_data.begin(); }

//     /// Return begin iterator of this Vec<Param> instance (for STL compatibility reasons).
//     auto begin() { return m_data.begin(); }

//     /// Return end const iterator of this Vec<Param> instance (for STL compatibility reasons).
//     auto end() const { return m_data.end(); }

//     /// Return end iterator of this Vec<Param> instance (for STL compatibility reasons).
//     auto end() { return m_data.end(); }

//     /// Append a new Param at the back of the container (for STL compatibility reasons).
//     auto push_back(const Param& param) -> void { append(param); }

//     /// Insert a container of Param objects into this Vec<Param> instance (for STL compatibility reasons).
//     template<typename Iterator, typename InputIterator>
//     auto insert(Iterator pos, InputIterator begin, InputIterator end) -> void { m_data.insert(pos, begin, end); }

//     /// The type of the value stored in a Vec<Param> (for STL compatibility reasons).
//     using value_type = Param;
// };

// } // namespace Reaktoro

// //======================================================================
// // CODE BELOW NEEDED FOR MEMOIZATION TECHNIQUE INVOLVING PARAMS
// //======================================================================

// namespace Reaktoro {

// /// Specialize MemoizationTraits for Vec<Param>.
// template<typename T>
// struct MemoizationTraits;

// template<>
// struct MemoizationTraits<Vec<Param>>
// {
//     using CacheType = VectorXr;

//     static auto equal(const VectorXr& a, const Vec<Param>& b)
//     {
//         if(a.size() != b.size()) return false;
//         for(auto i = 0; i < a.size(); ++i)
//             if(a[i] != b[i].value())
//                 return false;
//         return true;
//     }

//     static auto assign(VectorXr& a, const Vec<Param>& b)
//     {
//         a.resize(b.size());
//         for(auto i = 0; i < a.size(); ++i)
//             a[i] = b[i].value();
//     }
// };

// } // namespace Reaktoro

// //======================================================================
// // CODE BELOW NEEDED FOR AUTOMATIC DIFFERENTIATION INVOLVING PARAMS
// //======================================================================

// namespace autodiff {
// namespace detail {

// /// Implementation of VectorTraits for Reaktoro::Vec<Param>.
// template<>
// struct VectorTraits<Reaktoro::Vec<Param>>
// {
//     using ValueType = Reaktoro::Param;

//     template<typename NewValueType>
//     using ReplaceValueType = std::vector<NewValueType>;
// };

// } // namespace autodiff
} // namespace detail


