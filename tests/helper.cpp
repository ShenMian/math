// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>
#include <numbers>

TEST(Math, degrees)
{
	EXPECT_FLOAT_EQ((float)degrees(std::numbers::pi), 180.f);
	EXPECT_FLOAT_EQ(degrees(0.f), 0.f);
}

TEST(Math, radians)
{
	EXPECT_FLOAT_EQ(radians(180.f), (float)std::numbers::pi);
	EXPECT_FLOAT_EQ(radians(0.f), 0.f);
}
