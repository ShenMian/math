// Copyright 2021 SMS
// License(Apache-2.0)

#include <gtest/gtest.h>
#include <Math/Matrix.hpp>

TEST(Matrix, trace)
{
    EXPECT_FLOAT_EQ(Matrix4().trace(), 4);
    EXPECT_FLOAT_EQ(Matrix3().trace(), 3);
}