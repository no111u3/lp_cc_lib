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
 * Type list traits
 * @file type_list_traits.hh
 * @author Boris Vinogradov
 */

#include <type_list.hh>

#ifndef LP_CC_LIB_TYPE_LIST_TRAITS_HH
#define LP_CC_LIB_TYPE_LIST_TRAITS_HH

namespace lp {
    /// Repack multilevel types to single layer type list
    template <typename ...Types>
    struct repack;

    template <>
    struct repack<> {
        using type = type_list<>;
    };

    template <typename ...Types>
    struct repack<type_list<>, Types...> {
        using type = typename type_list<>::template append<Types...>;
    };

    template <typename ...Types1, typename ...Types2>
    struct repack<type_list<Types1...>, Types2...> {
        using type = typename repack<Types1...>::type::template extend<typename repack<Types2...>::type>;
    };

    template <typename Type, typename ...Types>
    struct repack<Type, Types...> {
        using type = typename repack<Types...>::type:: template insert<Type>;
    };

    template <typename ...Types>
    using repack_v = typename type_list<Types...>::template assign<repack>::type;
} // namespace lp

#endif // LP_CC_LIB_TYPE_LIST_TRAITS_HH
