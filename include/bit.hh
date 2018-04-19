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
 * Bit reperpesentation layer
 * @file bit.hh
 * @author Boris Vinogradov
 */

#include <operations.hh>
#include <types.hh>

#ifndef LP_CC_LIB_BIT
#define LP_CC_LIB_BIT

namespace lp {

    /// Fovard declaration of bit type
    template <word_t ...Params>
    struct bit;

    /// Impementation of bit for single bits
    template <word_t Position>
    struct bit<Position> : operations<bit<Position>> {
        static constexpr const word_t position = Position;

        template<typename T>
        struct mask {
            static_assert(Position < sizeof(T) * 8, "Can't create overflow bit");

            static constexpr const T value = 1 << position;
        };
    };

    /// Impementation of bit for multiple bits
    template <word_t Position, word_t Width>
    struct bit<Position, Width> : operations<bit<Position, Width>> {
        static constexpr const word_t position = Position;
        static constexpr const word_t width = Width;
        static constexpr const word_t default_value = (1 << width) - 1;

        template <typename T, T Current_value = default_value>
        struct mask {
            static_assert(Position + Width < sizeof(T) * 8, "Can't create overflow bit");

            static constexpr T const value =
                (Current_value & default_value) << position;
        };

        template<word_t Current_value>
        struct with_value : operations<with_value<Current_value>> {
            template <typename T>
            struct mask : bit::template mask<T, static_cast<T>(Current_value)> {};
        };
    };

    /// Impementation of bit for full field length
    template <>
    struct bit<0, 32> : operations<bit<0, 32>> {
        static constexpr const word_t position = 0;
        static constexpr const word_t width = 32;
        static constexpr const word_t default_value = 0xffff'ffff;

        template <typename T, T Current_value = default_value>
        struct mask {
            static constexpr const T value = Current_value;
        };

        template<word_t Current_value>
        struct with_value : operations<with_value<Current_value>> {
            template <typename T>
            struct mask : bit::template mask<T, static_cast<T>(Current_value)> {};
        };
    };

} // namespace lp

#endif // LP_CC_LIB_BIT
