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
 * Type list reperpesentation layer
 * @file lp/type_list.hh
 * @author Boris Vinogradov
 */

#include <type_traits.hh>
#include <lp/types.hh>

#ifndef LP_CC_LIB_LP_TYPE_LIST_HH
#define LP_CC_LIB_LP_TYPE_LIST_HH

namespace lp {
    /// Fovard declaration of type_list type
    template <typename ...Types>
    struct type_list;

    /// Getting head and tail from type_list
    template <typename ...Types>
    struct get_head_tail;

    template <>
    struct get_head_tail<> {
        using head_type = std::none_type;
        using tail_type = std::none_type;
    };

    template <typename Type, typename ...Types>
    struct get_head_tail<Type, Types...> {
        using head_type = Type;
        using tail_type = type_list<Types...>;
    };

    /// Getting type_list from joined two other type_list
    template <typename List1, typename List2>
    struct get_joined;

    template <typename ...Types1, typename ...Types2>
    struct get_joined<type_list<Types1...>, type_list<Types2...>> {
        using type = type_list<Types1..., Types2...>;
    };

    /// Join operator
    template <typename List1, typename List2>
    using join = typename get_joined<List1, List2>::type;

    /// Getting item from index
    template <word_t N, typename List>
    struct get_item {
        static_assert(N < List::size,
            "Can't get item with index higher than size");
        using type = typename get_item<N - 1, typename List::tail>::type;
    };

    template <typename List>
    struct get_item<0, List> {
        using type = typename List::head;
    };

    /// Assign type_list to type with multiply type specializatoin
    template <template <typename ...> class Assign,
        typename ...Types>
    struct get_assign {
        using type = Assign<Types...>;
    };

    /// Find item selected by predicate
    template <template <typename> class Predicate, typename List>
    struct find {
        using type = std::conditional_t<
            Predicate<typename List::head>::value,
            typename List::head,
            typename find<Predicate, typename List::tail>::type
        >;
    };

    template <template <typename> class Predicate>
    struct find<Predicate, std::none_type> {
        using type = std::none_type;
    };

    /// Conditional adding to type_list
    template <template <typename> class Predicate,
        typename List, typename ...Types>
    struct conditional_append;

    template <template <typename> class Predicate, typename List>
    struct conditional_append<Predicate, List> {
        using type = List;
    };

    template <template <typename> class Predicate, typename List,
        typename Type, typename ...Types>
    struct conditional_append<Predicate, List, Type, Types...> {
        using type = std::conditional_t<
            Predicate<Type>::value,
            typename conditional_append<
                Predicate,
                typename List::template append<Type>, Types...>::type,
            typename conditional_append<Predicate, List, Types...>::type
        >;
    };

    /// Remove matched from types and pack to type_list
    template <template <typename> class Predicate, typename ...Types>
    struct remove {
        template <typename T>
        struct negate_predicate : public std::conditional_t<
            Predicate<T>::value, std::false_type, std::true_type> {
        };

        using type = typename conditional_append<
            negate_predicate, type_list<>, Types...>::type;
    };

    /// Reverse insert to begin
    template <typename List, typename ...Types>
    struct reverse_insert;

    template <typename List>
    struct reverse_insert<List> {
        using type = List;
    };

    template <typename List, typename Type, typename ...Types>
    struct reverse_insert<List, Type, Types...> {
        using type = typename reverse_insert<
            typename List::template insert<Type>,
            Types...>::type;
    };

    /// Impementation of type_list
    template <typename ...Types>
    struct type_list {
        using head_tail = get_head_tail<Types...>;

        using head = typename head_tail::head_type;

        using tail = typename head_tail::tail_type;

        template <typename ...Appends>
        using append = type_list<Types..., Appends...>;

        template <typename ...Inserts>
        using insert = type_list<Inserts..., Types...>;

        template <typename List>
        using extend = typename get_joined<type_list<Types...>, List>::type;

        template <word_t N>
        using get = typename get_item<N, type_list<Types...>>::type;

        template <template <typename ...> class Assign>
        using assign = typename get_assign<Assign, Types...>::type;

        template <template <typename> class Predicate>
        using find = typename find<Predicate, type_list<Types...>>::type;

        template <template <typename> class Predicate>
        using filter =
            typename conditional_append<
                Predicate, type_list<>, Types...>::type;

        template <template <typename> class Predicate>
        using remove = typename remove<Predicate, Types...>::type;

        using reverse = typename reverse_insert<type_list<>, Types...>::type;

        static constexpr const word_t size = sizeof...(Types);
    };
} // namespace lp

#endif // LP_CC_LIB_LP_TYPE_LIST_HH
