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
 * IO register operations meta
 * @file io_register_operations.hh
 * @author Boris Vinogradov
 */

#ifndef LP_CC_LIB_IO_REGISTER_OPERATIONS
#define LP_CC_LIB_IO_REGISTER_OPERATIONS

namespace lp {
    /// The type used as compiled-time set type
    struct set_type {};

    /// The type used as compiled-time set or type
    struct set_or_type {};

    /// The type used as compiled-time set nand type
    struct set_nand_type {};

    /// The type used as compiled-time modify type
    struct modify_type {};

    /// Operation marker type
    template <typename T>
    struct io_register_operations {
        /// Default marker for operation
        using type = set_type;

        /// Marker for set operation
        struct op_set : T {
            using type = set_type;
        };

        /// Marker for set or operation
        struct op_set_or : T {
            using type = set_or_type;
        };

        /// Marker for set nand operation
        struct op_set_nand : T {
            using type = set_nand_type;
        };

        /// Marker for modify operation
        struct op_modify : T {
            using type = modify_type;
        };
    };
}

#endif // LP_CC_LIB_IO_REGISTER_OPERATIONS
