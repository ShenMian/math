// Copyright 2021 SMS
// License(Apache-2.0)

#include <gtest/gtest.h>
#include <Math/Math.hpp>

TEST(Math, degrees)
{
    EXPECT_FLOAT_EQ((float)Math::degrees(Math::pi), 180.f);
    EXPECT_FLOAT_EQ(Math::degrees(0.f), 0.f);
}

TEST(Math, radians)
{
    EXPECT_FLOAT_EQ(Math::radians(180.f), (float)Math::pi);
    EXPECT_FLOAT_EQ(Math::radians(0.f), 0.f);
}
