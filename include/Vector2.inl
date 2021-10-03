// Copyright 2021 SMS
// License(Apache-2.0)

#include <cassert>
#include <cmath>
#include <concepts>

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::unit(1, 1);

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::unit_x(1, 0);

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::unit_y(0, 1);

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::zero(0, 0);

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::up(0, 1);

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::down(0, -1);

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::right(1, 0);

template <typename T>
inline const VectorT<T, 2> VectorT<T, 2>::left(-1, 0);

template <typename T>
inline VectorT<T, 2>::VectorT(const T& scalar)
    : x(scalar), y(scalar)
{
}

template <typename T>
VectorT<T, 2>::VectorT(const T& x, const T& y)
    : x(x), y(y)
{
}

template <typename T>
VectorT<T, 2>::VectorT(const VectorT& v)
    : x(v.x), y(v.y)
{
}

template <typename T>
inline T VectorT<T, 2>::sizeSquared() const
{
    return x * x + y * y;
}

template <typename T>
inline T VectorT<T, 2>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T>
inline VectorT<T, 2>& VectorT<T, 2>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

template <typename T>
inline VectorT<T, 2> VectorT<T, 2>::normalized() const
{
    return VectorT(*this).normalize();
}

template <typename T>
inline T VectorT<T, 2>::dot(const VectorT& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

template <typename T>
inline T VectorT<T, 2>::cross(const VectorT& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

template <typename T>
inline T VectorT<T, 2>::angle() const
{
    return std::atan2(y, x);
}

template <typename T>
inline void VectorT<T, 2>::rotate(const VectorT<T, 2>& point, float angle)
{
    const auto sin = std::sin(angle);
    const auto cos = std::cos(angle);

    if(point == VectorT::zero)
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
T VectorT<T, 2>::distance(const VectorT& point) const
{
    return std::sqrt(distanceSquared());
}

template <typename T>
T VectorT<T, 2>::distanceSquared(const VectorT& point) const
{
    const auto dx = std::abs(x - point.x);
    const auto dy = std::abs(y - point.y);
    return dx * dx + dy * dy;
}

template <typename T>
inline void* VectorT<T, 2>::data()
{
    return &x;
}

template <typename T>
inline const void* VectorT<T, 2>::data() const
{
    return &x;
}

template <typename T>
inline T& VectorT<T, 2>::operator[](size_t index)
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline const T& VectorT<T, 2>::operator[](size_t index) const
{
    assert(index < components);
    return *(&x + index);
}

// TODO
/*
template <typename T>
requires std::floating_point<T>
inline bool VectorT<T, 2>::operator==(const VectorT<T, 2>& rhs) const
{
    return (std::abs(x - rhs.x) < std::numeric_limits<T>::epsilon()) &&
           (std::abs(y - rhs.y) < std::numeric_limits<T>::epsilon());
}
*/

template <typename T>
inline bool VectorT<T, 2>::operator==(const VectorT<T, 2>& rhs) const
{
    if constexpr(std::floating_point<T>)
        return (std::abs(x - rhs.x) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(y - rhs.y) < std::numeric_limits<T>::epsilon());
    else
        return x == rhs.x && y == rhs.y;
}

template <typename T>
inline VectorT<T, 2>& VectorT<T, 2>::operator+=(const VectorT<T, 2>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template <typename T>
inline VectorT<T, 2>& VectorT<T, 2>::operator-=(const VectorT<T, 2>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template <typename T>
inline VectorT<T, 2>& VectorT<T, 2>::operator*=(const T& rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

template <typename T>
inline VectorT<T, 2>& VectorT<T, 2>::operator/=(const T& rhs)
{
    assert(rhs);
    x /= rhs;
    y /= rhs;
    return *this;
}

template <typename T>
VectorT<T, 2> VectorT<T, 2>::operator-() const
{
    return VectorT(-x, -y);
}