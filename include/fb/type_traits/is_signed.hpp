#pragma once
#include "integral_constant.hpp"
#include "is_arithmetic.hpp"
#include "remove_cv.hpp"

namespace fb {
    template <typename T, bool = fb::is_arithmetic<T>::value>
    struct is_signed_helper 
        : fb::false_type 
    {
    };

    template <typename T>
    struct is_signed_helper<T, true> 
        : fb::integral_constant<bool, (T(-1) < T(0))> 
    {
    };

    template <typename T>
    inline constexpr bool is_signed_helper_v = is_signed_helper<T>::value;

    template <typename T>
    struct is_signed 
        : fb::is_signed_helper<fb::remove_cv_t<T>, fb::is_arithmetic_v<fb::remove_cv_t<T>>> 
    {
    };

    template <typename T>
    inline constexpr bool is_signed_v = fb::is_signed_helper_v<fb::remove_cv_t<T>>;
}
