// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/vector/vector.hpp>

TEST_SUITE_BEGIN("vector");

TEST_CASE("operator[]")
{
	Vectorf<2> vec({1.f, 2.f});
	CHECK_EQ(vec[0], doctest::Approx(1.f));
	CHECK_EQ(vec[1], doctest::Approx(2.f));
}

TEST_CASE("norm")
{
	CHECK_EQ(Vectorf<2>({3.f, 4.f}).norm(), doctest::Approx(5.f));
	CHECK_EQ(Vectorf<2>({6.f, 8.f}).norm(), doctest::Approx(10.f));
	CHECK_EQ(Vectorf<2>({7.f, 24.f}).norm(), doctest::Approx(25.f));
	CHECK_EQ(Vectorf<2>({8.f, 15.f}).norm(), doctest::Approx(17.f));
	CHECK_EQ(Vectorf<2>({9.f, 40.f}).norm(), doctest::Approx(41.f));
}

TEST_CASE("normSquared")
{
	CHECK_EQ(Vectorf<2>({3, 4}).normSq(), doctest::Approx((float)std::pow(5.f, 2)));
}

TEST_CASE("normalize")
{
	CHECK_EQ(Vectorf<2>({1.f, 2.f}).normalize().norm(), doctest::Approx(1.f));
	CHECK_EQ(Vectorf<2>({2.f, 3.f}).normalize(), Vectorf<2>({4.f, 6.f}).normalize());
	CHECK_EQ(Vectorf<2>(0.f).normalize(), Vectorf<2>(0.f));
}

TEST_CASE("dot")
{
	Vectorf<2> vec({1.f, 2.f});
	CHECK_EQ(vec.normalized().dot(vec.normalized()), doctest::Approx(1.f));
	CHECK_EQ(vec.normalized().dot(-vec.normalized()), doctest::Approx(-1.f));
}

TEST_CASE("sum")
{
	Vectorf<2> vec({1.f, 2.f});
	CHECK_EQ(vec.sum(), doctest::Approx(3.f));
}

TEST_CASE("minCoeff")
{
	Vectorf<2> vec({1.f, 2.f});
	CHECK_EQ(vec.minCoeff(), doctest::Approx(1.f));
}

TEST_CASE("maxCoeff")
{
	Vectorf<2> vec({1.f, 2.f});
	CHECK_EQ(vec.maxCoeff(), doctest::Approx(2.f));
}

TEST_CASE("clamp")
{
	Vectorf<2> vec({1.f, 5.f});
	Vectorf<2> min({2.f, 2.f});
	Vectorf<2> max({4.f, 4.f});
	CHECK_EQ(vec.clamp(min, max), Vectorf<2>({2.f, 4.f}));
}

TEST_CASE("equal")
{
	Vectorf<2> vec({1.f, 2.f});
	CHECK_EQ(vec, Vectorf<2>({1.f, 2.f}));
}

TEST_CASE("operator<<")
{
	Vectorf<2>         vec({1.f, 2.f});
	std::ostringstream stream;
	stream << vec;
	CHECK_EQ(stream.str(), "1 2 ");
}

TEST_CASE("midpoint")
{
	Vectorf<2> a({0.f, 0.f});
	Vectorf<2> b({2.f, 4.f});
	CHECK_EQ(midpoint(a, b), Vectorf<2>({1.f, 2.f}));
}

TEST_SUITE_END;
