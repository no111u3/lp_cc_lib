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
 * IO register reperpesentation layer
 * @file reg.hh
 * @author Boris Vinogradov
 */

#include <operation_traits.hh>
#include <io_register_operations.hh>
#include <types.hh>

#ifndef LP_CC_LIB_IO_REGISTER
#define LP_CC_LIB_IO_REGISTER

namespace lp {
    /// Fovard declaration of io_register type
    template <typename Type, addr_t Address>
    struct io_register;

    /// Implementation for io_register type
    template <typename Type, addr_t Address>
    struct io_register : io_register_operations<io_register<Type, Address>> {
        using register_type = io_register<Type, Address>;
        static constexpr addr_t address = Address;

        static constexpr volatile Type & get() noexcept {
            return *reinterpret_cast<volatile Type *>(Address);
        }

        template <typename ...Ops>
        static Type get_and() noexcept {
            return get() & op_unpack<Type, 0, Ops...>::value;
        }

        template <typename ...Ops>
        static constexpr void set() noexcept {
            get() = op_unpack<Type, 0, Ops...>::value;
        }

        template <word_t Shift, typename ...Ops>
        static constexpr void set() noexcept {
            get() = op_unpack<Type, 0, Ops...>::value << Shift;
        }

        template <typename ...Ops>
        static constexpr void set_or() noexcept {
            get() |= op_unpack<Type, 0, Ops...>::value;
        }

        template <typename ...Ops>
        static constexpr void set_nand() noexcept {
            get() &= ~op_unpack<Type, 0, Ops...>::value;
        }

        static constexpr void set_value(const Type value) noexcept {
            get() = value;
        }

        template <typename ...Ops>
        static constexpr void modify() noexcept {
            get() = op_unpack_func<Type, Ops...>::get_value(get());
        }
    };

}

#endif // LP_CC_LIB_IO_REGISTER
