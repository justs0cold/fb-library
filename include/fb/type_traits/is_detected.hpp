#pragma once

#include "integral_constant.hpp"
#include "void_t.hpp"

namespace fb
{
    struct nonesuch 
    {
        nonesuch() = delete;
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };

    namespace detail 
    {
        template <typename Default, typename AlwaysVoid, template <typename...> typename Op, typename... Args>
        struct detector
        {
            using value_t = fb::false_type;
            using type = Default;
        };

        template <typename Default, template<typename...> typename Op, typename... Args>
        struct detector<Default, fb::void_t<Op<Args...>>, Op, Args...> 
        {
            using value_t = fb::true_type;
            using type = Op<Args...>;
        };
    }

    template <template<typename...> typename Op, typename... Args>
    using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

    template <template<typename...> typename Op, typename... Args>
    inline constexpr bool is_detected_v = is_detected<Op, Args...>::value;
}