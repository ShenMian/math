// Copyright 2021 SMS
// License(Apache-2.0)

#include "Vector2.hpp"
#include <cassert>
#include <cmath>
#include <concepts>

template <typename T>
Vector2T<T>::Vector2T(const T& x, const T& y)
    : x(x), y(y)
{
}

template <typename T>
Vector2T<T>::Vector2T(const Vector2T& rhs)
    : x(rhs.x), y(rhs.y)
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
    Vector2T v(*this);
    return v.normalize();
}

template <typename T>
inline T& Vector2T<T>::operator[](size_t index)
{
    assert(index < components);
    return *(&x + index);
}

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
    return x == rhs.x && y == rhs.y;
}

template <typename T>
inline bool Vector2T<T>::operator!=(const Vector2T<T>& rhs) const
{
    return !(*this == rhs);
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
    return {x + rhs.x, y + rhs.y};
}

template <typename T>
Vector2T<T> Vector2T<T>::operator-(const Vector2T<T>& rhs) const
{
    return {x - rhs.x, y - rhs.y};
}

template <typename T>
Vector2T<T> Vector2T<T>::operator*(const T& rhs) const
{
    return {x * rhs, y * rhs};
}

template <typename T>
Vector2T<T> Vector2T<T>::operator/(const T& rhs) const
{
    assert(rhs);
    return {x / rhs, y / rhs};
}

template <typename T>
Vector2T<T> Vector2T<T>::operator-() const
{
    return {-x, -y};
}