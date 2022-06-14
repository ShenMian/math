// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <doctest/doctest.h>

TEST_CASE("Quaternion::eular")
{
	Quaternion    quat;
	const Vector3 angles(1, 2, 3);
	quat.eular(angles);
	// EXPECT_EQ(quat.eular(), angles);
}
