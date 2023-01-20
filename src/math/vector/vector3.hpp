﻿// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "vector2.hpp"
#include <cstddef>

/**
 * @brief 三维向量.
 */
template <arithmetic T>
class VectorT<T, 3>
{
public:
	union {
		struct
		{
			T x;
			T y;
			T z;
		};
		struct
		{
			T r;
			T g;
			T b;
		};
	};

	/**
	 * @brief 默认构造函数.
	 */
	VectorT();

	/**
	 * @brief 构造函数.
	 */
	constexpr explicit VectorT(const T& scalar);

	/**
	 * @brief 构造函数.
	 *
	 * @param x x 分量.
	 * @param y y 分量.
	 * @param z z 分量.
	 */
	constexpr VectorT(const T& x, const T& y, const T& z);

	/**
	 * @brief 构造函数.
	 *
	 * @param v 二维向量.
	 * @param z z 分量.
	 */
	constexpr VectorT(const Vector2T<T>& v, const T& z = T());

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
	T dot(const VectorT& rhs) const;

	/**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
	VectorT cross(const VectorT& rhs) const;

	/**
	 * @brief 获取所有元素之和.
	 */
	constexpr T sum() const;

	/**
	 * @brief 获取两点之间的距离.
	 *
	 * @param point 另一个点.
	 *
	 * @see distanceSquared
	 */
	T distance(const VectorT& point) const;

	/**
	 * @brief 获取两点之间的距离的平方.
	 *
	 * @param point 另一个点.
	 *
	 * @see distance
	 */
	T distanceSquared(const VectorT& point) const;

	/**
	 * @brief 获取分量数.
	 */
	constexpr size_t components() const;

	/**
	 * @brief 获取原始数据.
	 */
	T*       data();
	const T* data() const;

	T&       operator[](size_t index);
	const T& operator[](size_t index) const;

	constexpr bool     operator==(const VectorT&) const;
	constexpr VectorT& operator+=(const VectorT&);
	constexpr VectorT& operator-=(const VectorT&);
	constexpr VectorT& operator*=(const T&);
	constexpr VectorT& operator/=(const T&);
	constexpr VectorT  operator-() const;

	template <typename C>
	operator VectorT<C, 3>()
	{
		return VectorT<C, 3>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(z));
	}

	friend std::ostream& operator<<(std::ostream& stream, const VectorT& vec)
	{
		size_t max = 0;
		for(size_t i = 0; i < 3; i++)
		{
			std::ostringstream stm;
			stm << vec[i];
			const auto size = stm.str().size();
			max             = std::max(max, size);
		}
		max = std::min<size_t>(max, 6);
		for(size_t i = 0; i < 3; i++)
		{
			std::ostringstream stm;
			stm.setf(std::ios::fixed);
			stm.precision(6);
			stm << vec[i];
			auto str = stm.str();
			str.erase(str.find_last_not_of('0') + 1);
			if(str.back() == '.')
				str.pop_back();
			stream.width(max);
			stream << str << ' ';
		}
		return stream;
	}

	static VectorT lerp(const VectorT& from, const VectorT& to, T t);

	static const VectorT unit;   // (1, 1, 1)
	static const VectorT unit_x; // (1, 0, 0)
	static const VectorT unit_y; // (0, 1, 0)
	static const VectorT unit_z; // (0, 0, 1)
	static const VectorT zero;   // (0, 0, 0)

	static const VectorT up;    // (0,  1,  0)
	static const VectorT down;  // (0,  -1, 0)
	static const VectorT right; // (1,  0,  0)
	static const VectorT left;  // (-1, 0,  0)
	static const VectorT front; // (0,  0,  1)
	static const VectorT back;  // (0,  0,  -1)
};

#include "vector3.inl"

template <typename T>
using Vector3T = VectorT<T, 3>;

using Vector3f = Vector3T<float>;
using Vector3d = Vector3T<double>;
using Vector3i = Vector3T<int32_t>;
using Vector3  = Vector3f;
