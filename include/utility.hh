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
 * C++ utitlity
 * @file utitlity.hh
 * @author Boris Vinogradov
 */

#include <internal/std_types.hh>
#include <type_traits.hh>

#ifndef LP_CC_LIB_UTILITY_HH
#define LP_CC_LIB_UTILITY_HH

namespace std {
    /// Forward lvalue
    template <typename T>
    constexpr T && forward(typename remove_reference<T>::type &t) noexcept {
        return static_cast<T &&>(t);
    }

    /// Forward rvalue
    template <typename T>
    constexpr T && forward(typename remove_reference<T>::type &&t) noexcept {
        static_assert(!is_lvalue_reference<T>::value,
            "template argument substituting T is an lvalue reference type");

        return static_cast<T &&>(t);
    }

    /// Move
    template <typename T>
    constexpr typename remove_reference<T>::type && move(T&& t) noexcept {
        return static_cast<typename remove_reference<T>::type &&>(t);
    }

    /// Swap elements
    template <typename T>
    constexpr inline void swap(T &a, T &b)
        noexcept(and_pred<is_nothrow_move_constructible<T>,
            is_nothrow_move_assignable<T>>::value) {
        T tmp = move(a);
        a = move(b);
        b = move(tmp);
    }

    /// Swap arrays
    template <typename T, size_t Number>
    constexpr inline void swap(T (&a)[Number], T (&b)[Number])
        noexcept(noexcept(swap(*a, *b))) {
        for (int i = 0; i < Number; i++) {
            swap(a[i], b[i]);
        }
    }
} // namespace std

#endif // LP_CC_LIB_UTILITY_HH
