// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "../Vector/Vector3.hpp"
#include <cstddef>
#include <iostream>
#include <type_traits>

/**
 * @brief 矩阵.
 *
 * @tparam T 数据类型.
 * @tparam R 行数.
 * @tparam C 列数.
 */
template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
class MatrixT
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	MatrixT();

	/**
	 * @brief 构造函数.
	 *
	 * @param list 初始化列表.
	 */
	MatrixT(const std::initializer_list<T>& list);

	/**
	 * @brief 求逆.
	 */
	MatrixT& inverse();

	/**
	 * @brief 获取逆矩阵.
	 */
	MatrixT<T, R, C> inversed() const;

	/**
	 * @brief 转置.
	 */
	MatrixT& transpose();

	/**
	 * @brief 获取转置后的矩阵.
	 */
	MatrixT<T, R, C> transposed() const;

	/**
	 * @brief 计算行列式的值.
	 */
	T determinant() const;

	/**
	 * @brief 求迹.
	 */
	constexpr T trace() const;

	/**
	 * @brief 获取所有元素之和.
	 */
	constexpr T sum() const;

	/**
	 * @brief 获取最小元素的值.
	 */
	constexpr T minCoeff() const;

	/**
	 * @brief 获取最大元素的值.
	 */
	constexpr T maxCoeff() const;
	
	/**
	 * @brief 获取主对角线.
	 */
	constexpr const VectorT<T, R> diagonal() const;

	/**
	 * @brief 分解.
	 */
	void decompose(Vector3T<T>* translation, Vector3T<T>* rotation, Vector3T<T>* scale) const;

	/**
	 * @brief 重组.
	 */
	MatrixT& recompose(const Vector3T<T>& translation, const Vector3T<T>& rotation, const Vector3T<T>& scale);

	/**
	 * @brief 获取行数.
	 */
	constexpr size_t rows() const;

	/**
	 * @brief 获取列数.
	 */
	constexpr size_t cols() const;

	/**
	 * @brief 获取原始数据.
	 */
	constexpr T* data();
	constexpr const T* data() const;

	constexpr T& operator()(size_t r, size_t c);
	constexpr const T& operator()(size_t r, size_t c) const;

	constexpr T* operator[](size_t row);
	constexpr const T* operator[](size_t row) const;

	constexpr bool     operator==(const MatrixT&) const;
	constexpr MatrixT& operator+=(const MatrixT&);
	constexpr MatrixT& operator-=(const MatrixT&);
	MatrixT& operator*=(const MatrixT&);
	MatrixT& operator/=(const MatrixT&);
	constexpr MatrixT& operator*=(const T&);
	constexpr MatrixT& operator/=(const T&);
	constexpr MatrixT  operator-();

	template <typename T0>
	operator MatrixT<T0, R, C>()
	{
		MatrixT result;
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				result[r][c] = static_cast<T0>(m_[r][c]);
		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, const MatrixT& mat)
	{
		for(size_t r = 0; r < R; r++)
		{
			for(size_t c = 0; c < C - 1; c++)
				stream << mat[r][c] << ' ';
			stream << mat[r][C - 1] << '\n';
		}
		return stream;
	}

	/**
	 * @brief 生成平移变换矩阵.
	 *
	 * @param translation 平移向量. 指定了三个轴的变化量.
	 */
	static MatrixT translate(const Vector3T<T>& translation);

	/**
	 * @brief 生成旋转变换矩阵.
	 *
	 * @param axis  旋转轴.
	 * @param angle 旋转角度, 单位: 弧度制.
	 */
	static MatrixT rotation(const Vector3T<T>& axis, float angle);

	/**
	 * @brief 生成缩放变换矩阵.
	 *
	 * @param scale 缩放向量. 指定了三个轴的缩放比.
	 */
	static MatrixT scale(const Vector3T<T>& scale);

	/**
	 * @brief 生成透视投影矩阵.
	 *
	 * @param vFOV   垂直视角, 单位: 弧度制.
	 * @param aspect 宽高比.
	 * @param near   近裁剪面.
	 * @param far    远裁剪面.
	 */
	static MatrixT<T, 4, 4> perspective(float vFOV, float aspect, float near, float far);

	/**
	 * @brief 生成正交投影矩阵.
	 *
	 * @param width  宽度.
	 * @param height 高度.
	 * @param near   近裁剪面.
	 * @param far    远裁剪面.
	 */
	static MatrixT<T, 4, 4> orthogonal(float width, float height, float near, float far);

	/**
	 * @brief 生成正交投影矩阵.
	 *
	 * @param left   左平面.
	 * @param right  右平面.
	 * @param bottom 底面.
	 * @param top    顶面.
	 * @param near   近裁剪面.
	 * @param far    远裁剪面.
	 */
	static MatrixT<T, 4, 4> orthographic(float left, float right, float bottom, float top,
		float near, float far);

	/**
	 * @brief 生成视图矩阵.
	 *
	 * @param eye    观察者位置.
	 * @param target 目标的位置.
	 * @param up     观察者向上的方向.
	 */
	static MatrixT<T, 4, 4> lookAt(const Vector3T<T>& eye, const Vector3T<T>& target, const Vector3T<T>& up = Vector3T<T>::up);

	/**
	 * @brief 获取单位矩阵.
	 */
	static MatrixT identity();

	/**
	 * @brief 获取零矩阵.
	 */
	static MatrixT zero();

private:
	T m_[R][C] = {};

	inline static const size_t rows_ = R;
	inline static const size_t cols_ = C;
};

#include "Matrix.inl"

template <size_t R, size_t C>
using Matrixf = MatrixT<float, R, C>;

template <size_t R, size_t C>
using Matrixd = MatrixT<double, R, C>;

template <size_t R, size_t C>
using Matrixi = MatrixT<int32_t, R, C>;

#define DEF_MATRIX_NxN(n)                                        \
    template <typename T> using Matrix##n##T = MatrixT<T, n, n>; \
    using Matrix##n     = Matrix##n##T<float>;                   \
    using Matrix##n##f  = Matrix##n##T<float>;                   \
    using Matrix##n##d  = Matrix##n##T<double>;                  \

DEF_MATRIX_NxN(2);
DEF_MATRIX_NxN(3);
DEF_MATRIX_NxN(4);

#undef DEF_MATRIX_NxN

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C> operator+(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
{
	return MatrixT(lhs) += rhs;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C> operator-(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
{
	return MatrixT(lhs) -= rhs;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C> operator*(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
{
	return MatrixT(lhs) *= rhs;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C> operator/(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
{
	return MatrixT(lhs) /= rhs;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
MatrixT<T, R, C> constexpr operator*(const MatrixT<T, R, C>& lhs, const T& rhs)
{
	return MatrixT(lhs) *= rhs;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
MatrixT<T, R, C> constexpr operator/(const MatrixT<T, R, C>& lhs, const T& rhs)
{
	return MatrixT(lhs) /= rhs;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
MatrixT<T, R, C> constexpr operator*(const T& lhs, const MatrixT<T, R, C>& rhs)
{
	return rhs * lhs;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
MatrixT<T, R, C> constexpr operator/(const T& lhs, const MatrixT<T, R, C>& rhs)
{
	return rhs / lhs;
}

/**
 * @class MatrixT
 *
 * @details 大小固定的矩阵, 可用于表示线性变换等.
 *
 * 例子:
 * @code{cpp}
 *
 * // 创建
 * Matrix2f m; // 创建一个 2x2 矩阵, 类型为 float, 初始值为 2x2 单位矩阵
 *
 * // 操作
 * m[0][1] = 4; // 设置第一行第二列的值为 4
 * m(1, 0) = 3; // 设置第二行第一列的值为 3
 * std::cout << m; // 输出矩阵, 结果为:
 *                 // 1 4
 *                 // 3 1
 *
 * @endcode
 */
