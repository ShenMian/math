// Copyright 2021 SMS
// License(Apache-2.0)

#include <math/math.hpp>
#include <doctest/doctest.h>

TEST_CASE("Quaternion::eular")
{
	Quaternion    quat;
	const Vector3 angles(1, 2, 3);
	quat.eular(angles);
	// EXPECT_EQ(quat.eular(), angles);
}

TEST_CASE("Quaternion::normalize")
{
	Quaternion quat(0.f, 0.f, 0.f, 0.f);
	CHECK_EQ(quat.normalize(), quat);
}
