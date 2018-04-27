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
 * Tuple traits test
 * @file lp/tuple_traits_test.cc
 * @author Boris Vinogradov
 */

#include <lp/tuple_traits.hh>

#include <type_traits.hh>

void tuple_traits_test() {
    using namespace lp;

    static_assert(
        tuple_append(std::make_tuple(1), 2) ==
        std::make_tuple(1, 2), "");

    static_assert(
        tuple_append(std::tuple<>{}, 1, 2) ==
        std::make_tuple(1, 2), "");

    static_assert(
        tuple_insert(std::make_tuple(1), 2) ==
        std::make_tuple(2, 1), "");

    static_assert(
        tuple_insert(std::tuple<>{}, 1, 2) ==
        std::make_tuple(1, 2), "");
}
