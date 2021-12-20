// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(AABB3, expand)
{
	{
		AABB3 aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand({1, 2, 3});
		EXPECT_EQ(aabb, AABB3({0, 0, 0}, {1, 2, 3}));
	}
	{
		AABB3 aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand({-1, 0, 2});
		EXPECT_EQ(aabb, AABB3({-1, 0, 0}, {1, 1, 2}));
	}
}

TEST(AABB3, getCenter)
{
	EXPECT_EQ(AABB3({0, 0, 0}, {1, 1, 1}).getCenter(), Vector3(0.5, 0.5, 0.5));
}

TEST(AABB3, isEmpty)
{
	EXPECT_TRUE(AABB3({3, 4, 5}, {3, 4, 5}).isEmpty());
	EXPECT_FALSE(AABB3({3, 4, 5}, {3, 4, 6}).isEmpty());
}

TEST(AABB3, isValid)
{
	EXPECT_TRUE(AABB3({3, 4, 5}, {3, 4, 5}).isValid());
	EXPECT_FALSE(AABB3({3, 4, 6}, {3, 4, 5}).isValid());
}
