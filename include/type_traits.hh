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

    /// Define typename if true
    template <bool Cond, typename T = void>
    struct enable_if {};
    
    template <typename T>
    struct enable_if<true, T> { using type = T; };

    /// Helper for enable_if
    template <bool Cond, typename T = void>
    using enable_if_t = typename enable_if<Cond, T>::type;

    // Const and volatile modification
    /// Remove const
    template <typename T>
    struct remove_const {
        using type = T;
    };
    
    template <typename T>
    struct remove_const<const T> {
        using type = T;
    };

    /// Remove volatile
    template <typename T>
    struct remove_volatile {
        using type = T;
    };

    template <typename T>
    struct remove_volatile<volatile T> {
        using type = T;
    };

    /// Remove const and volatile
    template <typename T>
    struct remove_cv {
        using type = typename remove_volatile<typename remove_const<T>::type>::type;
    };

    template <typename T>
    using remove_cv_t = typename remove_cv<T>::type;

    template <typename T>
    using remove_const_t = typename remove_const<T>::type;

    template <typename T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    /// Add const
    template <typename T>
    struct add_const {
        using type = const T;
    };

    /// Add volatile
    template <typename T>
    struct add_volatile {
        using type = volatile T;
    };

    /// Add const and volatile
    template <typename T>
    struct add_cv {
        using type = typename add_const<typename add_volatile<T>::type>::type;
    };

    /// Add const, volatile and cv helpers
    template <typename T>
    using add_cv_t = typename add_cv<T>::type;

    template <typename T>
    using add_const_t = typename add_const<T>::type;

    template <typename T>
    using add_volatile_t = typename add_volatile<T>::type;

    // Check const and volatile
    /// Check const
    template <typename T>
    struct is_const : false_type {};

    template <typename T>
    struct is_const<const T> : true_type {};

    /// Check volatile
    template <typename T>
    struct is_volatile : false_type {};

    template <typename T>
    struct is_volatile<volatile T> : true_type {};

    template <typename T>
    using is_const_v = typename is_const<T>::value;

    template <typename T>
    using is_volatile_v = typename is_volatile<T>::value;
} // namespace std

#endif // LP_CC_LIB_TYPE_TRAITS
