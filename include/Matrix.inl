// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix.hpp"

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
    static_assert(R == C);

    return *this;
}

template <typename T, size_t R, size_t C>
inline MatrixT<T, C, R> MatrixT<T, R, C>::transposed() const
{
    return MatrixT(*this).transpose();
}

template <typename T, size_t R, size_t C>
inline T MatrixT<T, R, C>::trace() const
{
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
T* MatrixT<T, R, C>::operator[](size_t row)
{
    assert(row < R);
    return m_[row];
}

template <typename T, size_t R, size_t C>
const T* MatrixT<T, R, C>::operator[](size_t row) const
{
    assert(row < R);
    return m_[row];
}