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

TEST_SUITE_END;
