// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>

template <typename T>
class Vector2T;

/**
 * @brief 三维向量.
 */
template <typename T>
class Vector3T
{
public:
    /**
	 * @brief 默认构造函数.
	 */
    Vector3T() = default;

    /**
	 * @brief 构造函数.
	 */
    explicit Vector3T(const T& scalar);

    /**
	 * @brief 构造函数.
	 *
	 * @param x x 分量.
	 * @param y y 分量.
	 * @param z z 分量.
	 */
    Vector3T(const T& x, const T& y, const T& z);

    /**
	 * @brief 构造函数.
	 *
	 * @param v 二维向量.
	 * @param z z 分量.
	 */
    Vector3T(const Vector2T<T>& v, const T& z);

    /**
	 * @brief 拷贝构造函数.
	 */
    Vector3T(const Vector3T& v);

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
    Vector3T& normalize();

    /**
	 * @brief 获取标准化单位向量.
	 */
    Vector3T normalized() const;

    /**
	 * @brief 计算向量点积.
	 *
	 * @param rhs 要点乘的向量.
	 */
    T dot(const Vector3T& rhs) const;

    /**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
    T cross(const Vector3T& rhs) const;

    /**
	 * @brief 获取原始数据.
	 */
    void*       data();
    const void* data() const;

    template <typename C>
    operator Vector3T<C>()
    {
        return Vector3T<C>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(z));
    }

    T&       operator[](size_t index);
    const T& operator[](size_t index) const;

    bool      operator==(const Vector3T&) const;
    Vector3T& operator+=(const Vector3T&);
    Vector3T& operator-=(const Vector3T&);
    Vector3T& operator*=(const T&);
    Vector3T& operator/=(const T&);
    Vector3T  operator+(const Vector3T&) const;
    Vector3T  operator-(const Vector3T&) const;
    Vector3T  operator*(const T&) const;
    Vector3T  operator/(const T&) const;
    Vector3T  operator-() const;

    static const size_t components = 3;

    static const Vector3T unit;   // (1, 1, 1)
    static const Vector3T unit_x; // (1, 0, 0)
    static const Vector3T unit_y; // (0, 1, 0)
    static const Vector3T unit_z; // (0, 0, 1)
    static const Vector3T zero;   // (0, 0, 0)

    static const Vector3T up;    // (0,  1,  0)
    static const Vector3T down;  // (0,  -1, 0)
    static const Vector3T right; // (1,  0,  0)
    static const Vector3T left;  // (-1, 0,  0)
    static const Vector3T front; // (0,  0,  -1)
    static const Vector3T back;  // (0,  0,  1)

private:
    T x = T();
    T y = T();
    T z = T();
};

#include "vector3.inl"

using Vector3f = Vector3T<float>;
using Vector3d = Vector3T<double>;
using Vector3i = Vector3T<int32_t>;
using Vector3  = Vector3f;