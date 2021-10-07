// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector3.hpp"
#include <cstddef>

template <typename T, size_t R, size_t C>
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
     * @brief 计算行列式的值.
     */
    T determinant() const;

    /**
     * @brief 求逆.
     */
    MatrixT& inverse();

    /**
     * @brief 转置.
     */
    MatrixT& transpose();

    /**
     * @brief 转置.
     */
    MatrixT<T, C, R> transposed() const;

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
    operator MatrixT<T0, R, C>()
    {
        MatrixT result;
        for(size_t r = 0; r < R; r++)
            for(size_t c = 0; c < C; c++)
                result[r][c] = static_cast<T0>(m_[r][c]);
        return result;
    }

    static const size_t rows    = R;
    static const size_t columns = C;

    static const MatrixT identity;

private:
    T m_[R][C] = {};
};

#include "Matrix.inl"

template <typename T>
using Matrix3T = MatrixT<T, 3, 3>;
using Matrix3  = Matrix3T<float>;

template <typename T>
using Matrix4T = MatrixT<T, 4, 4>;
using Matrix4  = Matrix4T<float>;