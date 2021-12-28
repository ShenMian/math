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
	EXPECT_FLOAT_EQ((Matrixf<3, 3>().trace()), 3);
	EXPECT_FLOAT_EQ((Matrixf<4, 4>().trace()), 4);
	EXPECT_FLOAT_EQ((Matrixf<5, 5>().trace()), 5);
}

TEST(Matrix, inverse)
{
}

TEST(Matrix, transpose)
{
	Matrix3f a = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};
	Matrix3f b = {
		1, 4, 7,
		2, 5, 8,
		3, 6, 9
	};
	EXPECT_EQ(a.transpose(), b);
}

TEST(Matrix, determinant)
{
}
