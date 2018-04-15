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
 * Associate bit test
 * @file associate_bit_test.cc
 * @author Boris Vinogradov
 */

#include <type_traits.hh>
#include <associate_bit.hh>
#include <io_register.hh>

void associate_bit_test() {
    using namespace lp;

    using test_register = io_register<int, 0x400>;
    using first_bit = assoc_bit<test_register, 0>;
    using second_bit = assoc_bit<test_register, 1, 2>;
    using third_bit = assoc_bit<test_register, 2, 3>;

    static_assert(std::is_same<first_bit::bit, bit<0>>::value, "");

    static_assert(first_bit::mask<int>::value == 0b1, "");
    
    static_assert(std::is_same<first_bit::type, or_type>::value, "");

    static_assert(std::is_same<first_bit::register_type, test_register>::value, "");
    
    static_assert(std::is_same<second_bit::bit_type, bit<1, 2>>::value, "");
    
    static_assert(second_bit::mask<unsigned>::value == 0b110, "");
    
    static_assert(std::is_same<second_bit::register_type, test_register>::value, "");

    static_assert(third_bit::with_value<0b101>::mask<unsigned>::value == 0b10100, "");
    
    static_assert(std::is_same<second_bit::with_value<0b101>::register_type, test_register>::value, "");

    static_assert(first_bit::op_or::mask<unsigned>::value == 0b1, "");
    
    static_assert(second_bit::op_or::mask<unsigned>::value == 0b110, "");

    static_assert(std::is_same<second_bit::op_or::register_type, test_register>::value, "");

    static_assert(std::is_same<second_bit::with_value<0b101>::op_or::register_type, test_register>::value, "");
}
