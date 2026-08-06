#pragma once

#include "fb/concepts/concepts.hpp"

namespace fb {
	[[nodiscard]] constexpr auto div(fb::arithmetic auto... nums)
		noexcept(noexcept((nums / ...)))
		requires(sizeof...(nums) > 0)
	{
		return (nums / ...);
	}
}