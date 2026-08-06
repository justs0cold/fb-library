#pragma once
#include "integral_constant.hpp"

namespace fb {
    template <typename T>
    struct is_trivially_copyable 
        : fb::integral_constant<bool, __is_trivially_copyable(T)> 
    {
    };

    template <typename T>
    inline constexpr bool is_trivially_copyable_v = __is_trivially_copyable(T);
}
