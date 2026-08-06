#pragma once

#include "add_rvalue_reference.hpp"

namespace fb
{
    template <typename T>
    fb::add_rvalue_reference_t<T> declval() noexcept;
}