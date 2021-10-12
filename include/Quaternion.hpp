// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector3.hpp"
#include <type_traits>

/**
 * @brief 四元数.
 */
template <typename T>
requires std::floating_point<T>
class QuaternionT
{
public:
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
    QuaternionT(const T& x, const T& y, const T& z, const T& w);

    /**
     * @brief 设置欧拉角.
     */
    void eular(const Vector3T<T>& angles);

    /**
     * @brief 获取欧拉角.
     */
    Vector3T<T> eular() const;

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
    T sizeSquared() const;

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

private:
    T x = T();
    T y = T();
    T z = T();
    T w = T(1);
};

#include "Quaternion.inl"

using Quaternionf = QuaternionT<float>;
using Quaterniond = QuaternionT<double>;
using Quaternion  = Quaternionf;