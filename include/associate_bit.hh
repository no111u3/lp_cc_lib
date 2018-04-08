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
 * Associate bit representation layer
 * @file associate_bit.hh
 * @author Boris Vinogradov
 */

#include <bit.hh>
#include <operations.hh>
#include <types.hh>

#ifndef LP_CC_LIB_ASSOCIATE_BIT
#define LP_CC_LIB_ASSOCIATE_BIT

namespace lp {

    template <typename Register, word_t ...BitOpts>
    struct associate_bit;

    template <typename Register, word_t BitOpt>
    struct associate_bit<Register, BitOpt> : bit<BitOpt> {
        using register_type = Register;
    };

    template <typename Register, word_t ...BitOpts>
    struct associate_bit : operations<associate_bit<Register, BitOpts...>> {
        using register_type = Register;

        using bit_type = bit<BitOpts...>;

        template <typename T>
        using mask = typename bit_type::template mask<T>;

        template<word_t Current_value>
        struct with_value : operations<with_value<Current_value>> {
            using register_type = associate_bit::register_type;

            template <typename T>
            using mask = typename bit_type::template with_value<Current_value>::template mask<T>;
        };
    };

    template <typename Register, word_t ...BitOpts>
    using assoc_bit = associate_bit<Register, BitOpts...>;

} // namespace lp

#endif // LP_CC_LIB_ASSOCIATE_BIT
