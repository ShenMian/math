// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "vector3.hpp"
#include <cstddef>

/**
 * @brief 三维向量.
 */
template <arithmetic T>
class alignas(sizeof(T)) VectorT<T, 4>
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
	constexpr VectorT(const T& x, const T& y, const T& z, const T& w);

	/**
	 * @brief 构造函数.
	 *
	 * @param v 三维向量.
	 * @param w w 分量.
	 */
	constexpr VectorT(const Vector3T<T>& v, const T& w = T());

	/**
	 * @brief 构造函数.
	 *
	 * @param v 二维向量.
	 * @param z z 分量.
	 * @param w w 分量.
	 */
	constexpr VectorT(const Vector2T<T>& v, const T& z = T(), const T& w = T());

	/**
	 * @brief 构造函数.
	 *
	 * @param list 初始化列表.
	 */
	constexpr VectorT(const std::initializer_list<T>& list);

	/**
	 * @brief 获取模.
	 *
	 * @see normSquared
	 */
	T norm() const;

	/**
	 * @brief 获取模的平方.
	 *
	 * @see norm
	 */
	constexpr T normSq() const;

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
	constexpr T dot(const VectorT& rhs) const;

	/**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
	constexpr VectorT cross(const VectorT& rhs) const;

	/**
	 * @brief 获取所有元素之和.
	 */
	constexpr T sum() const;

	/**
	 * @brief 获取原始数据.
	 */
	constexpr T* data();
	constexpr const T* data() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	constexpr bool     operator==(const VectorT&) const;
	constexpr VectorT& operator+=(const VectorT&);
	constexpr VectorT& operator-=(const VectorT&);
	constexpr VectorT& operator*=(const T&);
	constexpr VectorT& operator/=(const T&);
	constexpr VectorT  operator-() const;

	template <typename C>
	operator VectorT<C, 4>()
	{
		return VectorT<C, 4>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(z), static_cast<C>(w));
	}

	friend std::ostream& operator<<(std::ostream& stream, const VectorT& vec)
	{
		stream << vec.x << ' ' << vec.y << ' ' << vec.z << ' ' << vec.w;
		return stream;
	}

	static constexpr size_t components = 4;

	static const VectorT unit;   // (1, 1, 1, 1)
	static const VectorT unit_x; // (1, 0, 0, 0)
	static const VectorT unit_y; // (0, 1, 0, 0)
	static const VectorT unit_z; // (0, 0, 1, 0)
	static const VectorT unit_w; // (0, 0, 0, 1)
	static const VectorT zero;   // (0, 0, 0, 0)
};

#include "vector4.inl"

template <typename T>
using Vector4T = VectorT<T, 4>;

using Vector4f = Vector4T<float>;
using Vector4d = Vector4T<double>;
using Vector4i = Vector4T<int32_t>;
using Vector4 = Vector4f;
