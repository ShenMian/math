// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>
#include <random>

TEST_SUITE_BEGIN("simd");

TEST_CASE("matrix_addu")
{
	const float a[16] = {1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
	                     9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
	const float b[16] = {16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f,
	                     8.0f,  7.0f,  6.0f,  5.0f,  4.0f,  3.0f,  2.0f,  1.0f};
	float       c[16];
	simd::matrix_addu(a, b, c);

	for(size_t i = 0; i < 16; i++)
	{
		CAPTURE(i);
		CHECK(c[i] == doctest::Approx(a[i] + b[i]));
	}
}

TEST_CASE("matrix_subu")
{
	const float       a[16] = {1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
	                     9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
	const float b[16] = {16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f,
	                     8.0f,  7.0f,  6.0f,  5.0f,  4.0f,  3.0f,  2.0f,  1.0f};
	float       c[16];
	simd::matrix_subu(a, b, c);

	for(size_t i = 0; i < 16; i++)
	{
		CAPTURE(i);
		CHECK(c[i] == doctest::Approx(a[i] - b[i]));
	}
}

void matrix_mul(const float a[16], const float b[16], float c[16])
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			c[i * 4 + j] = 0.0f;
			for(int k = 0; k < 4; ++k)
				c[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
		}
	}
}

TEST_CASE("matrix_mulu")
{
	{
		const float a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		const float b[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
		float c[16];
		simd::matrix_mulu(a, b, c);

		const float expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		for(size_t i = 0; i < 16; i++)
		{
			CAPTURE(i);
			CHECK(c[i] == doctest::Approx(expected[i]));
		}
	}

	{
		const float a[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
		const float b[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		float c[16];
		simd::matrix_mulu(a, b, c);

		const float expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		for(size_t i = 0; i < 16; i++)
		{
			CAPTURE(i);
			CHECK(c[i] == doctest::Approx(expected[i]));
		}
	}
}

TEST_SUITE_END;
