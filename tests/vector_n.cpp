// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>
#include <sstream>

TEST_SUITE_BEGIN("vector_n");

TEST_CASE("operator[]")
{
	Vector2 vec({1.f, 2.f});
	CHECK_EQ(vec[0], doctest::Approx(1.f));
	CHECK_EQ(vec[1], doctest::Approx(2.f));
}

TEST_CASE("norm")
{
	CHECK_EQ(Vector2({3.f, 4.f}).norm(), doctest::Approx(5.f));
	CHECK_EQ(Vector2({6.f, 8.f}).norm(), doctest::Approx(10.f));
	CHECK_EQ(Vector2({7.f, 24.f}).norm(), doctest::Approx(25.f));
	CHECK_EQ(Vector2({8.f, 15.f}).norm(), doctest::Approx(17.f));
	CHECK_EQ(Vector2({9.f, 40.f}).norm(), doctest::Approx(41.f));
}

TEST_CASE("norm_sq")
{
	CHECK_EQ(Vector2({3, 4}).norm_sq(), doctest::Approx((float)std::pow(5.f, 2)));
}

TEST_CASE("normalize")
{
	CHECK_EQ(Vector2({3, 4}).normalize().norm(), doctest::Approx(1.f));
	CHECK_EQ(Vector2({2, 3}).normalize(), Vector2({4, 6}).normalize());
}

TEST_CASE("dot")
{
	Vector2 vec({3, 4});
	CHECK_EQ(vec.normalized().dot(Vector2({3, 4}).normalized()), doctest::Approx(1.f));
	CHECK_EQ(vec.normalized().dot(Vector2({4, -3}).normalized()), doctest::Approx(0.f));
	CHECK_EQ(vec.normalized().dot(-Vector2({3, 4}).normalized()), doctest::Approx(-1.f));
}

TEST_CASE("cross" * doctest::skip())
{
	CHECK(false);
}

TEST_CASE("angle")
{
	// CHECK_EQ(degrees(Vector2({1, 1}).angle()), doctest::Approx(45.f));
	// CHECK_EQ(degrees(Vector2({1, std::sqrt(3.f)).angle()}), doctest::Approx(60.f));
	// CHECK_EQ(degrees(Vector2({std::sqrt(3.f), 1).angle()}), doctest::Approx(30.f));
}

TEST_CASE("rotate")
{
	// Vector2 v({1, 1});
	// v.rotate(Vector2({0, 0}), radians(45.f));
	// CHECK_EQ(degrees(v.angle()), doctest::Approx(90.f));
}

TEST_CASE("equal")
{
	Vector2 vec({1, 2});
	CHECK_EQ(vec, Vector2({1, 2}));
	CHECK_NE(vec, Vector2({0, 2}));
	CHECK_NE(vec, Vector2({1, 0}));
}

TEST_CASE("operator<<")
{
	Vector2            vec({1, 2});
	std::ostringstream stream;
	stream << vec;
	CHECK_EQ(stream.str(), "1 2 ");
}


TEST_CASE("operator[]")
{
	Vectorf<3> vec({1, 2, 3});
	CHECK_EQ(vec[0], doctest::Approx(1.f));
	CHECK_EQ(vec[1], doctest::Approx(2.f));
	CHECK_EQ(vec[2], doctest::Approx(3.f));
}

TEST_CASE("norm")
{
	CHECK_EQ(Vectorf<3>({3, 4, 5}).norm(), doctest::Approx(5.f * std::sqrt(2.f)));
}

TEST_CASE("norm_sq")
{
	CHECK_EQ(Vectorf<3>({3, 4, 5}).norm_sq(), doctest::Approx((float)std::pow(5.f * std::sqrt(2.f), 2)));
}

TEST_CASE("normalize")
{
	CHECK_EQ(Vectorf<3>({3, 4, 5}).normalize().norm(), doctest::Approx(1.f));
	CHECK_EQ(Vectorf<3>({2, 3, 4}).normalize(), Vectorf<3>({4, 6, 8}).normalize());
}

TEST_CASE("dot")
{
	Vectorf<3> vec({3, 4, 5});
	CHECK_EQ(vec.normalized().dot(vec.normalized()), doctest::Approx(1.f));
	CHECK_EQ(vec.normalized().dot(-vec.normalized()), doctest::Approx(-1.f));
}

TEST_CASE("cross" * doctest::skip())
{
	Vectorf<3> v({1, 2, 3});
	Vectorf<3> w({0, 1, 2});
	CHECK_EQ(v.cross(w), Vectorf<3>({1, -2, 1}));
}

TEST_CASE("equal")
{
	Vectorf<3> vec({1, 2, 3});
	CHECK_EQ(vec, Vectorf<3>({1, 2, 3}));
	CHECK_NE(vec, Vectorf<3>({0, 2, 3}));
	CHECK_NE(vec, Vectorf<3>({1, 0, 3}));
	CHECK_NE(vec, Vectorf<3>({1, 2, 0}));
}

TEST_CASE("lerp")
{
	CHECK_EQ(lerp(Vectorf<3>(0), Vectorf<3>(1), 0.5f), Vectorf<3>(0.5));
}

TEST_CASE("operator<<")
{
	Vectorf<3>         vec({1, 2, 3});
	std::ostringstream stream;
	stream << vec;
	CHECK_EQ(stream.str(), "1 2 3 ");
}

TEST_CASE("operator[]")
{
	Vectorf<4> vec({1, 2, 3, 4});
	CHECK_EQ(vec[0], doctest::Approx(1.f));
	CHECK_EQ(vec[1], doctest::Approx(2.f));
	CHECK_EQ(vec[2], doctest::Approx(3.f));
	CHECK_EQ(vec[3], doctest::Approx(4.f));
}

TEST_CASE("normalize")
{
	CHECK_EQ(Vectorf<4>({3, 4, 5, 6}).normalize().norm(), doctest::Approx(1.f));
	CHECK_EQ(Vectorf<4>({2, 3, 4, 5}).normalize(), Vectorf<4>({4, 6, 8, 10}).normalize());
}

TEST_CASE("dot")
{
	Vectorf<4> vec({3, 4, 5, 6});
	CHECK_EQ(vec.normalized().dot(vec.normalized()), doctest::Approx(1.f));
	CHECK_EQ(vec.normalized().dot(-vec.normalized()), doctest::Approx(-1.f));
}

TEST_CASE("equal")
{
	Vectorf<4> vec({1, 2, 3, 4});
	CHECK_EQ(vec, Vectorf<4>({1, 2, 3, 4}));
	CHECK_NE(vec, Vectorf<4>({0, 2, 3, 4}));
	CHECK_NE(vec, Vectorf<4>({1, 0, 3, 4}));
	CHECK_NE(vec, Vectorf<4>({1, 2, 0, 4}));
	CHECK_NE(vec, Vectorf<4>({1, 2, 3, 0}));
}

TEST_CASE("operator<<")
{
	Vectorf<4>         vec({1, 2, 3, 4});
	std::ostringstream stream;
	stream << vec;
	CHECK_EQ(stream.str(), "1 2 3 4 ");
}

TEST_SUITE_END;
