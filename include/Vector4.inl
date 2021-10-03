// Copyright 2021 SMS
// License(Apache-2.0)

#include <cassert>
#include <cmath>
#include <concepts>

template <typename T>
inline const Vector4T<T> Vector4T<T>::unit(1, 1, 1, 1);

template <typename T>
inline const Vector4T<T> Vector4T<T>::unit_x(1, 0, 0, 0);

template <typename T>
inline const Vector4T<T> Vector4T<T>::unit_y(0, 1, 0, 0);

template <typename T>
inline const Vector4T<T> Vector4T<T>::unit_z(0, 0, 1, 0);

template <typename T>
inline const Vector4T<T> Vector4T<T>::unit_w(0, 0, 0, 1);

template <typename T>
inline const Vector4T<T> Vector4T<T>::zero(0, 0, 0, 0);

template <typename T>
inline Vector4T<T>::Vector4T(const T& scalar)
    : x(scalar), y(scalar), z(scalar), w(scalar)
{
}

template <typename T>
Vector4T<T>::Vector4T(const T& x, const T& y, const T& z, const T& w)
    : x(x), y(y), z(z), w(w)
{
}

template <typename T>
Vector4T<T>::Vector4T(const Vector3T<T>& v, const T& w)
    : x(v.x), y(v.y), z(v.z), w(w)
{
}

template <typename T>
Vector4T<T>::Vector4T(const Vector2T<T>& v, const T& z, const T& w)
    : x(v.x), y(v.y), z(z), w(w)
{
}

template <typename T>
Vector4T<T>::Vector4T(const Vector4T& v)
    : x(v.x), y(v.y), z(v.z), w(v.w)
{
}

template <typename T>
inline T Vector4T<T>::sizeSquared() const
{
    return x * x + y * y + z * z + w * w;
}

template <typename T>
inline T Vector4T<T>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T>
inline Vector4T<T>& Vector4T<T>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

template <typename T>
inline Vector4T<T> Vector4T<T>::normalized() const
{
    return Vector4T(*this).normalize();
}

template <typename T>
inline T Vector4T<T>::dot(const Vector4T& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

template <typename T>
inline T Vector4T<T>::cross(const Vector4T& rhs) const
{
    return x * rhs.y - y * rhs.x - z * rhs.z - w * rhs.w;
}

template <typename T>
inline void* Vector4T<T>::data()
{
    return &x;
}

template <typename T>
inline const void* Vector4T<T>::data() const
{
    return &x;
}

template <typename T>
inline T& Vector4T<T>::operator[](size_t index)
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline const T& Vector4T<T>::operator[](size_t index) const
{
    assert(index < components);
    return *(&x + index);
}

template <typename T>
inline bool Vector4T<T>::operator==(const Vector4T<T>& rhs) const
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
inline Vector4T<T>& Vector4T<T>::operator+=(const Vector4T<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

template <typename T>
inline Vector4T<T>& Vector4T<T>::operator-=(const Vector4T<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

template <typename T>
inline Vector4T<T>& Vector4T<T>::operator*=(const T& rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

template <typename T>
inline Vector4T<T>& Vector4T<T>::operator/=(const T& rhs)
{
    assert(rhs);
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

template <typename T>
Vector4T<T> Vector4T<T>::operator+(const Vector4T<T>& rhs) const
{
    Vector4T v;
    v += rhs;
    return v;
}

template <typename T>
Vector4T<T> Vector4T<T>::operator-(const Vector4T<T>& rhs) const
{
    Vector4T v;
    v -= rhs;
    return v;
}

template <typename T>
Vector4T<T> Vector4T<T>::operator*(const T& rhs) const
{
    Vector4T v;
    v *= rhs;
    return v;
}

template <typename T>
Vector4T<T> Vector4T<T>::operator/(const T& rhs) const
{
    assert(rhs);
    Vector4T v;
    v /= rhs;
    return v;
}

template <typename T>
Vector4T<T> Vector4T<T>::operator-() const
{
    return {-x, -y, -z, -w};
}