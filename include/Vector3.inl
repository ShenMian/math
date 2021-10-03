// Copyright 2021 SMS
// License(Apache-2.0)

#include "vector3.hpp"
#include <cassert>
#include <cmath>
#include <concepts>

template <typename T>
inline const Vector3T<T> Vector3T<T>::unit(1, 1, 1);

template <typename T>
inline const Vector3T<T> Vector3T<T>::unit_x(1, 0, 0);

template <typename T>
inline const Vector3T<T> Vector3T<T>::unit_y(0, 1, 0);

template <typename T>
inline const Vector3T<T> Vector3T<T>::unit_z(0, 0, 1);

template <typename T>
inline const Vector3T<T> Vector3T<T>::zero(0, 0, 0);

template <typename T>
inline const Vector3T<T> Vector3T<T>::up(0, 1, 0);

template <typename T>
inline const Vector3T<T> Vector3T<T>::down(0, -1, 0);

template <typename T>
inline const Vector3T<T> Vector3T<T>::right(1, 0, 0);

template <typename T>
inline const Vector3T<T> Vector3T<T>::left(-1, 0, 0);

template <typename T>
inline const Vector3T<T> Vector3T<T>::front(0, 0, -1);

template <typename T>
inline const Vector3T<T> Vector3T<T>::back(0, 0, 1);

template <typename T>
inline Vector3T<T>::Vector3T(const T& scalar)
    : x(scalar), y(scalar), z(scalar)
{
}

template <typename T>
Vector3T<T>::Vector3T(const T& x, const T& y, const T& z)
    : x(x), y(y), z(z)
{
}

template <typename T>
Vector3T<T>::Vector3T(const Vector2T<T>& v, const T& z)
    : x(v.x), y(v.y), z(z)
{
}

template <typename T>
Vector3T<T>::Vector3T(const Vector3T& v)
    : x(v.x), y(v.y), z(v.z)
{
}

template <typename T>
inline T Vector3T<T>::sizeSquared() const
{
    return x * x + y * y + z * z;
}

template <typename T>
inline T Vector3T<T>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T>
inline Vector3T<T>& Vector3T<T>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

template <typename T>
inline Vector3T<T> Vector3T<T>::normalized() const
{
    return Vector3T(*this).normalize();
}

template <typename T>
inline T Vector3T<T>::dot(const Vector3T& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <typename T>
inline T Vector3T<T>::cross(const Vector3T& rhs) const
{
    return x * rhs.y - y * rhs.x - z * rhs.z;
}

template <typename T>
T Vector3T<T>::distance(const Vector3T& point) const
{
    return std::sqrt(distanceSquared());
}

template <typename T>
T Vector3T<T>::distanceSquared(const Vector3T& point) const
{
    const auto dx = std::abs(x - point.x);
    const auto dy = std::abs(y - point.y);
    const auto dz = std::abs(z - point.z);
    return dx * dx + dy * dy + dz * dz;
}

template <typename T>
inline void* Vector3T<T>::data()
{
    return &x;
}

template <typename T>
inline const void* Vector3T<T>::data() const
{
    return &x;
}

template <typename T>
inline T& Vector3T<T>::operator[](size_t index)
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline const T& Vector3T<T>::operator[](size_t index) const
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline bool Vector3T<T>::operator==(const Vector3T<T>& rhs) const
{
    if constexpr(std::floating_point<T>)
        return (std::abs(x - rhs.x) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(y - rhs.y) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(z - rhs.z) < std::numeric_limits<T>::epsilon());
    else
        return x == rhs.x && y == rhs.y && z == rhs.z;
}

template <typename T>
inline Vector3T<T>& Vector3T<T>::operator+=(const Vector3T<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

template <typename T>
inline Vector3T<T>& Vector3T<T>::operator-=(const Vector3T<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template <typename T>
inline Vector3T<T>& Vector3T<T>::operator*=(const T& rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

template <typename T>
inline Vector3T<T>& Vector3T<T>::operator/=(const T& rhs)
{
    assert(rhs);
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

template <typename T>
Vector3T<T> Vector3T<T>::operator+(const Vector3T<T>& rhs) const
{
    Vector3T v;
    v += rhs;
    return v;
}

template <typename T>
Vector3T<T> Vector3T<T>::operator-(const Vector3T<T>& rhs) const
{
    Vector3T v;
    v -= rhs;
    return v;
}

template <typename T>
Vector3T<T> Vector3T<T>::operator*(const T& rhs) const
{
    Vector3T v;
    v *= rhs;
    return v;
}

template <typename T>
Vector3T<T> Vector3T<T>::operator/(const T& rhs) const
{
    assert(rhs);
    Vector3T v;
    v /= rhs;
    return v;
}

template <typename T>
Vector3T<T> Vector3T<T>::operator-() const
{
    return {-x, -y, -z};
}