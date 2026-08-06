#pragma once

namespace fb
{
    template <typename T>
    struct add_rvalue_reference
    {
        using type = T&&;
    };

    template <>
    struct add_rvalue_reference<void>
    {
        using type = void;
    };

    template <>
    struct add_rvalue_reference<const void>
    {
        using type = const void;
    };

    template <>
    struct add_rvalue_reference<volatile void>
    {
        using type = volatile void;
    };

    template <>
    struct add_rvalue_reference<const volatile void>
    {
        using type = const volatile void;
    };

    template <typename T>
    using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
}