#pragma once

namespace fb
{
    template<typename T, T v>
    struct integral_constant
    {
        static constexpr T value = v;

        using value_type = T;
        using type       = integral_constant<T, v>;

        constexpr operator value_type() const noexcept 
        { 
            return value; 
        }

        constexpr value_type operator()() const noexcept 
        { 
            return value;
        }
    };

    template <bool v>
    using bool_constant = integral_constant<bool, v>;

    using true_type  = bool_constant<true>;
    using false_type = bool_constant<false>;
}