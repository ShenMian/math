// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

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