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
 * Type list traits test
 * @file lp/type_list_traits_test.cc
 * @author Boris Vinogradov
 */

#include <lp/type_list.hh>
#include <lp/type_list_traits.hh>

#include <type_traits.hh>

void type_list_traits_test() {
    using namespace lp;

    using test_hierarhial_type_list =
        type_list<char, type_list<short, int>, long, type_list<type_list<>>>;
    using test_type_list = type_list<char, short, int, long>;
    using test_repited_list = type_list<int, long, char, int, short>;

    static_assert(std::is_same<
        test_type_list::assign<repack>::type, test_type_list>::value, "");

    static_assert(std::is_same<
        test_hierarhial_type_list::assign<repack>::type,
        test_type_list>::value, "");

    static_assert(std::is_same<
        repack_t<test_hierarhial_type_list>, test_type_list>::value, "");

    static_assert(std::is_same<
        repack_t<char, type_list<short, int>, long, type_list<type_list<>>>,
        test_type_list>::value, "");

    static_assert(std::is_same<unique_t<int, int>, type_list<int>>::value, "");

    static_assert(std::is_same<
        unique_t<int, long, char, int, short>,
        type_list<int, long, char, short>>::value, "");

    static_assert(std::is_same<
        unique_t<test_repited_list>,
        type_list<int, long, char, short>>::value, "");

    static_assert(std::is_same<
        unique_t<test_type_list>,
        test_type_list>::value, "");

    static_assert(std::is_same<
        for_each_t<std::make_signed, test_type_list>,
        type_list<signed char, signed short, signed int, signed long>
        >::value, "");

    static_assert(std::is_same<
        for_each_t<std::is_integral, int, void, float, double, char, bool>,
        type_list<std::true_type, std::false_type, std::false_type,
            std::false_type, std::true_type, std::true_type>>::value, "");
}
