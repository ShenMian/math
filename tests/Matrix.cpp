// Copyright 2021 SMS
// License(Apache-2.0)

#include <math/math.hpp>
#include <doctest/doctest.h>
#include <sstream>

TEST_CASE("Matrix::operator()")
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

TEST_CASE("Matrix::inverse")
{
	// TODO
}

TEST_CASE("Matrix::transpose")
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
	CHECK_EQ(a.transpose(), b);
}

TEST_CASE("Matrix::determinant")
{
}

TEST_CASE("Matrix::trace")
{
	CHECK_EQ((Matrixf<3, 3>().trace()), doctest::Approx(3.f));
	CHECK_EQ((Matrixf<4, 4>().trace()), doctest::Approx(4.f));
	CHECK_EQ((Matrixf<5, 5>().trace()), doctest::Approx(5.f));
}

TEST_CASE("Matrix::sum")
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	CHECK_EQ(a.sum(), doctest::Approx(10.f));
}

TEST_CASE("Matrix::minCoeff")
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	CHECK_EQ(a.minCoeff(), doctest::Approx(1.f));
}

TEST_CASE("Matrix::maxCoeff")
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	CHECK_EQ(a.maxCoeff(), doctest::Approx(4.f));
}

TEST_CASE("Matrix::diagonal")
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	CHECK_EQ(a.diagonal(), Vector2f(1, 4));
}

TEST_CASE("Matrix::translate")
{
	auto a = Matrix4f::identity();
	Matrix4f b = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 2, 2, 1
	};
	CHECK_EQ(a.translate(Vector3f(2.f)), b);
}

TEST_CASE("Matrix::scale")
{
}

TEST_CASE("Matrix::front/back/right/left/up/down")
{
    auto a = Matrix4f::lookAt(Vector3f::unit, Vector3f::unit - Vector3f::unit_z, Vector3f::up);
    CHECK_EQ(a.front(), -Vector3f::unit_z);
    CHECK_EQ(a.back(), Vector3f::unit_z);
    CHECK_EQ(a.right(), Vector3f::unit_x);
    CHECK_EQ(a.left(), -Vector3f::unit_x);
    CHECK_EQ(a.up(), Vector3f::up);
    CHECK_EQ(a.down(), -Vector3f::up);
}

TEST_CASE("Matrix::createTranslate")
{
	auto a = Matrix4f::identity();
	Matrix4f b = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 2, 2, 1
	};
	CHECK_EQ(a.createTranslate(Vector3f(2.f)), b);
}

TEST_CASE("Matrix::createRotation")
{
	auto a = Matrix4f::createRotation(radians(90.f), Vector3f::unit_z);
	CHECK_EQ(a * Vector4f({1.f, 0.f, 0.f, 1.f}), Vector4f({0.f, 1.f, 0.f, 1.f}));
}

TEST_CASE("Matrix::createScale")
{
	auto a = Matrix4f::identity();
	Matrix4f b = {
		2, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 2, 0,
		0, 0, 0, 1
	};
	CHECK_EQ(a.createScale(Vector3f(2.f)), b);
}

TEST_CASE("Matrix::perspective")
{
	// TODO
	Matrix4f::perspective(radians(60.f), 1 / 1, -1, 1);
}

TEST_CASE("Matrix::orthographic")
{
	// TODO
	Matrix4f::orthogonal(-1, 1, -1, 1, -1, 1);
}

TEST_CASE("Matrix::lookAt")
{
	// TODO
	Matrix4f::lookAt(Vector3f(1.f), Vector3f(0.f), Vector3f(0.f, 1.f, 0.f));
}

TEST_CASE("Matrix::identity")
{
	Matrix2f a = {
		1, 0,
		0, 1
	};
	CHECK_EQ(Matrix2f::identity(), a);
}

TEST_CASE("Matrix::zero")
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
	CHECK_EQ(Matrix2f::zero(), a);
	CHECK_EQ((Matrixf<3, 4>::zero()), b);
}

TEST_CASE("Matrix::addition")
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
    CHECK_EQ(a + b, c);
}

TEST_CASE("Matrix::subtraction")
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
    CHECK_EQ(a - b, c);
}

TEST_CASE("Matrix::multiplication")
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

TEST_CASE("Matrix::division")
{
    Matrix2f a = {
            1, 2,
            3, 4
    };
    Matrix2f b = {
            0.5, 1,
            1.5, 2
    };
    CHECK_EQ(a / 2.f, b);
}

TEST_CASE("Matrix::io")
{
	Matrix2f a = {
		1, 2,
		3, 4
	};
	std::ostringstream stream;
	stream << a;
	CHECK_EQ(stream.str(), " 1.00  2.00\n 3.00  4.00\n");
}
