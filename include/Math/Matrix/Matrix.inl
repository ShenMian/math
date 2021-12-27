﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix.hpp"
#include "../Helper.hpp"
#include "../Assert.hpp"

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>::MatrixT()
{
	if constexpr(R == C)
		for(size_t n = 0; n < R; n++)
			m_[n][n] = T(1);
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>::MatrixT(const std::initializer_list<T>& list)
{
	assert(list.size() == rows() * cols());
	auto it = list.begin();
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] = *it++;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::transpose()
{
	static_assert(R == C, "only square matrix supports this operation");

	return *this;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::transposed() const
{
	return MatrixT(*this).transpose();
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline T MatrixT<T, R, C>::trace() const
{
	static_assert(R == C, "only square matrix supports this operation");
	T result = T(0);
	for(size_t r = 0; r < rows(); r++)
		result += m_[r][r];
	return result;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline void MatrixT<T, R, C>::decompose(Vector3T<T>* translation, Vector3T<T>* rotation, Vector3T<T>* scale) const
{
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr size_t MatrixT<T, R, C>::rows() const
{
	return rows_;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr size_t MatrixT<T, R, C>::cols() const
{
	return cols_;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline T* MatrixT<T, R, C>::data()
{
	return &m_[0][0];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline const T* MatrixT<T, R, C>::data() const
{
	return &m_[0][0];
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline T& MatrixT<T, R, C>::operator()(size_t r, size_t c)
{
	assert(r < rows() && c < cols());
	return m_[r][c];
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline const T& MatrixT<T, R, C>::operator()(size_t r, size_t c) const
{
	assert(r < rows() && c < cols());
	return m_[r][c];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline T* MatrixT<T, R, C>::operator[](size_t row)
{
	assert(row < rows());
	return m_[row];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline const T* MatrixT<T, R, C>::operator[](size_t row) const
{
	assert(row < rows());
	return m_[row];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline bool MatrixT<T, R, C>::operator==(const MatrixT& rhs) const
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			if(!equal(m_[r][c], rhs.m_[r][c]))
				return false;
	return true;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator+=(const MatrixT& rhs)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] += rhs[r][c];
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator-=(const MatrixT& rhs)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] -= rhs[r][c];
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator*=(const MatrixT& rhs)
{
	// TODO: 在此处插入 return 语句
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator/=(const MatrixT& rhs)
{
	// TODO: 在此处插入 return 语句
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::operator-()
{
	MatrixT result;
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			result[r][c] = -m_[r][c];
	return result;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::translate(const Vector3T<T>& v)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	MatrixT result;
	result[0][3] = v.x;
	result[1][3] = v.y;
	result[2][3] = v.z;
	return result;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::perspective(float yFOV, float aspect, float n, float f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	assert(!equal(aspect, 0.f));
	assert(n != f);

	const float tanHalfFOV = std::tan(yFOV / 2.f);

	MatrixT mat;
	mat[0][0] = 1.f / (aspect * tanHalfFOV);
	mat[1][1] = 1.f / tanHalfFOV;
	mat[2][2] = f / (f - n);
	mat[2][3] = 1.f;
	mat[3][2] = -(f * n) / (f - n);
	return mat;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::lookAt(const Vector3T<T>& eye, const Vector3T<T>& center, const Vector3T<T>& up)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return MatrixT();
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::orthogonal(float w, float h, float n, float f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return MatrixT();
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::identity()
{
	static_assert(R == C, "only square matrix supports this operation");
	static MatrixT mat;
	return mat;
}