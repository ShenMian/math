// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Matrix.hpp"

template <typename T, size_t N> requires std::is_arithmetic_v<T>
class MatrixT<T, N, N>
{
public:
	MatrixT();
};

#include "MatrixNN.inl"
