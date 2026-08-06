#pragma once

#include "remove_cv.hpp"
#include "integral_constant.hpp"

namespace fb
{
    template <typename T>
    struct is_integral_helper 
        : fb::false_type 
    {
    };

    template <> struct is_integral_helper<bool>               : true_type {};
    template <> struct is_integral_helper<char>               : true_type {};
    template <> struct is_integral_helper<signed char>        : true_type {};
    template <> struct is_integral_helper<unsigned char>      : true_type {};
    template <> struct is_integral_helper<short>              : true_type {};
    template <> struct is_integral_helper<unsigned short>     : true_type {};
    template <> struct is_integral_helper<int>                : true_type {};
    template <> struct is_integral_helper<unsigned int>       : true_type {};
    template <> struct is_integral_helper<long>               : true_type {};
    template <> struct is_integral_helper<unsigned long>      : true_type {};
    template <> struct is_integral_helper<long long>          : true_type {};
    template <> struct is_integral_helper<unsigned long long> : true_type {};
    template <> struct is_integral_helper<char8_t>            : true_type {};
    template <> struct is_integral_helper<char16_t>           : true_type {};
    template <> struct is_integral_helper<char32_t>           : true_type {};
    template <> struct is_integral_helper<wchar_t>            : true_type {};

    template <typename T>
    struct is_integral 
        : is_integral_helper<remove_cv_t<T>>
    {
    };

    template <typename T>
    inline constexpr bool is_integral_v = is_integral<T>::value;
}