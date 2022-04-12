// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix.hpp"
#include "../Assert.hpp"
#include "../Helper.hpp"
#include "../SIMD.hpp"
#include <algorithm>

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>::MatrixT()
{
	if constexpr(R == C)
		for(size_t n = 0; n < R; n++)
			m_[n][n] = T(1);
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>::MatrixT(const std::initializer_list<T>& list)
{
	assert(list.size() == rows() * cols(), "Initializers number not correct");
	auto it = list.begin();
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] = *it++;
}

template <arithmetic T, size_t R, size_t C>
constexpr MatrixT<T, R, C>::MatrixT(const T (&arr)[R * C])
{
    for(size_t r = 0; r < rows(); r++)
        for(size_t c = 0; c < cols(); c++)
            m_[r][c] = arr[r * cols() + c];
}

template<arithmetic T, size_t R, size_t C>
constexpr MatrixT<T, R, C>::MatrixT(const T *data)
{
    for(size_t r = 0; r < rows(); r++)
        for(size_t c = 0; c < cols(); c++)
            m_[r][c] = data[r * cols() + c];
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::inverse()
{
	// TODO
	assert(false);
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::inversed() const
{
	return MatrixT(*this).inverse();
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::transpose()
{
	static_assert(R == C, "only square matrix supports this operation");

	for(size_t r = 0; r < rows(); r++)
		for(size_t c = r; c < cols(); c++)
			std::swap(m_[r][c], m_[c][r]);
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::transposed() const
{
	return MatrixT(*this).transpose();
}

template <arithmetic T, size_t R, size_t C>
inline constexpr T MatrixT<T, R, C>::trace() const
{
	static_assert(R == C, "only square matrix supports this operation");
	return diagonal().sum();
}

template <arithmetic T, size_t R, size_t C>
inline constexpr T MatrixT<T, R, C>::sum() const
{
	const auto& mat = *this;
	T result = T(0);
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			result += mat(r, c);
	return result;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr T MatrixT<T, R, C>::minCoeff() const
{
	const auto& mat = *this;
	T min = std::numeric_limits<T>::max();
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			if(mat(r, c) < min)
				min = mat(r, c);
	return min;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr T MatrixT<T, R, C>::maxCoeff() const
{
	const auto& mat = *this;
	T max = std::numeric_limits<T>::min();
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			if(mat(r, c) > max)
				max = mat(r, c);
	return max;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr const VectorT<T, R> MatrixT<T, R, C>::diagonal() const
{
	static_assert(R == C, "only square matrix supports this operation");
	VectorT<T, R> result;
	for(size_t n = 0; n < rows(); n++)
		result[n] = m_[n][n];
	return result;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::translate(const Vector3T<T>& v)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	auto& mat = *this;
	mat(3, 0) += v.x;
	mat(3, 1) += v.y;
	mat(3, 2) += v.z;
	return *this;
}

template<arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::rotate(const QuaternionT<T>& rotation)
{
	auto& mat = *this;
	mat *= MatrixT::createRotation(rotation);
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::rotateX(float angle)
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

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::rotateY(float angle)
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

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::rotateZ(float angle)
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

template <arithmetic T, size_t R, size_t C>
MatrixT<T, R, C> &MatrixT<T, R, C>::scale(const Vector3T<T> &scale)
{
    auto& mat = *this;
    mat(0, 0) *= scale.x;
    mat(1, 1) *= scale.y;
    mat(2, 2) *= scale.z;
    return *this;
}

template <arithmetic T, size_t R, size_t C>
inline void MatrixT<T, R, C>::decompose(Vector3T<T>& translation, QuaternionT<T>& rotation, Vector3T<T>& scale) const
{
    static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	// TODO
	assert(false);
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::recompose(const Vector3T<T>& translation, const QuaternionT<T>& rotation, const Vector3T<T>& scale)
{
    static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	auto& mat = *this;
    mat.translate(translation);
	mat.rotate(rotation);
    mat.scale(scale);
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr VectorT<T, C> MatrixT<T, R, C>::row(size_t index) const
{
	assert(index < R);

	VectorT<T, C> vec;
	for(size_t i = 0; i < C; i++)
		vec[i] = (*this)(index, i);
	return vec;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr VectorT<T, R> MatrixT<T, R, C>::col(size_t index) const
{
	assert(index < C);

	auto& mat = *this;
	VectorT<T, R> vec;
	for(size_t i = 0; i < R; i++)
		vec[i] = mat(i, index);
	return vec;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr size_t MatrixT<T, R, C>::rows() const
{
	return rows_;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr size_t MatrixT<T, R, C>::cols() const
{
	return cols_;
}

template <arithmetic T, size_t R, size_t C>
inline Vector3T<T> MatrixT<T, R, C>::front() const
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return -back();
}

template <arithmetic T, size_t R, size_t C>
inline Vector3T<T> MatrixT<T, R, C>::back() const
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return {(*this)(2, 0), (*this)(2, 1), (*this)(2, 2)};
}

template <arithmetic T, size_t R, size_t C>
inline Vector3T<T> MatrixT<T, R, C>::left() const
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return -right();
}

template <arithmetic T, size_t R, size_t C>
inline Vector3T<T> MatrixT<T, R, C>::right() const
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return {(*this)(0, 0), (*this)(0, 1), (*this)(0, 2)};
}

template <arithmetic T, size_t R, size_t C>
inline Vector3T<T> MatrixT<T, R, C>::up() const
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return {(*this)(1, 0), (*this)(1, 1), (*this)(1, 2)};
}

template <arithmetic T, size_t R, size_t C>
inline Vector3T<T> MatrixT<T, R, C>::down() const
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	return -up();
}

template <arithmetic T, size_t R, size_t C>
inline constexpr T* MatrixT<T, R, C>::data()
{
	return &m_[0][0];
}

template <arithmetic T, size_t R, size_t C>
inline constexpr const T* MatrixT<T, R, C>::data() const
{
	return &m_[0][0];
}

template <arithmetic T, size_t R, size_t C>
inline constexpr T& MatrixT<T, R, C>::operator()(size_t r, size_t c)
{
	assert(r < rows() && c < cols(), "subscript out of range");
#if ROW_MANJOR
		return m_[r][c];
#else
		return m_[c][r];
#endif
}

template <arithmetic T, size_t R, size_t C>
inline constexpr const T& MatrixT<T, R, C>::operator()(size_t r, size_t c) const
{
	assert(r < rows() && c < cols(), "subscript out of range");
#if ROW_MANJOR
	return m_[r][c];
#else
	return m_[c][r];
#endif
}

template <arithmetic T, size_t R, size_t C>
inline constexpr bool MatrixT<T, R, C>::operator==(const MatrixT& rhs) const
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			if(!equal(m_[r][c], rhs.m_[r][c]))
				return false;
	return true;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator+=(const MatrixT& rhs)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			(*this)(r, c) += rhs(r, c);
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator-=(const MatrixT& rhs)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			(*this)(r, c) -= rhs(r, c);
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator*=(const MatrixT& rhs)
{
	if constexpr(R == C && R == 4)
	{
		__m128 m1[4];
		__m128 m2[4];
		simd::load(m1, data());
		simd::load(m2, rhs.data());
		simd::matrixMul(m1, m2, m1);
		simd::store(data(), m1);
	}
	else
	{
		// TODO
		assert(false);
	}
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C>& MatrixT<T, R, C>::operator/=(const MatrixT& rhs)
{
	// TODO
	assert(false);
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator*=(const T& v)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] *= v;
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr MatrixT<T, R, C>& MatrixT<T, R, C>::operator/=(const T& v)
{
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			m_[r][c] /= v;
	return *this;
}

template <arithmetic T, size_t R, size_t C>
inline constexpr MatrixT<T, R, C> MatrixT<T, R, C>::operator-()
{
	MatrixT result;
	for(size_t r = 0; r < rows(); r++)
		for(size_t c = 0; c < cols(); c++)
			result[r][c] = -m_[r][c];
	return result;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createTranslate(const Vector3T<T>& v)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	MatrixT mat;
	mat(3, 0) = v.x;
	mat(3, 1) = v.y;
	mat(3, 2) = v.z;
	return mat;
}

template<arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createRotation(const QuaternionT<T>& q)
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

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createRotation(float angle, Vector3T<T> axis)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	assert(axis == Vector3T<T>::unit_x || axis == Vector3T<T>::unit_y || axis == Vector3T<T>::unit_z);

	axis.normalize();
	const float x = axis.x;
	const float y = axis.y;
	const float z = axis.z;

	const float sin = std::sin(angle);
	const float cos = std::cos(angle);
	const float t = 1.0f - cos;
	const float tx = t * x;
	const float ty = t * y;
	const float tz = t * z;
	const float txy = tx * y;
	const float txz = tx * z;
	const float tyz = ty * z;
	const float sx = sin * x;
	const float sy = sin * y;
	const float sz = sin * z;

	auto mat = MatrixT::identity();
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

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createRotationX(float angle)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	const float sin = std::sin(angle);
	const float cos = std::cos(angle);

	auto mat = MatrixT::identity();
	mat(1, 1) = cos;
	mat(1, 2) = sin;
	mat(2, 1) = -sin;
	mat(2, 2) = cos;
	return mat;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createRotationY(float angle)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	const float sin = std::sin(angle);
	const float cos = std::cos(angle);

	auto mat = MatrixT::identity();
	mat(0, 0) = cos;
	mat(0, 2) = sin;
	mat(2, 0) = -sin;
	mat(2, 2) = cos;
	return mat;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createRotationZ(float angle)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	const float sin = std::sin(angle);
	const float cos = std::cos(angle);

	auto mat = MatrixT::identity();
	mat(0, 0) = cos;
	mat(0, 1) = -sin;
	mat(1, 0) = sin;
	mat(1, 1) = cos;
	return mat;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::createScale(const Vector3T<T>& scale)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");

	MatrixT mat;
	mat(0, 0) = scale.x;
	mat(1, 1) = scale.y;
	mat(2, 2) = scale.z;
	return mat;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::perspective(T vFOV, T aspect, T n, T f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);
	assert(!equal(aspect, 0.f));
	assert(n != f);

	const auto tanHalfFOV = std::tan(vFOV / 2.f);

	auto mat = MatrixT::zero();
	mat(0, 0) = T(1) / (aspect * tanHalfFOV);
	mat(1, 1) = T(1) / tanHalfFOV;
	mat(2, 2) = f / (f - n);
	mat(2, 3) = T(1);
	mat(3, 2) = -(f * n) / (f - n);
	return mat;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::orthogonal(T w, T h, T n, T f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);

	return orthogonal(-w / T(2), w / T(2), -h / T(2), h / T(2), n, f);
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::orthogonal(T l, T r, T b, T t, T n, T f)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);
	assert(!equal(l, r) && !equal(b, t) && !equal(n, f));

	auto mat = MatrixT::zero();
	mat(0, 0) = T(2) / (r - l);
	mat(1, 1) = T(2) / (b - t);
	mat(2, 2) = T(1) / (f - n);
	mat(3, 0) = -(r + l) / (r - l);
	mat(3, 1) = -(b + t) / (b - t);
	mat(3, 2) = -n / (f - n);
	mat(3, 3) = T(1);
	return mat;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, 4, 4> MatrixT<T, R, C>::lookAt(const Vector3T<T>& eye, const Vector3T<T>& center, const Vector3T<T>& up)
{
	static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
	static_assert(std::is_floating_point_v<T>);

	Vector3T<T> f((center - eye).normalize()); // front
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

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::identity()
{
	static_assert(R == C, "only square matrix supports this operation");
	static MatrixT mat;
	return mat;
}

template <arithmetic T, size_t R, size_t C>
inline MatrixT<T, R, C> MatrixT<T, R, C>::zero()
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

inline Vector4f operator*(const MatrixT<float, 4, 4>& mat, const Vector4f& vec)
{
	__m128 m[4];
	__m128 v = {};
	simd::load(m, mat.data());
	simd::load(v, vec.data());
	simd::matrixMulVec(m, v, v);

	Vector4f result;
	simd::store(result.data(), v);
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
