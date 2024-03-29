// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_CASE("AABB<3>")
{
	AABB<3> aabb({0, 0, 0}, {3, 3, 3});

	SUBCASE("contains")
	{
		CHECK(aabb.contains({2, 3, 3}) == true);
		CHECK(aabb.contains({-1, 2, 3}) == false);
	}

	SUBCASE("intersects")
	{
		AABB<3> inner({1, 1, 1}, {2, 2, 2});
		CHECK(aabb.intersects(inner) == true);
		CHECK(inner.intersects(aabb) == true);
	}

	SUBCASE("expand")
	{
		AABB<3> aabb2({-1, -2, -3}, {0, 1, 2});
		aabb.expand(aabb2);
		CHECK(aabb.min()[0] == -1);
		CHECK(aabb.max()[2] == 3);
	}

	SUBCASE("center")
	{
		Vectorf<3> center = aabb.center();
		CHECK(center[0] == 1.5f);
		CHECK(center[1] == 1.5f);
		CHECK(center[2] == 1.5f);
	}

	SUBCASE("extent")
	{
		Vectorf<3> extent = aabb.extent();
		CHECK(extent[0] == 3);
		CHECK(extent[1] == 3);
		CHECK(extent[2] == 3);
	}

	SUBCASE("volume")
	{
		CHECK(aabb.volume() == 27);
	}

	SUBCASE("empty")
	{
		AABB<3> aabb2({0, 0, 0}, {0, 0, 0});
		CHECK(aabb.empty() == false);
		CHECK(aabb2.empty() == true);
	}
}

TEST_CASE("AABB<2>")
{
	AABB<2> box({1.f, 2.f}, {3.f, 4.f});

	SUBCASE("center")
	{
		Vectorf<2> center = box.center();
		// FIXME
		// CHECK(center.x() == doctest::Approx(2.f));
		// CHECK(center.y() == doctest::Approx(3.f));
	}

	SUBCASE("extent")
	{
		Vectorf<2> extent = box.extent();
		// FIXME
		// CHECK(extent.x() == doctest::Approx(2.f));
		// CHECK(extent.y() == doctest::Approx(2.f));
	}

	SUBCASE("volume")
	{
		float volume = box.volume();
		CHECK(volume == doctest::Approx(4.f));
	}

	SUBCASE("contains")
	{
		Vectorf<2> point1{1.f, 2.f};
		CHECK(box.contains(point1) == true);

		Vectorf<2> point2{0.f, 0.f};
		CHECK(box.contains(point2) == false);
	}

	SUBCASE("intersects")
	{
		AABB<2> box1({0.f, 1.f}, {2.f, 3.f});
		AABB<2> box2({1.f, 2.f}, {3.f, 4.f});
		AABB<2> box3({4.f, 5.f}, {6.f, 7.f});

		CHECK(box.intersects(box1) == true);
		CHECK(box.intersects(box2) == true);
		CHECK(box.intersects(box3) == false);

		// 包围体十字形相交, 四个端点都不再对方内部
		AABB<2> crossA({2, 1}, {3, 7});
		AABB<2> crossB({2, 5}, {7, 6});
		CHECK(crossA.intersects(crossB) == true);
		CHECK(crossB.intersects(crossA) == true);
	}

	SUBCASE("expand")
	{
		AABB<2> box1({1.f, 2.f}, {3.f, 4.f});
		box.expand(box1);

		CHECK(box.min().x() == doctest::Approx(1.f));
		CHECK(box.min().y() == doctest::Approx(2.f));
		CHECK(box.max().x() == doctest::Approx(3.f));
		CHECK(box.max().y() == doctest::Approx(4.f));
	}

	SUBCASE("empty")
	{
		AABB<2> emptyBox;
		CHECK(emptyBox.empty() == true);

		AABB<2> nonEmptyBox({1.f, 2.f}, {3.f, 4.f});
		CHECK(nonEmptyBox.empty() == false);
	}
}
