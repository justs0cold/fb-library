#pragma once

#include "is_same.hpp"
#include "remove_cv.hpp"

namespace fb
{
    template <typename T>
    struct is_void 
        : fb::is_same<fb::remove_cv_t<T>, void> 
    {
    };

    template <typename T>
    inline constexpr bool is_void_v = is_void<T>::value;
}