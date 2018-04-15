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
 * Type traits test
 * @file type_traits_test.cc
 * @author Boris Vinogradov
 */

#include <type_traits.hh>

struct A {};
struct B {};

void type_traits_test() {
    using namespace std;

    static_assert(false_type::value == false_type::value, "");
    static_assert(true_type::value == true_type::value, "");
    static_assert(true_type::value != false_type::value, "");

    static_assert(is_same<int, int>::value == true, "");
    static_assert(is_same<char, int>::value == false, "");
    static_assert(is_same<A, A>::value == true, "");
    static_assert(is_same<A, B>::value == false, "");

    static_assert(is_same<conditional<true, int, double>::type, int>::value, "");
    static_assert(is_same<conditional<false, int, double>::type, double>::value, "");

    static_assert(is_same<enable_if_t<true>, void>::value, "");

    static_assert(is_same<remove_const_t<const int>, int>::value, "");
    static_assert(is_same<remove_volatile_t<volatile int>, int>::value, "");
    static_assert(is_same<remove_const_t<const volatile int>, volatile int>::value, "");
    static_assert(is_same<remove_volatile_t<const volatile int>, const int>::value, "");
    static_assert(is_same<remove_cv_t<volatile const int>, int>::value, "");
    static_assert(is_same<remove_cv_t<const volatile int>, int>::value, "");

    static_assert(is_same<add_cv_t<int>, const volatile int>::value, "");
    static_assert(is_same<add_const_t<int>, const int>::value, "");
    static_assert(is_same<add_volatile_t<int>, volatile int>::value, "");

    static_assert(is_const<const int>::value == true, "");
    static_assert(is_const<int>::value == false, "");
    static_assert(is_volatile<volatile char>::value == true, "");
    static_assert(is_volatile<char>::value == false, "");

    static_assert(is_void<void>::value == true, "");
    static_assert(is_void<A>::value == false, "");

    static_assert(is_integral<char>::value == true, "");
    static_assert(is_integral<int>::value == true, "");
    static_assert(is_integral<double>::value == false, "");
    static_assert(is_integral<B>::value == false, "");

    static_assert(is_floating_point<float>::value == true, "");
    static_assert(is_floating_point<int>::value == false, "");
    static_assert(is_floating_point<A>::value == false, "");

    static_assert(is_array<int>::value == false, "");
    static_assert(is_array<int[]>::value == true, "");
    static_assert(is_array<int[1]>::value == true, "");
    static_assert(is_array<A>::value == false, "");
    static_assert(is_array<A[]>::value == true, "");
    static_assert(is_array<A[4]>::value == true, "");

    static_assert(is_pointer<int>::value == false, "");
    static_assert(is_pointer<int *>::value == true, "");
    static_assert(is_pointer<int &>::value == false, "");
    static_assert(is_pointer<int[]>::value == false, "");
    static_assert(is_pointer<A>::value == false, "");
    static_assert(is_pointer<A **>::value == true, "");
}
