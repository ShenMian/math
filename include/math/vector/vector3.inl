// Copyright 2021 SMS
// License(Apache-2.0)

#include "../assert.hpp"
#include <cmath>
#include <concepts>

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::unit(1, 1, 1);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::unit_x(1, 0, 0);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::unit_y(0, 1, 0);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::unit_z(0, 0, 1);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::zero(0, 0, 0);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::up(0, 1, 0);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::down(0, -1, 0);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::right(1, 0, 0);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::left(-1, 0, 0);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::front(0, 0, 1);

template <arithmetic T>
inline const VectorT<T, 3> VectorT<T, 3>::back(0, 0, -1);

template <arithmetic T>
inline VectorT<T, 3>::VectorT() : x(0), y(0), z(0)
{
}

template <arithmetic T>
inline constexpr VectorT<T, 3>::VectorT(const T& scalar) : x(scalar), y(scalar), z(scalar)
{
}

template <arithmetic T>
inline constexpr VectorT<T, 3>::VectorT(const T& x, const T& y, const T& z) : x(x), y(y), z(z)
{
}

template <arithmetic T>
inline constexpr VectorT<T, 3>::VectorT(const Vector2T<T>& v, const T& z) : x(v.x), y(v.y), z(z)
{
}

template <arithmetic T>
inline constexpr VectorT<T, 3>::VectorT(const std::initializer_list<T>& list)
{
	assert(list.size() <= 3, "Too many initializers");
	auto it = list.begin();
	x       = *it;
	y       = *(++it);
	z       = *(++it);
}

template <arithmetic T>
inline T VectorT<T, 3>::norm() const
{
	return static_cast<T>(std::hypot(x, y, z));
}

template <arithmetic T>
inline constexpr T VectorT<T, 3>::normSq() const
{
	return x * x + y * y + z * z;
}

template <arithmetic T>
inline VectorT<T, 3>& VectorT<T, 3>::normalize()
{
	const auto len = norm();
	if(len < std::numeric_limits<T>::epsilon())
		return *this;
	return *this *= 1.f / len;
}

template <arithmetic T>
inline VectorT<T, 3> VectorT<T, 3>::normalized() const
{
	return VectorT(*this).normalize();
}

template <arithmetic T>
inline T VectorT<T, 3>::dot(const VectorT& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <arithmetic T>
inline VectorT<T, 3> VectorT<T, 3>::cross(const VectorT& rhs) const
{
	VectorT result;
	result.x = y * rhs.z - z * rhs.y;
	result.y = z * rhs.x - x * rhs.z;
	result.z = x * rhs.y - y * rhs.x;
	return result;
}

template <arithmetic T>
inline constexpr T VectorT<T, 3>::sum() const
{
	T sum = T(0);
	sum += x;
	sum += y;
	sum += z;
	return sum;
}

template <arithmetic T>
inline T VectorT<T, 3>::distance(const VectorT& point) const
{
	return std::sqrt(distanceSquared());
}

template <arithmetic T>
inline T VectorT<T, 3>::distanceSquared(const VectorT& point) const
{
	const auto dx = std::abs(x - point.x);
	const auto dy = std::abs(y - point.y);
	const auto dz = std::abs(z - point.z);
	return dx * dx + dy * dy + dz * dz;
}

template <arithmetic T>
constexpr size_t VectorT<T, 3>::components() const
{
	return 3;
}

template <arithmetic T>
inline T* VectorT<T, 3>::data()
{
	return &x;
}

template <arithmetic T>
inline const T* VectorT<T, 3>::data() const
{
	return &x;
}

template <arithmetic T>
inline T& VectorT<T, 3>::operator[](size_t index)
{
	assert(index < components());
	return *(&x + index);
}

template <arithmetic T>
inline const T& VectorT<T, 3>::operator[](size_t index) const
{
	assert(index < components());
	return *(&x + index);
}

template <arithmetic T>
inline constexpr bool VectorT<T, 3>::operator==(const VectorT<T, 3>& rhs) const
{
	return equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z);
}

template <arithmetic T>
inline constexpr VectorT<T, 3>& VectorT<T, 3>::operator+=(const VectorT<T, 3>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template <arithmetic T>
inline constexpr VectorT<T, 3>& VectorT<T, 3>::operator-=(const VectorT<T, 3>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template <arithmetic T>
inline constexpr VectorT<T, 3>& VectorT<T, 3>::operator*=(const T& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

template <arithmetic T>
inline constexpr VectorT<T, 3>& VectorT<T, 3>::operator/=(const T& rhs)
{
	assert(rhs, "divisor cannot be zero");
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

template <arithmetic T>
inline constexpr VectorT<T, 3> VectorT<T, 3>::operator-() const
{
	return {-x, -y, -z};
}

template <arithmetic T>
inline VectorT<T, 3> VectorT<T, 3>::lerp(const VectorT<T, 3>& from, const VectorT<T, 3>& to, T t)
{
	VectorT result;
	result.x = std::lerp(from.x, to.x, t);
	result.y = std::lerp(from.y, to.y, t);
	result.z = std::lerp(from.z, to.z, t);
	return result;
}
