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
 * IO register operaton traits
 * @file io_register_operation_traits.hh
 * @author Boris Vinogradov
 */

#include <io_register_operations.hh>
#include <type_list.hh>

#ifndef LP_CC_LIB_IO_REGISTER_OPERATION_TRAITS
#define LP_CC_LIB_IO_REGISTER_OPERATION_TRAITS

namespace lp {
    /// Io register operation apply for compiled time value
    template <typename Register, typename Op_list, typename Op_type>
    struct register_op_apply;

    template <typename Register, typename Op_list>
    struct register_op_apply<Register, Op_list, set_type> {
        static void apply() noexcept {
            Register::template set<Op_list>();
        }
    };

    template <typename Register, typename Op_list>
    struct register_op_apply<Register, Op_list, set_or_type> {
        static void apply() noexcept {
            Register::template set_or<Op_list>();
        }
    };

    template <typename Register, typename Op_list>
    struct register_op_apply<Register, Op_list, set_nand_type> {
        static void apply() noexcept {
            Register::template set_nand<Op_list>();
        }
    };

    template <typename Register, typename Op_list>
    struct register_op_apply<Register, Op_list, modify_type> {
        static void apply() noexcept {
            Register::template modify<Op_list>();
        }
    };

    /// Io register operation unpack for compiled time value
    template <typename Register_list, typename Op_list>
    struct register_op_unpack;

    template <typename Register>
    struct register_op_unpack<Register, type_list<>> {
        static void apply() noexcept {
        }
    };

    template <typename ...Ops>
    struct register_op_unpack<type_list<>, type_list<Ops...>> {
        static void apply() noexcept {
        }
    };

    template <typename ...Regs>
    struct register_op_unpack<type_list<Regs...>, type_list<>> {
        static void apply() noexcept {
        }
    };

    template <>
    struct register_op_unpack<type_list<>, type_list<>> {
        static void apply() noexcept {
        }
    };

    template <typename Register, typename ...Ops>
    struct register_op_unpack<Register, type_list<Ops...>> {
        static void apply() noexcept {
            register_op_apply<Register, type_list<Ops...>, typename Register::type>::apply();
        }
    };

    template <typename ...Regs, typename ...Ops>
    struct register_op_unpack<type_list<Regs...>, type_list<Ops...>> {
        using register_list = type_list<Regs...>;
        using op_list = type_list<Ops...>;
        using current_register = typename register_list::head;
        using tail = typename register_list::tail;
        template <typename T>
        using is_same_type =
            std::is_same<typename current_register::register_type, typename T::register_type>;

        static void apply() noexcept {
            register_op_unpack<current_register, typename op_list::template filter<is_same_type>>::apply();
            register_op_unpack<tail, typename op_list::template remove<is_same_type>>::apply();
        }
    };
}

#endif // LP_CC_LIB_IO_REGISTER_OPERATION_TRAITS
