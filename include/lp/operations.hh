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
 * Low level operation wrappers
 * @file lp/operations.hh
 * @author Boris Vinogradov
 */

#include <lp/types.hh>

#ifndef LP_CC_LIB_LP_OPERATIONS_HH
#define LP_CC_LIB_LP_OPERATIONS_HH

namespace lp {
    enum struct operation_type {
        set = 0,
        clear,
        toggle
    };

    template <typename T, operation_type Op>
    struct operation {
        using type = T;
        static constexpr const operation_type op_code = Op;

        constexpr operation() noexcept = default;
        template <typename ...Types>
        constexpr operation(Types ...types) noexcept
            : value(types...) {}

        const type value;
    };

    template <typename T>
    using set = operation<T, operation_type::set>;

    template <typename T>
    using clear = operation<T, operation_type::clear>;

    template <typename T>
    using toggle = operation<T, operation_type::toggle>;
} // namespace lp

#endif // LP_CC_LIB_LP_OPERATIONS_HH
