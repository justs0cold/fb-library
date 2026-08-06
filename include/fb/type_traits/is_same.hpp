#pragma once

#include "integral_constant.hpp"

namespace fb
{
    template <typename, typename>
    struct is_same 
        : fb::false_type 
    {
    };

    template <typename T>
    struct is_same<T, T> 
        : fb::true_type 
    {
    };

    template <typename T, typename U>
    inline constexpr bool is_same_v = is_same<T, U>::value;
}