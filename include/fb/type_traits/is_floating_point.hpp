#pragma once

#include "remove_cv.hpp"
#include "integral_constant.hpp"

#include <stdfloat>

namespace fb
{
    template <typename T>
    struct is_floating_point_helper 
        : false_type 
    {
    };

    template <> struct is_floating_point_helper<float> : true_type {};
    template <> struct is_floating_point_helper<double> : true_type {};
    template <> struct is_floating_point_helper<long double> : true_type {};
    template <> struct is_floating_point_helper<std::float16_t> : true_type {};
    template <> struct is_floating_point_helper<std::float32_t> : true_type {};
    template <> struct is_floating_point_helper<std::float64_t> : true_type {};
    template <> struct is_floating_point_helper<std::float128_t> : true_type {};
    template <> struct is_floating_point_helper<std::bfloat16_t> : true_type {};

    template <typename T>
    struct is_floating_point : 
        is_floating_point_helper<typename fb::remove_cv<T>::type> 
    {
    };

    template <typename T>
    inline constexpr bool is_floating_point_v = is_floating_point<T>::value;
}