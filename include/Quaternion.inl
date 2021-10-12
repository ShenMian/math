// Copyright 2021 SMS
// License(Apache-2.0)

#include <cmath>

template <typename T>
requires std::floating_point<T>
QuaternionT<T>::QuaternionT(const T& x, const T& y, const T& z, const T& w)
    : x(x), y(y), z(z), w(w)
{
}

template <typename T>
requires std::floating_point<T>
inline void QuaternionT<T>::eular(const Vector3T<T>& angles)
{
    const auto cr = std::cos(angles.x / T(2));
    const auto cp = std::cos(angles.y / T(2));
    const auto cy = std::cos(angles.z / T(2));

    const auto sr = std::sin(angles.x / T(2));
    const auto sp = std::sin(angles.y / T(2));
    const auto sy = std::sin(angles.z / T(2));

    const auto cpcy = cp * cy;
    const auto spsy = sp * sy;
    const auto cpsy = cp * sy;
    const auto spcy = sp * cy;

    x = sr * cpcy - cr * spsy;
    y = cr * spcy + sr * cpsy;
    z = cr * cpsy - sr * spcy;
    w = cr * cpcy + sr * spsy;

    normalize();
}

template <typename T>
requires std::floating_point<T>
inline Vector3T<T> QuaternionT<T>::eular() const
{
    Vector3T angles;

    const auto xx = x * x;
    const auto yy = y * y;
    const auto zz = z * z;
    const auto ww = w * w;

    angles.x = std::atan2(T(2) * (y * z + x * w), -xx - yy + zz + ww);
    angles.y = std::asin(Clamp(T(2) * (y * w - x * z), T(-1), T(1)));
    angles.z = std::atan2(T(2) * (x * y + z * w), xx - yy - zz + ww);

    return angles;
}

template <typename T>
requires std::floating_point<T>
inline T QuaternionT<T>::sizeSquared() const
{
    return x * x + y * y + z * z + w * w;
}

template <typename T>
requires std::floating_point<T>
inline T QuaternionT<T>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T>
requires std::floating_point<T>
inline QuaternionT<T>& QuaternionT<T>::inverse()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

template <typename T>
requires std::floating_point<T>
inline QuaternionT<T> QuaternionT<T>::inversed() const
{
    return {-x, -y, -z, w};
}

template <typename T>
requires std::floating_point<T>
inline QuaternionT<T>& QuaternionT<T>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}