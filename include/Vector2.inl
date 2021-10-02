// Copyright 2021 SMS
// License(Apache-2.0)

#include "vector2.hpp"
#include <cassert>
#include <cmath>
#include <concepts>

template <typename T>
inline Vector2T<T>::Vector2T(const T& scalar)
    : x(scalar), y(scalar)
{
}

template <typename T>
Vector2T<T>::Vector2T(const T& x, const T& y)
    : x(x), y(y)
{
}

template <typename T>
Vector2T<T>::Vector2T(const Vector2T& v)
    : x(v.x), y(v.y)
{
}

template <typename T>
inline T Vector2T<T>::sizeSquared() const
{
    return x * x + y * y;
}

template <typename T>
inline T Vector2T<T>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T>
inline Vector2T<T>& Vector2T<T>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

template <typename T>
inline Vector2T<T> Vector2T<T>::normalized() const
{
    return Vector2T(*this).normalize();
}

template <typename T>
inline T Vector2T<T>::dot(const Vector2T& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

template <typename T>
inline T Vector2T<T>::cross(const Vector2T& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

template <typename T>
inline T Vector2T<T>::angle() const
{
    return std::atan2(y, x);
}

template <typename T>
inline void Vector2T<T>::rotate(const Vector2T<T>& point, float angle)
{
    const auto sin = std::sin(angle);
    const auto cos = std::cos(angle);

    if(point == Vector2T::zero)
    {
        const auto tmpX = x * cos - y * sin;
        y               = y * cos + x * sin;
        x               = tmpX;
    }
    else
    {
        const auto tempX = x - point.x;
        const auto tempY = y - point.y;

        x = tempX * cos - tempY * sin + point.x;
        y = tempY * cos + tempX * sin + point.y;
    }
}

template <typename T>
T Vector2T<T>::distance(const Vector2T& point) const
{
    return std::sqrt(distanceSquared());
}

template <typename T>
T Vector2T<T>::distanceSquared(const Vector2T& point) const
{
    const auto dx = std::abs(x - point.x);
    const auto dy = std::abs(y - point.y);
    return dx * dx + dy * dy;
}

template <typename T>
inline void* Vector2T<T>::data()
{
    return &x;
}

template <typename T>
inline const void* Vector2T<T>::data() const
{
    return &x;
}

template <typename T>
inline T& Vector2T<T>::operator[](size_t index)
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline const T& Vector2T<T>::operator[](size_t index) const
{
    assert(index < components);
    return *(&x + index);
}

// TODO
/*
template <typename T>
requires std::floating_point<T>
inline bool Vector2T<T>::operator==(const Vector2T<T>& rhs) const
{
    return (std::abs(x - rhs.x) < std::numeric_limits<T>::epsilon()) &&
           (std::abs(y - rhs.y) < std::numeric_limits<T>::epsilon());
}
*/

template <typename T>
inline bool Vector2T<T>::operator==(const Vector2T<T>& rhs) const
{
    if constexpr(std::floating_point<T>)
        return (std::abs(x - rhs.x) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(y - rhs.y) < std::numeric_limits<T>::epsilon());
    else
        return x == rhs.x && y == rhs.y;
}

template <typename T>
inline Vector2T<T>& Vector2T<T>::operator+=(const Vector2T<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template <typename T>
inline Vector2T<T>& Vector2T<T>::operator-=(const Vector2T<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template <typename T>
inline Vector2T<T>& Vector2T<T>::operator*=(const T& rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

template <typename T>
inline Vector2T<T>& Vector2T<T>::operator/=(const T& rhs)
{
    assert(rhs);
    x /= rhs;
    y /= rhs;
    return *this;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator+(const Vector2T<T>& rhs) const
{
    Vector2T v;
    v += rhs;
    return v;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator-(const Vector2T<T>& rhs) const
{
    Vector2T v;
    v -= rhs;
    return v;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator*(const T& rhs) const
{
    Vector2T v;
    v *= rhs;
    return v;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator/(const T& rhs) const
{
    assert(rhs);
    Vector2T v;
    v /= rhs;
    return v;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator-() const
{
    return {-x, -y};
}