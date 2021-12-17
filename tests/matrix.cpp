// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(Matrix, trace)
{
	EXPECT_FLOAT_EQ(Matrix4().trace(), 4);
	EXPECT_FLOAT_EQ(Matrix3().trace(), 3);
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
