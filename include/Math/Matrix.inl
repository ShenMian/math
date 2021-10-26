// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix.hpp"
#include "Math.hpp"

template <size_t R, size_t C, typename T>
inline MatrixT<R, C, T>::MatrixT()
{
    static_assert(R == C);
    for(size_t r = 0; r < R; r++)
        m_[r][r] = T(1);
}

template <size_t R, size_t C, typename T>
inline MatrixT<R, C, T>::MatrixT(const std::initializer_list<T>& list)
{
    assert(list.size() == R * C);
    auto it = list.begin();
    for(size_t r = 0; r < R; r++)
        for(size_t c = 0; c < C; c++, it++)
            m_[r][c] = *it;
}

template <size_t R, size_t C, typename T>
inline MatrixT<R, C, T>& MatrixT<R, C, T>::transpose()
{
    static_assert(R == C, "only square matrix supports this operation");

    return *this;
}

template <size_t R, size_t C, typename T>
inline MatrixT<C, R, T> MatrixT<R, C, T>::transposed() const
{
    return MatrixT(*this).transpose();
}

template <size_t R, size_t C, typename T>
inline T MatrixT<R, C, T>::trace() const
{
    static_assert(R == C, "only square matrix supports this operation");
    T result = T(0);
    for(size_t r = 0; r < R; r++)
        result += m_[r][r];
    return result;
}

template <size_t R, size_t C, typename T>
inline void MatrixT<R, C, T>::decompose(Vector3T<T>* translation, Vector3T<T>* rotation, Vector3T<T>* scale) const
{
}

template <size_t R, size_t C, typename T>
inline T* MatrixT<R, C, T>::data()
{
    return m_;
}

template <size_t R, size_t C, typename T>
inline const T* MatrixT<R, C, T>::data() const
{
    return m_;
}

template <size_t R, size_t C, typename T>
inline T* MatrixT<R, C, T>::operator[](size_t row)
{
    assert(row < R);
    return m_[row];
}

template <size_t R, size_t C, typename T>
inline const T* MatrixT<R, C, T>::operator[](size_t row) const
{
    assert(row < R);
    return m_[row];
}

template <size_t R, size_t C, typename T>
inline bool MatrixT<R, C, T>::operator==(const MatrixT& rhs) const
{
    for(size_t r = 0; r < R; r++)
        for(size_t c = 0; c < C; c++)
            if(!Math::equal(m_[r][c], rhs.m_[r][c]))
                return false;
    return true;
}

template <size_t R, size_t C, typename T>
inline MatrixT<R, C, T> MatrixT<R, C, T>::createTranslate(const Vector3T<T>& v)
{
    static_assert(R == C && R == 4, "only 4x4 matrix supports this operation");
    MatrixT result;
    result[0][3] = v.x;
    result[1][3] = v.y;
    result[2][3] = v.z;
    return result;
}