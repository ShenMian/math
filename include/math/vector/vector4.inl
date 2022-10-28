// Copyright 2021 SMS
// License(Apache-2.0)

#include "../check.hpp"
#include <cmath>

template <arithmetic T>
inline const VectorT<T, 4> VectorT<T, 4>::unit(1, 1, 1, 1);

template <arithmetic T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_x(1, 0, 0, 0);

template <arithmetic T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_y(0, 1, 0, 0);

template <arithmetic T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_z(0, 0, 1, 0);

template <arithmetic T>
inline const VectorT<T, 4> VectorT<T, 4>::unit_w(0, 0, 0, 1);

template <arithmetic T>
inline const VectorT<T, 4> VectorT<T, 4>::zero(0, 0, 0, 0);

template <arithmetic T>
inline VectorT<T, 4>::VectorT() : x(0), y(0), z(0), w(0)
{
}

template <arithmetic T>
inline VectorT<T, 4>::VectorT(const T& scalar) : x(scalar), y(scalar), z(scalar), w(scalar)
{
}

template <arithmetic T>
constexpr VectorT<T, 4>::VectorT(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w)
{
}

template <arithmetic T>
constexpr VectorT<T, 4>::VectorT(const Vector3T<T>& v, const T& w) : x(v.x), y(v.y), z(v.z), w(w)
{
}

template <arithmetic T>
constexpr VectorT<T, 4>::VectorT(const Vector2T<T>& v, const T& z, const T& w) : x(v.x), y(v.y), z(z), w(w)
{
}

template <arithmetic T>
constexpr VectorT<T, 4>::VectorT(const std::initializer_list<T>& list)
{
	check(list.size() <= 4, "Too many initializers");
	auto it = list.begin();
	x       = *it;
	y       = *(++it);
	z       = *(++it);
	w       = *(++it);
}

template <arithmetic T>
inline T VectorT<T, 4>::norm() const
{
	return static_cast<T>(std::sqrt(normSq()));
}

template <arithmetic T>
constexpr T VectorT<T, 4>::normSq() const
{
	return x * x + y * y + z * z + w * w;
}

template <arithmetic T>
inline VectorT<T, 4>& VectorT<T, 4>::normalize()
{
	const auto len = norm();
	if(len < std::numeric_limits<T>::epsilon())
		return *this;
	return *this *= 1.f / len;
}

template <arithmetic T>
inline VectorT<T, 4> VectorT<T, 4>::normalized() const
{
	return VectorT(*this).normalize();
}

template <arithmetic T>
constexpr T VectorT<T, 4>::dot(const VectorT& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

template <arithmetic T>
constexpr VectorT<T, 4> VectorT<T, 4>::cross(const VectorT& rhs) const
{
	// TODO
	check(false);
	return VectorT<T, 4>();
}

template <arithmetic T>
constexpr T VectorT<T, 4>::sum() const
{
	T sum = T(0);
	sum += x;
	sum += y;
	sum += z;
	sum += w;
	return sum;
}

template <arithmetic T>
constexpr size_t VectorT<T, 4>::components() const
{
	return 4;
}

template <arithmetic T>
constexpr T* VectorT<T, 4>::data()
{
	return &x;
}

template <arithmetic T>
constexpr const T* VectorT<T, 4>::data() const
{
	return &x;
}

template <arithmetic T>
inline T& VectorT<T, 4>::operator[](size_t index)
{
	check(index < components(), "subscript out of range");
	return *(&x + index);
}

template <arithmetic T>
inline const T& VectorT<T, 4>::operator[](size_t index) const
{
	check(index < components(), "subscript out of range");
	return *(&x + index);
}

template <arithmetic T>
constexpr bool VectorT<T, 4>::operator==(const VectorT<T, 4>& rhs) const
{
	return equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z) && equal(w, rhs.w);
}

template <arithmetic T>
constexpr VectorT<T, 4>& VectorT<T, 4>::operator+=(const VectorT<T, 4>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 4>& VectorT<T, 4>::operator-=(const VectorT<T, 4>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 4>& VectorT<T, 4>::operator*=(const T& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 4>& VectorT<T, 4>::operator/=(const T& rhs)
{
	check(rhs, "divisor cannot be zero");
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 4> VectorT<T, 4>::operator-() const
{
	return {-x, -y, -z, -w};
}
