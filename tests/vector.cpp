// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_SUITE_BEGIN("vector");

TEST_CASE("vector")
{
	Vectorf<2> vec({1.f, 2.f});

	SUBCASE("operator[]")
	{
		CHECK_EQ(vec[0], doctest::Approx(1.f));
		CHECK_EQ(vec[1], doctest::Approx(2.f));
	}

	SUBCASE("at")
	{
		CHECK_EQ(vec.at(0), doctest::Approx(1.f));
		CHECK_EQ(vec.at(1), doctest::Approx(2.f));
		CHECK_THROWS_AS(vec.at(2), std::out_of_range);
	}

	SUBCASE("minCoeff")
	{
		CHECK_EQ(vec.min_coeff(), doctest::Approx(1.f));
	}

	SUBCASE("maxCoeff")
	{
		CHECK_EQ(vec.max_coeff(), doctest::Approx(2.f));
	}

	SUBCASE("equal")
	{
		CHECK_EQ(vec, Vectorf<2>({1.f, 2.f}));
	}

	SUBCASE("operator<<")
	{
		Vectorf<2>         vec({1.f, 2.f});
		std::ostringstream stream;
		stream << vec;
		CHECK_EQ(stream.str(), "1 2 ");
	}

	SUBCASE("normSq")
	{
		CHECK_EQ(vec.norm_sq(), doctest::Approx(1.f * 1.f + 2.f * 2.f));
	}

	SUBCASE("norm")
	{
		CHECK_EQ(vec.norm(), doctest::Approx(std::sqrt(1.f * 1.f + 2.f * 2.f)));
	}

	SUBCASE("dot")
	{
		CHECK_EQ(vec.normalized().dot(vec.normalized()), doctest::Approx(1.f));
		CHECK_EQ(vec.normalized().dot(-vec.normalized()), doctest::Approx(-1.f));
	}

	SUBCASE("sum")
	{
		CHECK_EQ(vec.sum(), doctest::Approx(3.f));
	}

	SUBCASE("normalize")
	{
		CHECK_EQ(vec.normalize().norm(), doctest::Approx(1.f));
		CHECK_EQ(Vectorf<2>({2.f, 3.f}).normalize(), Vectorf<2>({4.f, 6.f}).normalize());
		CHECK_EQ(Vectorf<2>(0.f).normalize(), Vectorf<2>(0.f));
	}
}

TEST_CASE("clamp")
{
	Vectorf<2> vec({1.f, 5.f});
	Vectorf<2> min({2.f, 2.f});
	Vectorf<2> max({4.f, 4.f});
	CHECK_EQ(vec.clamp(min, max), Vectorf<2>({2.f, 4.f}));
}

TEST_CASE("midpoint")
{
	Vectorf<2> a({0.f, 0.f});
	Vectorf<2> b({2.f, 4.f});
	CHECK_EQ(midpoint(a, b), Vectorf<2>({1.f, 2.f}));
}

TEST_SUITE_END;
