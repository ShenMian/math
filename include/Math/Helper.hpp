// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>
#include <numbers>

// TODO: 用命名空间后, 移除该命名空间
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

inline constexpr bool equal(float lhs, float rhs, float error = std::numeric_limits<float>::epsilon())
{
	return detail::abs(lhs - rhs) <= error;
}

inline constexpr bool equal(double lhs, double rhs, double error = std::numeric_limits<double>::epsilon())
{
	return detail::abs(lhs - rhs) <= error;
}

/*
// Will cause error on gcc
template <typename T>
	requires std::floating_point<T>
inline constexpr bool equal(T lhs, T rhs, T error = std::numeric_limits<T>::epsilon())
{
	return detail::abs(lhs - rhs) <= error;
}
*/


template <typename T>
	requires std::floating_point<T>
inline constexpr T radians(T degrees)
{
	return degrees * static_cast<T>(std::numbers::pi) / 180;
}

template <typename T>
	requires std::floating_point<T>
inline constexpr T degrees(T radians)
{
	return radians * 180 / static_cast<T>(std::numbers::pi);
}
