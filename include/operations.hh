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
 * Operations meta
 * @file operations.hh
 * @author Boris Vinogradov
 */

#ifndef LP_CC_LIB_OPERATIONS
#define LP_CC_LIB_OPERATIONS

namespace lp {

    /// The type used as compiled-time and type
    struct and_type {};

    /// The type used as compiled-time or type
    struct or_type {};

    /// The type used as compiled-time nand type
    struct nand_type {};

    /// The type used as compiled-time nor type
    struct nor_type {};

    /// The type used as compiled-time xor type
    struct xor_type {};

    /// The type used as compiled-time nxor type
    struct nxor_type {};

    /// Operation marker type
    template <typename T>
    struct operations {
        /// Default marker for operation
        using type = or_type;

        /// Marker for and operation
        struct op_and : T {
            using type = and_type;
        };

        /// Marker for or operation
        struct op_or : T {
            using type = or_type;
        };

        /// Marker for nand operation
        struct op_nand : T {
            using type = nand_type;
        };

        /// Marker for nor operation
        struct op_nor : T {
            using type = nor_type;
        };

        /// Marker for xor operation
        struct op_xor : T {
            using type = xor_type;
        };

        /// Marker for nxor operation
        struct op_nxor : T {
            using type = nxor_type;
        };
    };

} // namespace lp

#endif // LP_CC_LIB_OPERATIONS
