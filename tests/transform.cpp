// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <doctest/doctest.h>
#include <math/math.hpp>

TEST_SUITE_BEGIN("transform");

TEST_CASE("constructor" * doctest::skip(true))
{
	Matrix4f mat;
	mat.recompose(Vector3({1.f, 2.f, 3.f}), Quaternion(0.1f, 0.2f, 0.3f, 0.4f), Vector3({2.f, 3.f, 4.f}));
	Transform transform(mat);
	CHECK(transform.translation() == Vector3({1.f, 2.f, 3.f}));
	CHECK(transform.rotation() == Quaternion(0.1f, 0.2f, 0.3f, 0.4f));
	CHECK(transform.scale() == Vector3({2.f, 3.f, 4.f}));
}

TEST_CASE("translation")
{
	Vector3f a = {1, 2, 3};

	Transform trans;
	trans.translation() = a;

	Vector3f b;
	trans.matrix().decompose(&b, nullptr, nullptr);
	CHECK_EQ(a, b);
}

TEST_CASE("scale")
{
	Vector3f a = {1, 2, 3};

	Transform trans;
	trans.scale() = a;

	Vector3f b;
	trans.matrix().decompose(nullptr, nullptr, &b);
	CHECK_EQ(a, b);
}

TEST_SUITE_END;
