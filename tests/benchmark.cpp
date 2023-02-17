// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>
#include <nanobench.h>

using namespace ankerl;

TEST_SUITE_BEGIN("benchmark");

TEST_CASE("matrix" * doctest::skip(true))
{
	SUBCASE("4x4")
	{
		// clang-format off
        const Matrix4f a = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        };
		// clang-format on

		// clang-format off
        const Matrix4f b = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        };
		// clang-format on

		nanobench::Bench().run("4x4 matrix multiplication", [&] {
			const auto c = a * b;
			nanobench::doNotOptimizeAway(c);
		});
	}

	SUBCASE("100x100")
	{
		const auto a = MatrixT<float, 100, 100>::identity();
		const auto b = MatrixT<float, 100, 100>::identity();

		nanobench::Bench().run("100x100 matrix multiplication", [&] {
			auto c = a * b;
			nanobench::doNotOptimizeAway(c);
		});
	}
}

TEST_SUITE_END;
