#pragma once
#include "integral_constant.hpp"
#include "is_arithmetic.hpp"
#include "is_signed.hpp"
#include "remove_cv.hpp"

namespace fb {
    template <typename T, bool = fb::is_arithmetic_v<T>>
    struct is_unsigned_helper 
        : fb::false_type 
    {
    };

    template <typename T>
    struct is_unsigned_helper<T, true> 
        : fb::integral_constant<bool, !fb::is_signed_v<T>> 
    {
    };

    template <typename T>
    inline constexpr bool is_unsigned_helper_v = is_unsigned_helper<T>::value;

    template <typename T>
    struct is_unsigned 
        : fb::is_unsigned_helper<fb::remove_cv_t<T>, fb::is_arithmetic_v<fb::remove_cv_t<T>>> 
    {
    };

    template <typename T>
    inline constexpr bool is_unsigned_v = fb::is_unsigned_helper_v<fb::remove_cv_t<T>>;
}
