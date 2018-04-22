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
 * Types test
 * @file lp/types_test.cc
 * @author Boris Vinogradov
 */

#include <type_traits.hh>

#include <lp/types.hh>

void types_test() {
    using namespace lp;

    static_assert(sizeof(char) == 1, "");
    static_assert(sizeof(short) == 2, "");
    static_assert(sizeof(int) == 4, "");
    static_assert(sizeof(long) == 4 || sizeof(long) == 8, "");
    static_assert(sizeof(long long) == 8, "");

    auto x = sizeof(int[4]);
    static_assert(sizeof(word_t) == sizeof(x), "");
    static_assert(std::is_same<word_t, decltype(x)>::value, "");
    word_t *a;
    using pointer_type = decltype(a);
    static_assert(sizeof(pointer_type) == sizeof(addr_t), "");
    static_assert(std::is_same<std::remove_pointer_t<pointer_type>, addr_t>::value, "");
}
