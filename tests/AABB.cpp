// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(AABB3, isEmpty)
{
	EXPECT_TRUE(AABB3({3, 3}, {4, 4}).isEmpty());
}
