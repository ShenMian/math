// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector3.hpp"
#include <cstddef>

/**
 * @brief 三维向量.
 */
template <typename T> requires std::is_arithmetic_v<T>
class VectorT<T, 4>
{
public:
	union
	{
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		struct
		{
			T r;
			T g;
			T b;
			T a;
		};
	};

	/**
	 * @brief 默认构造函数.
	 */
	VectorT();

	/**
	 * @brief 构造函数.
	 */
	explicit VectorT(const T& scalar);

	/**
	 * @brief 构造函数.
	 *
	 * @param x x 分量.
	 * @param y y 分量.
	 * @param z z 分量.
	 * @param w w 分量.
	 */
	VectorT(const T& x, const T& y, const T& z, const T& w);

	/**
	 * @brief 构造函数.
	 *
	 * @param v 三维向量.
	 * @param w w 分量.
	 */
	VectorT(const Vector3T<T>& v, const T& w);

	/**
	 * @brief 构造函数.
	 *
	 * @param v 二维向量.
	 * @param z z 分量.
	 * @param w w 分量.
	 */
	VectorT(const Vector2T<T>& v, const T& z, const T& w);

	/**
	 * @brief 构造函数.
	 *
	 * @param list 初始化列表.
	 */
	VectorT(const std::initializer_list<T>& list);

	/**
	 * @brief 拷贝构造函数.
	 */
	VectorT(const VectorT& v);

	/**
	 * @brief 获取长度平方.
	 *
	 * @see size
	 */
	T sizeSquared() const;

	/**
	 * @brief 获取长度.
	 *
	 * @see sizeSquared
	 */
	T size() const;

	/**
	 * @brief 标准化成单位向量.
	 *
	 * @warning 当向量大小太小时, 将会不进行标准化.
	 */
	VectorT& normalize();

	/**
	 * @brief 获取标准化单位向量.
	 *
	 * @warning 当向量大小太小时, 将会不进行标准化.
	 */
	VectorT normalized() const;

	/**
	 * @brief 计算向量点积.
	 *
	 * @param rhs 要点乘的向量.
	 */
	T dot(const VectorT& rhs) const;

	/**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
	VectorT cross(const VectorT& rhs) const;

	/**
	 * @brief 获取原始数据.
	 */
	T* data();
	const T* data() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	bool     operator==(const VectorT&) const;
	VectorT& operator+=(const VectorT&);
	VectorT& operator-=(const VectorT&);
	VectorT& operator*=(const T&);
	VectorT& operator/=(const T&);
	VectorT  operator-() const;

	template <typename C>
	operator VectorT<C, 4>()
	{
		return VectorT<C, 4>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(z), static_cast<C>(w));
	}

	static const size_t components = 4;

	static const VectorT unit;   // (1, 1, 1, 1)
	static const VectorT unit_x; // (1, 0, 0, 0)
	static const VectorT unit_y; // (0, 1, 0, 0)
	static const VectorT unit_z; // (0, 0, 1, 0)
	static const VectorT unit_w; // (0, 0, 0, 1)
	static const VectorT zero;   // (0, 0, 0, 0)
};

#include "Vector4.inl"

template <typename T>
using Vector4T = VectorT<T, 4>;

using Vector4f = Vector4T<float>;
using Vector4d = Vector4T<double>;
using Vector4i = Vector4T<int32_t>;
using Vector4 = Vector4f;
