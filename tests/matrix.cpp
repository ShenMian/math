// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>
#include <sstream>

TEST_SUITE_BEGIN("matrix");

TEST_CASE("transpose")
{
	// clang-format off
	Matrix3f a = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};
	Matrix3f b = {
		1, 4, 7,
		2, 5, 8,
		3, 6, 9
	};
	// clang-format on
	CHECK_EQ(a.transpose(), b);
}

TEST_CASE("trace")
{
	CHECK_EQ((Matrixf<3, 3>().trace()), doctest::Approx(3.f));
	CHECK_EQ((Matrixf<4, 4>().trace()), doctest::Approx(4.f));
	CHECK_EQ((Matrixf<5, 5>().trace()), doctest::Approx(5.f));
}

TEST_CASE("sum")
{
	// clang-format off
	Matrix2f a = {
		1, 2,
		3, 4
	};
	// clang-format on
	CHECK_EQ(a.sum(), doctest::Approx(10.f));
}

TEST_CASE("min_coeff")
{
	// clang-format off
	Matrix2f a = {
		1, 2,
		3, 4
	};
	// clang-format on
	CHECK_EQ(a.min_coeff(), doctest::Approx(1.f));
}

TEST_CASE("max_coeff")
{
	// clang-format off
	Matrix2f a = {
		1, 2,
		3, 4
	};
	// clang-format on
	CHECK_EQ(a.max_coeff(), doctest::Approx(4.f));
}

TEST_CASE("diagonal")
{
	// clang-format off
	Matrix2f a = {
		1, 2,
		3, 4
	};
	// clang-format on
	CHECK_EQ(a.diagonal(), Vector2f({1, 4}));
}

TEST_CASE("translate")
{
	auto a = Matrix4f::identity();
	// clang-format off
	Matrix4f b = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 2, 2, 1
	};
	// clang-format on
	CHECK_EQ(a.translate(Vector3f(2.f)), b);
}

TEST_CASE("front/back/right/left/up/down")
{
	// TODO
	// auto mat = Matrix4f::look_at(Vector3f::unit, Vector3f::unit - Vector3f::unit_z, Vector3f::up);
	//
	// SUBCASE("front")
	// {
	// 	CHECK_EQ(mat.front(), -Vector3f::unit_z);
	// }
	//
	// SUBCASE("back")
	// {
	// 	CHECK_EQ(mat.back(), Vector3f::unit_z);
	// }
	//
	// SUBCASE("right")
	// {
	// 	CHECK_EQ(mat.right(), Vector3f::unit_x);
	// }
	//
	// SUBCASE("left")
	// {
	// 	CHECK_EQ(mat.left(), -Vector3f::unit_x);
	// }
	//
	// SUBCASE("up")
	// {
	// 	CHECK_EQ(mat.up(), Vector3f::up);
	// }
	//
	// SUBCASE("down")
	// {
	// 	CHECK_EQ(mat.down(), -Vector3f::up);
	// }
}

TEST_CASE("decompose/recompose" * doctest::skip(true))
{
	Matrix4f mat;
	mat.recompose({1.f, 2.f, 3.f}, {30.f, 60.f, 90.f, 1.f}, {2.f, 2.f, 2.f});

	Vector3    translation;
	Quaternion rotation;
	Vector3    scale;
	mat.decompose(&translation, &rotation, &scale);

	// TODO
	CHECK_EQ(translation, Vector3({1.f, 2.f, 3.f}));
	CHECK_EQ(rotation, Quaternion(30.f, 60.f, 90.f, 1.f));
	CHECK_EQ(scale, Vector3({2.f, 2.f, 2.f}));
}

TEST_CASE("operator==")
{
	// clang-format off
	Matrix2f a = {
		1, 2,
		3, 4
	};
	Matrix2f b = {
		1, 2,
		3, 4
	};
	Matrix2f c = {
		0, 2,
		3, 4
	};
	// clang-format on

	CHECK_EQ(a, b);
	CHECK_NE(a, c);
}

TEST_CASE("operator()")
{
	Matrix2f a;
	a(0, 0) = 3;
	a(1, 0) = 2.5;
	a(0, 1) = -1;
	a(1, 1) = a(1, 0) + a(0, 1);
	CHECK_EQ(a, Matrix2f({3, -1, 2.5, 1.5}));
	CHECK_EQ(a(0, 0), doctest::Approx(3.f));
	CHECK_EQ(a(0, 1), doctest::Approx(-1.f));
	CHECK_EQ(a(1, 0), doctest::Approx(2.5f));
	CHECK_EQ(a(1, 1), doctest::Approx(1.5f));
}

TEST_CASE("translate")
{
	auto a = Matrix4f::identity();
	// clang-format off
	Matrix4f b = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 2, 2, 1
	};
	// clang-format on
	CHECK_EQ(a.translate(Vector3f(2.f)), b);
}

TEST_CASE("rotation")
{
	// TODO
	// auto a = Matrix4f::create_rotation(radians(90.f), Vector3f::unit_z);
	// CHECK_EQ(a * Vectorf<4>({1.f, 0.f, 0.f, 1.f}), Vectorf<4>({0.f, 1.f, 0.f, 1.f}));
}

TEST_CASE("create_scale")
{
	auto a = Matrix4f::identity();
	// clang-format off
	Matrix4f b = {
		2, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 2, 0,
		0, 0, 0, 1
	};
	// clang-format on
	CHECK_EQ(a.create_scale(Vector3f(2.f)), b);
}

TEST_CASE("perspective" * doctest::skip(true))
{
	// TODO
	Matrix4f::perspective(radians(60.f), 1 / 1, -1, 1);
}

TEST_CASE("orthographic" * doctest::skip(true))
{
	// TODO
	Matrix4f::orthogonal(-1, 1, -1, 1, -1, 1);
}

TEST_CASE("look_at" * doctest::skip(true))
{
	// TODO
	Matrix4f::look_at(Vector3f(1.f), Vector3f(0.f), Vector3f({0.f, 1.f, 0.f}));
}

TEST_CASE("identity")
{
	// clang-format off
	Matrix2f a = {
		1, 0,
		0, 1
	};
	// clang-format on
	CHECK_EQ(Matrix2f::identity(), a);
}

TEST_CASE("zero")
{
	// clang-format off
	Matrix2f a = {
		0, 0,
		0, 0
	};
	Matrixf<3, 4> b = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};
	// clang-format on
	CHECK_EQ(Matrix2f::zero(), a);
	CHECK_EQ((Matrixf<3, 4>::zero()), b);
}

TEST_CASE("addition")
{
	// clang-format off
	Matrix2d a = {
			1, 2,
			3, 4
	};
	Matrix2d b = {
			2, 3,
			1, 4
	};

	Matrix2d c = {
			3, 5,
			4, 8
	};
	// clang-format on
	CHECK_EQ(a + b, c);
}

TEST_CASE("subtraction")
{
	// clang-format off
	Matrix2d a = {
			1, 2,
			3, 4
	};
	Matrix2d b = {
			2, 3,
			1, 4
	};

	Matrix2d c = {
			-1, -1,
			2, 0
	};
	// clang-format on
	CHECK_EQ(a - b, c);
}

TEST_CASE("multiplication")
{
	// clang-format off
	Matrix2f a = {
			1, 2,
			3, 4
	};
	// clang-format on

	{
		// clang-format off
		Matrix2f b = {
				2.5, 5,
				7.5, 10
		};
		// clang-format on
		CHECK_EQ(2.5f * a, b);
	}
	/*
	{
	    Matrix2f b = {
	        7, 10,
	        15, 22
	    };
	    CHECK_EQ(a * a, b);
	}
	*/
}

TEST_CASE("division")
{
	// clang-format off
	Matrix2f a = {
			1, 2,
			3, 4
	};
	Matrix2f b = {
			0.5, 1,
			1.5, 2
	};
	// clang-format on
	CHECK_EQ(a / 2.f, b);
}

TEST_CASE("operator<<")
{
	{
		// clang-format off
		Matrix2f a = {
			1, 2,
			3, 4
		};
		// clang-format on
		std::ostringstream stream;
		stream << a;
		CHECK_EQ(stream.str(), "1 2 \n3 4 \n");
	}

	{
		// clang-format off
		Matrix3f a = {
			1.11, 2,    3.33,
			4,    5,    6,
			7,    8.89, 9
		};
		// clang-format on
		std::ostringstream stream;
		stream << a;
		CHECK_EQ(stream.str(), "1.11    2 3.33 \n   4    5    6 \n   7 8.89    9 \n");
	}
}

TEST_SUITE_END;
