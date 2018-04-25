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
 * Associate type wrapper
 * @file associate_type.hh
 * @author Boris Vinogradov
 */

#include <lp/types.hh>

#ifndef LP_CC_LIB_ASSOCIATE_TYPE_HH
#define LP_CC_LIB_ASSOCIATE_TYPE_HH

namespace lp {
    /// With value wrapper
    template <typename T, word_t Current_value, word_t length = T::width>
    struct with_value {
        using type = typename T::template with_value<Current_value>;
    };

    template <typename T, word_t Current_value>
    struct with_value<T, Current_value, 1> {
        using type = T;
    };

    /// Associate wrapper
    template <typename T, typename A_type>
    struct associate_type {
        using type = T;
        using assoc_type = A_type;

        template <word_t Current_value>
        using with_value =
            associate_type<
                typename with_value<T, Current_value>::type, A_type>;
    };

    /// Alias
    template <typename T, typename A_type>
    using assoc_type = associate_type<T, A_type>;

    /// Extract type
    template <typename T>
    struct extract_type {
        using type = T;
    };

    template <typename T, typename A_type>
    struct extract_type<associate_type<T, A_type>> {
        using type = T;
    };

    /// Extract associate type
    template <typename T>
    struct extract_assoc_type {
        using type = T;
    };

    template <typename T, typename A_type>
    struct extract_assoc_type<associate_type<T, A_type>> {
        using type = A_type; 
    };
} // namespace lp

#endif // LP_CC_LIB_ASSOCIATE_TYPE_HH
