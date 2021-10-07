// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cmath>

class Math
{
public:
    /*
    template <typename T>
    static Matrix4T<T> transform()
    {
        return Matrix4();
    }

    template <typename T>
    static Matrix4T<T> rotate()
    {
        return Matrix4();
    }

    template <typename T>
    static Matrix4T<T> scale()
    {
        return Matrix4();
    }

    
    template <typename T>
    static Matrix4T<T> ortho()
    {
        return Matrix4T();
    }

    template <typename T>
    static Matrix4T<T> perspective()
    {
        return Matrix4T();
    }
    */


    template <typename T>
    static bool equal(const T& lhs, const T& rhs)
    {
        return lhs == rhs;
    }

    template <typename T>
    requires std::floating_point<T>
    static bool equal(const T& lhs, const T& rhs)
    {
        return (std::abs(lhs - rhs) <= std::numeric_limits<T>::epsilon());
    }


    template <typename T>
    requires std::floating_point<T>
    static T radians(T degrees)
    {
        return degrees * static_cast<T>(pi) / 180;
    }

    template <typename T>
    requires std::floating_point<T>
    static T degrees(T radians)
    {
        return radians * 180 / static_cast<T>(pi);
    }

    inline static constexpr double pi = 3.14159265358979323846;
};
