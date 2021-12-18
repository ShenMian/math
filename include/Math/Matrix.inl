// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix.hpp"
#include "Helper.hpp"
#include <cassert>

template <typename T, size_t R, size_t C>
inline MatrixT<T, R, C>::MatrixT()
{
	static_assert(R == C);
	for(size_t r = 0; r < R; r++)
		m_[r][r] = T(1);
}

template <typename T, size_t R, size_t C>
inline MatrixT<T, R, C>::MatrixT(const std::initializer_list<T>& list)
{
	assert(list.size() == R * C);
	auto it = list.begin();
	for(size_t r = 0; r < R; r++)
		for(size_t c = 0; c < C; c++, it++)
			m_[r][c] = *it;
}

template <typename T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::transpose()
{
	static_assert(R == C, "only square matrix supports this operation");

	return *this;
}

template <typename T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::transposed() const
{
	return MatrixT(*this).transpose();
}

template <typename T, size_t R, size_t C>
inline T MatrixT<T, R, C>::trace() const
{
	static_assert(R == C, "only square matrix supports this operation");
	T result = T(0);
	for(size_t r = 0; r < R; r++)
		result += m_[r][r];
	return result;
}

template <typename T, size_t R, size_t C>
inline void MatrixT<T, R, C>::decompose(Vector3T<T>* translation, Vector3T<T>* rotation, Vector3T<T>* scale) const
{
}

template <typename T, size_t R, size_t C>
inline T* MatrixT<T, R, C>::data()
{
	return m_;
}

template <typename T, size_t R, size_t C>
inline const T* MatrixT<T, R, C>::data() const
{
	return m_;
}

template <typename T, size_t R, size_t C>
inline T* MatrixT<T, R, C>::operator[](size_t row)
{
	assert(row < R);
	return m_[row];
}

template <typename T, size_t R, size_t C>
inline const T* MatrixT<T, R, C>::operator[](size_t row) const
{
	assert(row < R);
	return m_[row];
}

template <typename T, size_t R, size_t C>
inline bool MatrixT<T, R, C>::operator==(const MatrixT& rhs) const
{
	for(size_t r = 0; r < R; r++)
		for(size_t c = 0; c < C; c++)
			if(!equal(m_[r][c], rhs.m_[r][c]))
				return false;
	return true;
}

template <typename T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createTranslate(const Vector3T<T>& v)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	MatrixT result;
	result[0][3] = v.x;
	result[1][3] = v.y;
	result[2][3] = v.z;
	return result;
}

template<typename T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::perspective(float yFOV, float aspect, float n, float f)
{
	assert(std::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
	assert(aspect != 0 && n != f);

	const float tanHalfFOV = std::tan(yFOV / 2.f);

	Matrix4 mat;
	mat.m[0][0] = 1.f / (aspect * tanHalfFOV);
	mat.m[1][1] = 1.f / tanHalfFOV;
	mat.m[2][2] = f / (f - n);
	mat.m[2][3] = 1.f;
	mat.m[3][2] = -(f * n) / (f - n);
	return mat;
}

template<typename T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::orthogonal(float w, float h, float n, float f)
{
	return MatrixT();
}
