#pragma once

namespace fb
{
    template <bool>
    struct conditional
    {
        template <typename T, typename>
        using type = T;
    };

    template <>
    struct conditional<false>
    {
        template <typename, typename U>
        using type = U;
    };

    template <bool Condition, typename T, typename U>
    using conditional_t = typename conditional<Condition>::template type<T, U>;
}