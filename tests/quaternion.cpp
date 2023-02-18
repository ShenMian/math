// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_SUITE_BEGIN("quaternion");

TEST_CASE("eular")
{
	Quaternion quat;
	Vector3    angles(radians(30.f), radians(60.f), radians(90.f));
	quat.eular(angles);
	CHECK_EQ(quat.eular(), angles);

	quat.eular(quat.eular());
	CHECK_EQ(quat.eular(), angles);
}

TEST_CASE("normalize")
{
	Quaternion quat(0.f, 0.f, 0.f, 0.f);
	CHECK_EQ(quat.normalize(), quat);
}

TEST_CASE("QuaternionT constructor from matrix" * doctest::skip(true)) // TOOD: AI 生成
{
	// clang-format off
	Matrix4T<float> mat = {
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
	// clang-format on
    QuaternionT<float> q(mat);

    CHECK_EQ(q.x, doctest::Approx(0.5f));
    CHECK_EQ(q.y, doctest::Approx(0.5f));
    CHECK_EQ(q.z, doctest::Approx(0.5f));
    CHECK_EQ(q.w, doctest::Approx(0.5f));
}

TEST_CASE("QuaternionT eular angles" * doctest::skip(true)) // TOOD: AI 生成
{
    Vector3T<float> angles(0.5f, 1.2f, 0.8f);
    QuaternionT<float> q;
    q.eular(angles);

    CHECK_EQ(q.x, doctest::Approx(0.1320427f));
	CHECK_EQ(q.y, doctest::Approx(0.5997445f));
	CHECK_EQ(q.z, doctest::Approx(0.2541122f));
	CHECK_EQ(q.w, doctest::Approx(0.7401726f));

    Vector3T<float> new_angles = q.eular();
    CHECK_EQ(new_angles.x, angles.x);
    CHECK_EQ(new_angles.y, angles.y);
    CHECK_EQ(new_angles.z, angles.z);
}

TEST_CASE("QuaternionT inverse")
{
    QuaternionT<float> q(1.0f, 2.0f, 3.0f, 4.0f);
    QuaternionT<float> inverse = q.inverse();

    CHECK_EQ(inverse.x, doctest::Approx(-0.03333333f));
	CHECK_EQ(inverse.y, doctest::Approx(-0.06666667f));
	CHECK_EQ(inverse.z, doctest::Approx(-0.1f));
	CHECK_EQ(inverse.w, doctest::Approx(0.13333333f));
}

TEST_SUITE_END;
