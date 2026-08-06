#pragma once

#include "declval.hpp"
#include "integral_constant.hpp"
#include "void_t.hpp"

namespace fb
{
    template <typename To>
    void test_convert(To);

    template <typename, typename, typename = void>
    struct is_convertible : fb::false_type
    {
    };

    template <typename From, typename To>
    struct is_convertible<
        From,
        To,
        fb::void_t<decltype(test_convert<To>(fb::declval<From>()))>
    > : fb::true_type
    {
    };
}