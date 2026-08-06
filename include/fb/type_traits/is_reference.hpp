#pragma once

#include "integral_constant.hpp"
#include "is_lvalue_reference.hpp"
#include "is_rvalue_reference.hpp"

namespace fb
{
    template <typename T>
    struct is_reference 
        : fb::bool_constant<fb::is_lvalue_reference_v<T> || fb::is_rvalue_reference_v<T>> 
    {
    };

    template <typename T>
    inline constexpr bool is_reference_v = is_reference<T>::value;
}