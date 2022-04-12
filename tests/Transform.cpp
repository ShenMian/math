// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(Transform, position)
{
	Transform trans;
	trans.position() = {1, 2, 3};

    Vector3f a = {1, 2, 3};
    Vector3f b;
    trans.matrix().decompose(&b, nullptr, nullptr);
	EXPECT_EQ(a, b);
}

TEST(Transform, scale)
{
	Transform trans;
	trans.scale() = {1, 2, 3};

    Vector3f a = {1, 2, 3};
    Vector3f b;
    trans.matrix().decompose(nullptr, nullptr, &b);
	EXPECT_EQ(a, b);
}
