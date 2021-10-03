// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

class Math
{
public:
    static double radians(double degrees)
    {
        return degrees * pi / 180.0;
    }

    static double degrees(double radians)
    {
        return radians * 180.0 / pi;
    }

    static float radians(float degrees)
    {
        return degrees * (float)pi / 180.f;
    }

    static float degrees(float radians)
    {
        return radians * 180.f / (float)pi;
    }

    inline static constexpr double pi = 3.14159265358979323846;
};
