// Copyright 2021 SMS
// License(Apache-2.0)

#include <math/math.hpp>
#include <doctest/doctest.h>

TEST_CASE("Transform::position")
{
	Vector3f a = {1, 2, 3};

	Transform trans;
	trans.position() = a;

	Vector3f b;
	trans.matrix().decompose(&b, nullptr, nullptr);
	CHECK_EQ(a, b);
}

TEST_CASE("Transform::scale")
{
	Vector3f a = {1, 2, 3};

	Transform trans;
	trans.scale() = a;

	Vector3f b;
	trans.matrix().decompose(nullptr, nullptr, &b);
	CHECK_EQ(a, b);
}
