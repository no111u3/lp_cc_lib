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
 * Operation traits test
 * @file operation_traits_test.cc
 * @author Boris Vinogradov
 */

#include <bit.hh>
#include <operation_traits.hh>
#include <type_list.hh>

void operation_traits_test() {
    using namespace lp;

    static_assert(op_unpack<int, 0, bit<0>::op_or>::value == 0b1, "");

    static_assert(op_unpack<int, 0b10100, bit<2, 3>::with_value<0b101>::op_xor>::value == 0b0, "");

    static_assert(op_unpack<int, 0b11011, bit<0, 2>::op_nand, bit<2>::op_or>::value == 0b11100, "");

    static_assert(op_unpack<int, 0, bit<0>, bit<2, 3>, bit<1>>::value == 0b11111, "");

    static_assert(op_unpack<int, 0, type_list<bit<0>, bit<2, 3>, bit<1>>>::value == 0b11111, "");
}
