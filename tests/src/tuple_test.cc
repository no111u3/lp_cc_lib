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
 * Tuple test
 * @file tuple_test.cc
 * @author Boris Vinogradov
 */

#include <tuple.hh>
#include <type_traits.hh>

struct A {
};

struct B final {
};

constexpr auto f() {
    constexpr int x = 5;
    return std::make_tuple(x, 7);
}

constexpr auto test_tie() {
    int a = 0, b = 0;

    std::tie(a, b) = f();

    return a == 5 && b == 7;
}

constexpr auto test_tie_2() {
    int a = 0;

    std::tie(std::ignore, a) = f();

    return a == 7;
}

constexpr auto test_swap() {
    auto a = std::make_tuple(1, 2);
    auto b = std::make_tuple(3, 4);

    std::swap(a, b);

    return a == std::make_tuple(3, 4) && b == std::make_tuple(1, 2);
}

void tuple_test() {
    using namespace std;
    constexpr tuple<> t{};

    constexpr tuple<int> t1{0};

    constexpr tuple<char, int> t2{'A', 10};

    constexpr tuple<char, int, double> t3{'A', 10, 5.6};

    constexpr tuple<int> t4{tuple<int>{4}};

    constexpr tuple<int> t5{t4};

    constexpr tuple<int> t6{move(t4)};

    constexpr tuple<A> t7{};

    constexpr tuple<B> t8{};

    constexpr tuple<A> t9 = t7;

    constexpr tuple<B> t10{move(t8)};

    static_assert(is_same<tuple<>, tuple<>>::value, "");

    static_assert(is_same<tuple<int, long>, tuple<int, long>>::value, "");

    static_assert(
        is_same<tuple_element_t<1, decltype(t2)>, const int>::value, "");

    static_assert(
        tuple_size<decltype(t3)>::value == 3, "");

    static_assert(
        tuple_size<decltype(t)>::value == 0, "");

    static_assert(get<0>(t2) == 'A', "");

    static_assert(is_same<decltype(get<2>(t3)), const double &>::value, "");

    static_assert(is_same<decltype(make_tuple()), tuple<>>::value, "");

    static_assert(is_same<
        decltype(make_tuple(4, 8)), tuple<int, int>>::value, "");

    constexpr auto t11 = make_tuple(4, 8, 'A', 4.6);

    static_assert(is_same<
        decltype(t11), const tuple<int, int, char, double>>::value, "");

    static_assert(get<0>(t11) == 4 &&
        get<1>(t11) == 8 && get<2>(t11) == 'A' && get<3>(t11) == 4.6, "");

    static_assert(get<char>(t3) == 'A' && get<int>(t3) == 10 &&
        get<double>(t3) == 5.6, "");

    static_assert(make_tuple(4, 8) == tuple<int, int>(4, 8), "");

    static_assert(make_tuple(4, 6) == make_tuple(4, 6), "");

    static_assert(make_tuple(5, 1) != make_tuple(8, 2), "");

    static_assert(make_tuple(5, 2) < make_tuple(5, 3), "");

    static_assert(make_tuple(4, 1) > make_tuple(2, 9), "");

    static_assert(test_tie(), "");

    static_assert(test_tie_2(), "");

    auto t12 = forward_as_tuple(20, 'A');
    static_assert(
        is_same<decltype(t12), tuple<int &&, char &&>>::value, "");

    static_assert(test_swap(), "");

    static_assert(
        tuple_cat(t1, t2, t3) == make_tuple(0, 'A', 10, 'A', 10, 5.6), "");
}
