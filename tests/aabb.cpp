// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_SUITE_BEGIN("aabb");

TEST_CASE("AABB")
{
	CHECK_EQ(AABB<3>({1, 1, 1}, {0, 0, 0}), AABB<3>({0, 0, 0}, {1, 1, 1}));
}

TEST_CASE("contains")
{
	AABB<3> aabb({0, 0, 0}, {2, 2, 2});

	// contains(const Vectorf<N>&)
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
	CHECK_FALSE(aabb.contains({0, 0, 3}));

	// contains(const AABB<3>&)
	CHECK(aabb.contains(aabb));
	CHECK(aabb.contains(AABB<3>({1, 1, 1}, {2, 2, 2})));
}

TEST_CASE("expand")
{
	AABB<3> aabb({0, 0, 0}, {1, 1, 1});

	// expand(const Vectorf<N>&)
	SUBCASE("")
	{
		aabb.expand({1, 2, 3});
		CHECK_EQ(aabb, AABB<3>({0, 0, 0}, {1, 2, 3}));
	}
	SUBCASE("")
	{
		aabb.expand({-1, 0, 2});
		CHECK_EQ(aabb, AABB<3>({-1, 0, 0}, {1, 1, 2}));
	}

	// expand(const AABB<3>&)
	SUBCASE("")
	{
		aabb.expand(AABB<3>({-1, -1, -1}, {0, 0, 0}));
		CHECK_EQ(aabb, AABB<3>({-1, -1, -1}, {1, 1, 1}));
	}
}

TEST_CASE("extent")
{
	CHECK_EQ(AABB<3>({0, 0, 0}, {1, 1, 1}).extent(), Vector3(1, 1, 1));
	CHECK_EQ(AABB<3>({-2, -2, -2}, {2, 2, 2}).extent(), Vector3(4, 4, 4));
}

TEST_CASE("volume")
{
	CHECK_EQ(AABB<3>({0, 0, 0}, {1, 1, 1}).volume(), doctest::Approx(1.f));
	CHECK_EQ(AABB<3>({-2, -2, -2}, {2, 2, 2}).volume(), doctest::Approx(64.f));
}

TEST_CASE("center")
{
	CHECK_EQ(AABB<3>({0, 0, 0}, {1, 1, 1}).center(), Vector3(0.5, 0.5, 0.5));
	CHECK_EQ(AABB<3>({-2, -2, -2}, {2, 2, 2}).center(), Vector3(0, 0, 0));
	CHECK_EQ(AABB<3>({-1, -1, -1}, {0, 0, 0}).center(), Vector3(-0.5, -0.5, -0.5));
}

TEST_CASE("empty")
{
	CHECK(AABB<3>({3, 4, 5}, {3, 4, 5}).empty());
	CHECK_FALSE(AABB<3>({3, 4, 5}, {3, 4, 6}).empty());
}

TEST_SUITE_END;
