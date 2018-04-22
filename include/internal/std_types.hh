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
 * C++ library types
 * @file internal/std_types.hh
 * @author Boris Vinogradov
 */

#ifndef LP_CC_LIB_INTERNAL_STD_TYPES_HH
#define LP_CC_LIB_INTERNAL_STD_TYPES_HH

namespace std {
    /// Platform size type
    using size_t = decltype(sizeof(int));

    namespace internal {
        struct h {
            static constexpr const size_t *x = nullptr;
        };
    } // namespace internal

    /// Platform pointer difference type
    using ptrdiff_t = decltype(internal::h::x - internal::h::x);

    /// Platform null pointer type
    using nullptr_t = decltype(nullptr);
} // namespace std

#endif // LP_CC_LIB_INTERNAL_STD_TYPES_HH
