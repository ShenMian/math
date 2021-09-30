// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <type_traits>

class Math
{
public:
	template <typename T>
	static T radians(T degrees)
	{
		static_assert(std::is_floating_point<T>::value);
		return degrees * pi / 180;
	}

	template <typename T>
	static T degrees(T radians)
	{
		static_assert(std::is_floating_point<T>::value);
		return radians * 180 / pi;
	}

	static const double pi = 3.14159265358979323846;
};
