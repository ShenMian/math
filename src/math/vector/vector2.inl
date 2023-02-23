// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "../check.hpp"
#include <cmath>

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::unit(1, 1);

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::unit_x(1, 0);

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::unit_y(0, 1);

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::zero(0, 0);

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::up(0, 1);

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::down(0, -1);

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::right(1, 0);

template <arithmetic T>
inline const VectorT<T, 2> VectorT<T, 2>::left(-1, 0);

template <arithmetic T>
inline VectorT<T, 2>::VectorT() : x(0), y(0)
{
}

template <arithmetic T>
constexpr VectorT<T, 2>::VectorT(const T& scalar) : x(scalar), y(scalar)
{
}

template <arithmetic T>
constexpr VectorT<T, 2>::VectorT(const T& x, const T& y) : x(x), y(y)
{
}

template <arithmetic T>
constexpr VectorT<T, 2>::VectorT(const std::initializer_list<T>& list)
{
	MATH_DEBUG_CHECK(list.size() <= 2, "Too many initializers");
	auto it = list.begin();
	x       = *it;
	y       = *(++it);
}

template <arithmetic T>
inline T VectorT<T, 2>::norm() const
{
	return static_cast<T>(std::hypot(x, y));
}

template <arithmetic T>
inline T constexpr VectorT<T, 2>::normSq() const noexcept
{
	return x * x + y * y;
}

template <arithmetic T>
inline VectorT<T, 2>& VectorT<T, 2>::normalize()
{
	const auto len = norm();
	if(len < std::numeric_limits<T>::epsilon())
		return *this;
	return *this *= 1.f / len;
}

template <arithmetic T>
inline VectorT<T, 2> VectorT<T, 2>::normalized() const
{
	return VectorT(*this).normalize();
}

template <arithmetic T>
inline T VectorT<T, 2>::dot(const VectorT& rhs) const noexcept
{
	return x * rhs.x + y * rhs.y;
}

template <arithmetic T>
inline VectorT<T, 2> VectorT<T, 2>::cross(const VectorT& rhs) const
{
	// TODO
	MATH_DEBUG_CHECK(false);
	return VectorT<T, 2>();
}

template <arithmetic T>
constexpr T VectorT<T, 2>::sum() const noexcept
{
	T sum = T(0);
	sum += x;
	sum += y;
	return sum;
}

template <arithmetic T>
inline T VectorT<T, 2>::angle() const
{
	return std::atan2(y, x);
}

template <arithmetic T>
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

template <arithmetic T>
inline T VectorT<T, 2>::distance(const VectorT& point) const
{
	return std::sqrt(distanceSq(point));
}

template <arithmetic T>
inline T VectorT<T, 2>::distanceSq(const VectorT& point) const
{
	const auto dx = std::abs(x - point.x);
	const auto dy = std::abs(y - point.y);
	return dx * dx + dy * dy;
}

template <arithmetic T>
constexpr size_t VectorT<T, 2>::components() const
{
	return 2;
}

template <arithmetic T>
inline T* VectorT<T, 2>::data()
{
	return &x;
}

template <arithmetic T>
inline const T* VectorT<T, 2>::data() const
{
	return &x;
}

template <arithmetic T>
inline T& VectorT<T, 2>::operator[](size_t index)
{
	MATH_DEBUG_CHECK(index < components());
	return *(&x + index);
}

template <arithmetic T>
inline const T& VectorT<T, 2>::operator[](size_t index) const
{
	MATH_DEBUG_CHECK(index < components());
	return *(&x + index);
}

template <arithmetic T>
constexpr bool VectorT<T, 2>::operator==(const VectorT<T, 2>& rhs) const
{
	return equal(x, rhs.x) && equal(y, rhs.y);
}

template <arithmetic T>
constexpr VectorT<T, 2>& VectorT<T, 2>::operator+=(const VectorT<T, 2>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 2>& VectorT<T, 2>::operator-=(const VectorT<T, 2>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 2>& VectorT<T, 2>::operator*=(const T& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 2>& VectorT<T, 2>::operator/=(const T& rhs)
{
	MATH_DEBUG_CHECK(rhs, "divisor cannot be zero");
	x /= rhs;
	y /= rhs;
	return *this;
}

template <arithmetic T>
constexpr VectorT<T, 2> VectorT<T, 2>::operator-() const
{
	return {-x, -y};
}
