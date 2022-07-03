// Copyright 2021 SMS
// License(Apache-2.0)

#include <math/math.hpp>
#include <doctest/doctest.h>
#include <sstream>

TEST_CASE("Vector::subscript")
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	CHECK_EQ(vec[0], doctest::Approx(1.f));
	CHECK_EQ(vec[1], doctest::Approx(2.f));
	CHECK_EQ(vec[2], doctest::Approx(3.f));
	CHECK_EQ(vec[3], doctest::Approx(4.f));
	CHECK_EQ(vec[4], doctest::Approx(5.f));
}

TEST_CASE("Vector::norm")
{
	// TODO: 以下代码目前测试的是 VectorT<T, 2>的实现
	CHECK_EQ(Vectorf<2>({3.f, 4.f}).norm(), doctest::Approx(5.f));
	CHECK_EQ(Vectorf<2>({6.f, 8.f}).norm(), doctest::Approx(10.f));
	CHECK_EQ(Vectorf<2>({7.f, 24.f}).norm(), doctest::Approx(25.f));
	CHECK_EQ(Vectorf<2>({8.f, 15.f}).norm(), doctest::Approx(17.f));
	CHECK_EQ(Vectorf<2>({9.f, 40.f}).norm(), doctest::Approx(41.f));
}

TEST_CASE("Vector::normalize")
{
	CHECK_EQ(Vectorf<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalize().norm(), doctest::Approx(1.f));
	CHECK_EQ(Vectorf<5>({2.f, 3.f, 4.f, 5.f, 6.f}).normalize(), Vectorf<5>({4.f, 6.f, 8.f, 10.f, 12.f}).normalize());
    CHECK_EQ(Vectorf<5>(0.f).normalize(), Vectorf<5>(0.f));
}

TEST_CASE("Vector::dot")
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	CHECK_EQ(vec.normalized().dot(vec.normalized()), doctest::Approx(1.f));
	CHECK_EQ(vec.normalized().dot(-vec.normalized()), doctest::Approx(-1.f));
}

TEST_CASE("Vector::sum")
{
    Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
    CHECK_EQ(vec.sum(), doctest::Approx(15.f));
}

TEST_CASE("Vector::minCoeff")
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	CHECK_EQ(vec.minCoeff(), doctest::Approx(1.f));
}

TEST_CASE("Vector::maxCoeff")
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	CHECK_EQ(vec.maxCoeff(), doctest::Approx(5.f));
}

TEST_CASE("Vector::clamp")
{
    Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
    Vectorf<5> min({2.f, 2.f, 2.f, 2.f, 2.f});
    Vectorf<5> max({4.f, 4.f, 4.f, 4.f, 4.f});
    CHECK_EQ(vec.clamp(min, max), Vectorf<5>({2.f, 2.f, 3.f, 4.f, 4.f}));
}

TEST_CASE("Vector::equal")
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	CHECK_EQ(vec, Vectorf<5>({1.f, 2.f, 3.f, 4.f, 5.f}));
	CHECK_NE(vec, Vectorf<5>({0.f, 2.f, 3.f, 4.f, 5.f}));
	CHECK_NE(vec, Vectorf<5>({1.f, 0.f, 3.f, 4.f, 5.f}));
	CHECK_NE(vec, Vectorf<5>({1.f, 2.f, 0.f, 4.f, 5.f}));
	CHECK_NE(vec, Vectorf<5>({1.f, 2.f, 3.f, 0.f, 5.f}));
	CHECK_NE(vec, Vectorf<5>({1.f, 2.f, 3.f, 4.f, 0.f}));
}

TEST_CASE("Vector::io")
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	std::ostringstream stream;
	stream << vec;
	CHECK_EQ(stream.str(), " 1.00  2.00  3.00  4.00  5.00");
}
