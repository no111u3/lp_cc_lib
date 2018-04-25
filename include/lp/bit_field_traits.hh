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
 * Bit field traits
 * @file lp/bit_field_traits.hh
 * @author Boris Vinogradov
 */

#include <lp/operations.hh>
#include <lp/type_list.hh>
#include <lp/types.hh>

#ifndef LP_CC_LIB_LP_BIT_FIELD_TRAITS_HH
#define LP_CC_LIB_LP_BIT_FIELD_TRAITS_HH

namespace lp {
    /// Const value operation apply
    template <typename T>
    struct const_apply {
        template <typename V>
        static constexpr const V value_of(const V input_value) noexcept {
            return T{}.template set(input_value);
        }
    };

    template <typename T>
    struct const_apply<set<T>> {
        template <typename V>
        static constexpr const V value_of(const V input_value) noexcept {
            return T{}.template set(input_value);
        }
    };

    template <typename T>
    struct const_apply<clear<T>> {
        template <typename V>
        static constexpr const V value_of(const V input_value) noexcept {
            return T{}.template clear(input_value);
        }
    };

    template <typename T>
    struct const_apply<toggle<T>> {
        template <typename V>
        static constexpr const V value_of(const V input_value) noexcept {
            return T{}.template toggle(input_value);
        }
    };

    /// Variable value operation apply
    template <typename T>
    struct variable_apply {
        template <typename V>
        static constexpr const V value_of(const T bit,
                                          const V input_value) noexcept {
            return bit.template set(input_value);
        }
    };

    template <typename T>
    struct variable_apply<set<T>> {
        template <typename V>
        static constexpr const V value_of(const set<T> op,
                                          const V input_value) noexcept {
            return op.value.template set(input_value);
        }
    };

    template <typename T>
    struct variable_apply<clear<T>> {
        template <typename V>
        static constexpr const V value_of(const clear<T> op,
                                          const V input_value) noexcept {
            return op.value.template clear(input_value);
        }
    };

    template <typename T>
    struct variable_apply<toggle<T>> {
        template <typename V>
        static constexpr const V value_of(const toggle<T> op,
                                          const V input_value) noexcept {
            return op.value.template toggle(input_value);
        }
    };

    /// Constant value of setted bits
    template <typename T, typename ...Bits>
    struct const_value_of;

    template <typename T>
    struct const_value_of<T> {
        static constexpr const T value = 0;

        static constexpr const T value_of(const T input_value) noexcept {
            return input_value;
        }
    };

    template <typename T, typename ...Bits>
    struct const_value_of<T, type_list<Bits...>> {
        static constexpr const T value =
            const_value_of<T, Bits...>::value;

        static constexpr const T value_of(const T input_value) noexcept {
            return
                const_value_of<T, Bits...>::
                    value_of(input_value);
        }
    };

    template <typename T, typename Bit, typename ...Bits>
    struct const_value_of<T, Bit, Bits...> {
        static constexpr const T value =
            Bit::template mask_value<T>::value
                | const_value_of<T, Bits...>::value;

        static constexpr const T value_of(const T input_value) noexcept {
            return
                const_value_of<T, Bits...>::
                    value_of(const_apply<Bit>::value_of(input_value));
        }
    };

    /// Variable value of setted bits and bit values
    template <typename T, typename ...Bits>
    struct variable_value_of;

    template <typename T>
    struct variable_value_of<T> {
        static constexpr const T value_of(const T value) noexcept {
            return value;
        }
    };

    template <typename T, typename Bit, typename ...Bits>
    struct variable_value_of<T, Bit, Bits...> {
        static constexpr const T value_of(const T value,
                                          Bit bit, Bits ...bits) noexcept {
            return
                variable_value_of<T, Bits...>::
                    value_of(
                        variable_apply<Bit>::value_of(bit, value), bits...);
        }
    };

    /// Getting values of assigned bits
    template <typename T, typename ...Bits>
    struct get_value_of;

    template <typename T>
    struct get_value_of<T> {
        static constexpr void get_value(const T value) noexcept {}
    };

    template <typename T, typename Bit, typename ...Bits>
    struct get_value_of<T, Bit, Bits...> {
        template <typename Value, typename ...Values>
        static constexpr void get_value(const T value,
                                        Value &out, Values &...outs) noexcept {
            out = Bit{}.template get<Value, T>(value);
            get_value_of<T, Bits...>:: get_value(value, outs...);
        }
    };
} // namespace lp

#endif // LP_CC_LIB_LP_BIT_FIELD_TRAITS_HH
