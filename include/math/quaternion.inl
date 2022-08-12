// Copyright 2021 SMS
// License(Apache-2.0)

#include <algorithm>
#include <cmath>

template <std::floating_point T>
QuaternionT<T>::QuaternionT(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
{
}

template <std::floating_point T>
inline QuaternionT<T>::QuaternionT(const Matrix4T<T>& mat)
{
	const auto trace = mat[0][0] + mat[1][1] + mat[2][2] + T(1);
	if(trace > T(0))
	{
		const auto s = T(2) * std::sqrt(trace);
		x            = (mat[2][1] - mat[1][2]) / s;
		y            = (mat[0][2] - mat[2][0]) / s;
		z            = (mat[1][0] - mat[0][1]) / s;
		w            = T(0.25) * s;
	}
	else if(mat[0][0] > mat[1][1] && mat[0][0] > mat[2][2])
	{
		const auto s = T(2) * std::sqrt(T(1) + mat[0][0] - mat[1][1] - mat[2][2]);
		x            = T(0.25) * s;
		y            = (mat[0][1] + mat[1][0]) / s;
		z            = (mat[2][0] + mat[0][2]) / s;
		w            = (mat[2][1] - mat[1][2]) / s;
	}
	else if(mat[1][1] > mat[2][2])
	{
		const auto s = T(2) * std::sqrt(T(1) + mat[1][1] - mat[0][0] - mat[2][2]);
		x            = (mat[0][1] + mat[1][0]) / s;
		y            = T(0.25) * s;
		z            = (mat[1][2] + mat[2][1]) / s;
		w            = (mat[0][2] - mat[2][0]) / s;
	}
	else
	{
		const auto s = T(2) * std::sqrt(T(1) + mat[2][2] - mat[0][0] - mat[1][1]);
		x            = (mat[0][2] + mat[2][0]) / s;
		y            = (mat[1][2] + mat[2][1]) / s;
		z            = T(0.25) * s;
		w            = (mat[1][0] - mat[0][1]) / s;
	}
}

template <std::floating_point T>
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

template <std::floating_point T>
inline Vector3T<T> QuaternionT<T>::eular() const
{
	Vector3T<T> angles;

	const auto xx = x * x;
	const auto yy = y * y;
	const auto zz = z * z;
	const auto ww = w * w;

	angles.x = std::atan2(T(2) * (y * z + x * w), -xx - yy + zz + ww);
	angles.y = std::asin(std::clamp(T(2) * (y * w - x * z), T(-1), T(1)));
	angles.z = std::atan2(T(2) * (x * y + z * w), xx - yy - zz + ww);

	return angles;
}

template <std::floating_point T>
inline T QuaternionT<T>::sizeSq() const
{
	return x * x + y * y + z * z + w * w;
}

template <std::floating_point T>
inline T QuaternionT<T>::size() const
{
	return static_cast<T>(std::sqrt(sizeSq()));
}

template <std::floating_point T>
inline QuaternionT<T>& QuaternionT<T>::inverse()
{
	const T n = sizeSq();
	if(n == T(1))
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	if(n < std::numeric_limits<T>::epsilon())
		return *this;

	n = 1.0f / n;
	x = -x * n;
	y = -y * n;
	z = -z * n;
	w = w * n;
	return *this;
}

template <std::floating_point T>
inline QuaternionT<T> QuaternionT<T>::inversed() const
{
	return QuaternionT(*this).inverse();
}

template <std::floating_point T>
inline QuaternionT<T>& QuaternionT<T>::normalize()
{
	const auto len = size();
	if(len < std::numeric_limits<T>::epsilon())
		return *this;
	return *this *= 1.f / len;
}

template <std::floating_point T>
inline bool QuaternionT<T>::operator==(const QuaternionT& rhs) const
{
	return equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z) && equal(w, rhs.w);
}

template <std::floating_point T>
inline QuaternionT<T>& QuaternionT<T>::operator+=(const QuaternionT<T>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

template <std::floating_point T>
inline QuaternionT<T>& QuaternionT<T>::operator-=(const QuaternionT<T>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

template <std::floating_point T>
inline QuaternionT<T>& QuaternionT<T>::operator*=(const QuaternionT<T>& rhs)
{
	*this = QuaternionT(((x * rhs.w) + (w * rhs.x) + (z * rhs.y) - (y * rhs.z)),
	                    ((y * rhs.w) - (z * rhs.x) + (w * rhs.y) + (x * rhs.z)),
	                    ((z * rhs.w) + (y * rhs.x) - (x * rhs.y) + (w * rhs.z)),
	                    ((w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z)));
	return *this;
}

template <std::floating_point T>
inline QuaternionT<T>& QuaternionT<T>::operator*=(T rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}

template <std::floating_point T>
inline QuaternionT<T> QuaternionT<T>::operator-() const
{
	return {-x, -y, -z, w};
}
