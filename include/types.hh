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
 * Platform system types
 * @file types.hh
 * @author Boris Vinogradov
 */

#ifndef LP_CC_LIB_TYPES_HH
#define LP_CC_LIB_TYPES_HH

namespace lp {
    // system types
    using u8_t = unsigned char;
    using i8_t = char;
    using s8_t = signed char;
    using u16_t = unsigned short;
    using i16_t = short;
    using u32_t = unsigned int;
    using i32_t = int;
    using u64_t = unsigned long long;
    using i64_t = long long;

    // unsigned and signed machine word
    using word_t = unsigned long;
    using iword_t = long;

    // address types and constants
    enum struct arch_defines {
        word_bits = 32,
        address_shift = 12
    };

    using addr_t = word_t;

    const addr_t invalid_addr = ~0UL;

    // atomics
    using small_atomic_t = signed char;

    // time
    using cpu_time_t = u64_t;
}

#endif // LP_CC_LIB_TYPES_HH
