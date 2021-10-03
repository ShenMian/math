// Copyright 2021 SMS
// License(Apache-2.0)

#include <cassert>
#include <cmath>
#include <concepts>

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::unit(1, 1, 1);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::unit_x(1, 0, 0);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::unit_y(0, 1, 0);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::unit_z(0, 0, 1);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::zero(0, 0, 0);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::up(0, 1, 0);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::down(0, -1, 0);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::right(1, 0, 0);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::left(-1, 0, 0);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::front(0, 0, -1);

template <typename T>
inline const VectorT<T, 3> VectorT<T, 3>::back(0, 0, 1);

template <typename T>
inline VectorT<T, 3>::VectorT(const T& scalar)
    : x(scalar), y(scalar), z(scalar)
{
}

template <typename T>
VectorT<T, 3>::VectorT(const T& x, const T& y, const T& z)
    : x(x), y(y), z(z)
{
}

template <typename T>
VectorT<T, 3>::VectorT(const Vector2T<T>& v, const T& z)
    : x(v.x), y(v.y), z(z)
{
}

template <typename T>
VectorT<T, 3>::VectorT(const VectorT& v)
    : x(v.x), y(v.y), z(v.z)
{
}

template <typename T>
inline T VectorT<T, 3>::sizeSquared() const
{
    return x * x + y * y + z * z;
}

template <typename T>
inline T VectorT<T, 3>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T>
inline VectorT<T, 3>& VectorT<T, 3>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

template <typename T>
inline VectorT<T, 3> VectorT<T, 3>::normalized() const
{
    return VectorT(*this).normalize();
}

template <typename T>
inline T VectorT<T, 3>::dot(const VectorT& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <typename T>
inline T VectorT<T, 3>::cross(const VectorT& rhs) const
{
    return x * rhs.y - y * rhs.x - z * rhs.z;
}

template <typename T>
T VectorT<T, 3>::distance(const VectorT& point) const
{
    return std::sqrt(distanceSquared());
}

template <typename T>
T VectorT<T, 3>::distanceSquared(const VectorT& point) const
{
    const auto dx = std::abs(x - point.x);
    const auto dy = std::abs(y - point.y);
    const auto dz = std::abs(z - point.z);
    return dx * dx + dy * dy + dz * dz;
}

template <typename T>
inline void* VectorT<T, 3>::data()
{
    return &x;
}

template <typename T>
inline const void* VectorT<T, 3>::data() const
{
    return &x;
}

template <typename T>
inline T& VectorT<T, 3>::operator[](size_t index)
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline const T& VectorT<T, 3>::operator[](size_t index) const
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline bool VectorT<T, 3>::operator==(const VectorT<T, 3>& rhs) const
{
    if constexpr(std::floating_point<T>)
        return (std::abs(x - rhs.x) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(y - rhs.y) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(z - rhs.z) < std::numeric_limits<T>::epsilon());
    else
        return x == rhs.x && y == rhs.y && z == rhs.z;
}

template <typename T>
inline VectorT<T, 3>& VectorT<T, 3>::operator+=(const VectorT<T, 3>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

template <typename T>
inline VectorT<T, 3>& VectorT<T, 3>::operator-=(const VectorT<T, 3>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template <typename T>
inline VectorT<T, 3>& VectorT<T, 3>::operator*=(const T& rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

template <typename T>
inline VectorT<T, 3>& VectorT<T, 3>::operator/=(const T& rhs)
{
    assert(rhs);
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

template <typename T>
VectorT<T, 3> VectorT<T, 3>::operator+(const VectorT<T, 3>& rhs) const
{
    return VectorT(*this) += rhs;
}

template <typename T>
VectorT<T, 3> VectorT<T, 3>::operator-(const VectorT<T, 3>& rhs) const
{
    return VectorT(*this) -= rhs;
}

template <typename T>
VectorT<T, 3> VectorT<T, 3>::operator*(const T& rhs) const
{
    return VectorT(*this) *= rhs;
}

template <typename T>
VectorT<T, 3> VectorT<T, 3>::operator/(const T& rhs) const
{
    assert(rhs);
    return VectorT(*this) /= rhs;
}

template <typename T>
VectorT<T, 3> VectorT<T, 3>::operator-() const
{
    return {-x, -y, -z};
}