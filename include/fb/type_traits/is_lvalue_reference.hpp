#pragma once

#include "integral_constant.hpp"

namespace fb
{
    template <typename T>
    struct is_lvalue_reference
        : fb::false_type
    { 
    };

    template <typename T>
    struct is_lvalue_reference<T&>
        : fb::true_type
    { 
    };

    template <typename T>
    inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
}