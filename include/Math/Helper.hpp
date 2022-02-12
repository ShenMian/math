// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>
#include <numbers>
#include <numeric>

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
inline constexpr bool equal(T lhs, T rhs, T error = std::numeric_limits<T>::epsilon())
{
	return detail::abs(lhs - rhs) <= error;
}


/**
 * @brief 角度转弧度.
 *
 * @param degress 角度.
 */
template <typename T>
	requires std::floating_point<T>
inline constexpr T radians(T degrees)
{
	return degrees * static_cast<T>(std::numbers::pi) / 180;
}

/**
 * @brief 弧度转角度.
 *
 * @param radians 弧度.
 */
template <typename T>
	requires std::floating_point<T>
inline constexpr T degrees(T radians)
{
	return radians * 180 / static_cast<T>(std::numbers::pi);
}
