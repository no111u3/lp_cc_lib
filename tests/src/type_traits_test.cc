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
 * Type traits test
 * @file type_traits_test.cc
 * @author Boris Vinogradov
 */

#include <type_traits.hh>

struct A {
    int fun() const &;
};

class B {};

class C { virtual void foo(); virtual ~C(); };

class D { explicit D(int) {} D(const D &) {} };

struct D1 {
    explicit D1(int) {}

    D1(const D1 &) {}

    D1 & operator = (const D1 &) { return *this; }
};

enum E {};

class F { virtual void foo() = 0; };

struct G : F {};

class Z final {};

enum class Ec : int {};

union U { int a; float b; };

template <typename>
struct PM_traits {};

template <typename T, typename U>
struct PM_traits<U T::*> {
    using member_type = U;
};

int f();

void type_traits_test() {
    using namespace std;

    static_assert(false_type::value == false_type::value, "");
    static_assert(true_type::value == true_type::value, "");
    static_assert(true_type::value != false_type::value, "");

    static_assert(is_same<int, int>::value == true, "");
    static_assert(is_same<char, int>::value == false, "");
    static_assert(is_same<A, A>::value == true, "");
    static_assert(is_same<A, B>::value == false, "");

    static_assert(is_base_of<F, G>::value == true, "");
    static_assert(is_base_of<G, F>::value == false, "");
    static_assert(is_base_of<A, B>::value == false, "");

    static_assert(is_convertible<F*, G*>::value == false, "");
    static_assert(is_convertible<G*, F*>::value == true, "");
    static_assert(is_convertible<int, long>::value == true, "");

    static_assert(is_same<conditional<true, int, double>::type, int>::value, "");
    static_assert(is_same<conditional<false, int, double>::type, double>::value, "");

    static_assert(or_pred<false_type, true_type, false_type>::value == true, "");
    static_assert(and_pred<true_type, false_type, true_type>::value == false, "");
    static_assert(not_pred<true_type>::value == false, "");

    static_assert(is_same<enable_if_t<true>, void>::value, "");

    static_assert(is_same<remove_const_t<const int>, int>::value, "");
    static_assert(is_same<remove_volatile_t<volatile int>, int>::value, "");
    static_assert(is_same<remove_const_t<const volatile int>, volatile int>::value, "");
    static_assert(is_same<remove_volatile_t<const volatile int>, const int>::value, "");
    static_assert(is_same<remove_cv_t<volatile const int>, int>::value, "");
    static_assert(is_same<remove_cv_t<const volatile int>, int>::value, "");

    static_assert(is_same<add_cv_t<int>, const volatile int>::value, "");
    static_assert(is_same<add_const_t<int>, const int>::value, "");
    static_assert(is_same<add_volatile_t<int>, volatile int>::value, "");

    static_assert(is_same<remove_reference_t<int &&>, int>::value, "");
    static_assert(is_same<remove_reference_t<int &>, int>::value, "");

    static_assert(is_same<add_lvalue_reference_t<int>, int &>::value, "");
    static_assert(is_same<add_rvalue_reference_t<int>, int &&>::value, "");

    static_assert(is_same<remove_pointer_t<int>, int>::value, "");
    static_assert(is_same<remove_pointer_t<int *>, int>::value, "");
    static_assert(is_same<remove_pointer_t<int **>, int *>::value, "");

    static_assert(is_same<add_pointer_t<int>, int *>::value, "");
    static_assert(is_same<add_pointer_t<int *>, int **>::value, "");
    static_assert(is_same<add_pointer_t<int **>, int ***>::value, "");

    static_assert(is_same<remove_extent_t<int[2][3]>, int[3]>::value, "");
    static_assert(is_same<remove_extent_t<int[2]>, int>::value, "");

    static_assert(is_same<remove_all_extents_t<int[][1][2][3][4]>, int>::value, "");
    static_assert(is_same<remove_all_extents_t<double[2][4]>, double>::value, "");

    static_assert(is_const<const int>::value == true, "");
    static_assert(is_const<int>::value == false, "");
    static_assert(is_volatile<volatile char>::value == true, "");
    static_assert(is_volatile<char>::value == false, "");

    static_assert(is_trivial<A>::value == true, "");
    static_assert(is_trivial<D>::value == false, "");

    static_assert(is_void<void>::value == true, "");
    static_assert(is_void<A>::value == false, "");

    static_assert(is_null_pointer<nullptr_t>::value == true, "");
    static_assert(is_null_pointer<A>::value == false, "");

    static_assert(is_integral<char>::value == true, "");
    static_assert(is_integral<int>::value == true, "");
    static_assert(is_integral<double>::value == false, "");
    static_assert(is_integral<B>::value == false, "");

    static_assert(is_floating_point<float>::value == true, "");
    static_assert(is_floating_point<int>::value == false, "");
    static_assert(is_floating_point<A>::value == false, "");

    static_assert(is_array<int>::value == false, "");
    static_assert(is_array<int[]>::value == true, "");
    static_assert(is_array<int[1]>::value == true, "");
    static_assert(is_array<A>::value == false, "");
    static_assert(is_array<A[]>::value == true, "");
    static_assert(is_array<A[4]>::value == true, "");

    static_assert(is_enum<int>::value == false, "");
    static_assert(is_enum<A>::value == false, "");
    static_assert(is_enum<E>::value == true, "");
    static_assert(is_enum<Ec>::value == true, "");
    
    static_assert(is_union<int>::value == false, "");
    static_assert(is_union<A>::value == false, "");
    static_assert(is_union<E>::value == false, "");
    static_assert(is_union<Ec>::value == false, "");
    static_assert(is_union<U>::value == true, "");

    static_assert(is_class<A>::value == true, "");
    static_assert(is_class<int>::value == false, "");
    static_assert(is_class<E>::value == false, "");
    static_assert(is_class<U>::value == false, "");

    static_assert(is_function<A>::value == false, "");
    static_assert(is_function<int(int)>::value == true, "");
    static_assert(is_function<decltype(f)>::value == true, "");
    static_assert(is_function<int>::value == false, "");
    using T = PM_traits<decltype(&A::fun)>::member_type;
    static_assert(is_function<T>::value == true, "");

    static_assert(is_pointer<int>::value == false, "");
    static_assert(is_pointer<int *>::value == true, "");
    static_assert(is_pointer<int &>::value == false, "");
    static_assert(is_pointer<int[]>::value == false, "");
    static_assert(is_pointer<A>::value == false, "");
    static_assert(is_pointer<A **>::value == true, "");

    static_assert(is_lvalue_reference<int>::value == false, "");
    static_assert(is_lvalue_reference<int &>::value == true, "");
    static_assert(is_lvalue_reference<int &&>::value == false, "");
    static_assert(is_lvalue_reference<A>::value == false, "");
    static_assert(is_lvalue_reference<A &>::value == true, "");
    static_assert(is_lvalue_reference<A &&>::value == false, "");

    static_assert(is_rvalue_reference<int>::value == false, "");
    static_assert(is_rvalue_reference<int &>::value == false, "");
    static_assert(is_rvalue_reference<int &&>::value == true, "");
    static_assert(is_rvalue_reference<A>::value == false, "");
    static_assert(is_rvalue_reference<A &>::value == false, "");
    static_assert(is_rvalue_reference<A &&>::value == true, "");

    static_assert(is_member_pointer<int(A::*)>::value == true, "");
    static_assert(is_member_pointer<int>::value == false, "");

    static_assert(is_member_function_pointer<int>::value == false, "");
    static_assert(is_member_function_pointer<decltype(&A::fun)>::value == true, "");

    static_assert(is_member_object_pointer<int(A::*)>::value == true, "");
    static_assert(is_member_object_pointer<int(A::*)()>::value == false, "");

    static_assert(is_arithmetic<A>::value == false, "");
    static_assert(is_arithmetic<bool>::value == true, "");
    static_assert(is_arithmetic<int const>::value == true, "");
    static_assert(is_arithmetic<int &>::value == false, "");
    static_assert(is_arithmetic<float *>::value == false, "");

    static_assert(is_fundamental<A>::value == false, "");
    static_assert(is_fundamental<int>::value == true, "");
    static_assert(is_fundamental<int &>::value == false, "");
    static_assert(is_fundamental<float *>::value == false, "");

    static_assert(is_scalar<int>::value == true, "");
    static_assert(is_scalar<A>::value == false, "");

    static_assert(is_object<int>::value == true, "");
    static_assert(is_object<int &>::value == false, "");
    static_assert(is_object<A>::value == true, "");
    static_assert(is_object<A &>::value == false, "");

    static_assert(is_compound<A>::value == true, "");
    static_assert(is_compound<int>::value == false, "");

    static_assert(is_reference<int>::value == false, "");
    static_assert(is_reference<int &>::value == true, "");
    static_assert(is_reference<int &&>::value == true, "");
    static_assert(is_reference<A>::value == false, "");
    static_assert(is_reference<A &>::value == true, "");
    static_assert(is_reference<A &&>::value == true, "");

    static_assert(is_trivially_copyable<A>::value == true, "");
    static_assert(is_trivially_copyable<B>::value == true, "");
    static_assert(is_trivially_copyable<C>::value == false, "");

    static_assert(is_standard_layout<A>::value == true, "");
    static_assert(is_standard_layout<B>::value == true, "");
    static_assert(is_standard_layout<C>::value == false, "");

    static_assert(is_pod<A>::value == true, "");
    static_assert(is_pod<B>::value == true, "");
    static_assert(is_pod<C>::value == false, "");

    static_assert(is_literal_type<B>::value == true, "");
    static_assert(is_literal_type<C>::value == false, "");

    static_assert(is_empty<A>::value == true, "");
    static_assert(is_empty<U>::value == false, "");

    static_assert(is_polymorphic<A>::value == false, "");
    static_assert(is_polymorphic<C>::value == true, "");

    static_assert(is_abstract<A>::value == false, "");
    static_assert(is_abstract<C>::value == false, "");
    static_assert(is_abstract<F>::value == true, "");
    static_assert(is_abstract<G>::value == true, "");

    static_assert(is_final<A>::value == false, "");
    static_assert(is_final<Z>::value == true, "");

    static_assert(is_signed<A>::value == false, "");
    static_assert(is_signed<int>::value == true, "");
    static_assert(is_signed<float>::value == true, "");
    static_assert(is_signed<unsigned long>::value == false, "");

    static_assert(is_unsigned<A>::value == false, "");
    static_assert(is_unsigned<int>::value == false, "");
    static_assert(is_unsigned<float>::value == false, "");
    static_assert(is_unsigned<unsigned long>::value == true, "");

    static_assert(is_same<decay_t<int>, int>::value == true, "");
    static_assert(is_same<decay_t<int &>, int>::value == true, "");
    static_assert(is_same<decay_t<int &&>, int>::value == true, "");
    static_assert(is_same<decay_t<const int &>, int>::value == true, "");
    static_assert(is_same<decay_t<int[2]>, int *>::value == true, "");
    static_assert(is_same<decay_t<int(int)>, int(*)(int)>::value == true, "");

    static_assert(is_constructible<A>::value == true, "");
    static_assert(is_constructible<A, int>::value == false, "");
    static_assert(is_nothrow_constructible<A>::value == true, "");
    static_assert(is_nothrow_constructible<D>::value == false, "");
    static_assert(is_trivially_constructible<A, const A &>::value == true, "");
    static_assert(is_trivially_constructible<A, int>::value == false, "");
    static_assert(is_default_constructible<A>::value == true, "");
    static_assert(is_default_constructible<D>::value == false, "");
    static_assert(is_nothrow_default_constructible<A>::value == true, "");
    static_assert(is_nothrow_default_constructible<D>::value == false, "");
    static_assert(is_trivially_default_constructible<A>::value == true, "");
    static_assert(is_trivially_default_constructible<D>::value == false, "");

    static_assert(is_move_constructible<A>::value == true, "");
    static_assert(is_move_constructible<D>::value == false, "");
    static_assert(is_move_constructible<D1>::value == true, "");
    static_assert(is_trivially_move_constructible<A>::value == true, "");
    static_assert(is_trivially_move_constructible<D>::value == false, "");
    static_assert(is_nothrow_move_constructible<A>::value == true, "");
    static_assert(is_nothrow_move_constructible<D>::value == false, "");
    static_assert(is_nothrow_move_constructible<D1>::value == false, "");

    static_assert(is_assignable<int, int>::value == false, "");
    static_assert(is_assignable<int &, int>::value == true, "");
    static_assert(is_assignable<int, double>::value == false, "");
    static_assert(is_nothrow_assignable<int &, double>::value == true, "");
    static_assert(is_trivially_assignable<A &, A>::value == true, "");

    static_assert(is_trivially_copy_assignable<A>::value == true, "");
    static_assert(is_copy_assignable<int[2]>::value == false, "");
    static_assert(is_nothrow_copy_assignable<int>::value == true, "");

    static_assert(is_nothrow_move_assignable<A>::value == true, "");
    static_assert(is_move_assignable<int[2]>::value == false, "");
    static_assert(is_trivially_move_assignable<B>::value == true, "");
    static_assert(is_move_assignable<D1>::value == true, "");
    static_assert(is_nothrow_move_assignable<D1>::value == false, "");

    static_assert(is_destructible<A>::value == true, "");
    static_assert(is_nothrow_destructible<A>::value == true, "");
    static_assert(is_trivially_destructible<A>::value == true, "");

    static_assert(has_trivial_destructor<A>::value == true, "");
    static_assert(has_trivial_destructor<C>::value == false, "");

    static_assert(alignment_of<A>::value == 1, "");
    static_assert(alignment_of<int>::value == 4, "");
    static_assert(alignment_of<double>::value == 8, "");

    static_assert(rank<int[]>::value == 1, "");
    static_assert(rank<int[][2][3][4]>::value == 4, "");
    static_assert(rank<int>::value == 0, "");

    static_assert(extent<int[3][4]>::value == 3, "");
    static_assert(extent<int[3][4][5], 1>::value == 4, "");
    static_assert(extent<int[3][4][5], 3>::value == 0, "");
    static_assert(extent<int[]>::value == 0, "");
}

