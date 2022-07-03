// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "matrix.hpp"
#include "../Vector/vector3.hpp"

template <arithmetic T, size_t N>
class alignas(sizeof(T)) MatrixT<T, N, N>
{
public:
    /**
     * @brief 默认构造函数.
     */
	MatrixT();

    /**
     * @brief 转置.
     */
    MatrixT& transpose();

private:
    T m_[N][N] = {};
};

#include "MatrixNN.inl"
