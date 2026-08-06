#pragma once

#include "remove_reference.hpp"

namespace fb
{
    template <typename T>
    struct add_pointer
    {
        using type = fb::remove_reference_t<T>*;
    };

    template <typename T>
    using add_pointer_t = typename add_pointer<T>::type;
}