// Copyright 2021 SMS
// License(Apache-2.0)

#include "gtest/gtest.h"
#include "Matrix.hpp"

#include "Quaternion.hpp"

TEST(Matrix, trace)
{
    EXPECT_FLOAT_EQ(Matrix4().trace(), 4);
    EXPECT_FLOAT_EQ(Matrix3().trace(), 3);

    auto t = Matrix4::createTranslate({4, 5, 6});
}