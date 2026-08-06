#pragma once

namespace fb
{
    template <bool, typename = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> 
    { 
        using type = T; 
    };

    template <bool Condition, typename T = void>
    using enable_if_t = typename enable_if<Condition, T>::type;
}