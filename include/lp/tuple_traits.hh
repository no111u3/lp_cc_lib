/* Copyright 2018 Boris Vinogradov <no111u3@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Lepestrum C++ Library implementation
 * Extend stl tuple traits
 * @file lp/tuple_traits.hh
 * @author Boris Vinogradov
 */

#include <tuple.hh>

#ifndef LP_CC_LIB_LP_TUPLE_TRAITS_HH
#define LP_CC_LIB_LP_TUPLE_TRAITS_HH

namespace lp {
    /// Append element to tuple
    template <typename ...T_types, typename ...Types>
    static constexpr auto
    tuple_append(std::tuple<T_types ...> tuple, Types ...ts) noexcept {
        return std::tuple_cat(tuple, std::make_tuple(ts...));
    }

    /// Insert element to tuple
    template <typename ...T_types, typename ...Types>
    static constexpr auto
    tuple_insert(std::tuple<T_types ...> tuple, Types ...ts) noexcept {
        return std::tuple_cat(std::make_tuple(ts...), tuple);
    }
} // namespace lp

#endif // LP_CC_LIB_LP_TUPLE_TRAITS_HH
