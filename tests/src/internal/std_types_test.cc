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
 * Std types test
 * @file std_types_test.cc
 * @author Boris Vinogradov
 */

#include <internal/std_types.hh>

template <typename T, typename V>
struct is_same {
    static constexpr bool value = false;
};

template <typename T>
struct is_same<T, T> {
    static constexpr bool value = true;
};

void std_types_test() {
    using namespace std;

    auto size_int = sizeof(int);
    static_assert(sizeof(size_t) == sizeof(size_int), "");
    static_assert(is_same<size_t, decltype(size_int)>::value, "");

    auto *p = &size_int, *d = &size_int;
    auto ptr_difference = d - p;
    static_assert(sizeof(ptrdiff_t) == sizeof(ptr_difference), "");
    static_assert(is_same<ptrdiff_t, decltype(ptr_difference)>::value, "");

    auto null_ptr = nullptr;
    static_assert(sizeof(nullptr_t) == sizeof(null_ptr), "");
    static_assert(is_same<nullptr_t, decltype(null_ptr)>::value, "");
}
