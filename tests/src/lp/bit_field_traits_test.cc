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
 * Bit field traits test
 * @file lp/bit_field_traits_test.cc
 * @author Boris Vinogradov
 */

#include <lp/bit_field.hh>
#include <lp/bit_field_traits.hh>
#include <type_traits.hh>

template<int input_value, lp::word_t ...options>
constexpr const int get_value() noexcept {
    int value = 0;

    lp::get_value_of<int, lp::bit_field<options...>>::
        get_value(input_value, value);

    return value;
};

void bit_field_traits_test() {
    using namespace lp;

    static_assert(
        const_value_of<int, bit_field<0>, bit_field<2>>::value == 0b101, "");

    static_assert(
        const_value_of<
            int, bit_field<0>, bit_field<2>>::value_of(0b10) == 0b111, "");

    static_assert(
        const_value_of<
            int, bit_field<1, 2>>::value_of(0b1000) == 0b1110, "");

    static_assert(
        variable_value_of<
            int, bit_field<0>>::value_of(0b10, bit_field<0>{}) == 0b11, "");

    static_assert(
        variable_value_of<
            int, bit_field<1, 2>>::
                value_of(0b1000, bit_field<1, 2>{0b01}) == 0b1010, "");

    constexpr const int value1 = get_value<0b1010, 0>(),
        value2 = get_value<0b1010, 1, 2>();

    static_assert(value1 == 0b0 && value2 == 0b1, "");
}
