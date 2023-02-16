// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_SUITE_BEGIN("aabb");

TEST_CASE("AABB")
{
	CHECK_EQ(AABB({1, 1, 1}, {0, 0, 0}), AABB({0, 0, 0}, {1, 1, 1}));
}

TEST_CASE("contains")
{
	AABB aabb({0, 0, 0}, {2, 2, 2});

	// contains(const Vector3&)
	CHECK(aabb.contains(aabb.min()));
	CHECK(aabb.contains(aabb.max()));
	CHECK(aabb.contains({1, 0, 0}));
	CHECK(aabb.contains({0, 1, 0}));
	CHECK(aabb.contains({0, 0, 1}));
	CHECK(aabb.contains({2, 0, 0}));
	CHECK(aabb.contains({0, 2, 0}));
	CHECK(aabb.contains({0, 0, 2}));
	CHECK_FALSE(aabb.contains({-1, 0, 0}));
	CHECK_FALSE(aabb.contains({0, 3, 0}));

	// contains(const AABB&)
	CHECK(aabb.contains(aabb));
	CHECK(aabb.contains(AABB({1, 1, 1}, {2, 2, 2})));
}

TEST_CASE("expand")
{
	// expand(const Vector3&)
	{
		AABB aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand({1, 2, 3});
		CHECK_EQ(aabb, AABB({0, 0, 0}, {1, 2, 3}));
	}
	{
		AABB aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand({-1, 0, 2});
		CHECK_EQ(aabb, AABB({-1, 0, 0}, {1, 1, 2}));
	}

	// expand(const AABB&)
	{
		AABB aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand(AABB({-1, -1, -1}, {0, 0, 0}));
		CHECK_EQ(aabb, AABB({-1, -1, -1}, {1, 1, 1}));
	}
}

TEST_CASE("center")
{
	CHECK_EQ(AABB({0, 0, 0}, {1, 1, 1}).center(), Vector3(0.5, 0.5, 0.5));
	CHECK_EQ(AABB({-2, -2, -2}, {2, 2, 2}).center(), Vector3(0, 0, 0));
	CHECK_EQ(AABB({-1, -1, -1}, {0, 0, 0}).center(), Vector3(-0.5, -0.5, -0.5));
}

TEST_CASE("empty")
{
	CHECK(AABB({3, 4, 5}, {3, 4, 5}).empty());
	CHECK_FALSE(AABB({3, 4, 5}, {3, 4, 6}).empty());
}

TEST_SUITE_END;
