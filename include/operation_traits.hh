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
 * Operation traits
 * @file operation_traits.hh
 * @author Boris Vinogradov
 */

#include <operations.hh>
#include <type_list.hh>
#include <type_traits.hh>

#ifndef LP_CC_LIB_OPERATION_TRAITS
#define LP_CC_LIB_OPERATION_TRAITS

namespace lp {

    /// Operation apply for compiled time value
    template <typename T, T Value, typename Op, typename Op_type>
    struct op_apply;

    template <typename T, T Value, typename Op>
    struct op_apply<T, Value, Op, and_type> {
        static constexpr T value = Value & Op::template mask<T>::value;
    };

    template <typename T, T Value, typename Op>
    struct op_apply<T, Value, Op, or_type> {
        static constexpr T value = Value | Op::template mask<T>::value;
    };

    template <typename T, T Value, typename Op>
    struct op_apply<T, Value, Op, nand_type> {
        static constexpr T value = Value & ~Op::template mask<T>::value;
    };

    template <typename T, T Value, typename Op>
    struct op_apply<T, Value, Op, nor_type> {
        static constexpr T value = Value | ~Op::template mask<T>::value;
    };

    template <typename T, T Value, typename Op>
    struct op_apply<T, Value, Op, xor_type> {
        static constexpr T value = Value ^ Op::template mask<T>::value;
    };

    template <typename T, T Value, typename Op>
    struct op_apply<T, Value, Op, nxor_type> {
        static constexpr T value = Value ^ ~Op::template mask<T>::value;
    };

    /// Operation apply function for compiled time value
    template <typename T, typename Op, typename Op_type>
    struct op_apply_func;

    template <typename T, typename Op>
    struct op_apply_func<T, Op, and_type> {
        static constexpr T get_value(const T value) noexcept {
            return value & Op::template mask<T>::value;
        }
    };

    template <typename T, typename Op>
    struct op_apply_func<T, Op, or_type> {
        static constexpr T get_value(const T value) noexcept {
            return value | Op::template mask<T>::value;
        }
    };

    template <typename T, typename Op>
    struct op_apply_func<T, Op, nand_type> {
        static constexpr T get_value(const T value) noexcept {
            return value & ~Op::template mask<T>::value;
        }
    };

    template <typename T, typename Op>
    struct op_apply_func<T, Op, nor_type> {
        static constexpr T get_value(const T value) noexcept {
            return value | ~Op::template mask<T>::value;
        }
    };

    template <typename T, typename Op>
    struct op_apply_func<T, Op, xor_type> {
        static constexpr T get_value(const T value) noexcept {
            return value ^ Op::template mask<T>::value;
        }
    };

    template <typename T, typename Op>
    struct op_apply_func<T, Op, nxor_type> {
        static constexpr T get_value(const T value) noexcept {
            return value ^ ~Op::template mask<T>::value;
        }
    };

    /// Operation unpack for compiled time value
    template <typename T, T Value, typename ...Ops>
    struct op_unpack;

    template <typename T, T Value>
    struct op_unpack<T, Value> {
        static constexpr T value = Value;
    };

    template <typename T, T Value, typename ...Ops>
    struct op_unpack<T, Value, type_list<Ops...>> {
        static constexpr T value =
            op_unpack<T, Value, Ops...>::value;
    };

    template <typename T, T Value, typename Op, typename ...Ops>
    struct op_unpack<T, Value, Op, Ops...> {
        static constexpr T value =
            op_unpack<T,
                op_apply<T, Value, Op, typename Op::type>::value, Ops...
            >::value;
    };

    /// Operation unpack function for compiled time value
    template <typename T, typename ...Ops>
    struct op_unpack_func;

    template <typename T>
    struct op_unpack_func<T> {
        static constexpr T get_value(const T value) noexcept {
            return value;
        }
    };

    template <typename T, typename ...Ops>
    struct op_unpack_func<T, type_list<Ops...>> {
        static constexpr T get_value (const T value) noexcept {
            return op_unpack_func<T, Ops...>::get_value(value);
        }
    };

    template <typename T, typename Op, typename ...Ops>
    struct op_unpack_func<T, Op, Ops...> {
        static constexpr T get_value (const T value) noexcept {
            return op_unpack_func<T, Ops...>::get_value(
                op_apply_func<T, Op, typename Op::type>::get_value(value));
        }
    };

}

#endif // LP_CC_LIB_OPERATION_TRAITS
