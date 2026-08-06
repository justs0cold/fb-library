#pragma once

#include "integral_constant.hpp"
#include "is_floating_point.hpp"
#include "is_integral.hpp"

namespace fb
{
    template <typename T>
    struct is_arithmetic
        : bool_constant<is_integral_v<T> || is_floating_point_v<T>>
    {
    };

    template <typename T>
    inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
}