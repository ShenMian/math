// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <type_traits>

class Math
{
public:
    static double radians(double degrees)
	{
		return degrees * pi / 180;
	}

	static double degrees(double radians)
	{
		return radians * 180 / pi;
	}

    static double radians(float degrees)
    {
        return degrees * pi / 180;
    }

    static double degrees(float radians)
    {
        return radians * 180 / pi;
    }

	inline static constexpr double pi = 3.14159265358979323846;
};
