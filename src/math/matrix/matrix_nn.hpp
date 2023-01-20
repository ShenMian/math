// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "../Vector/vector3.hpp"
#include "matrix.hpp"

template <arithmetic T, size_t N>
class MatrixT<T, N, N>
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
