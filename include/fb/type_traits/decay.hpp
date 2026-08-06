#pragma once

#include "add_pointer.hpp"
#include "is_function.hpp"
#include "remove_cv.hpp"
#include "remove_reference.hpp"

#include <cstdint>

namespace fb
{
    template <typename T, bool IsFunction = fb::is_function_v<T>>
    struct decay_helper
    {
        using type = fb::remove_cv_t<T>;
    };

    template <typename T>
    struct decay_helper<T, true>
    {
        using type = fb::add_pointer_t<T>;
    };

    template <typename T, std::size_t N>
    struct decay_helper<T[N], false>
    {
        using type = T*;
    };

    template <typename T>
    struct decay_helper<T[], false>
    {
        using type = T*;
    };

    template <typename T>
    using decay_helper_t = typename decay_helper<T>::type;

    template <typename T>
    struct decay
    {
        using type = decay_helper_t<remove_reference_t<T>>;
    };

    template <typename T>
    using decay_t = typename decay<T>::type;
}