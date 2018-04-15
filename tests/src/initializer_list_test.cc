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
 * Initializer list test
 * @file initializer_list_test.cc
 * @author Boris Vinogradov
 */

#include <initializer_list.hh>
#include <type_traits.hh>

template <typename T>
struct Test {
    constexpr Test(std::initializer_list<T> l) : list(l) {}

    std::initializer_list<T> list;
};

void initializer_list_test() {
    static_assert(Test<int>({}).list.size() == 0, "");

    static_assert(Test<int>({1, 2, 3}).list.size() == 3, "");

    static_assert(*Test<int>({3, 4}).list.begin() == 3, "");

    static_assert(*(Test<int>({3, 4}).list.end() - 1) == 4, "");
}
