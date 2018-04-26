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
 * C++ tuple
 * @file tuple.hh
 * @author Boris Vinogradov
 */

#include <internal/std_types.hh>
#include <type_traits.hh>
#include <utility.hh>

#ifndef LP_CC_LIB_TUPLE_HH
#define LP_CC_LIB_TUPLE_HH

namespace std {
    /// Tuple forward declaration
    template <typename ...Types>
    class tuple;

    namespace internal {
        /// Head base implementation
        template <size_t Index, typename Head, bool Is_empty_not_final>
        struct head_base;

        template <size_t Index, typename Head>
        struct head_base<Index, Head, true>
            : Head {
            constexpr head_base() noexcept
                : Head{} {}

            constexpr head_base(const Head &head) noexcept
                : Head{head} {}

            constexpr head_base(const head_base &) noexcept = default;

            constexpr head_base(head_base &&) noexcept = default;

            template <typename T_head>
            constexpr head_base(T_head &&head) noexcept
                : Head{forward<T_head>(head)} {}

            static constexpr Head & get_head(head_base &base) noexcept {
                return base;
            }

            static constexpr const Head &
            get_head(const head_base &base) noexcept {
                return base;
            }
        };

        template <size_t Index, typename Head>
        struct head_base<Index, Head, false> {
            constexpr head_base() noexcept
                : head_{} {}

            constexpr head_base(const Head &head) noexcept
                : head_{head} {}

            constexpr head_base(const head_base &) noexcept = default;

            constexpr head_base(head_base &&) noexcept = default;

            template <typename T_head>
            constexpr head_base(T_head &&head) noexcept
                : head_{forward<T_head>(head)} {}

            static constexpr Head & get_head(head_base &base) noexcept {
                return base.head_;
            }

            static constexpr const Head &
            get_head(const head_base &base) noexcept {
                return base.head_;
            }

            Head head_;
        };

        /// Is empty but not tuple
        template <typename T>
        struct is_empty_non_tuple
            : is_empty<T> {};

        template <typename El0, typename ...Els>
        struct is_empty_non_tuple<tuple<El0, Els...>>
            : false_type {};

        /// Is empty but not final
        template <typename T>
        using is_empty_not_final =
            conditional_t<
                is_final<T>::value,
                false_type,
                is_empty_non_tuple<T>
            >;

        /// Tuple implementation
        template <size_t Index, typename ...Types>
        struct tuple_impl;

        template <size_t Index, typename Head, typename ...Tail>
        struct tuple_impl<Index, Head, Tail...>
            : tuple_impl<Index + 1, Tail...>,
            head_base<Index, Head, is_empty_not_final<Head>::value> {

            using inherit = tuple_impl<Index + 1, Tail...>;
            using base =
                head_base<Index, Head, is_empty_not_final<Head>::value>;

            static constexpr Head & get_head(tuple_impl & tuple) noexcept {
                return base::get_head(tuple); }

            static constexpr const Head &
            get_head(const tuple_impl &tuple) noexcept {
                return base::get_head(tuple);
            }

            static constexpr inherit & get_tail(tuple_impl &tuple) noexcept {
                return tuple;
            }

            static constexpr const inherit &
            get_tail(const tuple_impl &tuple) noexcept {
                return tuple;
            }

            constexpr tuple_impl() noexcept
                : inherit{}, base{} {}

            explicit constexpr
            tuple_impl(const Head head, const Tail ...tail) noexcept
                : inherit{tail...}, base{head} {}

            constexpr tuple_impl(const tuple_impl &) noexcept = default;

            constexpr tuple_impl(tuple_impl && tuple)
                noexcept(and_pred<is_nothrow_move_constructible<Head>,
                    is_nothrow_move_constructible<inherit>>::value)
                : inherit(move(get_tail(tuple))), 
                base(forward<Head>(get_head(tuple))) {}

            template <typename ...U_elements>
            constexpr
            tuple_impl(const tuple_impl<Index, U_elements...> &tuple) noexcept
                : inherit(tuple_impl<Index, U_elements...>::get_tail(tuple)),
                base(tuple_impl<Index, U_elements...>::get_head(tuple)) {}

            template <typename U_head, typename ...U_tail>
            constexpr
            tuple_impl(tuple_impl<Index, U_head, U_tail...> &&tuple) noexcept
                : inherit(move(tuple_impl<Index, U_head, U_tail...>::
                    get_tail(tuple))),
                base(forward<U_head>(tuple_impl<Index, U_head, U_tail...>::
                    get_head(tuple))) {}

            constexpr tuple_impl & operator =
            (const tuple_impl & tuple) noexcept {
                get_head(*this) = get_head(tuple);
                get_tail(*this) = get_tail(tuple);

                return *this;
            }

            template <typename ...U_elements>
            constexpr tuple_impl & operator =
            (const tuple_impl<Index, U_elements...> &tuple) noexcept {
                get_head(*this) =
                    tuple_impl<Index, U_elements...>::get_head(tuple);
                get_tail(*this) =
                    tuple_impl<Index, U_elements...>::get_tail(tuple);

                return *this;
            }

            template <typename U_head, typename ...U_tail>
            constexpr tuple_impl & operator =
            (tuple_impl<Index, U_head, U_tail...> && tuple) noexcept {
                get_head(*this) =
                    forward<U_head>(
                        tuple_impl<Index, U_head, U_tail...>::get_head(tuple));
                get_tail(*this) =
                    move
                        (tuple_impl<Index, U_head, U_tail...>::get_tail(tuple));

                return *this;
            }

            constexpr void apply_swap(tuple_impl &tuple)
                noexcept(
                    noexcept(swap(declval<Head &>(), declval<Head &>()))
                    && noexcept(get_tail(tuple).apply_swap(get_tail(tuple)))) {
                swap(get_head(*this), get_head(tuple));
                inherit::apply_swap(get_tail(tuple));
            }
        };

        template <size_t Index, typename Head>
        struct tuple_impl<Index, Head>
            : head_base<Index, Head, is_empty_not_final<Head>::value> {
            using base =
                head_base<Index, Head, is_empty_not_final<Head>::value>;

            static constexpr Head & get_head(tuple_impl &tuple) noexcept {
                return base::get_head(tuple);
            }

            static constexpr const Head &
            get_head(const tuple_impl &tuple) noexcept {
                return base::get_head(tuple);
            }

            constexpr tuple_impl() noexcept
                : base{} {}

            explicit constexpr tuple_impl(const Head &head) noexcept
                : base{head} {}

            template <typename U_head>
            explicit constexpr tuple_impl(U_head &&head)
                : base(forward<U_head>(head)) {}

            constexpr tuple_impl(const tuple_impl &) noexcept = default;

            constexpr tuple_impl(tuple_impl &&tuple)
                noexcept(is_nothrow_move_constructible<Head>::value)
                : base(forward<Head>(get_head(tuple))) {}

            template <typename U_head>
            constexpr
            tuple_impl(const tuple_impl<Index, U_head> &tuple) noexcept
                : base(tuple_impl<Index, U_head>::get_head(tuple)) {}

            template <typename U_head>
            constexpr tuple_impl(tuple_impl<Index, U_head> &&tuple) noexcept
                : base(forward<U_head>(tuple_impl<Index, U_head>::
                    get_head(tuple))) {}
	
            constexpr tuple_impl & operator = (const tuple_impl &tuple) noexcept {
                get_head(*this) = get_head(tuple);

                return *this;
            }

            constexpr tuple_impl & operator = (tuple_impl &&tuple)
                noexcept(is_nothrow_move_assignable<Head>::value) {
                get_head(*this) = forward<Head>(get_head(tuple));

                return *this;
            }

            template <typename U_head>
            constexpr tuple_impl & operator =
            (const tuple_impl<Index, U_head> &tuple) noexcept {
                get_head(*this) = tuple_impl<Index, U_head>::get_head(tuple);

                return *this;
            }

            template <typename U_head>
            constexpr tuple_impl & operator =
            (tuple_impl<Index, U_head> &&tuple) noexcept {
                get_head(*this) =
                    forward<U_head>(tuple_impl<Index, U_head>::get_head(tuple));

                return *this;
            }

            constexpr void apply_swap(tuple_impl& tuple)
                noexcept(
                    noexcept(
                        swap(std::declval<Head&>(), std::declval<Head&>()))) {
                swap(get_head(*this), get_head(tuple));
            }
        };
    } // namespace internal

    /// Tuple
    template <typename ...Types>
    class tuple : public internal::tuple_impl<0, Types...> {
        using inherit = internal::tuple_impl<0, Types...>;
    public:
        constexpr tuple() noexcept
            : inherit{} {}

        explicit constexpr tuple(const Types &...elements) noexcept
            : inherit{elements...} {}

        template <typename ...UTypes, typename =
            typename enable_if<
                and_pred<is_convertible<UTypes, Types>...>::value>::type>
        explicit constexpr tuple(UTypes &&...elements) noexcept
            : inherit{forward<UTypes>(elements)...} {}

        constexpr tuple(const tuple &) noexcept = default;

        constexpr tuple(tuple &&) noexcept = default; 

        template <typename ...UTypes, typename =
            typename enable_if<
                and_pred<is_convertible<const UTypes &, Types>...>::value
                    >::type>
        constexpr tuple(const tuple<UTypes...>& tuple) noexcept
            : inherit
                {static_cast<
                    const internal::tuple_impl<0, UTypes ...> &>(tuple)} {}

        template <typename ...UTypes, typename =
            typename enable_if<
                and_pred<is_convertible<UTypes,
                    Types>...>::value>::type>
        constexpr tuple(tuple<UTypes...> &&tuple) noexcept
            : inherit
                {static_cast<internal::tuple_impl<0, UTypes ...>&&>(tuple)} {}

        constexpr tuple & operator = (const tuple &tuple) noexcept {
            static_cast<inherit &>(*this) = tuple;

            return *this;
        }

        constexpr tuple & operator = (tuple &&tuple)
            noexcept(is_nothrow_move_assignable<inherit>::value) {
            static_cast<inherit &>(*this) = move(tuple);

            return *this;
        }

        template <typename ...UTypes, typename =
            typename enable_if<sizeof...(UTypes) == sizeof...(Types)>::type>
        constexpr tuple & operator = (const tuple<UTypes ...> &tuple) noexcept {
            static_cast<inherit &>(*this) = tuple;

            return *this;
        }

        template <typename ...UTypes, typename = typename
            enable_if<sizeof...(UTypes) == sizeof...(Types)>::type>
        constexpr tuple & operator = (tuple<UTypes ...> &&tuple) {
            static_cast<inherit &>(*this) = move(tuple);

            return *this;
        }

        constexpr void swap(tuple &tuple)
            noexcept(noexcept(tuple.apply_swap(tuple))) {
            inherit::apply_swap(tuple);
        }
    };

    /// Zero elements tuple
    template <>
    class tuple<> {
    public:
        void swap(tuple &tuple) noexcept {}
    };

    /// Getting type of tuple element
    template <size_t Index, typename T>
    struct tuple_element;

    template <size_t Index, typename Head, typename ...Tail>
    struct tuple_element<Index, tuple<Head, Tail...>>
        : tuple_element<Index - 1, tuple<Tail ...>> {};

    template <typename Head, typename ...Tail>
    struct tuple_element<0, tuple<Head, Tail ...>> {
        using type = Head;
    };

    template <size_t Index, typename T>
    using tuple_element_t = typename tuple_element<Index, T>::type;

    template <size_t Index, typename T>
    struct tuple_element<Index, const T> {
        using type = add_const_t<tuple_element_t<Index, T>>;
    };

    template <size_t Index, typename T>
    struct tuple_element<Index, volatile T> {
        using type = add_volatile_t<tuple_element_t<Index, T>>;
    };

    template <size_t Index, typename T>
    struct tuple_element<Index, const volatile T> {
        using type = add_cv_t<tuple_element_t<Index, T>>;
    };

    /// Tuple size
    template <typename T>
    struct tuple_size;

    template <typename T>
    struct tuple_size<const T>
        : integral_constant<size_t, tuple_size<T>::value> {};

    template <typename T>
    struct tuple_size<volatile T>
        : integral_constant<size_t, tuple_size<T>::value> {};

    template <typename T>
    struct tuple_size<const volatile T>
        : integral_constant<size_t, tuple_size<T>::value> {};

    template <typename ...Types>
    struct tuple_size<tuple<Types...>>
        : integral_constant<size_t, sizeof...(Types)> {};

    namespace internal {
        template <size_t i, typename Head, typename ...Tail>
        constexpr Head &
        get_h(tuple_impl<i, Head, Tail ...>& tuple) noexcept {
            return tuple_impl<i, Head, Tail ...>::get_head(tuple);
        }

        template <size_t i, typename Head, typename ...Tail>
        constexpr const Head &
        get_h(const tuple_impl<i, Head, Tail ...> &tuple) noexcept {
            return tuple_impl<i, Head, Tail ...>::get_head(tuple);
        }
    } // namespace internal

    /// Getting a tuple element by index
    template <size_t i, typename ...Types>
    constexpr tuple_element_t<i, tuple<Types...>> &
    get(tuple<Types...> &tuple) noexcept {
        return internal::get_h<i>(tuple);
    }

    template <size_t i, typename ...Types>
    constexpr const tuple_element_t<i, tuple<Types...>> &
    get(const tuple<Types...> &tuple) noexcept {
        return internal::get_h<i>(tuple);
    }

    template <size_t i, typename ...Types>
    constexpr tuple_element_t<i, tuple<Types ...>> &&
    get(tuple<Types...>&& tuple_) noexcept {
        using element_type = tuple_element_t<i, tuple<Types ...>>;
        return forward<element_type&&>(get<i>(tuple_));
    }

    namespace internal {
        template <typename Head, size_t i, typename... Tail>
        constexpr Head &
        get_h_2(tuple_impl<i, Head, Tail ...>& tuple_) noexcept {
            return tuple_impl<i, Head, Tail ...>::get_head(tuple_);
        }

        template <typename Head, size_t i, typename... Tail>
        constexpr const Head &
        get_h_2(const tuple_impl<i, Head, Tail ...>& tuple_) noexcept {
            return tuple_impl<i, Head, Tail ...>::get_head(tuple_);
        }
    } // namespace internal

    template <typename T, typename ...Types>
    constexpr T & get(tuple<Types ...> & tuple_) noexcept {
        return internal::get_h_2<T>(tuple_);
    }

    template <typename T, typename ...Types>
    constexpr T && get(tuple<Types ...>&& tuple_) noexcept {
        return forward<T&&>(internal::get_h_2<T>(tuple_));
    }

    template <typename T, typename ...Types>
    constexpr const T & get(const tuple<Types ...>& tuple_) noexcept {
        return internal::get_h_2<T>(tuple_);
    }

    namespace internal {
        template<typename T, typename U, size_t i, size_t size>
        struct tuple_compare {
            static constexpr bool eq(const T &t, const U &u) noexcept {
                return bool(get<i>(t) == get<i>(u))
                    && tuple_compare<T, U, i + 1, size>::eq(t, u);
            }

            static constexpr bool less(const T &t, const U &u) noexcept {
                return bool(get<i>(t) < get<i>(u))
                    || (!bool(get<i>(u) < get<i>(t))
                    && tuple_compare<T, U, i + 1, size>::less(t, u));
            }
        };

        template<typename T, typename U, size_t size>
        struct tuple_compare<T, U, size, size> {
            static constexpr bool eq(const T &, const U &) noexcept {
                return true;
            }

            static constexpr bool less(const T &, const U&) noexcept {
                return false;
            }
        };
    } // namespace internal

    template<typename ...T_types, typename ...U_types>
    constexpr bool operator ==
    (const tuple<T_types ...>& t, const tuple<U_types ...>& u) noexcept {
        static_assert(sizeof...(T_types) == sizeof...(U_types),
            "tuple objects can only be compared if they have equal sizes.");
        using compare = internal::tuple_compare<
            tuple<T_types ...>, tuple<U_types ...>, 0, sizeof...(T_types)>;
        return compare::eq(t, u);
    }

    template<typename ...T_types, typename ...U_types>
    constexpr bool operator <
    (const tuple<T_types ...> &t, const tuple<U_types ...> &u) noexcept {
        static_assert(sizeof...(T_types) == sizeof...(U_types),
        "tuple objects can only be compared if they have equal sizes.");
        using compare = internal::tuple_compare<
            tuple<T_types ...>, tuple<U_types ...>, 0, sizeof...(T_types)>;
        return compare::less(t, u);
    }

    template<typename ...T_types, typename ...U_types>
    constexpr bool operator !=
    (const tuple<T_types ...> &t, const tuple<U_types ...> &u) noexcept {
        return !(t == u);
    }

    template<typename ...T_types, typename ...U_types>
    constexpr bool operator >
    (const tuple<T_types ...> &t, const tuple<U_types ...> &u) noexcept {
        return u < t;
    }

    template<typename ...T_types, typename ...U_types>
    constexpr bool operator <=
    (const tuple<T_types ...> &t, const tuple<U_types ...> &u) noexcept {
        return !(u < t);
    }

    template<typename ...T_types, typename ...U_types>
    constexpr bool operator >=
    (const tuple<T_types ...> &t, const tuple<U_types ...> &u) noexcept {
        return !(t < u);
    }

    template<typename ...Types>
    constexpr tuple<typename decay_and_strip<Types>::type...>
    make_tuple(Types &&...args) noexcept {
        using result_type = tuple<typename decay_and_strip<Types>::type ...>;
        return result_type(forward<Types>(args)...);
    }
} // namespace std

#endif // LP_CC_LIB_TUPLE_HH
