#pragma once

#include "declval.hpp"
#include "decay.hpp"

namespace fb
{
    template <typename...>
    struct common_type;

    template <typename T>
    struct common_type<T>
    {
        using type = decay_t<T>;
    };

    template <typename T, typename U>
    struct common_type<T, U>
    {
        using type = decay_t<decltype(
            true? fb::declval<T>() : declval<U>()
        )>;
    };

    template <typename T, typename U, typename... Rest>
    struct common_type<T, U, Rest...>
    {
        using type = typename common_type<
            typename common_type<T, U>::type,
            Rest...
        >::type;
    };

    template <typename... Types>
    using common_type_t = typename common_type<Types...>::type;
}