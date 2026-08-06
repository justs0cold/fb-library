#pragma once

#include "fb/type_traits/type_traits.hpp"

#include <cstddef>
#include <type_traits>
#include <print>
#include <type_traits>
#include <utility>

namespace fb {
    template <typename>
    struct always_false : fb::false_type {};

    template <typename... Types>
    struct Tuple {};

    template<>
    struct Tuple<>
    {
        constexpr Tuple() noexcept = default;

        constexpr Tuple(const Tuple&) noexcept = default;
        constexpr Tuple(Tuple&&) noexcept = default;
        
        constexpr Tuple& operator=(const Tuple&) noexcept = default;
        constexpr Tuple& operator=(Tuple&&) noexcept = default;
    };

    template <typename T, typename... Types>
    struct Tuple<T, Types...>
    {
        T value;
        [[no_unique_address]]
        Tuple<Types...> rest;

        template <typename U, typename... Us>
        requires (sizeof...(Types) == sizeof...(Us))
        constexpr Tuple(U&& first, Us&&... remaining)
            noexcept(
                std::is_nothrow_constructible_v<T, U&&> &&
                std::is_nothrow_constructible_v<Tuple<Types...>, Us&&...>
            )
            : value(std::forward<U>(first)),
            rest(std::forward<Us>(remaining)...)
        {}

        constexpr Tuple(const Tuple&) = default;
        constexpr Tuple(Tuple&&) = default;

        constexpr Tuple& operator=(const Tuple&) = default;
        constexpr Tuple& operator=(Tuple&&) = default;
    };

    template <std::size_t Index, typename TupleType>
    struct tuple_getter;

    template <typename T, typename... Types>
    struct tuple_getter<0, Tuple<T, Types...>>
    {
        static constexpr T& get(Tuple<T, Types...>& tuple) noexcept
        {
            return tuple.value;
        }

        static constexpr const T& get(const Tuple<T, Types...>& tuple) noexcept
        {
            return tuple.value;
        }
    };

    template <std::size_t Index, typename T, typename... Types>
    struct tuple_getter<Index, Tuple<T, Types...>>
    {
        static constexpr decltype(auto) get(Tuple<T, Types...>& tuple)
            noexcept(
                noexcept(
                    tuple_getter<Index - 1, Tuple<Types...>>::get(tuple.rest)
                )
            )
        {
            return tuple_getter<Index - 1, Tuple<Types...>>::get(tuple.rest);
        }

        static constexpr decltype(auto) get(const Tuple<T, Types...>& tuple)
            noexcept(
                noexcept(
                    tuple_getter<Index - 1, Tuple<Types...>>::get(tuple.rest)
                )
            )
        {
            return tuple_getter<Index - 1, Tuple<Types...>>::get(tuple.rest);
        }
    };

    template <std::size_t Index, typename... Types>
    constexpr decltype(auto) get(Tuple<Types...>& tuple)
        noexcept(
            noexcept(
                tuple_getter<Index, Tuple<Types...>>::get(tuple)
            )
        )
    {
        static_assert(Index < sizeof...(Types), "Tuple index out of range");

        return tuple_getter<Index, Tuple<Types...>>::get(tuple);
    }

    template <std::size_t Index, typename... Types>
    constexpr decltype(auto) get(const Tuple<Types...>& tuple)
        noexcept(
            noexcept(
                tuple_getter<Index, Tuple<Types...>>::get(tuple)
            )
        )
    {
        static_assert(Index < sizeof...(Types), "Tuple index out of range");

        return tuple_getter<Index, Tuple<Types...>>::get(tuple);
    }

    template <std::size_t Index, typename... Types>
    constexpr decltype(auto) get(Tuple<Types...>&& tuple)
        noexcept(
            noexcept(
                std::move(tuple_getter<Index, Tuple<Types...>>::get(tuple))
            )
        )
    {
        static_assert(Index < sizeof...(Types), "Tuple index out of range");

        return std::move(
            tuple_getter<Index, Tuple<Types...>>::get(tuple)
        );
    }

    template <std::size_t Index, typename... Types>
    constexpr decltype(auto) get(const Tuple<Types...>&& tuple)
        noexcept(
            noexcept(
                std::move(tuple_getter<Index, Tuple<Types...>>::get(tuple))
            )
        )
    {
        static_assert(Index < sizeof...(Types), "Tuple index out of range");

        return std::move(
            tuple_getter<Index, Tuple<Types...>>::get(tuple)
        );
    }

    template <typename T>
    struct tuple_size;

    template <typename... Types>
    struct tuple_size<Tuple<Types...>>
    {
        static constexpr std::size_t value = sizeof...(Types);
    };

    template <typename T>
    struct tuple_size<const T> :
        tuple_size<T>
    {};

    template <typename T>
    struct tuple_size<volatile T> :
        tuple_size<T>
    {};

    template <typename T>
    struct tuple_size<const volatile T> :
        tuple_size<T>
    {};

    template <std::size_t Index, typename TupleType>
    struct tuple_element;

    template <typename T, typename... Types>
    struct tuple_element<0, Tuple<T, Types...>>
    {
        using type = T;
    };

    template <std::size_t Index, typename T, typename... Types>
        requires (Index < sizeof...(Types))
    struct tuple_element<Index, Tuple<T, Types...>>
    {
        using type = typename tuple_element<
            Index - 1,
            Tuple<Types...>
        >::type;
    };

    template<std::size_t Index, typename T>
    struct tuple_element<Index, const T>
        : tuple_element<Index, T>
    {};

    template<std::size_t Index, typename T>
    struct tuple_element<Index, volatile T>
        : tuple_element<Index, T>
    {};

    template<std::size_t Index, typename T> 
    struct tuple_element<Index, const volatile T>
        : tuple_element<Index, T>
    {};

    template <typename... Types>
    constexpr auto make_tuple(Types&&... args)
        noexcept(
            std::is_nothrow_constructible_v<
                Tuple<fb::decay_t<Types>...>,
                Types&&...
            >
        )
    {
        return Tuple<fb::decay_t<Types>...>(
            std::forward<Types>(args)...
        );
    }

    template <typename Search, typename TupleType>
    struct contains : fb::false_type {};

    template <typename T, typename... Types>
    struct contains<T, Tuple<T, Types...>>
        : fb::true_type
    {};

    template <typename T, typename U, typename... Types>
    struct contains<T, Tuple<U, Types...>>
        : contains<T, Tuple<Types...>>
    {};

    template <typename T, typename TupleType>
    struct count_occurrences;

    template <typename T>
    struct count_occurrences<T, Tuple<>>
    {
        static constexpr std::size_t value = 0;
    };

    template <typename U, typename T, typename... Types>
    struct count_occurrences<U, Tuple<T, Types...>>
    {
        static constexpr std::size_t value =
            (is_same_v<U, T> ? 1 : 0) +
            count_occurrences<U, Tuple<Types...>>::value;
    };

    template <typename Search, typename TupleType>
    struct tuple_type_getter;

    template <typename T, typename... Types>
    struct tuple_type_getter<T, Tuple<T, Types...>>
    {
        static constexpr T& get(Tuple<T, Types...>& tuple)
        {
            return tuple.value;
        }

        static constexpr const T& get(const Tuple<T, Types...>& tuple)
        {
            return tuple.value;
        }
    };

    template <typename T, typename U, typename... Types>
    struct tuple_type_getter<T, Tuple<U, Types...>>
    {
        static T& get(Tuple<U, Types...>& tuple)
        {
            return tuple_type_getter<
                T,
                Tuple<Types...>
            >::get(tuple.rest);
        }

        static const T& get(const Tuple<U, Types...>& tuple)
        {
            return tuple_type_getter<
                T,
                Tuple<Types...>
            >::get(tuple.rest);
        }
    };

    template <typename T>
    struct tuple_type_getter<T, Tuple<>>
    {
        static T& get(Tuple<>&)
        {
            static_assert(
                always_false<T>::value,
                "Type not found in Tuple"
            );
        }

        static const T& get(const Tuple<>&)
        {
            static_assert(
                always_false<T>::value,
                "Type not found in Tuple"
            );
        }
    };

    template <typename T, typename... Types>
    requires contains<T, Tuple<Types...>>::value &&
        (count_occurrences<T, Tuple<Types...>>::value == 1)
    T& get(Tuple<Types...>& tuple)
    {
        return tuple_type_getter<
            T,
            Tuple<Types...>
        >::get(tuple);
    }

    template <typename T, typename... Types>
    requires contains<T, Tuple<Types...>>::value &&
        (count_occurrences<T, Tuple<Types...>>::value == 1)
    const T& get(const Tuple<Types...>& tuple)
    {
        return tuple_type_getter<
            T,
            Tuple<Types...>
        >::get(tuple);
    };

    template <typename A, typename B>
    struct tuple_concat;

    template <typename... A, typename... B>
    struct tuple_concat<Tuple<A...>, Tuple<B...>>
    {
        using type = Tuple<A..., B...>;
    };

    template <
        typename Result, 
        typename TupleType1,
        typename TupleType2, 
        std::size_t... Indexes1,
        std::size_t... Indexes2
    >
    constexpr Result expand_tuple(
        TupleType1&& tuple, 
        TupleType2&& other, 
        std::index_sequence<Indexes1...>,
        std::index_sequence<Indexes2...>
    )
        noexcept(noexcept(
            Result(
                get<Indexes1>(std::forward<TupleType1>(tuple))...,
                get<Indexes2>(std::forward<TupleType2>(other))...
            )
        ))
    {
        return Result(   
            get<Indexes1>(std::forward<TupleType1>(tuple))...,
            get<Indexes2>(std::forward<TupleType2>(other))...
        );
    }

    template <typename T>
    constexpr decltype(auto) tuple_cat(T&& tuple) {
        return std::forward<T>(tuple);
    }

    template <typename A, typename B>
    constexpr auto tuple_cat_impl(A&& a, B&& b)
        -> typename tuple_concat<fb::remove_cvref_t<A>, fb::remove_cvref_t<B>>::type
    {
        using concatenated_tuple = typename tuple_concat<
            fb::remove_cvref_t<A>, 
            fb::remove_cvref_t<B>
        >::type;

        return expand_tuple<concatenated_tuple>(
            std::forward<A>(a),
            std::forward<B>(b),
            std::make_index_sequence<tuple_size<fb::remove_cvref_t<A>>::value>{},
            std::make_index_sequence<tuple_size<fb::remove_cvref_t<B>>::value>{}
        );
    }

    template<typename A, typename B, typename... Rest>
    constexpr auto tuple_cat(A&& a, B&& b, Rest&&... rest)
    {
        if constexpr(sizeof...(Rest) == 0) 
        {
            return tuple_cat_impl(
                std::forward<A>(a),
                std::forward<B>(b)
            );
        }
        else
        {
            return tuple_cat(
                tuple_cat_impl(
                    std::forward<A>(a),
                    std::forward<B>(b)
                ),
                std::forward<Rest>(rest)...
            );
        }
    }

    template <typename T>
    struct is_tuple : fb::false_type {};

    template <typename... Types>
    struct is_tuple<Tuple<Types...>> : fb::true_type {};

    template <typename T>
    void print_value(T& value)
    {
        if constexpr (is_tuple<T>::value)
        {
            print_tuple(value);
        }
        else
        {
            std::println("{}", value);
        }
    }

    template <typename Tuple, std::size_t... Indexes>
    void print_impl(Tuple& tuple, std::index_sequence<Indexes...>)
    {
        (print_value(get<Indexes>(tuple)), ...);
    }

    template <typename... Types>
    void print_tuple(Tuple<Types...>& tuple)
    {
        print_impl(
            tuple,
            std::make_index_sequence<sizeof...(Types)>{}
        );
    } 

    template <std::size_t Index, typename TupleType>
    using tuple_element_t = typename tuple_element<Index, TupleType>::type;

    template <typename A, typename B>
    using tuple_concat_t = typename tuple_concat<A, B>::type;
}