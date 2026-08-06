#pragma once

namespace fb
{
    template <typename T>
    struct add_volatile
    {
        using type = volatile T;
    };

    template <typename T>
    using add_volatile_t = typename add_volatile<T>::type;
}