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
 * Bit field reperpesentation layer
 * @file lp/bit_field.hh
 * @author Boris Vinogradov
 */

#include <lp/types.hh>

#ifndef LP_CC_LIB_LP_BIT_FIELD_HH
#define LP_CC_LIB_LP_BIT_FIELD_HH

namespace lp {

    /// Fovard declaration of bit field type
    template <word_t ...Params>
    struct bit_field;

    /// Impementation of bit field for single bits
    template <word_t Position>
    struct bit_field<Position> {
        static constexpr const word_t position = Position;
        static constexpr const word_t width = 1;

        template<typename T>
        struct mask_value {
            static_assert(Position < sizeof(T) * 8,
                "Can't create overflow bit field");

            static constexpr const T mask = 1 << position;
            static constexpr const T value = 1 << position;
        };
    };

    /// Impementation of bit field for multiple bits
    template <word_t Position, word_t Width>
    struct bit_field<Position, Width> {
        static constexpr const word_t position = Position;
        static constexpr const word_t width = Width;
        static constexpr const word_t default_value = (1 << width) - 1;

        template <typename T, T Current_value = default_value>
        struct mask_value {
            static_assert(Position + Width < sizeof(T) * 8,
                "Can't create overflow bit field");

            static constexpr T const mask =
                (default_value) << position;

            static constexpr T const value =
                (Current_value & default_value) << position;
        };

        template<word_t Current_value>
        struct with_value {
            template <typename T>
            struct mask_value : bit_field::
                template mask_value<T, static_cast<T>(Current_value)> {};
        };
    };

    /// Impementation of bit field for full field length
    template <>
    struct bit_field<0, 32> {
        static constexpr const word_t position = 0;
        static constexpr const word_t width = 32;
        static constexpr const word_t default_value = 0xffff'ffff;

        template <typename T, T Current_value = default_value>
        struct mask_value {

            static constexpr const T mask = default_value;
            static constexpr const T value = Current_value;
        };

        template<word_t Current_value>
        struct with_value {
            template <typename T>
            struct mask_value : bit_field::template
                mask_value<T, static_cast<T>(Current_value)> {};
        };
    };

} // namespace lp

#endif // LP_CC_LIB_LP_BIT_FIELD_HH