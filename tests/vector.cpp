// Copyright 2021 SMS
// License(Apache-2.0)

#include "gtest/gtest.h"
#include "Math.hpp"
#include "Vector2.hpp"

TEST(Vector2, subscript)
{
    EXPECT_EQ(Vector2(3, 4)[0], 3);
    EXPECT_EQ(Vector2(3, 4)[1], 4);
}

TEST(Vector2, size)
{
    EXPECT_EQ(Vector2(3, 4).size(), 5);
}

TEST(Vector2, sizeSquared)
{
    EXPECT_EQ(Vector2(3, 4).sizeSquared(), 5 * 5);
}

TEST(Vector2, normalize)
{
    EXPECT_EQ(Vector2(3, 4).normalize().size(), 1);
    EXPECT_EQ(Vector2(3, 4).normalize(), Vector2(6, 8).normalize());
}

TEST(Vector2, dot)
{
}

TEST(Vector2, cross)
{
}

TEST(Vector2, angle)
{
    EXPECT_FLOAT_EQ(Math::degrees(Vector2(1, 1).angle()), 45.f);
    // EXPECT_FLOAT_EQ(Math::degrees(Vector2(1, 2).angle()), 60.f);
    // EXPECT_EQ(Math::degrees(Vector2(2, 1).angle()), 30);
}

TEST(Vector2, equal)
{
    EXPECT_EQ(Vector2(3, 4), Vector2(3, 4));
}