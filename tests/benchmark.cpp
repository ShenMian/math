// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

using namespace ankerl;

TEST_SUITE_BEGIN("benchmark");

TEST_CASE("matrix" * doctest::skip(true))
{
	SUBCASE("4x4")
	{
		// clang-format off
        Matrix4f a = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        };
		// clang-format on

		// clang-format off
        Matrix4f b = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        };
		// clang-format on

		nanobench::Bench().run("4x4 matrix multiplication", [&] {
			auto c = a * b;
			nanobench::doNotOptimizeAway(c);
		});
	}

	SUBCASE("500x500")
	{
		auto a = MatrixT<float, 500, 500>::identity();
		auto b = MatrixT<float, 500, 500>::identity();

		nanobench::Bench().run("500x500 matrix multiplication", [&] {
			auto c = a * b;
			nanobench::doNotOptimizeAway(c);
		});
	}
}

TEST_SUITE_END;
