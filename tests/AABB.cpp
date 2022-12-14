// Copyright 2022 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_CASE("AABB3::AABB3")
{
	CHECK_EQ(AABB3({1, 1, 1}, {0, 0, 0}), AABB3({0, 0, 0}, {1, 1, 1}));
}

TEST_CASE("AABB3::contains")
{
	AABB3 aabb({0, 0, 0}, {2, 2, 2});

	// contains(const Vector3&)
	CHECK(aabb.contains(aabb.min));
	CHECK(aabb.contains(aabb.max));
	CHECK(aabb.contains({1, 0, 0}));
	CHECK(aabb.contains({0, 1, 0}));
	CHECK(aabb.contains({0, 0, 1}));
	CHECK(aabb.contains({2, 0, 0}));
	CHECK(aabb.contains({0, 2, 0}));
	CHECK(aabb.contains({0, 0, 2}));
	CHECK_FALSE(aabb.contains({-1, 0, 0}));
	CHECK_FALSE(aabb.contains({0, 3, 0}));

	// contains(const AABB3&)
	CHECK(aabb.contains(aabb));
	CHECK(aabb.contains(AABB3({1, 1, 1}, {2, 2, 2})));
}

TEST_CASE("AABB3::expand")
{
	// expand(const Vector3&)
	{
		AABB3 aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand({1, 2, 3});
		CHECK_EQ(aabb, AABB3({0, 0, 0}, {1, 2, 3}));
	}
	{
		AABB3 aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand({-1, 0, 2});
		CHECK_EQ(aabb, AABB3({-1, 0, 0}, {1, 1, 2}));
	}

	// expand(const AABB3&)
	{
		AABB3 aabb({0, 0, 0}, {1, 1, 1});
		aabb.expand(AABB3({-1, -1, -1}, {0, 0, 0}));
		CHECK_EQ(aabb, AABB3({-1, -1, -1}, {1, 1, 1}));
	}
}

TEST_CASE("AABB3::getCenter")
{
	CHECK_EQ(AABB3({0, 0, 0}, {1, 1, 1}).center(), Vector3(0.5, 0.5, 0.5));
	CHECK_EQ(AABB3({-2, -2, -2}, {2, 2, 2}).center(), Vector3(0, 0, 0));
	CHECK_EQ(AABB3({-1, -1, -1}, {0, 0, 0}).center(), Vector3(-0.5, -0.5, -0.5));
}

TEST_CASE("AABB3::isEmpty")
{
	CHECK(AABB3({3, 4, 5}, {3, 4, 5}).empty());
	CHECK_FALSE(AABB3({3, 4, 5}, {3, 4, 6}).empty());
}
