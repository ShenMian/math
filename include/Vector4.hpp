// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>

template <typename T>
class Vector2T;

template <typename T>
class Vector3T;

/**
 * @brief 三维向量.
 */
template <typename T>
class Vector4T
{
public:
    /**
	 * @brief 默认构造函数.
	 */
    Vector4T() = default;

    /**
	 * @brief 构造函数.
	 */
    explicit Vector4T(const T& scalar);

    /**
	 * @brief 构造函数.
	 *
	 * @param x x 分量.
	 * @param y y 分量.
	 * @param z z 分量.
	 * @param w w 分量.
	 */
    Vector4T(const T& x, const T& y, const T& z, const T& w);

    /**
	 * @brief 构造函数.
	 *
	 * @param v 三维向量.
	 * @param w w 分量.
	 */
    Vector4T(const Vector3T<T>& v, const T& w);

    /**
	 * @brief 构造函数.
	 *
	 * @param v 二维向量.
	 * @param z z 分量.
	 * @param w w 分量.
	 */
    Vector4T(const Vector2T<T>& v, const T& z, const T& w);

    /**
	 * @brief 拷贝构造函数.
	 */
    Vector4T(const Vector4T& v);

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
    Vector4T& normalize();

    /**
	 * @brief 获取标准化单位向量.
	 */
    Vector4T normalized() const;

    /**
	 * @brief 计算向量点积.
	 *
	 * @param rhs 要点乘的向量.
	 */
    T dot(const Vector4T& rhs) const;

    /**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
    T cross(const Vector4T& rhs) const;

    /**
	 * @brief 获取原始数据.
	 */
    void*       data();
    const void* data() const;

    template <typename C>
    operator Vector4T<C>()
    {
        return Vector4T<C>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(z), static_cast<C>(w));
    }

    T&       operator[](size_t index);
    const T& operator[](size_t index) const;

    bool      operator==(const Vector4T&) const;
    Vector4T& operator+=(const Vector4T&);
    Vector4T& operator-=(const Vector4T&);
    Vector4T& operator*=(const T&);
    Vector4T& operator/=(const T&);
    Vector4T  operator+(const Vector4T&) const;
    Vector4T  operator-(const Vector4T&) const;
    Vector4T  operator*(const T&) const;
    Vector4T  operator/(const T&) const;
    Vector4T  operator-() const;

    static const size_t components = 4;

    static const Vector4T unit; // (1, 1, 1, 1)
    static const Vector4T zero; // (0, 0, 0, 0)

private:
    T x = T();
    T y = T();
    T z = T();
    T w = T();
};

#include "vector4.inl"

using Vector4f = Vector4T<float>;
using Vector4d = Vector4T<double>;
using Vector4i = Vector4T<int32_t>;
using Vector4  = Vector4f;