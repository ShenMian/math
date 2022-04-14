// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(Transform, position)
{
    Vector3f a = {1, 2, 3};

	Transform trans;
	trans.position() = a;

    Vector3f b;
    trans.matrix().decompose(&b, nullptr, nullptr);
	EXPECT_EQ(a, b);
}

TEST(Transform, scale)
{
    Vector3f a = {1, 2, 3};

	Transform trans;
	trans.scale() = a;

    Vector3f b;
    trans.matrix().decompose(nullptr, nullptr, &b);
	EXPECT_EQ(a, b);
}
