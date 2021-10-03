// Copyright 2021 SMS
// License(Apache-2.0)

#include <cassert>
#include <cmath>
#include <concepts>

template <typename T>
inline const VectorT<T, 4> VectorT<T, 4>::unit(1, 1, 1, 1);

template <typename T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_x(1, 0, 0, 0);

template <typename T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_y(0, 1, 0, 0);

template <typename T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_z(0, 0, 1, 0);

template <typename T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_w(0, 0, 0, 1);

template <typename T>
inline const VectorT<T, 4> VectorT<T, 4>::zero(0, 0, 0, 0);

template <typename T>
inline VectorT<T, 4>::VectorT(const T& scalar)
    : x(scalar), y(scalar), z(scalar), w(scalar)
{
}

template <typename T>
VectorT<T, 4>::VectorT(const T& x, const T& y, const T& z, const T& w)
    : x(x), y(y), z(z), w(w)
{
}

template <typename T>
VectorT<T, 4>::VectorT(const Vector3T<T>& v, const T& w)
    : x(v.x), y(v.y), z(v.z), w(w)
{
}

template <typename T>
VectorT<T, 4>::VectorT(const Vector2T<T>& v, const T& z, const T& w)
    : x(v.x), y(v.y), z(z), w(w)
{
}

template <typename T>
VectorT<T, 4>::VectorT(const VectorT& v)
    : x(v.x), y(v.y), z(v.z), w(v.w)
{
}

template <typename T>
inline T VectorT<T, 4>::sizeSquared() const
{
    return x * x + y * y + z * z + w * w;
}

template <typename T>
inline T VectorT<T, 4>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T>
inline VectorT<T, 4>& VectorT<T, 4>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

template <typename T>
inline VectorT<T, 4> VectorT<T, 4>::normalized() const
{
    return VectorT(*this).normalize();
}

template <typename T>
inline T VectorT<T, 4>::dot(const VectorT& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

template <typename T>
inline T VectorT<T, 4>::cross(const VectorT& rhs) const
{
    return x * rhs.y - y * rhs.x - z * rhs.z - w * rhs.w;
}

template <typename T>
inline void* VectorT<T, 4>::data()
{
    return &x;
}

template <typename T>
inline const void* VectorT<T, 4>::data() const
{
    return &x;
}

template <typename T>
inline T& VectorT<T, 4>::operator[](size_t index)
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline const T& VectorT<T, 4>::operator[](size_t index) const
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline bool VectorT<T, 4>::operator==(const VectorT<T, 4>& rhs) const
{
    if constexpr(std::floating_point<T>)
        return (std::abs(x - rhs.x) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(y - rhs.y) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(z - rhs.z) < std::numeric_limits<T>::epsilon()) &&
               (std::abs(w - rhs.w) < std::numeric_limits<T>::epsilon());
    else
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

template <typename T>
inline VectorT<T, 4>& VectorT<T, 4>::operator+=(const VectorT<T, 4>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

template <typename T>
inline VectorT<T, 4>& VectorT<T, 4>::operator-=(const VectorT<T, 4>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

template <typename T>
inline VectorT<T, 4>& VectorT<T, 4>::operator*=(const T& rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

template <typename T>
inline VectorT<T, 4>& VectorT<T, 4>::operator/=(const T& rhs)
{
    assert(rhs);
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

template <typename T>
VectorT<T, 4> VectorT<T, 4>::operator-() const
{
    return {-x, -y, -z, -w};
}