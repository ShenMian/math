// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>
#include <numbers>

namespace detail
{

template <typename T>
	requires std::is_arithmetic_v<T>
constexpr T abs(T x)
{
	return x >= 0 ? x : -x;
}

}

template <typename T>
inline constexpr bool equal(const T& lhs, const T& rhs)
{
	return lhs == rhs;
}

template <typename T>
	requires std::floating_point<T>
inline constexpr bool equal(const T& lhs, const T& rhs)
{
	return detail::abs(lhs - rhs) <= std::numeric_limits<T>::epsilon();
}


template <typename T>
	requires std::floating_point<T>
inline T radians(T degrees)
{
	return degrees * static_cast<T>(std::numbers::pi) / 180;
}

template <typename T>
	requires std::floating_point<T>
inline T degrees(T radians)
{
	return radians * 180 / static_cast<T>(std::numbers::pi);
}
