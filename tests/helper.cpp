// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>
#include <numbers>

TEST_SUITE_BEGIN("helper");

TEST_CASE("degrees")
{
	CHECK_EQ(degrees((float)std::numbers::pi), doctest::Approx(180.f));
	CHECK_EQ(degrees(0.f), doctest::Approx(0.f));
}

TEST_CASE("radians")
{
	CHECK_EQ(radians(180.f), (float)std::numbers::pi);
	CHECK_EQ(radians(0.f), 0.f);
}

TEST_SUITE_END;
