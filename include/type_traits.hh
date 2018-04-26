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
 * @file type_traits.hh
 * @author Boris Vinogradov
 */

#include <internal/std_types.hh>

#include <algorithm.hh>

#ifndef LP_CC_LIB_TYPE_TRAITS_HH
#define LP_CC_LIB_TYPE_TRAITS_HH

namespace std {
    /// The type used as compiled-time none type
    struct none_type;

    /// Integral constant
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

    template <bool Cond, typename TrueType, typename FalseType>
    using conditional_t = typename conditional<Cond, TrueType, FalseType>::type;

    // Predicates
    /// Or predicate
    template <typename ...Ts>
    struct or_pred;

    template <>
    struct or_pred<>
        : false_type {};

    template <typename T>
    struct or_pred<T>
        : T {};

    template <typename T1, typename T2>
    struct or_pred<T1, T2>
        : conditional_t<T1::value, T1, T2> {};

    template <typename T1, typename T2, typename T3, typename ...Ts>
    struct or_pred<T1, T2, T3, Ts...>
        : conditional_t<T1::value, T1, or_pred<T2, T3, Ts...>> {};

    /// And predicate
    template <typename ...Ts>
    struct and_pred;

    template <>
    struct and_pred<>
        : true_type {};

    template <typename T>
    struct and_pred<T>
        : T {};

    template <typename T1, typename T2>
    struct and_pred<T1, T2>
        : conditional_t<T1::value, T2, T1> {};

    template <typename T1, typename T2, typename T3, typename ...Ts>
    struct and_pred<T1, T2, T3, Ts...>
        : conditional_t<T1::value, and_pred<T2, T3, Ts...>, T1> {};

    /// Not predicate
    template <typename T>
    struct not_pred
        : integral_constant<bool, !T::value> {};

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

    /// Remove const, volatile and cv helpers
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

    /// Is void
    template <typename T>
    struct is_void
        : is_same<void, remove_cv_t<T>> {};

    /// Is null pointer
    template <typename T>
    struct is_null_pointer
        : is_same<nullptr_t, remove_cv_t<T>> {};

    // Integral check
    namespace internal {
        template <typename T>
        struct is_integral_h
            : false_type {};

        template <>
        struct is_integral_h<bool>
            : true_type {};

        template <>
        struct is_integral_h<char>
            : true_type {};

        template <>
        struct is_integral_h<signed char>
            : true_type {};

        template <>
        struct is_integral_h<unsigned char>
            : true_type {};

        template <>
        struct is_integral_h<short>
            : true_type {};

        template <>
        struct is_integral_h<unsigned short>
            : true_type {};

        template <>
        struct is_integral_h<int>
            : true_type {};

        template <>
        struct is_integral_h<unsigned int>
            : true_type {};

        template <>
        struct is_integral_h<long>
            : true_type {};

        template <>
        struct is_integral_h<unsigned long>
            : true_type {};

        template <>
        struct is_integral_h<long long>
            : true_type {};

        template <>
        struct is_integral_h<unsigned long long>
            : true_type {};
    } // namespace internal

    /// Is integral
    template <typename T>
    struct is_integral
        : internal::is_integral_h<remove_cv_t<T>>::type {};

    // Float check
    namespace internal {
        template <typename T>
        struct is_floating_point_h
            : false_type {};

        template <>
        struct is_floating_point_h<float>
            : true_type {};

        template <>
        struct is_floating_point_h<double>
            : true_type {};

        template <>
        struct is_floating_point_h<long double>
            : true_type {};
    }

    /// Is floating point
    template <typename T>
    struct is_floating_point
        : internal::is_floating_point_h<remove_cv_t<T>>::type {};

    /// Is array
    template <typename T>
    struct is_array
        : false_type {};

    template <typename T, size_t Size>
    struct is_array<T[Size]>
        : true_type {};

    template <typename T>
    struct is_array<T[]>
        : true_type {};

    /// Is enum
    template <typename T>
    struct is_enum
        : integral_constant<bool, __is_enum(T)> {};

    /// Is union
    template <typename T>
    struct is_union
        : integral_constant<bool, __is_union(T)> {};

    /// Is class
    template <typename T>
    struct is_class
        : integral_constant<bool, __is_class(T)> {};

    /// Is function
    template <typename T>
    struct is_function
        : false_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...)>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......)>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) const>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) volatile>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) const volatile>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) const>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) volatile>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) const volatile>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) const &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) volatile &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) const volatile &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) const &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) volatile &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) const volatile &>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) &&>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) &&>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) const &&>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) volatile &&>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args...) const volatile &&>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) const &&>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) volatile &&>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_function<Ret(Args......) const volatile &&>
        : true_type {};

    // Pointer check
    namespace internal {
        template <typename T>
        struct is_pointer_h
            : false_type {};

        template <typename T>
        struct is_pointer_h<T *>
            : true_type {};
    } // namespace internal

    /// Is pointer
    template <typename T>
    struct is_pointer
        : internal::is_pointer_h<remove_cv_t<T>>::type {};

    /// Is lvalue reference
    template <typename T>
    struct is_lvalue_reference
        : false_type {};

    template <typename T>
    struct is_lvalue_reference<T &>
        : true_type {};

    /// Is rvalue reference
    template <typename T>
    struct is_rvalue_reference
        : false_type {};

    template <typename T>
    struct is_rvalue_reference<T &&>
        : true_type {};

    /// Is member pointer
    namespace internal {
        template <typename T>
        struct is_member_pointer_h
            : false_type {};

        template <typename T, typename U>
        struct is_member_pointer_h<T U::*>
            : true_type {};
    } // namespace internal

    template <typename T>
    struct is_member_pointer
        : internal::is_member_pointer_h<remove_cv_t<T>> {};

    /// Is member function pointer
    namespace internal {
        template <typename T>
        struct is_member_function_pointer_h
            : false_type {};

        template <typename T, typename U>
        struct is_member_function_pointer_h<T U::*>
            : is_function<T> {};
    } // namespace internal

    template <typename T>
    struct is_member_function_pointer
        : internal::is_member_function_pointer_h<remove_cv_t<T>> {};

    /// Is member object pointer
    template <typename T>
    struct is_member_object_pointer
        : and_pred<is_member_pointer<T>,
            not_pred<is_member_function_pointer<T>>>::type {};

    /// Is arithmetic
    template <typename T>
    struct is_arithmetic
        : or_pred<is_integral<T>, is_floating_point<T>>::type {};

    /// Is fundamental
    template <typename T>
    struct is_fundamental
        : or_pred<is_arithmetic<T>,
            is_void<T>,
            is_same<nullptr_t, remove_cv_t<T>>>::type {};

    /// Is scalar
    template <typename T>
    struct is_scalar
        : or_pred<is_arithmetic<T>,
            is_enum<T>,
            is_pointer<T>,
            is_member_pointer<T>,
            is_null_pointer<T>>::type {};

    /// Is object
    template <typename T>
    struct is_object
        : or_pred<is_scalar<T>,
            is_array<T>,
            is_union<T>,
            is_class<T>>::type {};

    /// Is compound
    template <typename T>
    struct is_compound
        : not_pred<is_fundamental<T>>::type {};

    /// Is reference
    template <typename T>
    struct is_reference
        : or_pred<is_lvalue_reference<T>,
            is_rvalue_reference<T>>::type {};

    /// Is referenceable
    template <typename T>
    struct is_referenceable
        : or_pred<is_object<T>,
            is_reference<T>>::type {};

    /// Is base of
    template <typename Base, typename Derived>
    struct is_base_of
        : integral_constant<bool, __is_base_of(Base, Derived)> {};

    /// Is referenceable
    template <typename Ret, typename ...Args>
    struct is_referenceable<Ret(Args...)>
        : true_type {};

    template <typename Ret, typename ...Args>
    struct is_referenceable<Ret(Args......)>
        : true_type {};

    /// Add lvalue reference
    namespace internal {
        template <typename T, bool = is_referenceable<T>::value>
        struct add_lvalue_reference_h {
            using type = T;
        };

        template <typename T>
        struct add_lvalue_reference_h<T, true> {
            using type = T &;
        };
    }

    template <typename T>
    struct add_lvalue_reference
        : internal::add_lvalue_reference_h<T> {};

    template <typename T>
    using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

    /// Add rvalue reference
    namespace internal {
        template <typename T, bool = is_referenceable<T>::value>
        struct add_rvalue_reference_h {
            using type = T;
        };

        template <typename T>
        struct add_rvalue_reference_h<T, true> {
            using type = T &&;
        };
    } // namespace internal

    template <typename T>
    struct add_rvalue_reference
        : internal::add_rvalue_reference_h<T> {};

    template <typename T>
    using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

    /// Remove reference
    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T &> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T &&> {
        using type = T;
    };

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    /// Remove pointer
    template <typename T>
    struct remove_pointer {
        using type = T;
    };

    template <typename T>
    struct remove_pointer<T *> {
        using type = T;
    };

    template <typename T>
    struct remove_pointer<T * const> {
        using type = T;
    };

    template <typename T>
    struct remove_pointer<T * volatile> {
        using type = T;
    };

    template <typename T>
    struct remove_pointer<T * const volatile> {
        using type = T;
    };

    template <typename T>
    using remove_pointer_t = typename remove_pointer<T>::type;

    /// Add pointer
    namespace internal {
        template <typename T, bool is_function_type = false>
        struct add_pointer_h {
            using type = remove_reference_t<T> *;
        };

        template <typename T>
        struct add_pointer_h<T, true> {
            using type = T;
        };

        template <typename T, typename ...Args>
        struct add_pointer_h<T(Args...), true> {
            using type = T(*)(Args...);
        };

        template <typename T, class ...Args>
        struct add_pointer_h<T(Args..., ...), true> {
            using type = T(*)(Args..., ...);
        };
    } // namespace internal

    template <typename T>
    struct add_pointer
        : internal::add_pointer_h<T, is_function<T>::value> {};

    template <typename T>
    using add_pointer_t = typename add_pointer<T>::type;

    template<size_t Len>
    struct aligned_storage_h { 
        union type {
            unsigned char data[Len];
            struct alignas(size_t) { } align; 
        };
    };

    template <size_t Len, size_t Align = alignof(aligned_storage_h<Len>)>
    struct aligned_storage {
        struct type {
            alignas(Align) unsigned char data[Len];
        };
    };

    template <size_t Len, size_t Align>
    using aligned_storage_t = typename aligned_storage<Len, Align>::type;

    template <size_t Len, typename ...Types>
    struct aligned_union {
        static constexpr size_t alignment_value = max({alignof(Types)...});

        struct type {
            alignas(alignment_value) char s[max({Len, sizeof(Types)...})];
        };
    };

    template <size_t Len, typename ...Types>
    using aligned_union_t = typename aligned_union<Len, Types...>::type;

    /// Extent
    template <typename, unsigned = 0>
    struct extent;

    template <typename, unsigned N>
    struct extent
        : integral_constant<size_t, 0> {};

    template <typename T, unsigned N, size_t Size>
    struct extent<T[Size], N>
        : integral_constant<size_t, N == 0 ? Size : extent<T, N - 1>::value> {};

    template <typename T, unsigned N>
    struct extent<T[], N>
        : integral_constant<size_t, N == 0 ? 0 : extent<T, N - 1>::value> {};

    /// Rank
    template <typename T>
    struct rank
        : integral_constant<size_t, 0> {};

    template <typename T>
    struct rank<T[]>
        : integral_constant<size_t, rank<T>::value + 1> {};

    template <typename T, size_t N>
    struct rank<T[N]>
        : integral_constant<size_t, rank<T>::value + 1> {};

    /// Remove extent
    template <typename T>
    struct remove_extent {
        using type = T;
    };

    template <typename T>
    struct remove_extent<T[]> {
        using type = T;
    };

    template <typename T, size_t N>
    struct remove_extent<T[N]> {
        using type = T;
    };

    template <typename T>
    using remove_extent_t = typename remove_extent<T>::type;

    /// Remove all extents
    template <typename T>
    struct remove_all_extents;

    template <typename T>
    struct remove_all_extents {
        using type = T;
    };

    template <typename T, size_t Size>
    struct remove_all_extents<T[Size]> {
        using type = typename remove_all_extents<T>::type;
    };

    template <typename T>
    struct remove_all_extents<T[]> {
        using type = typename remove_all_extents<T>::type;
    };

    template <typename T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;

    /// Is array with unknown bounds
    template <typename T>
    struct is_array_unknown_bounds
        : and_pred<is_array<T>, not_pred<extent<T>>>::type {};

    /// Declare value
    template <typename T>
    struct declval_h {
        static add_rvalue_reference_t<T> delegate();
    };

    /// Is array with known bounds
    template <typename T>
    struct is_array_known_bounds
        : integral_constant<bool, (extent<T>::value > 0)> {};

    template <typename T>
    inline add_rvalue_reference_t<T> declval() noexcept {
        return declval_h<T>::delegate();
    }

    /// Is convertible
    namespace internal {
        template <typename From, typename To,
            bool = or_pred<is_void<From>, is_function<To>, is_array<To>>::value>
        struct is_convertible_h {
            using type = typename is_void<To>::type;
        };

        template <typename From, typename To>
        struct is_convertible_h<From, To, false>
        {
            template <typename To1>
            static void test_aux(To1);

            template <typename From1, typename To1,
                typename = decltype(test_aux<To1>(declval<From1>()))>
            static true_type test(int);

            template <typename, typename>
            static false_type
            test(...);

            using type = decltype(test<From, To>(0));
        };
    } // namespace internal

    template <typename From, typename To>
    struct is_convertible
        : internal::is_convertible_h<From, To>::type {};

    /// Is trivially copyable
    template <typename T>
    struct is_trivially_copyable
        : integral_constant<bool, __is_trivially_copyable(T)> {};

    /// Is standard_layout
    template <typename T>
    struct is_standard_layout
        : integral_constant<bool, __is_standard_layout(T)> {};

    /// Is POD
    template <typename T>
    struct is_pod
        : integral_constant<bool, __is_pod(T)> {};

    /// Is literal type
    template <typename T>
    struct is_literal_type
        : integral_constant<bool, __is_literal_type(T)> {};

    /// Is empty
    template <typename T>
    struct is_empty
        : integral_constant<bool, __is_empty(T)> {};

    /// Is polymorphic
    template <typename T>
    struct is_polymorphic
        : integral_constant<bool, __is_polymorphic(T)> {};

    /// Is abstract
    template <typename T>
    struct is_abstract
        : integral_constant<bool, __is_abstract(T)> {};

    /// Is final
    template <typename T>
    struct is_final
        : integral_constant<bool, __is_final(T)> {};

    /// Is signed
    template <typename T, bool = is_arithmetic<T>::value>
    struct is_signed_h
        : false_type {};

    template <typename T>
    struct is_signed_h<T, true>
        : integral_constant<bool, T(-1) < T(0)> {};

    template <typename T>
    struct is_signed
        : is_signed_h<T>::type {};

    /// Decay
    template <typename T>
    struct decay {
        using U = remove_reference_t<T>;

        using type = conditional_t<
            is_array<U>::value,
            remove_extent_t<U> *,
            conditional_t<
                is_function<U>::value,
                add_pointer_t<U>,
                remove_cv_t<U>
            >
        >;
    };

    template <typename T>
    using decay_t = typename decay<T>::type;

    template<typename T>
    class reference_wrapper;

    namespace internal {
    template <typename T>
    struct strip_reference_wrapper {
        using type = T;
    };

    template <typename T>
    struct strip_reference_wrapper<reference_wrapper<T>> {
        using type = T &;
    };
    } // namespace internal

    /// Decay and strip
    template <typename T>
    struct decay_and_strip {
        using type =
            typename internal::strip_reference_wrapper<
                typename decay<T>::type>::type;
    };

    /// Is unsigned
    template <typename T>
    struct is_unsigned
        : and_pred<is_arithmetic<T>, not_pred<is_signed<T>>>::type {};

    /// Is destructible
    namespace internal {
        struct do_is_destructible_h {
            template <typename T, typename = decltype(declval<T&>().~T())>
            static true_type test(int);

            template <typename>
            static false_type test(...);
        };

        template <typename T>
        struct is_destructible_h
            : do_is_destructible_h {
            using type = decltype(test<T>(0));
        };

        template <typename T, bool = or_pred<is_void<T>,
            is_array_unknown_bounds<T>, is_function<T>>::value,
            bool = or_pred<is_reference<T>, is_scalar<T>>::value>
        struct is_destructible_safe;

        template <typename T>
        struct is_destructible_safe<T, false, false>
            : is_destructible_h<remove_all_extents_t<T>>::type {};

        template <typename T>
        struct is_destructible_safe<T, true, false>
            : false_type {};

        template <typename T>
        struct is_destructible_safe<T, false, true>
            : true_type {};
    }

    template <typename T>
    struct is_destructible
        : internal::is_destructible_safe<T>::type {};

    /// Has trivial destructor
    template <typename T>
    struct has_trivial_destructor
        : integral_constant<bool, __has_trivial_destructor(T)>::type {};

    /// Is trivially destructible
    template <typename T>
    struct is_trivially_destructible
        : and_pred<is_destructible<T>,
            has_trivial_destructor<T>> {};

    /// Is nothrow destructible
    namespace internal {
        struct do_is_nothrow_destructible_h {
            template <typename T>
            static integral_constant<bool, noexcept(declval<T &>().~T())> test(int);

            template <typename>
            static false_type test(...);
        };

        template <typename T>
        struct is_nothrow_destructible_h
            : do_is_nothrow_destructible_h {
            using type = decltype(test<T>(0));
        };

        template <typename T,
            bool = or_pred<is_void<T>, is_array_unknown_bounds<T>, is_function<T>>::value,
            bool = or_pred<is_reference<T>, is_scalar<T>>::value>
        struct is_nothrow_destructible_safe;

        template <typename T>
        struct is_nothrow_destructible_safe<T, false, false>
            : is_nothrow_destructible_h<typename
                remove_all_extents<T>::type>::type {};

        template <typename T>
        struct is_nothrow_destructible_safe<T, true, false>
            : false_type {};

        template <typename T>
        struct is_nothrow_destructible_safe<T, false, true>
            : true_type { };
    }

    template <typename T>
    struct is_nothrow_destructible
        : internal::is_nothrow_destructible_safe<T>::type {};

    /// Is clean constructible
    namespace internal {
        struct do_clean_constructible_h {
            template <typename T, typename ...Args, typename = decltype(T(declval<Args>()...))>
                static true_type test(int);

            template <typename, typename...>
                static false_type test(...);
        };

        template <typename T, typename ...Args>
        struct is_clean_constructible_h
            : do_clean_constructible_h {
            using type = decltype(test<T, Args...>(0));
        };
    } // namespace internal

    template <typename T, typename ...Args>
    struct is_clean_constructible
        : internal::is_clean_constructible_h<T, Args...>::type {};

    /// Is static castable
    namespace internal {
        struct do_is_static_castable_h {
            template <typename From, typename To, typename = 
                decltype(static_cast<To>(declval<From>()))>
                static true_type test(int);

            template <typename, typename>
                static false_type test(...);
        };

        template <typename From, typename To>
        struct is_static_castable_h
            : do_is_static_castable_h {
        using type = decltype(test<From, To>(0));
        };

        template <typename From, typename To>
        struct is_static_castable_safe
            : is_static_castable_h<From, To>::type {};
    } // namespace internal


    template <typename From, typename To>
    struct is_static_castable
        : integral_constant<bool, (
            internal::is_static_castable_safe<From, To>::value)> {};

    /// Is base to derived reference
    template <typename From, typename To, bool = not_pred<or_pred<is_void<From>, 
                          is_function<From>>>::value>
    struct is_base_to_derived_ref;

    template <typename From, typename To>
    struct is_base_to_derived_ref<From, To, true> {
        using src_t = typename remove_cv<remove_reference_t<From>>::type;
        using dst_t = typename remove_cv<remove_reference_t<To>>::type;

        using type = and_pred<not_pred<is_same<src_t, dst_t>>, is_base_of<src_t, dst_t>>;
        static constexpr bool value = type::value;
    };

    template <typename From, typename To>
    struct is_base_to_derived_ref<From, To, false>
        : false_type {};

    /// Is lvalue to rvalue reference
    template <typename From, typename To, bool =and_pred<is_lvalue_reference<From>,
                    is_rvalue_reference<To>>::value>
    struct is_lvalue_to_rvalue_ref;

    template <typename From, typename To>
    struct is_lvalue_to_rvalue_ref<From, To, true> {
        using src_t = typename remove_cv<remove_reference_t<From>>::type;
        using dst_t = typename remove_cv<remove_reference_t<To>>::type;

      using type = and_pred<not_pred<is_function<src_t>>,
        or_pred<is_same<src_t, dst_t>, is_base_of<dst_t, src_t>>>;
      static constexpr bool value = type::value;
    };

    template <typename From, typename To>
    struct is_lvalue_to_rvalue_ref<From, To, false>
        : false_type {};

    /// Is direct constructible
    namespace internal {
        template <typename T, typename Arg>
        struct is_direct_constructible_ref_cast
            : and_pred<is_static_castable<Arg, T>,
                not_pred<or_pred<is_base_to_derived_ref<Arg, T>,
                                    is_lvalue_to_rvalue_ref<Arg, T>
            >>>::type {};

        struct do_is_direct_constructible_h {
            template <typename T, typename Arg, typename = decltype(::new T(declval<Arg>()))>
                static true_type test(int);

            template <typename, typename>
                static false_type test(...);
        };

        template <typename T, typename Arg>
        struct is_direct_constructible_h
            : do_is_direct_constructible_h {
            using type = decltype(test<T, Arg>(0));
        };

        template <typename T, typename Arg>
        struct is_direct_constructible_new_safe
            : and_pred<is_destructible<T>,
                is_direct_constructible_h<T, Arg>>::type {};
    }

    template <typename T, typename Arg>
    struct is_direct_constructible
        : conditional_t<is_reference<T>::value,
            internal::is_direct_constructible_ref_cast<T, Arg>,
            internal::is_direct_constructible_new_safe<T, Arg>> {};

    /// Is default constructible
    namespace internal {
        struct do_is_default_constructible_h {
            template <typename T, typename = decltype(T())>
            static true_type test(int);

            template <typename>
            static false_type test(...);
        };

        template <typename T>
        struct is_default_constructible_h
            : do_is_default_constructible_h {
            using type = decltype(test<T>(0));
        };

        template <typename T>
        struct is_default_constructible_atom
            : and_pred<not_pred<is_void<T>>,
                is_default_constructible_h<T>>::type {};

        template <typename T, bool = is_array<T>::value>
        struct is_default_constructible_safe;

        template <typename T>
        struct is_default_constructible_safe<T, true>
            : and_pred<is_array_known_bounds<T>,
                is_default_constructible_atom<typename remove_all_extents<T>::type>>::type {};

        template <typename T>
        struct is_default_constructible_safe<T, false>
            : is_default_constructible_atom<T>::type {};
    }

    template <typename T>
    struct is_default_constructible
        : internal::is_default_constructible_safe<T>::type {};

    /// Is constructible
    template <typename T, typename ...Args>
    struct is_constructible_h
        : is_clean_constructible<T, Args...> {};

    template <typename T, typename Arg>
    struct is_constructible_h<T, Arg>
        : is_direct_constructible<T, Arg> {};

    template <typename T>
    struct is_constructible_h<T>
        : is_default_constructible<T> {};

    template <typename T, typename ...Args>
    struct is_constructible
        : is_constructible_h<T, Args...>::type {};

    /// Is trivially constructible
    template <typename T, typename ...Args>
    struct is_trivially_constructible
        : and_pred<is_constructible<T, Args...>,
            integral_constant<bool, __is_trivially_constructible(T, Args...)>>::type {};

    /// Is trivially default constructible
    template <typename T>
    struct is_trivially_default_constructible
        : is_trivially_constructible<T>::type {};

    /// Is trivial
    template <typename T>
    struct is_trivial
        : and_pred<is_trivially_copyable<T>,
            is_trivially_default_constructible<T>>::type {};

    /// Is nothrow default constructible
    namespace internal {
    template <typename T>
        struct is_nothrow_default_constructible_atom
            : integral_constant<bool, noexcept(T())> {};

        template <typename T, bool = is_array<T>::value>
        struct is_nothrow_default_constructible_h;

        template <typename T>
        struct is_nothrow_default_constructible_h<T, true>
            : and_pred<is_array_known_bounds<T>,
            is_nothrow_default_constructible_atom<typename
                remove_all_extents<T>::type>>::type {};

        template <typename T>
        struct is_nothrow_default_constructible_h<T, false>
            : is_nothrow_default_constructible_atom<T> {};
    }

    template <typename T>
    struct is_nothrow_default_constructible
        : and_pred<is_default_constructible<T>,
            internal::is_nothrow_default_constructible_h<T>>::type {};

    /// Is nothrow constructible
    namespace internal {
        template <typename T, typename ...Args>
        struct is_nothrow_consturctible
            : integral_constant<bool, noexcept(T(declval<Args>()...))> {};

        template <typename T, typename Arg>
        struct is_nothrow_consturctible<T, Arg>
            : integral_constant<bool, noexcept(static_cast<T>(declval<Arg>()))> {};

        template <typename T>
        struct is_nothrow_consturctible<T>
            : is_nothrow_default_constructible<T> {};
    } // namespace internal

    template <typename T, typename ...Args>
    struct is_nothrow_constructible
        : and_pred<is_constructible<T, Args...>,
            internal::is_nothrow_consturctible<T, Args...>>::type {};

    /// Is move constructible
    template <typename T>
    struct is_move_constructible
        : is_constructible<T, add_rvalue_reference_t<T>> {};

    /// Is trivially move constructible
    template <typename T>
    struct is_trivially_move_constructible
        : is_trivially_constructible<T, add_rvalue_reference_t<T>> {};

    /// Is nothrow move constructible
    template <typename T>
    struct is_nothrow_move_constructible
        : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};

    /// Is assignable
    namespace internal {
        template <typename T, typename U>
        struct is_assignable_h {
            template <typename T1, typename U1, typename =
                decltype(declval<T1>() = declval<U1>())>
            static true_type test(int);

            template <typename, typename>
            static false_type test(...);

            using type = decltype(test<T, U>(0));
        };
    } // namespace internal

    template <typename T, typename U>
    struct is_assignable
        : internal::is_assignable_h<T, U>::type {};

    /// Is trivially assignable
    template <typename T, typename U>
    struct is_trivially_assignable
        : and_pred<is_assignable<T, U>,
            integral_constant<bool, __is_trivially_assignable(T, U)>> {};

    /// Is nothrow assignable
    namespace internal {
        template <typename T, typename U>
        struct is_nothrow_assignable
            : integral_constant<bool, noexcept(declval<T>() = declval<U>())> {};
    } // namespace internal

    template <typename T, typename U>
    struct is_nothrow_assignable
        : and_pred<is_assignable<T, U>, internal::is_nothrow_assignable<T, U>> {};

    /// Is copy assignable
    template <typename T>
    struct is_copy_assignable
        : is_assignable<add_lvalue_reference_t<T>,
            add_lvalue_reference_t<const T>> {};

    /// Is trivially copy assignable
    template <typename T>
    struct is_trivially_copy_assignable
        : is_trivially_assignable<add_lvalue_reference_t<T>,
            add_lvalue_reference_t<const T>> {};

    /// Is nothrow copy assignable
    template <typename T>
    struct is_nothrow_copy_assignable
        : is_nothrow_assignable<add_lvalue_reference_t<T>,
            add_lvalue_reference_t<const T>> {};

    /// Is move assignable
    template <typename T>
    struct is_move_assignable
        : is_assignable<add_lvalue_reference_t<T>,
            add_rvalue_reference_t<const T>> {};

    /// Is trivially move assignable
    template <typename T>
    struct is_trivially_move_assignable
        : is_trivially_assignable<add_lvalue_reference_t<T>,
            add_rvalue_reference_t<const T>> {};

    /// Is nothrow move assignable
    template <typename T>
    struct is_nothrow_move_assignable
        : is_nothrow_assignable<add_lvalue_reference_t<T>,
            add_rvalue_reference_t<const T>> {};

    /// Has virtual destructor
    template <typename T>
    struct has_virtual_destructor
        : integral_constant<bool, __has_virtual_destructor(T)> {};

    /// Alignment of
    template <typename T>
    struct alignment_of
        : integral_constant<size_t, alignof(T)> {};

    namespace internal {
        template <typename Unqualified, bool IsConst, bool IsVol>
        struct cv_selector;

        template <typename Unqualified>
        struct cv_selector<Unqualified, false, false> {
            using type = Unqualified;
        };

        template <typename Unqualified>
        struct cv_selector<Unqualified, false, true> {
            using type = volatile Unqualified;
        };

        template <typename Unqualified>
        struct cv_selector<Unqualified, true, false> {
            using type = const Unqualified;
        };

        template <typename Unqualified>
        struct cv_selector<Unqualified, true, true> {
            using type = const volatile Unqualified;
        };

        template <typename Qualified, typename Unqualified,
            bool IsConst = is_const<Qualified>::value,
            bool IsVol = is_volatile<Qualified>::value>
        struct match_cv_qualifiers {
            using type = typename cv_selector<Unqualified, IsConst, IsVol>::type;
        };
    } // namespace internal

    /// Make unsigned
    namespace internal {
        template <typename T>
        struct make_unsigned_for_numbers {
            using type = T;
        };

        template <>
        struct make_unsigned_for_numbers<char> {
            using type = unsigned char;
        };

        template <>
        struct make_unsigned_for_numbers<signed char> {
            using type = unsigned char;
        };

        template <>
        struct make_unsigned_for_numbers<short> {
            using type = unsigned short;
        };

        template <>
        struct make_unsigned_for_numbers<int> {
            using type = unsigned int;
        };

        template <>
        struct make_unsigned_for_numbers<long> {
            using type = unsigned long;
        };

        template <>
        struct make_unsigned_for_numbers<long long> {
            using type = unsigned long long;
        };

        template <typename T, 
            bool IsInt = is_integral<T>::value,
            bool IsEnum = is_enum<T>::value>
        struct make_unsigned_h;

        template <typename T>
        struct make_unsigned_h<T, true, false> {
            using usigned_type =
                typename make_unsigned_for_numbers<typename remove_cv<T>::type>::type;
            using cv_unsigned = match_cv_qualifiers<T, usigned_type>;

            using type = typename cv_unsigned::type;
        };

        template <typename T>
        struct make_unsigned_h<T, false, true> {
            using smallest = unsigned char;
            static constexpr bool b0 = sizeof(T) <= sizeof(smallest);
            static constexpr bool b1 = sizeof(T) <= sizeof(unsigned short);
            static constexpr bool b2 = sizeof(T) <= sizeof(unsigned int);
            using cond2 = conditional_t<b2, unsigned int, unsigned long>;
            using cond1 = conditional_t<b1, unsigned short, cond2>;

            using type = conditional_t<b0, smallest, cond1>;
        };
    } // namespace internal

    template <typename T>
    struct make_unsigned { 
        using type = typename internal::make_unsigned_h<T>::type;
    };

    template <>
    struct make_unsigned<bool>;

    template <typename T>
    using make_unsigned_t = typename make_unsigned<T>::type;

    /// Make signed
    namespace internal {
        template <typename T>
        struct make_signed_for_numbers {
            using type = T;
        };

        template <>
        struct make_signed_for_numbers<char> { 
            using type = signed char;
        };

        template <>
        struct make_signed_for_numbers<unsigned char> {
            using type = signed char;
        };

        template <>
        struct make_signed_for_numbers<unsigned short> {
            using type = signed short;
        };

        template <>
        struct make_signed_for_numbers<unsigned int> {
            using type = signed int;
        };

        template <>
        struct make_signed_for_numbers<unsigned long> {
            using type = signed long;
        };

        template <>
        struct make_signed_for_numbers<unsigned long long> {
            using type = signed long long;
        };

        template <typename T, bool IsInt = is_integral<T>::value, bool IsEnum = is_enum<T>::value>
        struct make_signed_h;

        template <typename T>
        struct make_signed_h<T, true, false> {
            using signed_type =
                typename make_signed_for_numbers<typename remove_cv<T>::type>::type;
            using cv_signed = match_cv_qualifiers<T, signed_type>;

            using type = typename cv_signed::type;
        };

        template <typename T>
        struct make_signed_h<T, false, true> {
            using smallest = signed char;
            static constexpr bool b0 = sizeof(T) <= sizeof(smallest);
            static constexpr bool b1 = sizeof(T) <= sizeof(signed short);
            static constexpr bool b2 = sizeof(T) <= sizeof(signed int);
            using cond2 = conditional_t<b2, signed int, signed long>;
            using cond1 = conditional_t<b1, signed short, cond2>;

            using type = conditional_t<b0, smallest, cond1>;
        };
    } // namespace internal

    template <typename T>
    struct make_signed {
        using type = typename internal::make_signed_h<T>::type;
    };

    template <>
    struct make_signed<bool>;

    template <typename T>
    using make_signed_t = typename make_signed<T>::type;

    /// Void type
    template <typename ...>
    using void_t = void;

    /// Common type
    template <typename ...Ts>
    struct common_type {};

    template <typename ...Ts>
    using common_type_t = typename common_type<Ts...>::type;

    template <typename T>
    struct common_type<T> {
        using type = decay_t<T>;
    };

    namespace internal {
        template <typename T1, typename T2>
        using cond_t = decltype(false ? declval<T1>() : declval<T2>());

        template <typename T1, typename T2, typename = void>
        struct common_type_2_default {};

        template <typename T1, typename T2>
        struct common_type_2_default<T1, T2, void_t<cond_t<T1, T2>>> {
            using type = decay_t<cond_t<T1, T2>>;
        };

        template <typename T1, typename T2,
            typename D1 = decay_t<T1>, typename D2 = decay_t<T2>>
        struct common_type_2
            : common_type<D1, D2> {};

        template <typename D1, typename D2>
        struct common_type_2<D1, D2, D1, D2>
            : common_type_2_default<D1, D2> {};
    } // namespace internal

    template <typename T1, typename T2>
    struct common_type<T1, T2> : internal::common_type_2<T1, T2> {};

    namespace internal {
        template <typename Always_void,
            typename T1, typename T2, typename ...R>
        struct common_type_multi {};

        template <typename T1, typename T2, typename ...R>
        struct common_type_multi<void_t<common_type_t<T1, T2>>, T1, T2, R...>
            : common_type<common_type_t<T1, T2>, R...> {};
    } // namespace internal

    template <typename T1, typename T2, typename ...R>
    struct common_type<T1, T2, R...>
        : internal::common_type_multi<void, T1, T2, R...> {};

    /// The underlying type of an enum
    template <typename T>
    struct underlying_type {
        using type = __underlying_type(T);
    };

    template <typename T>
    using underlying_type_t = typename underlying_type<T>::type;
} // namespace std

#endif // LP_CC_LIB_TYPE_TRAITS_HH
