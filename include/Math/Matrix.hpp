// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector3.hpp"
#include <cstddef>

/**
 * @brief 矩阵.
 */
template <size_t R, size_t C, typename T>
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
    explicit MatrixT(const std::initializer_list<T>& list);

    /**
     * @brief 求逆.
     */
    MatrixT& inverse();

    /**
     * @brief 获取逆矩阵.
     */
    MatrixT<C, R, T> inversed() const;

    /**
     * @brief 转置.
     */
    MatrixT& transpose();

    /**
     * @brief 获取转置后的矩阵.
     */
    MatrixT<C, R, T> transposed() const;

    /**
     * @brief 计算行列式的值.
     */
    T determinant() const;

    /**
     * @brief 求迹.
     */
    T trace() const;

    /**
     * @brief 分解.
     */
    void decompose(Vector3T<T>* translation, Vector3T<T>* rotation, Vector3T<T>* scale) const;

    /**
     * @brief 重组.
     */
    MatrixT& recompose(const Vector3T<T>& translation, const Vector3T<T>& rotation, const Vector3T<T>& scale);

    /**
	 * @brief 获取原始数据.
	 */
    T*       data();
    const T* data() const;

    T*       operator[](size_t row);
    const T* operator[](size_t row) const;

    template <typename T0>
    operator MatrixT<R, C, T0>()
    {
        MatrixT result;
        for(size_t r = 0; r < R; r++)
            for(size_t c = 0; c < C; c++)
                result[r][c] = static_cast<T0>(m_[r][c]);
        return result;
    }

    bool operator==(const MatrixT&) const;

    static MatrixT createTranslate(const Vector3T<T>&);
    static MatrixT createRotation(const Vector3T<T>& axis, float angle);
    static MatrixT createScale(const Vector3T<T>&);

    static MatrixT createOrtho();
    static MatrixT createPerspective();

    static const size_t rows    = R;
    static const size_t columns = C;

    static const MatrixT identity;

private:
    T m_[R][C] = {};
};

#include "Matrix.inl"

#define DEF_MATRIX_NxN(n)                                        \
    template <typename T> using Matrix##n##T = MatrixT<n, n, T>; \
    using Matrix##n     = Matrix##n##T<float>;                   \
    using Matrix##n##f  = Matrix##n##T<float>;                   \
    using Matrix##n##d  = Matrix##n##T<double>;                  \

DEF_MATRIX_NxN(2);
DEF_MATRIX_NxN(3);
DEF_MATRIX_NxN(4);

// #undef DEF_MATRIX_NxN