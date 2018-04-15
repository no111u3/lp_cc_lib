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
 * C++ initializer list
 * @file initializer_list.hh
 * @author Boris Vinogradov
 */

#include <internal/std_types.hh>

#ifndef LP_CC_LIB_INITIALIZER_LIST_HH
#define LP_CC_LIB_INITIALIZER_LIST_HH

namespace std {
    /// Initializer list
    template <typename T>
    class initializer_list {
    public:
        using value_type = T;
        using reference = const T &;
        using const_reference =  const T &;
        using size_type = size_t;
        using iterator = const T *;
        using const_iterator = const T *;

        constexpr initializer_list() noexcept
            : array_(nullptr), size_(0) { }

        /// Size of array
        constexpr size_type size() const noexcept { return size_; }

        // First element
        constexpr const_iterator begin() const noexcept { return array_; }

        // One past the last element
        constexpr const_iterator end() const noexcept { return begin() + size_; }

    private:
        // The compiler called constructor
        constexpr initializer_list(const_iterator array, size_type size)
            : array_(array), size_(size) { }

        iterator array_;
        size_type size_;
    };

    /// Specialization of begin function for initializer_list
    template <typename T>
    constexpr const T * begin(initializer_list<T> il) noexcept {
        return il.begin();
    }

    /// Specialization of end function for initializer_list
    template <typename T>
    constexpr const T * end(initializer_list<T> il) noexcept {
        return il.end();
    }
} // namespace std

#endif // LP_CC_LIB_INITIALIZER_LIST_HH
