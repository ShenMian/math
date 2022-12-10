// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>
#include <concepts>
#include <numbers>
#include <numeric>

namespace detail
{

// C++ 23 后 std::abs 支持 constexpr
template <typename T>
    requires std::is_arithmetic_v<T>
constexpr T abs(T x) noexcept
{
	return (x >= T(0)) ? x : -x;
}

} // namespace detail

template <typename T>
constexpr bool equal(const T& lhs, const T& rhs) noexcept
{
	return lhs == rhs;
}

#if __GNUC__

constexpr bool equal(float lhs, float rhs, float error = std::numeric_limits<float>::epsilon()) noexcept
{
	return detail::abs(lhs - rhs) <= error;
}

constexpr bool equal(double lhs, double rhs, double error = std::numeric_limits<double>::epsilon()) noexcept
{
	return detail::abs(lhs - rhs) <= error;
}

#else

template <std::floating_point T>
constexpr bool equal(T lhs, T rhs, T error = std::numeric_limits<T>::epsilon())
{
	return detail::abs(lhs - rhs) <= error;
}

#endif

/**
 * @brief 角度转弧度.
 *
 * @param degress 角度.
 */
template <std::floating_point T>
constexpr T radians(T degrees) noexcept
{
	return degrees * std::numbers::pi_v<T> / 180;
}

/**
 * @brief 弧度转角度.
 *
 * @param radians 弧度.
 */
template <std::floating_point T>
constexpr T degrees(T radians) noexcept
{
	return radians * 180 / std::numbers::pi_v<T>;
}
