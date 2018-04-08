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
 * C++ meta type traits
 * @file type_traits
 * @author Boris Vinogradov
 */

#ifndef LP_CC_LIB_TYPE_TRAITS
#define LP_CC_LIB_TYPE_TRAITS

namespace std {
    /// The type used as compiled-time none type
    struct none_type;

    /// integral constant
    template <typename T, T v>
    struct integral_constant {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant;

        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    /// The type used as compiled-time boolean with true value
    using true_type = integral_constant<bool, true>;

    /// The type used as compiled-time boolean with false value
    using false_type = integral_constant<bool, false>;

    /// Types is same
    template <typename, typename>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T, T> : true_type {};

    /// Conditional select
    template <bool Cond, typename TrueType, typename FalseType>
    struct conditional {
        using type = TrueType;
    };

    template <typename TrueType, typename FalseType>
    struct conditional<false, TrueType, FalseType> {
        using type = FalseType;
    };
} // namespace std

#endif // LP_CC_LIB_TYPE_TRAITS
