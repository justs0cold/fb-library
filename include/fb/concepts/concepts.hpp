#pragma once

#include "fb/type_traits/is_floating_point.hpp"
#include "fb/type_traits/is_integral.hpp"
#include "fb/type_traits/is_same.hpp"
#include "fb/type_traits/is_signed.hpp"
#include "fb/type_traits/is_unsigned.hpp"
#include "fb/type_traits/remove_cvref.hpp"

#include <concepts>
#include <ranges>
#include <utility>

namespace fb
{
	template <typename T>
	concept integral = fb::is_integral_v<fb::remove_cvref_t<T>>;

	template <typename T>
	concept signed_integral = integral<T> && fb::is_signed_v<fb::remove_cvref_t<T>>;
	
	template <typename T>
	concept unsigned_integral = integral<T> && fb::is_unsigned_v<fb::remove_cvref_t<T>>;

	template <typename T>
	concept floating_point = fb::is_floating_point_v<fb::remove_cvref_t<T>>;

	template <typename T>
	concept numeric = integral<T> || floating_point<T>;

	template <typename T>
	concept character = fb::is_same_v<fb::remove_cvref_t<T>, char> ||
                   		fb::is_same_v<fb::remove_cvref_t<T>, signed char> ||
                    	fb::is_same_v<fb::remove_cvref_t<T>, unsigned char> ||
                    	fb::is_same_v<fb::remove_cvref_t<T>, wchar_t> ||
                    	fb::is_same_v<fb::remove_cvref_t<T>, char8_t> ||
                    	fb::is_same_v<fb::remove_cvref_t<T>, char16_t> ||
                    	fb::is_same_v<fb::remove_cvref_t<T>, char32_t>;

	template <typename T>
	concept arithmetic = numeric<T> && !character<T> && !fb::is_same_v<fb::remove_cvref_t<T>, bool>;

	template <typename T>
	concept contiguous_range = std::ranges::contiguous_range<T>;

	template <typename F, typename... Args>
	concept callable = requires {
		std::declval<F>()(std::declval<Args>()...);
	};
}