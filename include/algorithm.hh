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
 * C++ algorithms
 * @file algorithm.hh
 * @author Boris Vinogradov
 */

#include <internal/std_types.hh>

#include <initializer_list.hh>

#ifndef LP_CC_LIB_ALGORITHM_HH
#define LP_CC_LIB_ALGORITHM_HH

namespace std {
    /// Max element
    template <typename Forward_it>
    constexpr Forward_it max_element(Forward_it first, Forward_it last) {
        if (first == last)
            return last;

        Forward_it largest = first;
        ++first;
        for (; first != last; ++first) {
            if (*largest < *first) {
                largest = first;
            }
        }

        return largest;
    }

    template <typename Forward_it, typename Compare>
    constexpr Forward_it max_element(Forward_it first, Forward_it last, Compare comp) {
        if (first == last)
            return last;

        Forward_it largest = first;
        ++first;
        for (; first != last; ++first) {
            if (comp(*largest, *first)) {
                largest = first;
            }
        }

        return largest;
    }

    /// Max
    template <typename T>
    constexpr const T & max(const T &a, const T &b) {
        return (a < b) ? b : a;
    }

    template <typename T, typename Compare>
    constexpr const T & max(const T &a, const T &b, Compare comp) {
        return (comp(a, b)) ? b : a;
    }

    template <typename T>
    constexpr T max(initializer_list<T> ilist) {
        return *max_element(ilist.begin(), ilist.end());
    }

    template <typename T, typename Compare>
    constexpr T max(initializer_list<T> ilist, Compare comp) {
        return *max_element(ilist.begin(), ilist.end(), comp);
    }
} // namespace std

#endif // LP_CC_LIB_ALGORITHM_HH
