// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Quaternion.hpp>
#include <gtest/gtest.h>

TEST(Quaternion, eular)
{
	Quaternion    quat;
	const Vector3 angles(1, 2, 3);
	quat.eular(angles);
	// EXPECT_EQ(quat.eular(), angles);
}
