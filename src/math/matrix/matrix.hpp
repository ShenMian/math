// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "../check.hpp"
#include "../helper.hpp"
#include "../simd.hpp"
#include "../vector/vector3.hpp"
#include "../vector/vector4.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
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
	MatrixT()
	{
		if constexpr(R == C)
			for(size_t n = 0; n < R; n++)
				m_[n][n] = T(1);
	}

	/**
	 * @brief 构造函数.
	 *
	 * @param list 初始化列表.
	 */
	MatrixT(const std::initializer_list<T>& list)
	{
		check(list.size() == rows() * cols(), "initializers number not correct");
		auto it = list.begin();
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				m_[r][c] = *it++;
	}

	/**
	 * @brief 构造函数.
	 */
	constexpr explicit MatrixT(const T (&arr)[R * C])
	{
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				m_[r][c] = arr[r * cols() + c];
	}

	/**
	 * @brief 构造函数.
	 */
	constexpr explicit MatrixT(const T* data)
	{
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				m_[r][c] = data[r * cols() + c];
	}

	/**
	 * @brief 求逆.
	 */
	MatrixT& inverse()
	{
		// TODO
		check(false);
		return *this;
	}

	/**
	 * @brief 获取逆矩阵.
	 */
	MatrixT<T, R, C> inversed() const { return MatrixT(*this).inverse(); }

	/**
	 * @brief 转置.
	 */
	MatrixT& transpose()
	{
		static_assert(R == C, "only square matrix supports this operation");

		if constexpr(R == C && R == 4)
		{
			__m128 m[4];
			simd::loadu(m, data());
			simd::transpose(m, m);
			simd::storeu(data(), m);
		}
		else
		{
			for(size_t r = 0; r < rows(); r++)
				for(size_t c = r; c < cols(); c++)
					std::swap(m_[r][c], m_[c][r]);
		}
		return *this;
	}


	/**
	 * @brief 获取转置后的矩阵.
	 */
	MatrixT<T, R, C> transposed() const { return MatrixT(*this).transpose(); }

	/**
	 * @brief 求迹.
	 */
	constexpr T trace() const
	{
		static_assert(R == C, "only square matrix supports this operation");
		return diagonal().sum();
	}

	/**
	 * @brief 获取所有元素之和.
	 */
	constexpr T sum() const
	{
		const auto& mat    = *this;
		T           result = T(0);
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				result += mat(r, c);
		return result;
	}

	/**
	 * @brief 获取最小元素的值.
	 */
	constexpr T minCoeff() const
	{
		const auto& mat = *this;
		T           min = std::numeric_limits<T>::max();
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				if(mat(r, c) < min)
					min = mat(r, c);
		return min;
	}

	/**
	 * @brief 获取最大元素的值.
	 */
	constexpr T maxCoeff() const
	{
		const auto& mat = *this;
		T           max = std::numeric_limits<T>::min();
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				if(mat(r, c) > max)
					max = mat(r, c);
		return max;
	}

	/**
	 * @brief 获取行列式的值.
	 */
	constexpr T determinant() const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		const auto& mat = *this;
		const float a0  = mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);
		const float a1  = mat(0, 0) * mat(1, 2) - mat(0, 2) * mat(1, 0);
		const float a2  = mat(0, 0) * mat(1, 3) - mat(0, 3) * mat(1, 0);
		const float a3  = mat(0, 1) * mat(1, 2) - mat(0, 2) * mat(1, 1);
		const float a4  = mat(0, 1) * mat(1, 3) - mat(0, 3) * mat(1, 1);
		const float a5  = mat(0, 2) * mat(1, 3) - mat(0, 3) * mat(1, 2);
		const float b0  = mat(2, 0) * mat(3, 1) - mat(2, 1) * mat(3, 0);
		const float b1  = mat(2, 0) * mat(3, 2) - mat(2, 2) * mat(3, 0);
		const float b2  = mat(2, 0) * mat(3, 3) - mat(2, 3) * mat(3, 0);
		const float b3  = mat(2, 1) * mat(3, 2) - mat(2, 2) * mat(3, 1);
		const float b4  = mat(2, 1) * mat(3, 3) - mat(2, 3) * mat(3, 1);
		const float b5  = mat(2, 2) * mat(3, 3) - mat(2, 3) * mat(3, 2);
		return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
	}

	/**
	 * @brief 获取主对角线.
	 */
	constexpr VectorT<T, R> diagonal() const
	{
		static_assert(R == C, "only square matrix supports this operation");
		VectorT<T, R> result;
		for(size_t n = 0; n < rows(); n++)
			result[n] = m_[n][n];
		return result;
	}

	/**
	 * @brief 获取指定行.
	 */
	constexpr VectorT<T, C> row(size_t index) const
	{
		check(index < R);

		VectorT<T, C> vec;
		for(size_t i = 0; i < C; i++)
			vec[i] = (*this)(index, i);
		return vec;
	}

	/**
	 * @brief 获取指定列.
	 */
	constexpr VectorT<T, R> col(size_t index) const
	{
		check(index < C);

		auto&         mat = *this;
		VectorT<T, R> vec;
		for(size_t i = 0; i < R; i++)
			vec[i] = mat(i, index);
		return vec;
	}

	/**
	 * @brief 获取行数.
	 */
	constexpr size_t rows() const { return rows_; }

	/**
	 * @brief 获取列数.
	 */
	constexpr size_t cols() const { return cols_; }

	/**
	 * @brief 平移变换.
	 *
	 * @param translation 平移量.
	 *
	 * @return *this.
	 */
	MatrixT& translate(const Vector3T<T>& v)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		auto& mat = *this;
		mat(3, 0) += v.x;
		mat(3, 1) += v.y;
		mat(3, 2) += v.z;
		return *this;
	}

	/**
	 * @brief 旋转变换.
	 *
	 * @param rotation 四元数.
	 *
	 * @return *this.
	 */
	MatrixT& rotate(const QuaternionT<T>& rotation)
	{
		auto& mat = *this;
		mat *= MatrixT::createRotation(rotation);
		return *this;
	}

	/**
	 * @brief 绕 X 轴旋转.
	 *
	 * @param angle 旋转角度, 单位: 弧度制.
	 *
	 * @return *this.
	 */
	MatrixT& rotateX(float angle)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		auto& mat = *this;

		const auto cos = std::cos(angle);
		const auto sin = std::sin(angle);

		const auto m01 = mat(0, 1);
		const auto m11 = mat(1, 1);
		const auto m21 = mat(2, 1);

		mat(0, 1) = mat(0, 1) * cos + mat(0, 2) * sin;
		mat(1, 1) = mat(1, 1) * cos + mat(1, 2) * sin;
		mat(2, 1) = mat(2, 1) * cos + mat(2, 2) * sin;

		mat(0, 2) = mat(0, 2) * cos - m01 * sin;
		mat(1, 2) = mat(1, 2) * cos - m11 * sin;
		mat(2, 2) = mat(2, 2) * cos - m21 * sin;

		return *this;
	}

	/**
	 * @brief 绕 Y 轴旋转.
	 *
	 * @param angle 旋转角度, 单位: 弧度制.
	 *
	 * @return *this.
	 */
	MatrixT& rotateY(float angle)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		auto& mat = *this;

		const auto cos = std::cos(angle);
		const auto sin = std::sin(angle);

		const auto m00 = mat(0, 0);
		const auto m10 = mat(1, 0);
		const auto m20 = mat(2, 0);

		mat(0, 0) = mat(0, 0) * cos - mat(0, 2) * sin;
		mat(1, 0) = mat(1, 0) * cos - mat(1, 2) * sin;
		mat(2, 0) = mat(2, 0) * cos - mat(2, 2) * sin;

		mat(0, 2) = m00 * sin - mat(0, 2) * cos;
		mat(1, 2) = m10 * sin - mat(1, 2) * cos;
		mat(2, 2) = m20 * sin - mat(2, 2) * cos;

		return *this;
	}

	/**
	 * @brief 绕 Z 轴旋转.
	 *
	 * @param angle 旋转角度, 单位: 弧度制.
	 *
	 * @return *this.
	 */
	MatrixT& rotateZ(float angle)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		auto& mat = *this;

		const auto cos = std::cos(angle);
		const auto sin = std::sin(angle);

		const auto m00 = mat(0, 0);
		const auto m10 = mat(1, 0);
		const auto m20 = mat(2, 0);

		mat(0, 0) = mat(0, 0) * cos + mat(0, 1) * sin;
		mat(1, 0) = mat(1, 0) * cos + mat(1, 1) * sin;
		mat(2, 0) = mat(2, 0) * cos + mat(2, 1) * sin;

		mat(0, 1) = mat(0, 1) * cos - m00 * sin;
		mat(1, 1) = mat(1, 1) * cos - m10 * sin;
		mat(2, 1) = mat(2, 1) * cos - m20 * sin;

		return *this;
	}

	/**
	 * @brief 缩放变换.
	 *
	 * @param scale 缩放量.
	 *
	 * @return *this.
	 */
	MatrixT& scale(const Vector3T<T>& scale)
	{
		auto& mat = *this;
		mat(0, 0) *= scale.x;
		mat(1, 1) *= scale.y;
		mat(2, 2) *= scale.z;
		return *this;
	}

	/**
	 * @brief 分解.
	 */
	void decompose(Vector3T<T>* translation, QuaternionT<T>* rotation, Vector3T<T>* scale) const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		auto& mat = *this;
		if(translation)
		{
			translation->x = mat(3, 0);
			translation->y = mat(3, 1);
			translation->z = mat(3, 2);
		}

		if(scale == nullptr && rotation == nullptr)
			return;

		auto axisX  = Vector3T<T>(mat(0, 0), mat(0, 1), mat(0, 2));
		auto axisY  = Vector3T<T>(mat(1, 0), mat(1, 1), mat(1, 2));
		auto axisZ  = Vector3T<T>(mat(2, 0), mat(2, 1), mat(2, 2));
		auto scaleX = axisX.norm();
		auto scaleY = axisY.norm();
		auto scaleZ = axisZ.norm();
		if(determinant() < 0)
			scaleZ = -scaleZ;

		if(scale)
		{
			scale->x = scaleX;
			scale->y = scaleY;
			scale->z = scaleZ;
		}

		if(rotation)
		{
			if(scaleX < std::numeric_limits<T>::epsilon() || scaleY < std::numeric_limits<T>::epsilon() ||
			   scaleZ < std::numeric_limits<T>::epsilon())
				return; // 除数过于接近 0, 无法完成计算

			axisX.normalize();
			axisY.normalize();
			axisZ.normalize();
			const float trace = axisX.x + axisY.y + axisZ.z + 1.0f;

			if(trace > std::numeric_limits<T>::epsilon())
			{
				const float s = 0.5f / std::sqrt(trace);
				rotation->w   = 0.25f / s;
				rotation->x   = (axisY.z - axisZ.y) * s;
				rotation->y   = (axisZ.x - axisX.z) * s;
				rotation->z   = (axisX.y - axisY.x) * s;
			}
			else
			{
				if(axisX.x > axisY.y && axisX.x > axisZ.z)
				{
					const float s = 0.5f / std::sqrt(1.0f + axisX.x - axisY.y - axisZ.z);
					rotation->w   = (axisY.z - axisZ.y) * s;
					rotation->x   = 0.25f / s;
					rotation->y   = (axisY.x + axisX.y) * s;
					rotation->z   = (axisZ.x + axisX.z) * s;
				}
				else if(axisY.y > axisZ.z)
				{
					const float s = 0.5f / std::sqrt(1.0f + axisY.y - axisX.x - axisZ.z);
					rotation->w   = (axisZ.x - axisX.z) * s;
					rotation->x   = (axisY.x + axisX.y) * s;
					rotation->y   = 0.25f / s;
					rotation->z   = (axisZ.y + axisY.z) * s;
				}
				else
				{
					const float s = 0.5f / std::sqrt(1.0f + axisZ.z - axisX.x - axisY.y);
					rotation->w   = (axisX.y - axisY.x) * s;
					rotation->x   = (axisZ.x + axisX.z) * s;
					rotation->y   = (axisZ.y + axisY.z) * s;
					rotation->z   = 0.25f / s;
				}
			}
		}
	}

	/**
	 * @brief 重组.
	 */
	MatrixT& recompose(const Vector3T<T>& translation, const QuaternionT<T>& rotation, const Vector3T<T>& scale)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		auto& mat = *this;
		mat       = MatrixT::identity();
		mat.translate(translation);
		mat.rotate(rotation);
		mat.scale(scale);
		return *this;
	}

	Vector3T<T> front() const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		return -back();
	}

	Vector3T<T> back() const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		const auto& mat = *this;
		return {mat(2, 0), mat(2, 1), mat(2, 2)};
	}

	Vector3T<T> left() const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		return -right();
	}

	Vector3T<T> right() const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		const auto& mat = *this;
		return {mat(0, 0), mat(0, 1), mat(0, 2)};
	}
	Vector3T<T> up() const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		const auto& mat = *this;
		return {mat(1, 0), mat(1, 1), mat(1, 2)};
	}

	Vector3T<T> down() const
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		return -up();
	}

	/**
	 * @brief 获取原始数据.
	 */
	constexpr T*       data() { return &m_[0][0]; }
	constexpr const T* data() const { return &m_[0][0]; }

	/**
	 * @brief 获取指定元素.
	 */
	constexpr T& operator()(size_t r, size_t c)
	{
		check(r < rows() && c < cols(), "subscript out of range");
#if ROW_MANJOR
		return m_[r][c];
#else
		return m_[c][r];
#endif
	}

	constexpr const T& operator()(size_t r, size_t c) const
	{
		check(r < rows() && c < cols(), "subscript out of range");
#if ROW_MANJOR
		return m_[r][c];
#else
		return m_[c][r];
#endif
	}

	constexpr bool operator==(const MatrixT& rhs) const
	{
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				if(!equal(m_[r][c], rhs.m_[r][c]))
					return false;
		return true;
	}

	constexpr MatrixT& operator+=(const MatrixT& rhs)
	{
		if constexpr(R == C && R == 4)
		{
			__m128 m1[4];
			__m128 m2[4];
			simd::loadu(m1, data());
			simd::loadu(m2, rhs.data());
			simd::add(m1, m2, m1);
			simd::storeu(data(), m1);
		}
		else
		{
			for(size_t r = 0; r < rows(); r++)
				for(size_t c = 0; c < cols(); c++)
					(*this)(r, c) += rhs(r, c);
		}
		return *this;
	}
	constexpr MatrixT& operator-=(const MatrixT& rhs)
	{
		if constexpr(R == C && R == 4)
		{
			__m128 m1[4];
			__m128 m2[4];
			simd::loadu(m1, data());
			simd::loadu(m2, rhs.data());
			simd::sub(m1, m2, m1);
			simd::storeu(data(), m1);
		}
		else
		{
			for(size_t r = 0; r < rows(); r++)
				for(size_t c = 0; c < cols(); c++)
					(*this)(r, c) -= rhs(r, c);
		}
		return *this;
	}

	MatrixT& operator*=(const MatrixT& rhs)
	{
		if constexpr(R == C && R == 4)
		{
			__m128 m1[4];
			__m128 m2[4];
			simd::loadu(m1, data());
			simd::loadu(m2, rhs.data());
			simd::mul(m1, m2, m1);
			simd::storeu(data(), m1);
		}
		else
			check(false);
		return *this;
	}

	MatrixT& operator/=(const MatrixT& rhs)
	{
		// TODO
		check(false);
		return *this;
	}

	constexpr MatrixT& operator*=(const T& rhs)
	{
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				m_[r][c] *= rhs;
		return *this;
	}

	constexpr MatrixT& operator/=(const T& rhs)
	{
		for(size_t r = 0; r < rows(); r++)
			for(size_t c = 0; c < cols(); c++)
				m_[r][c] /= rhs;
		return *this;
	}

	constexpr MatrixT operator-()
	{
		MatrixT result;
		if constexpr(R == C && R == 4)
		{
			__m128 m[4];
			simd::loadu(m, data());
			simd::negate(m, m);
			simd::storeu(result.data(), m);
		}
		else
		{
			for(size_t r = 0; r < rows(); r++)
				for(size_t c = 0; c < cols(); c++)
					result[r][c] = -m_[r][c];
		}
		return result;
	}

	constexpr MatrixT& operator=(const MatrixT& rhs)
	{
		if(rhs == *this)
			return *this;
		std::memcpy(m_, rhs.m_, sizeof(m_));
		return *this;
	}


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
				max             = std::max(max, size);
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
	static MatrixT createTranslate(const Vector3T<T>& v)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		MatrixT mat;
		mat(3, 0) = v.x;
		mat(3, 1) = v.y;
		mat(3, 2) = v.z;
		return mat;
	}

	/**
	 * @brief 生成旋转变换矩阵.
	 *
	 * @param rotation 四元数.
	 */
	static MatrixT createRotation(const QuaternionT<T>& q)
	{
		float x2 = q.x + q.x;
		float y2 = q.y + q.y;
		float z2 = q.z + q.z;

		float xx2 = q.x * x2;
		float yy2 = q.y * y2;
		float zz2 = q.z * z2;
		float xy2 = q.x * y2;
		float xz2 = q.x * z2;
		float yz2 = q.y * z2;
		float wx2 = q.w * x2;
		float wy2 = q.w * y2;
		float wz2 = q.w * z2;

		MatrixT mat;
		mat(0, 0) = 1.0f - yy2 - zz2;
		mat(0, 1) = xy2 + wz2;
		mat(0, 2) = xz2 - wy2;

		mat(1, 0) = xy2 - wz2;
		mat(1, 1) = 1.0f - xx2 - zz2;
		mat(1, 2) = yz2 + wx2;

		mat(2, 0) = xz2 + wy2;
		mat(2, 1) = yz2 - wx2;
		mat(2, 2) = 1.0f - xx2 - yy2;
		return mat;
	}

	/**
	 * @brief 生成旋转变换矩阵.
	 *
	 * @param axis  旋转轴.
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotation(float angle, Vector3T<T> axis)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		check(axis == Vector3T<T>::unit_x || axis == Vector3T<T>::unit_y || axis == Vector3T<T>::unit_z);

		axis.normalize();
		const float x = axis.x;
		const float y = axis.y;
		const float z = axis.z;

		const float sin = std::sin(angle);
		const float cos = std::cos(angle);
		const float t   = 1.0f - cos;
		const float tx  = t * x;
		const float ty  = t * y;
		const float tz  = t * z;
		const float txy = tx * y;
		const float txz = tx * z;
		const float tyz = ty * z;
		const float sx  = sin * x;
		const float sy  = sin * y;
		const float sz  = sin * z;

		auto mat  = MatrixT::identity();
		mat(0, 0) = cos + tx * x;
		mat(0, 1) = txy + sz;
		mat(0, 2) = txz - sy;

		mat(1, 0) = txy - sz;
		mat(1, 1) = cos + ty * y;
		mat(1, 2) = tyz + sx;

		mat(2, 0) = txz + sy;
		mat(2, 1) = tyz - sx;
		mat(2, 2) = cos + tz * z;
		return mat;
	}
	/**
	 * @brief 生成绕 X 轴旋转变换矩阵.
	 *
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotationX(float angle)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		const float sin = std::sin(angle);
		const float cos = std::cos(angle);

		auto mat  = MatrixT::identity();
		mat(1, 1) = cos;
		mat(1, 2) = sin;
		mat(2, 1) = -sin;
		mat(2, 2) = cos;
		return mat;
	}

	/**
	 * @brief 生成绕 Y 轴旋转变换矩阵.
	 *
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotationY(float angle)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		const float sin = std::sin(angle);
		const float cos = std::cos(angle);

		auto mat  = MatrixT::identity();
		mat(0, 0) = cos;
		mat(0, 2) = sin;
		mat(2, 0) = -sin;
		mat(2, 2) = cos;
		return mat;
	}

	/**
	 * @brief 生成绕 Z 轴旋转变换矩阵.
	 *
	 * @param angle 旋转角度, 单位: 弧度.
	 */
	static MatrixT createRotationZ(float angle)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		const float sin = std::sin(angle);
		const float cos = std::cos(angle);

		auto mat  = MatrixT::identity();
		mat(0, 0) = cos;
		mat(0, 1) = -sin;
		mat(1, 0) = sin;
		mat(1, 1) = cos;
		return mat;
	}

	/**
	 * @brief 生成缩放变换矩阵.
	 *
	 * @param scale 缩放向量. 指定了三个轴的缩放比.
	 */
	static MatrixT createScale(const Vector3T<T>& scale)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

		MatrixT mat;
		mat(0, 0) = scale.x;
		mat(1, 1) = scale.y;
		mat(2, 2) = scale.z;
		return mat;
	}

	/**
	 * @brief 生成透视投影矩阵.
	 *
	 * @param vFOV   垂直视角, 单位: 弧度.
	 * @param aspect 宽高比.
	 * @param near   近裁剪面.
	 * @param far    远裁剪面.
	 */
	static MatrixT<T, 4, 4> perspective(T vFOV, T aspect, T near, T far)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		static_assert(std::is_floating_point_v<T>);
		check(!equal(aspect, 0.f));
		check(near != far);

		const auto tanHalfFOV = std::tan(vFOV / 2.f);

		auto mat  = MatrixT::identity();
		mat(0, 0) = T(1) / (aspect * tanHalfFOV);
		mat(1, 1) = T(1) / tanHalfFOV;
		mat(2, 2) = far / (far - near);
		mat(2, 3) = T(1);
		mat(3, 2) = -(far * near) / (far - near);
		return mat;
	}

	/**
	 * @brief 生成正交投影矩阵.
	 *
	 * @param width  宽度.
	 * @param height 高度.
	 * @param near   近裁剪面.
	 * @param far    远裁剪面.
	 */
	static MatrixT<T, 4, 4> orthogonal(T width, T height, T near, T far)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		static_assert(std::is_floating_point_v<T>);

		return orthogonal(-width / T(2), width / T(2), -height / T(2), height / T(2), near, far);
	}

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
	static MatrixT<T, 4, 4> orthogonal(T left, T right, T bottom, T top, T near, T far)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		static_assert(std::is_floating_point_v<T>);
		check(!equal(left, right) && !equal(bottom, top) && !equal(near, far));

		auto mat  = MatrixT::zero();
		mat(0, 0) = T(2) / (right - left);
		mat(1, 1) = T(2) / (bottom - top);
		mat(2, 2) = T(1) / (far - near);
		mat(3, 0) = -(right + left) / (right - left);
		mat(3, 1) = -(bottom + top) / (bottom - top);
		mat(3, 2) = -near / (far - near);
		mat(3, 3) = T(1);
		return mat;
	}

	/**
	 * @brief 生成视图矩阵.
	 *
	 * @param eye    观察者位置.
	 * @param target 目标的位置.
	 * @param up     观察者向上的方向.
	 */
	static MatrixT<T, 4, 4> lookAt(const Vector3T<T>& eye, const Vector3T<T>& target,
	                               const Vector3T<T>& up = Vector3T<T>::up)
	{
		static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
		static_assert(std::is_floating_point_v<T>);

		Vector3T<T> f((target - eye).normalize()); // front
		Vector3T<T> u(up.normalized());            // up
		Vector3T<T> r(f.cross(up).normalize());    // right
		u = r.cross(f);

		auto mat = MatrixT::identity();

		mat(0, 0) = r.x;
		mat(1, 0) = r.y;
		mat(2, 0) = r.z;

		mat(0, 1) = u.x;
		mat(1, 1) = u.y;
		mat(2, 1) = u.z;

		mat(0, 2) = -f.x;
		mat(1, 2) = -f.y;
		mat(2, 2) = -f.z;

		mat(3, 0) = -r.dot(eye);
		mat(3, 1) = -u.dot(eye);
		mat(3, 2) = f.dot(eye);

		return mat;
	}

	/**
	 * @brief 获取单位矩阵.
	 */
	static MatrixT identity()
	{
		static_assert(R == C, "only square matrix supports this operation");
		static MatrixT mat;
		return mat;
	}

	/**
	 * @brief 获取零矩阵.
	 */
	static MatrixT zero()
	{
		if constexpr(R == C)
		{
			MatrixT mat;
			for(size_t r = 0; r < R; r++)
				for(size_t c = 0; c < C; c++)
					mat(r, c) = T(0);
			return mat;
		}
		else
			return MatrixT();
	}

private:
#if ROW_MANJOR
	T m_[R][C] = {};
#else
	T m_[C][R] = {};
#endif

	inline static const size_t rows_ = R;
	inline static const size_t cols_ = C;
};

template <size_t R, size_t C>
using Matrixf = MatrixT<float, R, C>;

template <size_t R, size_t C>
using Matrixd = MatrixT<double, R, C>;

template <size_t R, size_t C>
using Matrixi = MatrixT<int32_t, R, C>;

#define DEF_MATRIX_NxN(n)                                                                                              \
	template <typename T>                                                                                              \
	using Matrix##n##T = MatrixT<T, n, n>;                                                                             \
	using Matrix##n    = Matrix##n##T<float>;                                                                          \
	using Matrix##n##f = Matrix##n##T<float>;                                                                          \
	using Matrix##n##d = Matrix##n##T<double>;

DEF_MATRIX_NxN(2);
DEF_MATRIX_NxN(3);
DEF_MATRIX_NxN(4);

#undef DEF_MATRIX_NxN

template <typename T, size_t R, size_t C>
    requires std::is_arithmetic_v<T>
constexpr MatrixT<T, R, C> operator+(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
{
	return MatrixT(lhs) += rhs;
}

template <typename T, size_t R, size_t C>
    requires std::is_arithmetic_v<T>
constexpr MatrixT<T, R, C> operator-(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
{
	return MatrixT(lhs) -= rhs;
}

template <typename T, size_t R, size_t C>
    requires std::is_arithmetic_v<T>
constexpr MatrixT<T, R, C> operator*(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
{
	return MatrixT(lhs) *= rhs;
}

template <typename T, size_t R, size_t C>
    requires std::is_arithmetic_v<T>
constexpr MatrixT<T, R, C> operator/(const MatrixT<T, R, C>& lhs, const MatrixT<T, R, C>& rhs)
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

inline Vector4f operator*(const MatrixT<float, 4, 4>& mat, const Vector4f& vec)
{
	Vector4f result;

	__m128 m[4];
	__m128 v = {};
	simd::loadu(m, mat.data());
	simd::loadu(v, vec.data());
	simd::matrixMulVec(m, v, v);
	simd::storeu(result.data(), v);

	return result;
}

inline Vector4f& operator*=(Vector4f& vec, const MatrixT<float, 4, 4>& mat)
{
	vec = mat * vec;
	return vec;
}

inline Vector4f operator*(const Vector4f& vec, const MatrixT<float, 4, 4>& mat)
{
	return mat * vec;
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
