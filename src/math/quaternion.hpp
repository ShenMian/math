// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "hash_combine.hpp"
#include "helper.hpp"
#include "matrix/matrix.hpp"
#include "vector/vector3.hpp"
#include <type_traits>

/**
 * @brief 四元数.
 */
template <std::floating_point T>
class QuaternionT
{
public:
	T x = T();
	T y = T();
	T z = T();
	T w = T(1);

	/**
	 * @brief 默认构造函数.
	 */
	QuaternionT() = default;

	/**
	 * @brief 构造函数.
	 *
	 * @param x x 分量.
	 * @param y y 分量.
	 * @param z z 分量.
	 * @param w w 分量.
	 */
	QuaternionT(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

	/**
	 * @brief 构造函数.
	 *
	 * @param mat 4x4 矩阵.
	 */
	constexpr explicit QuaternionT(const Matrix4T<T>& mat)
	{
		const auto trace = mat.trace();
		if(trace > T(0))
		{
			const auto s = T(2) * detail::sqrt(trace);
			x            = (mat(2, 1) - mat(1, 2)) / s;
			y            = (mat(0, 2) - mat(2, 0)) / s;
			z            = (mat(1, 0) - mat(0, 1)) / s;
			w            = T(0.25) * s;
		}
		else if(mat(0, 0) > mat(1, 1) && mat(0, 0) > mat(2, 2))
		{
			const auto s = T(2) * detail::sqrt(T(1) + mat(0, 0) - mat(1, 1) - mat(2, 2));
			x            = T(0.25) * s;
			y            = (mat(0, 1) + mat(1, 0)) / s;
			z            = (mat(2, 0) + mat(0, 2)) / s;
			w            = (mat(2, 1) - mat(1, 2)) / s;
		}
		else if(mat(1, 1) > mat(2, 2))
		{
			const auto s = T(2) * detail::sqrt(T(1) + mat(1, 1) - mat(0, 0) - mat(2, 2));
			x            = (mat(0, 1) + mat(1, 0)) / s;
			y            = T(0.25) * s;
			z            = (mat(1, 2) + mat(2, 1)) / s;
			w            = (mat(0, 2) - mat(2, 0)) / s;
		}
		else
		{
			const auto s = T(2) * detail::sqrt(T(1) + mat(2, 2) - mat(0, 0) - mat(1, 1));
			x            = (mat(0, 2) + mat(2, 0)) / s;
			y            = (mat(1, 2) + mat(2, 1)) / s;
			z            = T(0.25) * s;
			w            = (mat(1, 0) - mat(0, 1)) / s;
		}
	}

	/**
	 * @brief 设置欧拉角.
	 *
	 * @param angles 三个轴的角度, 单位: 弧度.
	 */
	constexpr void eular(const Vector3T<T>& angles) noexcept
	{
		const auto cr = detail::cos(angles.x / T(2));
		const auto cp = detail::cos(angles.y / T(2));
		const auto cy = detail::cos(angles.z / T(2));

		const auto sr = detail::sin(angles.x / T(2));
		const auto sp = detail::sin(angles.y / T(2));
		const auto sy = detail::sin(angles.z / T(2));

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

	/**
	 * @brief 获取欧拉角.
	 *
	 * 单位: 弧度.
	 */
	constexpr Vector3T<T> eular() const noexcept
	{
		Vector3T<T> angles;

		const auto xx = x * x;
		const auto yy = y * y;
		const auto zz = z * z;
		const auto ww = w * w;

		angles.x = detail::atan2(T(2) * (y * z + x * w), -xx - yy + zz + ww);
		angles.y = detail::asin(std::clamp(T(2) * (y * w - x * z), T(-1), T(1)));
		angles.z = detail::atan2(T(2) * (x * y + z * w), xx - yy - zz + ww);

		return angles;
	}

	/**
	 * @brief 求逆.
	 */
	constexpr QuaternionT& inverse()
	{
		T n = size_sq();
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

	/**
	 * @brief 获取求逆结果.
	 */
	constexpr QuaternionT inversed() const { return QuaternionT(*this).inverse(); }

	/**
	 * @brief 标准化成单位四元数.
	 *
	 * @warning 当向量大小太小时, 将会不进行标准化.
	 */
	constexpr QuaternionT& normalize()
	{
		const auto len = size();
		if(len < std::numeric_limits<T>::epsilon())
			return *this;
		return *this *= 1.f / len;
	}

	/**
	 * @brief 获取单位四元数.
	 *
	 * @warning 当向量大小太小时, 将会不进行标准化.
	 */
	constexpr QuaternionT normalized() const { return QuaternionT(*this).normalized(); }

	/**
	 * @brief 获取共轭四元数.
	 */
	constexpr QuaternionT conjugate() const { return {-x, -y, -z, w}; }

	/**
	 * @brief 获取长度平方.
	 *
	 * @see size
	 */
	constexpr T size_sq() const noexcept { return x * x + y * y + z * z + w * w; }

	/**
	 * @brief 获取长度.
	 *
	 * @see sizeSquared
	 */
	constexpr T size() const { return static_cast<T>(detail::sqrt(size_sq())); }

	template <typename C>
	operator QuaternionT<C>() const
	{
		return QuaternionT<C>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(z), static_cast<C>(w));
	}

	constexpr bool operator==(const QuaternionT& rhs) const
	{
		return equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z) && equal(w, rhs.w);
	}

	constexpr QuaternionT& operator+=(const QuaternionT& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	constexpr QuaternionT& operator-=(const QuaternionT& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	constexpr QuaternionT& operator*=(const QuaternionT& rhs)
	{
		*this = QuaternionT(((x * rhs.w) + (w * rhs.x) + (z * rhs.y) - (y * rhs.z)),
		                    ((y * rhs.w) - (z * rhs.x) + (w * rhs.y) + (x * rhs.z)),
		                    ((z * rhs.w) + (y * rhs.x) - (x * rhs.y) + (w * rhs.z)),
		                    ((w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z)));
		return *this;
	}

	constexpr QuaternionT& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	constexpr QuaternionT operator-() const { return {-x, -y, -z, w}; }
};

using Quaternionf = QuaternionT<float>;
using Quaterniond = QuaternionT<double>;
using Quaternion  = Quaternionf;

template <std::floating_point T>
struct std::hash<QuaternionT<T>>
{
	std::size_t operator()(const QuaternionT<T>& v) const
	{
		std::size_t ret = 0;
		hash_combine(ret, v.x, v.y, v.z, v.w);
		return ret;
	}
};
