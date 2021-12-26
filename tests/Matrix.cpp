// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(Matrix, element)
{
	Matrix2f m;
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	EXPECT_EQ(m, Matrix2f({3, -1, 2.5, 1.5}));
	EXPECT_FLOAT_EQ(m(0, 0), 3.f);
	EXPECT_FLOAT_EQ(m(0, 1), -1.f);
	EXPECT_FLOAT_EQ(m(1, 0), 2.5f);
	EXPECT_FLOAT_EQ(m(1, 1), 1.5f);
}

TEST(Matrix, trace)
{
	EXPECT_FLOAT_EQ(Matrix3().trace(), 3);
	EXPECT_FLOAT_EQ(Matrix4().trace(), 4);
	EXPECT_FLOAT_EQ((Matrixf<5, 5>().trace()), 5);
}

TEST(Matrix, inverse)
{
}

TEST(Matrix, transpost)
{
}

TEST(Matrix, determinant)
{
}
