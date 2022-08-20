// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "hash_combine.hpp"
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
	QuaternionT(T x, T y, T z, T w);

	/**
	 * @brief 构造函数.
	 *
	 * @param mat 4x4 矩阵.
	 */
	explicit QuaternionT(const Matrix4T<T>& mat);

	/**
	 * @brief 设置欧拉角.
	 *
	 * @param angles 三个轴的角度, 单位: 弧度.
	 */
	void eular(const Vector3T<T>& angles) noexcept;

	/**
	 * @brief 获取欧拉角.
	 * 
	 * 单位: 弧度.
	 */
	Vector3T<T> eular() const noexcept;

	/**
	 * @brief 求逆.
	 */
	QuaternionT& inverse();

	/**
	 * @brief 获取求逆结果.
	 */
	QuaternionT inversed() const;

	/**
	 * @brief 标准化.
	 */
	QuaternionT& normalize();

	/**
	 * @brief 获取长度平方.
	 *
	 * @see size
	 */
	T sizeSq() const noexcept;

	/**
	 * @brief 获取长度.
	 *
	 * @see sizeSquared
	 */
	T size() const;

	template <typename C>
	operator QuaternionT<C>() const
	{
		return QuaternionT<C>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(z), static_cast<C>(w));
	}

	bool         operator==(const QuaternionT&) const;
	QuaternionT& operator+=(const QuaternionT&);
	QuaternionT& operator-=(const QuaternionT&);
	QuaternionT& operator*=(const QuaternionT&);
	QuaternionT& operator*=(T);
	QuaternionT  operator-() const;
};

#include "quaternion.inl"

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
