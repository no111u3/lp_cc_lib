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
 * Algorithm test
 * @file algorithm_test.cc
 * @author Boris Vinogradov
 */

#include <algorithm.hh>
#include <type_traits.hh>

constexpr bool reverse_compare(const int a, const int b) {
    return a > b;
}

void algorithm_test() {
    using namespace std;

    constexpr auto elems = {1, 3, 2, 5, 4};
    static_assert(max(1, 8) == 8, "");
    static_assert(max(elems) == 5, "");
    static_assert(max(elems, reverse_compare) == 1, "");

    static_assert(*max_element(elems.begin(), elems.end()) == 5, "");
    static_assert(*max_element(elems.begin(), elems.end(), reverse_compare) == 1, "");
}
