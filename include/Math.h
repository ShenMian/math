// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <type_traits>

class Math
{
public:
	template <typename T>
	concept floating_point = std::is_floating_point_v<T>;

	template <typename T>
	requires floating_point<T>
	static T radians(T degrees)
	{
		return degrees * pi / 180;
	}

	template <typename T>
	requires floating_point<T>
	static T degrees(T radians)
	{
		return radians * 180 / pi;
	}

	static const double pi = 3.14159265358979323846;
};
