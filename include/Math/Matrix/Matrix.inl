// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix.hpp"
#include "../Helper.hpp"
#include "../Assert.hpp"
#include <algorithm>

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
	assert(list.size() == rows() * cols(), "Initializers number not correct");
	auto it = list.begin();
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] = *it++;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::inverse()
{
	// TODO
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::inversed() const
{
	return MatrixT(*this).inverse();
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::transpose()
{
	static_assert(R == C, "only square matrix supports this operation");

	for(size_t r = 0; r < rows(); r++)
		for(size_t c = r; c < cols(); c++)
			std::swap(m_[r][c], m_[c][r]);
	return *this;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::transposed() const
{
	return MatrixT(*this).transpose();
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr T MatrixT<T, R, C>::trace() const
{
	static_assert(R == C, "only square matrix supports this operation");
	return diagonal().sum();
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr T MatrixT<T, R, C>::sum() const
{
	T result = T(0);
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			result += m_[r][c];
	return result;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr T MatrixT<T, R, C>::minCoeff() const
{
	T min = std::numeric_limits<T>::max();
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			if(m_[r][c] < min)
				min = m_[r][c];
	return min;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr T MatrixT<T, R, C>::maxCoeff() const
{
	T max = std::numeric_limits<T>::min();
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			if(m_[r][c] > max)
				max = m_[r][c];
	return max;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr const VectorT<T, R> MatrixT<T, R, C>::diagonal() const
{
	static_assert(R == C, "only square matrix supports this operation");
	VectorT<T, R> result;
	for(size_t n = 0; n < rows(); n++)
		result[n] = m_[n][n];
	return result;
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline void MatrixT<T, R, C>::decompose(Vector3T<T>* translation, Vector3T<T>* rotation, Vector3T<T>* scale) const
{
	// TODO
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::recompose(const Vector3T<T>& translation, const Vector3T<T>& rotation, const Vector3T<T>& scale)
{
	// TODO
	return *this;
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
inline constexpr T* MatrixT<T, R, C>::data()
{
	return &m_[0][0];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr const T* MatrixT<T, R, C>::data() const
{
	return &m_[0][0];
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr T& MatrixT<T, R, C>::operator()(size_t r, size_t c)
{
	assert(r < rows() && c < cols(), "subscript out of range");
	return m_[r][c];
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr const T& MatrixT<T, R, C>::operator()(size_t r, size_t c) const
{
	assert(r < rows() && c < cols(), "subscript out of range");
	return m_[r][c];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr T* MatrixT<T, R, C>::operator[](size_t row)
{
	assert(row < rows(), "subscript out of range");
	return m_[row];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr const T* MatrixT<T, R, C>::operator[](size_t row) const
{
	assert(row < rows(), "subscript out of range");
	return m_[row];
}

template <typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr bool MatrixT<T, R, C>::operator==(const MatrixT& rhs) const
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			if(!equal(m_[r][c], rhs.m_[r][c]))
				return false;
	return true;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator+=(const MatrixT& rhs)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] += rhs[r][c];
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator-=(const MatrixT& rhs)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] -= rhs[r][c];
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator*=(const MatrixT& rhs)
{
	// TODO
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator/=(const MatrixT& rhs)
{
	// TODO
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator*=(const T& v)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] *= v;
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator/=(const T& v)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] /= v;
	return *this;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline constexpr MatrixT<T, R, C> MatrixT<T, R, C>::operator-()
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
inline MatrixT<T, R, C> MatrixT<T, R, C>::rotation(const Vector3T<T>& axis, float angle)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	assert(axis == Vector3T<T>::unit_x || axis == Vector3T<T>::unit_y || axis == Vector3T<T>::unit_z);

	// TODO
	MatrixT result;
	return result;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::rotationX(float angle)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	const float sin = std::sin(angle);
	const float cos = std::cos(angle);

	Matrix4 result = Matrix4::identity();
	result[1][1] = cos;
	result[1][2] = sin;
	result[2][1] = -sin;
	result[2][2] = cos;
	return result;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::rotationY(float angle)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	const float sin = std::sin(angle);
	const float cos = std::cos(angle);

	Matrix4 result = Matrix4::identity();
	result[0][0] = cos;
	result[0][2] = sin;
	result[2][0] = -sin;
	result[2][2] = cos;
	return result;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::rotationZ(float angle)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	const float sin = std::sin(angle);
	const float cos = std::cos(angle);

	Matrix4 result = Matrix4::identity();
	result[0][0] = cos;
	result[0][1] = -sin;
	result[1][0] = sin;
	result[1][1] = cos;
	return result;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::scale(const Vector3T<T>& scale)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	MatrixT result;
	result[0][0] = scale.x;
	result[1][1] = scale.y;
	result[2][2] = scale.z;
	return result;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::perspective(T vFOV, T aspect, T n, T f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);
	assert(!equal(aspect, 0.f));
	assert(n != f);

	const auto tanHalfFOV = std::tan(vFOV / 2.f);

	auto mat = MatrixT<T, 4, 4>::zero();
	mat[0][0] = T(1) / (aspect * tanHalfFOV);
	mat[1][1] = T(1) / tanHalfFOV;
	mat[2][2] = f / (f - n);
	mat[2][3] = T(1);
	mat[3][2] = -(f * n) / (f - n);
	return mat;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::orthogonal(T w, T h, T n, T f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);

	return orthographic(-w / T(2), w / T(2), -h / T(2), h / T(2), n, f);
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::orthographic(T l, T r, T b, T t, T n, T f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);
	assert(!equal(l, r) && !equal(b, t) && !equal(n, f));

	auto mat = MatrixT<T, 4, 4>::zero();
	mat[0][0] = T(2) / (r - l);
	mat[1][1] = T(2) / (b - t);
	mat[2][2] = T(1) / (f - n);
	mat[3][0] = -(r + l) / (r - l);
	mat[3][1] = -(b + t) / (b - t);
	mat[3][2] = -n / (f - n);
	mat[3][3] = T(1);
	return mat;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::lookAt(const Vector3T<T>& eye, const Vector3T<T>& center, const Vector3T<T>& up)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);

	const Vector3T<T> w((center - eye).normalize());
	const Vector3T<T> u(w.cross(up).normalize());
	const Vector3T<T> v(w.cross(u));

	auto mat = MatrixT<T, 4, 4>::identity();
	mat[0][0] = u.x;
	mat[1][0] = u.y;
	mat[2][0] = u.z;
	mat[0][1] = v.x;
	mat[1][1] = v.y;
	mat[2][1] = v.z;
	mat[0][2] = w.x;
	mat[1][2] = w.y;
	mat[2][2] = w.z;
	mat[3][0] = -u.dot(eye);
	mat[3][1] = -v.dot(eye);
	mat[3][2] = -w.dot(eye);
	return mat;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::identity()
{
	static_assert(R == C, "only square matrix supports this operation");
	static MatrixT mat;
	return mat;
}

template<typename T, size_t R, size_t C> requires std::is_arithmetic_v<T>
inline MatrixT<T, R, C> MatrixT<T, R, C>::zero()
{
	if constexpr(R == C)
	{
		MatrixT mat;
		for(size_t r = 0; r < R; r++)
			for(size_t c = 0; c < C; c++)
				mat[r][c] = T(0);
		return mat;
	}
	else
		return MatrixT();
}
