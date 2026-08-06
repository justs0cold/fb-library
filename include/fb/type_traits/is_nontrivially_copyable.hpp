#pragma once

#include "declval.hpp"
#include "integral_constant.hpp"
#include "void_t.hpp"

namespace fb {
    template <typename T, typename = void>
    struct is_copy_constructible_helper 
        : fb::false_type
    {
    };
    
    template <typename T>
    struct is_copy_constructible_helper<T, fb::void_t<decltype(T(fb::declval<const T&>()))>>
        : fb::true_type 
    {
    };

    template <typename T>
    struct is_nontrivially_copyable 
        : fb::integral_constant<bool, is_copy_constructible_helper<T>::value && !__is_trivially_copyable(T)> 
    {
    };

    template <typename T>
    inline constexpr bool is_nontrivially_copyable_v = is_copy_constructible_helper<T>::value && !__is_trivially_copyable(T); 
}