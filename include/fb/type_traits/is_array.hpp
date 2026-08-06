#pragma once

#include "integral_constant.hpp"
#include "remove_cv.hpp"

#include <cstdint>

namespace fb
{
    template <typename T>
    struct is_array_helper
        : fb::false_type
    {
    };

    template <typename T>
    struct is_array_helper<T[]>
        : fb::true_type
    {
    };

    template <typename T, std::size_t N>
    struct is_array_helper<T[N]>
        : fb::true_type
    {
    };

    template <typename T>
    struct is_array
        : is_array_helper<remove_cv_t<T>>
    {
    };

    template <typename T>
    inline constexpr bool is_array_v = is_array<T>::value;
}