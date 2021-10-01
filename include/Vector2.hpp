// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>

template <typename T = float>
class Vector2T
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	Vector2T() = default;

	/**
	 * @brief 构造函数.
	 *
	 * @param x x 分量.
	 * @param y y 分量.
	 */
	explicit Vector2T(const T& x, const T& y);

	/**
	 * @brief 拷贝构造函数.
	 */
	explicit Vector2T(const Vector2T& rhs);

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
	Vector2T& normalize();

	/**
	 * @brief 获取标准化单位向量.
	 */
	Vector2T normalized() const;

    /**
	 * @brief 计算向量点积.
	 *
	 * @param v 要点乘的向量.
	 */
	T dot(const Vector2T& v) const;

    /**
	 * @brief 计算向量叉积.
	 *
	 * @param v 要叉乘的向量.
	 */
	T cross(const Vector2T& v) const;

    T&       operator[](size_t index);
    const T& operator[](size_t index) const;

    bool      operator==(const Vector2T&) const;
    bool      operator!=(const Vector2T&) const;
    Vector2T& operator+=(const Vector2T&);
    Vector2T& operator-=(const Vector2T&);
    Vector2T& operator*=(const T&);
    Vector2T& operator/=(const T&);
    Vector2T  operator+(const Vector2T&) const;
    Vector2T  operator-(const Vector2T&) const;
    Vector2T  operator*(const T&) const;
    Vector2T  operator/(const T&) const;
    Vector2T  operator-() const;

	static const size_t components = 2;

private:
	T x, y;
};

#include "Vector2.inl"

using Vector2f = Vector2T<float>;
using Vector2d = Vector2T<double>;
using Vector2i = Vector2T<int32_t>;
using Vector2  = Vector2f;