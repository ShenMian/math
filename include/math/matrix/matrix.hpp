// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "../vector/vector3.hpp"
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <type_traits>

#define ROW_MANJOR true

template <std::floating_point T>
class QuaternionT;

/**
 * @brief 矩阵.
 *
 * @tparam T 数据类型.
 * @tparam R 行数.
 * @tparam C 列数.
 */
template <arithmetic T, size_t R, size_t C>
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
	 * @brief 构造函数.
	 */
	constexpr explicit MatrixT(const T(&arr)[R * C]);

	/**
	 * @brief 构造函数.
	 */
	constexpr explicit MatrixT(const T* data);

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
	 * @brief 获取行列式的值.
	 */
	constexpr T determinant() const;

	/**
	 * @brief 获取主对角线.
	 */
	constexpr VectorT<T, R> diagonal() const;

	/**
	 * @brief 获取指定行.
	 */
	constexpr VectorT<T, C> row(size_t index) const;

	/**
	 * @brief 获取指定列.
	 */
	constexpr VectorT<T, R> col(size_t index) const;

	/**
	 * @brief 获取行数.
	 */
	constexpr size_t rows() const;

	/**
	 * @brief 获取列数.
	 */
	constexpr size_t cols() const;

	/**
	 * @brief 平移变换.
	 *
	 * @param translation 平移量.
	 *
	 * @return *this.
	 */
	MatrixT& translate(const Vector3T<T>& translation);

	/**
	 * @brief 旋转变换.
	 *
	 * @param rotation 四元数.
	 *
	 * @return *this.
	 */
	MatrixT& rotate(const QuaternionT<T>& rotation);

	/**
	 * @brief 绕 X 轴旋转.
	 *
	 * @param angle 旋转角度, 单位: 弧度制.
	 *
	 * @return *this.
	 */
	MatrixT& rotateX(float angle);

	/**
	 * @brief 绕 Y 轴旋转.
	 *
	 * @param angle 旋转角度, 单位: 弧度制.
	 *
	 * @return *this.
	 */
	MatrixT& rotateY(float angle);

	/**
	 * @brief 绕 Z 轴旋转.
	 *
	 * @param angle 旋转角度, 单位: 弧度制.
	 *
	 * @return *this.
	 */
	MatrixT& rotateZ(float angle);

	/**
	 * @brief 缩放变换.
	 *
	 * @param scale 缩放量.
	 *
	 * @return *this.
	 */
	MatrixT& scale(const Vector3T<T>& scale);

	/**
	 * @brief 分解.
	 */
	void decompose(Vector3T<T>* translation, QuaternionT<T>* rotation, Vector3T<T>* scale) const;

	/**
	 * @brief 重组.
	 */
	MatrixT& recompose(const Vector3T<T>& translation, const QuaternionT<T>& rotation, const Vector3T<T>& scale);

	Vector3T<T> front() const;
	Vector3T<T> back() const;
	Vector3T<T> left() const;
	Vector3T<T> right() const;
	Vector3T<T> up() const;
	Vector3T<T> down() const;

	/**
	 * @brief 获取原始数据.
	 */
	constexpr T* data();
	constexpr const T* data() const;

	/**
	 * @brief 获取指定元素.
	 */
	constexpr T& operator()(size_t r, size_t c);
	constexpr const T& operator()(size_t r, size_t c) const;

	constexpr bool     operator==(const MatrixT&) const;
	constexpr MatrixT& operator+=(const MatrixT&);
	constexpr MatrixT& operator-=(const MatrixT&);
	MatrixT& operator*=(const MatrixT&);
	MatrixT& operator/=(const MatrixT&);
	constexpr MatrixT& operator*=(const T&);
	constexpr MatrixT& operator/=(const T&);
	constexpr MatrixT  operator-();

	constexpr MatrixT& operator=(const MatrixT&);

	template <typename T0>
	operator MatrixT<T0, R, C>()
	{
		MatrixT result;
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				result(r, c) = static_cast<T0>(*this(r, c));
		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, const MatrixT& mat)
	{
		size_t max = 0;
		for(size_t r = 0; r < R; r++)
		{
			for(size_t c = 0; c < C; c++)
			{

				std::ostringstream stm;
				stm << mat(r, c);
				const auto size = stm.str().size();
				max = std::max(max, size);
			}
		}
		max = std::min<size_t>(max, 6);

		for(size_t r = 0; r < R; r++)
		{
			for(size_t c = 0; c < C; c++)
			{
				std::ostringstream stm;
				stm.setf(std::ios::fixed);
				stm.precision(6);
				stm << mat(r, c);
				auto str = stm.str();
				str.erase(str.find_last_not_of('0') + 1);
				if(str.back() == '.')
					str.pop_back();
				stream.width(max);
				stream << str << ' ';
			}
			stream << '\n';
		}
		return stream;
	}

	/**
	 * @brief 生成平移变换矩阵.
	 *
	 * @param translation 平移向量. 指定了三个轴的变化量.
	 */
	static MatrixT createTranslate(const Vector3T<T>& translation);

	/**
	 * @brief 生成旋转变换矩阵.
	 *
	 * @param rotation 四元数.
	 */
	static MatrixT createRotation(const QuaternionT<T>& rotation);

	/**
	 * @brief 生成旋转变换矩阵.
	 *
	 * @param axis  旋转轴.
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotation(float angle, Vector3T<T> axis);

	/**
	 * @brief 生成绕 X 轴旋转变换矩阵.
	 *
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotationX(float angle);

	/**
	 * @brief 生成绕 Y 轴旋转变换矩阵.
	 *
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotationY(float angle);

	/**
	 * @brief 生成绕 Z 轴旋转变换矩阵.
	 *
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotationZ(float angle);

	/**
	 * @brief 生成缩放变换矩阵.
	 *
	 * @param scale 缩放向量. 指定了三个轴的缩放比.
	 */
	static MatrixT createScale(const Vector3T<T>& scale);

	/**
	 * @brief 生成透视投影矩阵.
	 *
	 * @param vFOV   垂直视角, 单位: 弧度.
	 * @param aspect 宽高比.
	 * @param near   近裁剪面.
	 * @param far    远裁剪面.
	 */
	static MatrixT<T, 4, 4> perspective(T vFOV, T aspect, T near, T far);

	/**
	 * @brief 生成正交投影矩阵.
	 *
	 * @param width  宽度.
	 * @param height 高度.
	 * @param near   近裁剪面.
	 * @param far    远裁剪面.
	 */
	static MatrixT<T, 4, 4> orthogonal(T width, T height, T near, T far);

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
	static MatrixT<T, 4, 4> orthogonal(T left, T right, T bottom, T top, T near, T far);

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
#if ROW_MANJOR
	T m_[R][C] = {};
#else
	T m_[C][R] = {};
#endif

	inline static const size_t rows_ = R;
	inline static const size_t cols_ = C;
};

#include "matrix.inl"

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

template <arithmetic T, size_t R, size_t C>
MatrixT<T, R, C> constexpr operator*(const MatrixT<T, R, C>& lhs, const T& rhs)
{
	return MatrixT(lhs) *= rhs;
}

template <arithmetic T, size_t R, size_t C>
MatrixT<T, R, C> constexpr operator/(const MatrixT<T, R, C>& lhs, const T& rhs)
{
	return MatrixT(lhs) /= rhs;
}

template <arithmetic T, size_t R, size_t C>
MatrixT<T, R, C> constexpr operator*(const T& lhs, const MatrixT<T, R, C>& rhs)
{
	return rhs * lhs;
}

template <arithmetic T, size_t R, size_t C>
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
 *
 * ```cpp
 * // 创建
 * Matrix2f m; // 创建一个 2x2 矩阵, 类型为 float, 初始值为 2x2 单位矩阵
 *
 * // 操作
 * m[0][1] = 4; // 设置第一行第二列的值为 4
 * m(1, 0) = 3; // 设置第二行第一列的值为 3
 * std::cout << m; // 输出矩阵, 结果为:
 *                 // 1 4
 *                 // 3 1
 * ```
 */
