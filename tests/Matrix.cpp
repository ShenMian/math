// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(Matrix, element)
{
	Matrix2f a;
	a(0, 0) = 3;
	a(1, 0) = 2.5;
	a(0, 1) = -1;
	a(1, 1) = a(1, 0) + a(0, 1);
	EXPECT_EQ(a, Matrix2f({3, -1, 2.5, 1.5}));
	EXPECT_FLOAT_EQ(a(0, 0), 3.f);
	EXPECT_FLOAT_EQ(a(0, 1), -1.f);
	EXPECT_FLOAT_EQ(a(1, 0), 2.5f);
	EXPECT_FLOAT_EQ(a(1, 1), 1.5f);
}

TEST(Matrix, inverse)
{
	// TODO
}

TEST(Matrix, front_back_right_left_up_down)
{
	auto a = Matrix4f::lookAt(Vector3f::unit, Vector3f::unit - Vector3f::unit_z, Vector3f::up);
	std::cout << a;
	EXPECT_EQ(a.front(), -Vector3f::unit_z);
	EXPECT_EQ(a.back(), Vector3f::unit_z);
	EXPECT_EQ(a.right(), Vector3f::unit_x);
	EXPECT_EQ(a.left(), -Vector3f::unit_x);
	EXPECT_EQ(a.up(), Vector3f::up);
	EXPECT_EQ(a.down(), -Vector3f::up);
}

TEST(Matrix, transpose)
{
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
	EXPECT_EQ(a.transpose(), b);
}

TEST(Matrix, determinant)
{
}

TEST(Matrix, trace)
{
	EXPECT_FLOAT_EQ((Matrixf<3, 3>().trace()), 3);
	EXPECT_FLOAT_EQ((Matrixf<4, 4>().trace()), 4);
	EXPECT_FLOAT_EQ((Matrixf<5, 5>().trace()), 5);
}

TEST(Matrix, sum)
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	EXPECT_FLOAT_EQ(a.sum(), 10.f);
}

TEST(Matrix, minCoeff)
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	EXPECT_FLOAT_EQ(a.minCoeff(), 1.f);
}

TEST(Matrix, maxCoeff)
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	EXPECT_FLOAT_EQ(a.maxCoeff(), 4.f);
}

TEST(Matrix, diagonal)
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	EXPECT_EQ(a.diagonal(), Vector2f(1, 4));
}

TEST(Matrix, addition)
{
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
	EXPECT_EQ(a + b, c);
}

TEST(Matrix, subtraction)
{
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
	EXPECT_EQ(a - b, c);
}

TEST(Matrix, multiplication)
{
	Matrix2f a = {
		1, 2,
		3, 4
	};

	{
		Matrix2f b = {
			2.5, 5,
			7.5, 10
		};
		EXPECT_EQ(2.5f * a, b);
	}
	/*
	{
		Matrix2f b = {
			7, 10,
			15, 22
		};
		EXPECT_EQ(a * a, b);
	}
	*/
}

TEST(Matrix, division)
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	Matrix2f b = {
		0.5, 1,
		1.5, 2
	};
	EXPECT_EQ(a / 2.f, b);
}

TEST(Matrix, translate)
{
	auto a = Matrix4f::identity();
	Matrix4f b = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 2, 2, 1
	};
	EXPECT_EQ(a.translate(Vector3f(2.f)), b);
}

TEST(Matrix, scale)
{
}

TEST(Matrix, createTranslate)
{
	auto a = Matrix4f::identity();
	Matrix4f b = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 2, 2, 1
	};
	EXPECT_EQ(a.createTranslate(Vector3f(2.f)), b);
}

TEST(Matrix, createRotation)
{
	auto a = Matrix4f::createRotation(radians(90.f), Vector3f::unit_z);
	EXPECT_EQ(a * Vector4f({1.f, 0.f, 0.f, 1.f}), Vector4f({0.f, 1.f, 0.f, 1.f}));
}

TEST(Matrix, createScale)
{
	auto a = Matrix4f::identity();
	Matrix4f b = {
		2, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 2, 0,
		0, 0, 0, 1
	};
	EXPECT_EQ(a.createScale(Vector3f(2.f)), b);
}

TEST(Matrix, perspective)
{
	// TODO
	Matrix4f::perspective(radians(60.f), 1 / 1, -1, 1);
}

TEST(Matrix, orthographic)
{
	// TODO
	Matrix4f::orthogonal(-1, 1, -1, 1, -1, 1);
}

TEST(Matrix, lookAt)
{
	// TODO
	Matrix4f::lookAt(Vector3f(1.f), Vector3f(0.f), Vector3f(0.f, 1.f, 0.f));
}

TEST(Matrix, identity)
{
	Matrix2f a = {
		1, 0,
		0, 1
	};
	EXPECT_EQ(Matrix2f::identity(), a);
}

TEST(Matrix, zero)
{
	Matrix2f a = {
		0, 0,
		0, 0
	};
	Matrixf<3, 4> b = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};
	EXPECT_EQ(Matrix2f::zero(), a);
	EXPECT_EQ((Matrixf<3, 4>::zero()), b);
}

TEST(Matrix, io)
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	std::ostringstream stream;
	stream << a;
	EXPECT_EQ(stream.str(), " 1.00  2.00\n 3.00  4.00\n");
}
