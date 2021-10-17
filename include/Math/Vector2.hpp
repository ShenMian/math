// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector.hpp"
#include <cstddef>

/**
 * @brief 二维向量.
 */
template <typename T>
class VectorT<T, 2>
{
public:
    T x = T();
    T y = T();

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
	 */
    explicit VectorT(const T& x, const T& y);

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
    void rotate(const VectorT& point, float angle);

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
	 * @brief 获取原始数据.
	 */
    T*       data();
    const T* data() const;

    template <typename C>
    operator VectorT<C, 2>()
    {
        return VectorT<C, 2>(static_cast<C>(x), static_cast<C>(y));
    }

    T&       operator[](size_t index);
    const T& operator[](size_t index) const;

    bool     operator==(const VectorT&) const;
    VectorT& operator+=(const VectorT&);
    VectorT& operator-=(const VectorT&);
    VectorT& operator*=(const T&);
    VectorT& operator/=(const T&);
    VectorT  operator-() const;

    static const size_t components = 2;

    static const VectorT unit;   // (1, 1)
    static const VectorT unit_x; // (1, 0)
    static const VectorT unit_y; // (0, 1)
    static const VectorT zero;   // (0, 0)

    static const VectorT up;    // (0, 1)
    static const VectorT down;  // (0, -1)
    static const VectorT right; // (1, 0)
    static const VectorT left;  // (-1, 0)
};

#include "Vector2.inl"

template <typename T>
using Vector2T = VectorT<T, 2>;

using Vector2f = Vector2T<float>;
using Vector2d = Vector2T<double>;
using Vector2i = Vector2T<int32_t>;
using Vector2  = Vector2f;
