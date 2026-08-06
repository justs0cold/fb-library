#pragma once

#include "integral_constant.hpp"

namespace fb {
    template <typename>
    struct is_function : fb::false_type {};

    #define FB_TRAITS_FUNCTION_QUALIFIERS(...)               \
        template <typename Return, typename... Args>         \
        struct is_function<Return(Args...) __VA_ARGS__>      \
            : fb::true_type                                  \
        {                                                    \
        };                                                   \
                                                             \
        template <typename Return, typename... Args>         \
        struct is_function<Return(Args..., ...) __VA_ARGS__> \
            : fb::true_type                                  \
        {                                                    \
        };                                                   \
                                                             \
        template <typename Return>                           \
        struct is_function<Return(...) __VA_ARGS__>          \
            : fb::true_type                                  \
        {                                                    \
        };    

    FB_TRAITS_FUNCTION_QUALIFIERS()
    FB_TRAITS_FUNCTION_QUALIFIERS(const)
    FB_TRAITS_FUNCTION_QUALIFIERS(volatile)
    FB_TRAITS_FUNCTION_QUALIFIERS(const volatile)
    FB_TRAITS_FUNCTION_QUALIFIERS(&)
    FB_TRAITS_FUNCTION_QUALIFIERS(const&)
    FB_TRAITS_FUNCTION_QUALIFIERS(volatile&)
    FB_TRAITS_FUNCTION_QUALIFIERS(const volatile&)
    FB_TRAITS_FUNCTION_QUALIFIERS(&&)
    FB_TRAITS_FUNCTION_QUALIFIERS(const&&)
    FB_TRAITS_FUNCTION_QUALIFIERS(volatile&&)
    FB_TRAITS_FUNCTION_QUALIFIERS(const volatile&&)
    FB_TRAITS_FUNCTION_QUALIFIERS(noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(const noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(volatile noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(const volatile noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(& noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(const& noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(volatile& noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(const volatile& noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(&& noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(const&& noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(volatile&& noexcept)
    FB_TRAITS_FUNCTION_QUALIFIERS(const volatile&& noexcept)

    #undef FB_TRAITS_FUNCTION_QUALIFIERS

    template <typename T>
    inline constexpr bool is_function_v = is_function<T>::value;
}