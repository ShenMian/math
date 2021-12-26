// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <initializer_list>

/**
 * @brief N 维向量.
 *
 * @tparam T 数据类型.
 * @tparam N 维数.
 */
template <typename T, size_t N>
class VectorT
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	VectorT() = default;

	/**
	 * @brief 构造函数.
	 */
	explicit VectorT(const T& scalar);

	/**
	 * @brief 构造函数.
	 *
	 * @param list 初始化列表, 下标依次为 0 到 N-1.
	 */
	VectorT(const std::initializer_list<T>& list);

	/**
	 * @brief 拷贝构造函数.
	 */
	VectorT(const VectorT& rhs);

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
	 */
	VectorT& normalize();

	/**
	 * @brief 获取标准化单位向量.
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
	operator VectorT<C, N>()
	{
		VectorT<C, N> result;
		for(size_t i = 0; i < N; i++)
			result[i] = static_cast<C>(v_[i]);
		return result;
	}

	static const size_t components = N;

private:
	T v_[N] = {};
};

#include "Vector.inl"

template <size_t N>
using Vectorf = VectorT<float, N>;

template <size_t N>
using Vectord = VectorT<float, N>;

template <size_t N>
using Vectori = VectorT<int32_t, N>;

template <typename T, size_t N>
VectorT<T, N> operator+(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) += rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator-(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) -= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator*(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) *= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator/(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) /= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator*(const VectorT<T, N>& lhs, const T& rhs)
{
	return VectorT(lhs) *= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator/(const VectorT<T, N>& lhs, const T& rhs)
{
	return VectorT(lhs) /= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator*(const T& lhs, const VectorT<T, N>& rhs)
{
	return rhs * lhs;
}

template <typename T, size_t N>
VectorT<T, N> operator/(const T& lhs, const VectorT<T, N>& rhs)
{
	return rhs / lhs;
}

/**
 * @class VectorT
 *
 * @details 大小固定的向量, 可以用于表示位置/速度/方向等.
 *
 * 例子:
 * @code{cpp}
 *
 * // 创建
 * Vector2i v(1, 2); // 创建一个 2 维向量, 类型为 int32_t, 初始值为 (1, 2)
 *
 * // 操作
 * v.x = 3;  // 设置 x 分量为 3
 * v[1] = 4; // 设置 y 分量为 4
 * std::cout << v.size() << std::endl; // 输出向量的长度, 结果为: 5
 *
 * @endcode
 */
