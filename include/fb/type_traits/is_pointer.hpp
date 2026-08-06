#pragma once

#include "integral_constant.hpp"
#include "remove_cv.hpp"

namespace fb {
    template <typename T>
    struct is_pointer_helper
        : false_type
    {
    };

    template <typename T>
    struct is_pointer_helper<T*> 
        : true_type
    {
    };

    template <typename T>
    struct is_pointer
        : is_pointer_helper<fb::remove_cv_t<T>>
    {
    };

    template <typename T>
    inline constexpr bool is_pointer_v = is_pointer<T>::value;
}