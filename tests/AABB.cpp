// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(AABB3, constructor)
{
	EXPECT_EQ(AABB3({1, 1, 1}, {0, 0, 0}), AABB3({0, 0, 0}, {1, 1, 1}));
}

TEST(AABB3, contains)
{
	AABB3 aabb({0, 0, 0}, {2, 2, 2});

	// contains(const Vector3&)
	EXPECT_TRUE(aabb.contains(aabb.min));
	EXPECT_TRUE(aabb.contains(aabb.max));
	EXPECT_TRUE(aabb.contains({1, 0, 0}));
	EXPECT_TRUE(aabb.contains({0, 1, 0}));
	EXPECT_TRUE(aabb.contains({0, 0, 1}));
	EXPECT_TRUE(aabb.contains({2, 0, 0}));
	EXPECT_TRUE(aabb.contains({0, 2, 0}));
	EXPECT_TRUE(aabb.contains({0, 0, 2}));
	EXPECT_FALSE(aabb.contains({-1, 0, 0}));
	EXPECT_FALSE(aabb.contains({0, 3, 0}));

	// contains(const AABB3&)
	EXPECT_TRUE(aabb.contains(aabb));
	EXPECT_TRUE(aabb.contains(AABB3({1, 1, 1}, {2, 2, 2})));
}

TEST(AABB3, expand)
{
	// expand(const Vector3&)
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

	// expand(const AABB3&)
	{
		AABB3 aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand(AABB3({-1, -1, -1}, {0, 0, 0}));
		EXPECT_EQ(aabb, AABB3({-1, -1, -1}, {1, 1, 1}));
	}
}

TEST(AABB3, getCenter)
{
	EXPECT_EQ(AABB3({0, 0, 0}, {1, 1, 1}).getCenter(), Vector3(0.5, 0.5, 0.5));
	EXPECT_EQ(AABB3({-2, -2, -2}, {2, 2, 2}).getCenter(), Vector3(0, 0, 0));
	EXPECT_EQ(AABB3({-1, -1, -1}, {0, 0, 0}).getCenter(), Vector3(-0.5, -0.5, -0.5));
}

TEST(AABB3, isEmpty)
{
	EXPECT_TRUE(AABB3({3, 4, 5}, {3, 4, 5}).isEmpty());
	EXPECT_FALSE(AABB3({3, 4, 5}, {3, 4, 6}).isEmpty());
}
