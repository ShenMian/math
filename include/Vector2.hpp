// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>

/**
 * @brief 二维向量.
 */
template <typename T>
class Vector2T
{
public:
    /**
	 * @brief 默认构造函数.
	 */
    Vector2T() = default;

    /**
	 * @brief 构造函数.
	 */
    explicit Vector2T(const T& scalar);

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
    Vector2T(const Vector2T& v);

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
	 * @param rhs 要点乘的向量.
	 */
    T dot(const Vector2T& rhs) const;

    /**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
    T cross(const Vector2T& rhs) const;

    /**
	 * @brief 获取角度.
	 *
	 * @return 角度, 弧度制. 范围: [2π, -2π)
	 */
    T angle() const;

    /**
	 * @brief 围绕指定点旋转指定弧度.
	 *
	 * @param point 点.
	 * @param angle 旋转角度, 弧度制.
	 */
    void rotate(const Vector2T& point, float angle);

    /**
	 * @brief 获取两点之间的距离.
	 *
	 * @param point 另一个点.
     * 
	 * @see distanceSquared
	 */
    T distance(const Vector2T& point) const;

    /**
	 * @brief 获取两点之间的距离的平方.
	 *
	 * @param point 另一个点.
     * 
	 * @see distance
	 */
    T distanceSquared(const Vector2T& point) const;

    /**
	 * @brief 获取原始数据.
	 */
    void*       data();
    const void* data() const;

    template <typename C>
    operator Vector2T<C>()
    {
        return Vector2T<C>(static_cast<C>(x), static_cast<C>(y));
    }

    T&       operator[](size_t index);
    const T& operator[](size_t index) const;

    bool      operator==(const Vector2T&) const;
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

    static const Vector2T unit;   // (1, 1)
    static const Vector2T unit_x; // (1, 0)
    static const Vector2T unit_y; // (0, 1)
    static const Vector2T zero;   // (0, 0)

    static const Vector2T up;    // (0, 1)
    static const Vector2T down;  // (0, -1)
    static const Vector2T right; // (1, 0)
    static const Vector2T left;  // (-1, 0)

private:
    T x = T();
    T y = T();
};

#include "vector2.inl"

using Vector2f = Vector2T<float>;
using Vector2d = Vector2T<double>;
using Vector2i = Vector2T<int32_t>;
using Vector2  = Vector2f;