// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>
#include <numbers>

class Math
{
public:
	template <typename T>
	static bool equal(const T& lhs, const T& rhs)
	{
		return lhs == rhs;
	}

	template <typename T>
		requires std::floating_point<T>
	static bool equal(const T& lhs, const T& rhs)
	{
		return std::abs(lhs - rhs) <= std::numeric_limits<T>::epsilon();
	}


	template <typename T>
		requires std::floating_point<T>
	static T radians(T degrees)
	{
		return degrees * static_cast<T>(std::numbers::pi) / 180;
	}

	template <typename T>
		requires std::floating_point<T>
	static T degrees(T radians)
	{
		return radians * 180 / static_cast<T>(std::numbers::pi);
	}
};
