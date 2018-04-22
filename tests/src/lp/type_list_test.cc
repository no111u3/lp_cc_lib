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
 * Type list test
 * @file lp/type_list_test.cc
 * @author Boris Vinogradov
 */

#include <lp/type_list.hh>
#include <type_traits.hh>

template <typename ...Types>
struct size_of;

template <>
struct size_of<> {
    constexpr static long size = 0;
};

template <typename Type>
struct size_of<Type> {
    constexpr static long size = sizeof(Type);
};

template <typename Type, typename ...Types>
struct size_of<Type, Types...> {
    constexpr static long size =
        size_of<Type>::size +
        size_of<Types...>::size;
};

template <typename ...Types>
constexpr long size_of_value = size_of<Types...>::size;

template <typename T>
using is_same_int = std::is_same<int, T>;

template <typename T>
using is_same_double = std::is_same<double, T>;

void type_list_test() {
    using namespace lp;

    // Equal empty type_list
    static_assert(std::is_same<type_list<>, type_list<>>::value, "");

    // Get head
    static_assert(std::is_same<
        type_list<int, long, double>::head, int>::value, "");

    // Get tail
    static_assert(std::is_same<
        type_list<char, short, double>::tail,
            type_list<short, double>>::value, "");

    // Get head from empty type_list
    static_assert(std::is_same<type_list<>::head, std::none_type>::value, "");

    // Get tail from empty type_list
    static_assert(std::is_same<type_list<>::tail, std::none_type>::value, "");

    // Int type_list
    using int_types = type_list<char, short, int, long>;

    // Append to type_list
    static_assert(std::is_same<
        type_list<char, short>::append<int, long>,
        int_types>::value, "");

    // Join two type_list
    static_assert(std::is_same<
        join<type_list<char, short>, type_list<int, long>>,
        int_types>::value, "");

    // Extend type_list
    static_assert(std::is_same<
        type_list<char, short>::extend<type_list<int, long>>,
        int_types>::value, "");

    // Getting by index
    static_assert(std::is_same<int_types::get<2>, int>::value, "");

    // Getting by wrond index
    // static_assert(std::is_same<type_list<char, short, int, long>::get<4>, none_type>::value, "");

    // Assign from type_list to type
    static_assert(
        int_types::assign<size_of>::size ==
            sizeof(char) +
            sizeof(short) +
            sizeof(int) +
            sizeof(long), "");

    // Find exist type
    static_assert(std::is_same<int_types::find<is_same_int>, int>::value, "");

    // Find non-exist type
    static_assert(std::is_same<
        int_types::find<is_same_double>, std::none_type>::value, "");

    // Filtering exist types
    static_assert(std::is_same<
        int_types::filter<is_same_int>, type_list<int>>::value, "");

    // Filtering non-exist types
    static_assert(std::is_same<
        int_types::filter<is_same_double>, type_list<>>::value, "");

    // Remove exist type
    static_assert(std::is_same<
        int_types::remove<is_same_int>,
        type_list<char, short, long>>::value, "");

    // Remove non-exist type
    static_assert(std::is_same<
        int_types::remove<is_same_double>, int_types>::value, "");

    // Insert to begin
    static_assert(std::is_same<
        type_list<int, long>::insert<char, short>, int_types>::value, "");

    // Reverse type_list
    static_assert(std::is_same<
        int_types::reverse, type_list<long, int, short, char>>::value, "");
}
