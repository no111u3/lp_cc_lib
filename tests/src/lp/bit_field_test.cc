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
 * Bit field test
 * @file lp/bit_field_test.cc
 * @author Boris Vinogradov
 */

#include <lp/bit_field.hh>
#include <type_traits.hh>

void bit_field_test() {
    using namespace lp;

    static_assert(std::is_same<bit_field<0>, bit_field<0>>::value, "");

    static_assert(std::is_same<bit_field<0, 2>, bit_field<0, 2>>::value, "");

    static_assert(bit_field<0>::mask_value<unsigned>::value == 0b1, "");

    static_assert(bit_field<0>::mask_value<unsigned>::mask == 0b1, "");

    static_assert(bit_field<0>::mask_value<int>::value == 0b1, "");

    static_assert(bit_field<4>{}.set<int>(0) == 0b10000, "");

    static_assert(bit_field<4>{}.clear<int>(0b10000) == 0b0, "");

    static_assert(bit_field<4>{}.toggle<int>(0b10000) == 0b0, "");

    static_assert(bit_field<4>{}.get<int, int>(0b10000) == 0b1, "");

    static_assert(bit_field<1, 2>::mask_value<unsigned>::value == 0b110, "");

    static_assert(bit_field<1, 2>::mask_value<unsigned>::mask == 0b110, "");

    static_assert(bit_field<1, 2>::mask_value<int>::value == 0b110, "");

    static_assert(bit_field<3, 2>{}.set<int>(0b1) == 0b11001, "");

    static_assert(bit_field<3, 2>{0b10}.set<int>(0b1) == 0b10001, "");

    static_assert(bit_field<3, 2>{0b10}.clear<int>(0b10001) == 0b1, "");

    static_assert(bit_field<3, 2>{0b10}.toggle<int>(0b10001) == 0b10001, "");

    static_assert(bit_field<3, 2>{}.get<int, int>(0b10001) == 0b10, "");

    static_assert(bit_field<0, 32>::
        mask_value<unsigned>::value == 0xffff'ffff, "");

    static_assert(
        bit_field<2, 3>::with_value<0b101>::
            mask_value<unsigned>::value == 0b10100, "");

    static_assert(
        bit_field<2, 3>::with_value<0b101>::
            mask_value<unsigned>::mask == 0b11100, "");
}
