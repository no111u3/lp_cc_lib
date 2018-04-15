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
 * Bit test
 * @file bit_test.cc
 * @author Boris Vinogradov
 */

#include <bit.hh>
#include <type_traits.hh>

void bit_test() {
    using namespace lp;

    static_assert(std::is_same<bit<0>, bit<0>>::value, "");

    static_assert(std::is_same<bit<0, 2>, bit<0, 2>>::value, "");

    static_assert(bit<0>::mask<unsigned>::value == 0b1, "");

    static_assert(bit<0>::mask<int>::value == 0b1, "");

    static_assert(bit<1, 2>::mask<unsigned>::value == 0b110, "");

    static_assert(bit<1, 2>::mask<int>::value == 0b110, "");
    
    static_assert(bit<0, 32>::mask<unsigned>::value == 0xffff'ffff, "");

    static_assert(bit<2, 3>::with_value<0b101>::mask<unsigned>::value == 0b10100, "");

    static_assert(bit<1, 2>::op_or::mask<unsigned>::value == 0b110, "");

    static_assert(bit<2, 3>::with_value<0b101>::op_and::mask<unsigned>::value == 0b10100, "");

    static_assert(std::is_same<bit<1, 2>::op_or::type, or_type>::value, "");

    static_assert(std::is_same<bit<2, 3>::with_value<0b101>::op_and::type, and_type>::value, "");
}
