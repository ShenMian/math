// Copyright 2021 SMS
// License(Apache-2.0)


#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_CASE("SIMD::matrixMul")
{
	// clang-format off
	Matrix4f a = {
		1,  2,  3,  4,
		5,  6,  7,  8,
		9,  10, 11, 12,
		13, 14, 15, 16
	};
	Matrix4f b = {
		90,  100, 110, 120,
		202, 228, 254, 280,
		314, 356, 398, 440,
		426, 484, 542, 600
	};
	// clang-format on

	CHECK_EQ(a * a, b);
}
