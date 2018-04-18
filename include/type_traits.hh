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
        : conditional<T1::value, T1, T2>::type {};

    template <typename T1, typename T2, typename T3, typename ...Ts>
    struct or_pred<T1, T2, T3, Ts...>
        : conditional<T1::value, T1, or_pred<T2, T3, Ts...>>::type {};

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
        : conditional<T1::value, T2, T1>::type {};

    template <typename T1, typename T2, typename T3, typename ...Ts>
    struct and_pred<T1, T2, T3, Ts...>
        : conditional<T1::value, and_pred<T2, T3, Ts...>, T1>::type {};

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
    template <typename T>
    struct is_integral_helper
        : false_type {};

    template <>
    struct is_integral_helper<bool>
        : true_type {};

    template <>
    struct is_integral_helper<char>
        : true_type {};

    template <>
    struct is_integral_helper<signed char>
        : true_type {};

    template <>
    struct is_integral_helper<unsigned char>
        : true_type {};

    template <>
    struct is_integral_helper<short>
        : true_type {};

    template <>
    struct is_integral_helper<unsigned short>
        : true_type {};

    template <>
    struct is_integral_helper<int>
        : true_type {};

    template <>
    struct is_integral_helper<unsigned int>
        : true_type {};

    template <>
    struct is_integral_helper<long>
        : true_type {};

    template <>
    struct is_integral_helper<unsigned long>
        : true_type {};

    template <>
    struct is_integral_helper<long long>
        : true_type {};

    template <>
    struct is_integral_helper<unsigned long long>
        : true_type {};

    /// Is integral
    template <typename T>
    struct is_integral
        : is_integral_helper<remove_cv_t<T>>::type {};

    // Float check
    template <typename T>
    struct is_floating_point_helper
        : false_type {};

    template <>
    struct is_floating_point_helper<float>
        : true_type {};

    template <>
    struct is_floating_point_helper<double>
        : true_type {};

    template <>
    struct is_floating_point_helper<long double>
        : true_type {};

    /// Is integral
    template <typename T>
    struct is_floating_point
        : is_floating_point_helper<remove_cv_t<T>>::type {};

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
    template <typename T>
    struct is_pointer_helper
        : false_type {};

    template <typename T>
    struct is_pointer_helper<T *>
        : true_type {};

    /// Is pointer
    template <typename T>
    struct is_pointer
        : is_pointer_helper<remove_cv_t<T>>::type {};

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
    template <typename T>
    struct is_member_pointer_helper
        : false_type {};

    template <typename T, typename U>
    struct is_member_pointer_helper<T U::*>
        : true_type {};

    template <typename T>
    struct is_member_pointer
        : is_member_pointer_helper<remove_cv_t<T>> {};

    /// Is member function pointer
    template <typename T>
    struct is_member_function_pointer_helper
        : false_type {};

    template <typename T, typename U>
    struct is_member_function_pointer_helper<T U::*>
        : is_function<T> {};

    template <typename T>
    struct is_member_function_pointer
        : is_member_function_pointer_helper<remove_cv_t<T>> {};

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
    template <typename T, bool = is_referenceable<T>::value>
    struct add_lvalue_reference_helper {
        using type = T;
    };

    template <typename T>
    struct add_lvalue_reference_helper<T, true> {
        using type = T &;
    };

    template <typename T>
    struct add_lvalue_reference
        : add_lvalue_reference_helper<T> {};

    template <typename T>
    using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

    /// Add rvalue reference
    template <typename T, bool = is_referenceable<T>::value>
    struct add_rvalue_reference_helper {
        using type = T;
    };

    template <typename T>
    struct add_rvalue_reference_helper<T, true> {
        using type = T &&;
    };

    template <typename T>
    struct add_rvalue_reference
        : add_rvalue_reference_helper<T> {};

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
    template <typename T, bool is_function_type = false>
    struct add_pointer_internal {
        using type = remove_reference_t<T> *;
    };

    template <size_t Len, size_t Align>
    struct aligned_storage {
        struct type {
            alignas(Align) unsigned char data[Len];
        };
    };

    template <size_t Len, size_t Align>
    using aligned_storage_t = typename aligned_storage<Len, Align>::type;

    template <typename T>
    struct add_pointer_internal<T, true> {
        using type = T;
    };

    template <typename T, typename ...Args>
    struct add_pointer_internal<T(Args...), true> {
        using type = T(*)(Args...);
    };

    template <typename T, class ...Args>
    struct add_pointer_internal<T(Args..., ...), true> {
        using type = T(*)(Args..., ...);
    };

    template <typename T>
    struct add_pointer
        : add_pointer_internal<T, is_function<T>::value> {};

    template <typename T>
    using add_pointer_t = typename add_pointer<T>::type;

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
    struct declval_internal {
        static add_rvalue_reference_t<T> delegate();
    };

    /// Is array with known bounds
    template <typename T>
    struct is_array_known_bounds
        : integral_constant<bool, (extent<T>::value > 0)> {};

    template <typename T>
    inline add_rvalue_reference_t<T> declval() noexcept {
        return declval_internal<T>::delegate();
    }

    /// Is convertible
    template <typename From, typename To,
        bool = or_pred<is_void<From>, is_function<To>, is_array<To>>::value>
    struct is_convertible_helper {
        using type = typename is_void<To>::type;
    };

    template <typename From, typename To>
    struct is_convertible_helper<From, To, false>
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

    template <typename From, typename To>
    struct is_convertible
        : is_convertible_helper<From, To>::type {};

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
    struct is_signed_helper
        : false_type {};

    template <typename T>
    struct is_signed_helper<T, true>
        : integral_constant<bool, T(-1) < T(0)> {};

    template <typename T>
    struct is_signed
        : is_signed_helper<T>::type {};

    /// Decay
    template <typename T>
    struct decay {
        using U = remove_reference_t<T>;

        using type = typename conditional<
            is_array<U>::value,
            remove_extent_t<U> *,
            typename conditional<
                is_function<U>::value,
                add_pointer_t<U>,
                remove_cv_t<U>
            >::type
        >::type;
    };

    template <typename T>
    using decay_t = typename decay<T>::type;

    /// Is unsigned
    template <typename T>
    struct is_unsigned
        : and_pred<is_arithmetic<T>, not_pred<is_signed<T>>>::type {};

    /// Is destructible
    struct do_is_destructible_internal {
        template <typename T, typename = decltype(declval<T&>().~T())>
        static true_type test(int);

        template <typename>
        static false_type test(...);
    };

    template <typename T>
    struct is_destructible_internal
        : do_is_destructible_internal {
        using type = decltype(test<T>(0));
    };

    template <typename T, bool = or_pred<is_void<T>,
        is_array_unknown_bounds<T>, is_function<T>>::value,
        bool = or_pred<is_reference<T>, is_scalar<T>>::value>
    struct is_destructible_safe;

    template <typename T>
    struct is_destructible_safe<T, false, false>
        : is_destructible_internal<remove_all_extents_t<T>>::type {};

    template <typename T>
    struct is_destructible_safe<T, true, false>
        : false_type {};

    template <typename T>
    struct is_destructible_safe<T, false, true>
        : true_type {};

    template <typename T>
    struct is_destructible
        : is_destructible_safe<T>::type {};

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
    struct do_is_nothrow_destructible_internal {
        template <typename T>
        static integral_constant<bool, noexcept(declval<T &>().~T())> test(int);

        template <typename>
        static false_type test(...);
    };

    template <typename T>
    struct is_nothrow_destructible_internal
        : do_is_nothrow_destructible_internal {
        using type = decltype(test<T>(0));
    };

    template <typename T,
        bool = or_pred<is_void<T>, is_array_unknown_bounds<T>, is_function<T>>::value,
        bool = or_pred<is_reference<T>, is_scalar<T>>::value>
    struct is_nothrow_destructible_safe;

    template <typename T>
    struct is_nothrow_destructible_safe<T, false, false>
        : is_nothrow_destructible_internal<typename
               remove_all_extents<T>::type>::type {};

  template <typename T>
    struct is_nothrow_destructible_safe<T, true, false>
        : false_type {};

  template <typename T>
    struct is_nothrow_destructible_safe<T, false, true>
        : true_type { };

    template <typename T>
    struct is_nothrow_destructible
        : is_nothrow_destructible_safe<T>::type {};

    /// Is clean constructible
    struct do_clean_constructible_internal {
        template <typename T, typename ...Args, typename = decltype(T(declval<Args>()...))>
            static true_type test(int);

        template <typename, typename...>
            static false_type test(...);
    };

    template <typename T, typename ...Args>
    struct is_clean_constructible_internal
        : do_clean_constructible_internal {
        using type = decltype(test<T, Args...>(0));
    };

    template <typename T, typename ...Args>
    struct is_clean_constructible
        : is_clean_constructible_internal<T, Args...>::type {};

    /// Is static castable
    struct do_is_static_castable_internal {
        template <typename From, typename To, typename = decltype(static_cast<To>(declval<From>()))>
            static true_type test(int);

        template <typename, typename>
            static false_type test(...);
    };

    template <typename From, typename To>
    struct is_static_castable_internal
        : do_is_static_castable_internal {
      using type = decltype(test<From, To>(0));
    };

    template <typename From, typename To>
    struct is_static_castable_safe
        : is_static_castable_internal<From, To>::type {};


    template <typename From, typename To>
    struct is_static_castable
        : integral_constant<bool, (
            is_static_castable_safe<From, To>::value)> {};

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

    /// Is direct constructible reference cast
    template <typename T, typename Arg>
    struct is_direct_constructible_ref_cast
        : and_pred<is_static_castable<Arg, T>,
            not_pred<or_pred<is_base_to_derived_ref<Arg, T>,
                                is_lvalue_to_rvalue_ref<Arg, T>
          >>>::type {};

    /// Is direct constructible new safe
    struct do_is_direct_constructible_internal {
        template <typename T, typename Arg, typename = decltype(::new T(declval<Arg>()))>
            static true_type test(int);

        template <typename, typename>
            static false_type test(...);
    };

    template <typename T, typename Arg>
    struct is_direct_constructible_internal
        : do_is_direct_constructible_internal {
        using type = decltype(test<T, Arg>(0));
    };

    template <typename T, typename Arg>
    struct is_direct_constructible_new_safe
        : and_pred<is_destructible<T>,
            is_direct_constructible_internal<T, Arg>>::type {};

    /// Is direct constructible
    template <typename T, typename Arg>
    struct is_direct_constructible
        : conditional<is_reference<T>::value,
            is_direct_constructible_ref_cast<T, Arg>,
            is_direct_constructible_new_safe<T, Arg>>::type {};

    /// Is default constructible safe
    struct do_is_default_constructible_internal {
        template <typename T, typename = decltype(T())>
        static true_type test(int);

        template <typename>
        static false_type test(...);
    };

    template <typename T>
    struct is_default_constructible_internal
        : do_is_default_constructible_internal {
        using type = decltype(test<T>(0));
    };

    template <typename T>
    struct is_default_constructible_atom
        : and_pred<not_pred<is_void<T>>,
            is_default_constructible_internal<T>>::type {};

    template <typename T, bool = is_array<T>::value>
    struct is_default_constructible_safe;

    template <typename T>
    struct is_default_constructible_safe<T, true>
        : and_pred<is_array_known_bounds<T>,
            is_default_constructible_atom<typename remove_all_extents<T>::type>>::type {};

    template <typename T>
    struct is_default_constructible_safe<T, false>
        : is_default_constructible_atom<T>::type {};

    /// is_default_constructible
    template <typename T>
    struct is_default_constructible
        : is_default_constructible_safe<T>::type {};

    /// Is constructible
    template <typename T, typename ...Args>
    struct is_constructible_internal
        : is_clean_constructible<T, Args...> {};

    template <typename T, typename Arg>
    struct is_constructible_internal<T, Arg>
        : is_direct_constructible<T, Arg> {};

    template <typename T>
    struct is_constructible_internal<T>
        : is_default_constructible<T> {};

    template <typename T, typename ...Args>
    struct is_constructible
        : is_constructible_internal<T, Args...>::type {};

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
    template <typename T>
    struct is_nothrow_default_constructible_atom
        : integral_constant<bool, noexcept(T())> {};

    template <typename T, bool = is_array<T>::value>
    struct is_nothrow_default_constructible_internal;

    template <typename T>
    struct is_nothrow_default_constructible_internal<T, true>
        : and_pred<is_array_known_bounds<T>,
        is_nothrow_default_constructible_atom<typename
            remove_all_extents<T>::type>>::type {};

    template <typename T>
    struct is_nothrow_default_constructible_internal<T, false>
        : is_nothrow_default_constructible_atom<T> {};

    template <typename T>
    struct is_nothrow_default_constructible
        : and_pred<is_default_constructible<T>,
            is_nothrow_default_constructible_internal<T>>::type {};

    /// Is nothrow constructible
    template <typename T, typename ...Args>
    struct is_nothrow_constructible_internal
        : integral_constant<bool, noexcept(T(declval<Args>()...))> {};

    template <typename T, typename Arg>
    struct is_nothrow_constructible_internal<T, Arg>
        : integral_constant<bool, noexcept(static_cast<T>(declval<Arg>()))> {};

    template <typename T>
    struct is_nothrow_constructible_internal<T>
        : is_nothrow_default_constructible<T> {};

    template <typename T, typename ...Args>
    struct is_nothrow_constructible
        : and_pred<is_constructible<T, Args...>,
            is_nothrow_constructible_internal<T, Args...>>::type {};

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
    template <typename T, typename U>
    struct is_assignable_internal {
        template <typename T1, typename U1, typename = decltype(declval<T1>() = declval<U1>())>
        static true_type test(int);

        template <typename, typename>
        static false_type test(...);

        using type = decltype(test<T, U>(0));
    };

    template <typename T, typename U>
    struct is_assignable
        : is_assignable_internal<T, U>::type {};

    /// Is trivially assignable
    template <typename T, typename U>
    struct is_trivially_assignable
        : and_pred<is_assignable<T, U>,
            integral_constant<bool, __is_trivially_assignable(T, U)>> {};

    /// Is nothrow assignable
    template <typename T, typename U>
    struct is_nothrow_assignable_internal
        : integral_constant<bool, noexcept(declval<T>() = declval<U>())> {};

    template <typename T, typename U>
    struct is_nothrow_assignable
        : and_pred<is_assignable<T, U>, is_nothrow_assignable_internal<T, U>> {};

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

    /// Alignment of
    template <typename T>
    struct alignment_of
        : integral_constant<size_t, alignof(T)> {};
} // namespace std

#endif // LP_CC_LIB_TYPE_TRAITS_HH
