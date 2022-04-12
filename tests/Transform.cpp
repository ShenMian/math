// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(Transform, position)
{
	Transform trans;
	trans.position() = {1, 2, 3};

	Matrix4f a = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 2, 3, 1
	};
	EXPECT_EQ(trans.matrix(), a);
}

TEST(Transform, scale)
{
	Transform trans;
	trans.scale() = {1, 2, 3};

	Matrix4f a = {
		1, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 3, 0,
		0, 0, 0, 1
	};
	EXPECT_EQ(trans.matrix(), a);
}
