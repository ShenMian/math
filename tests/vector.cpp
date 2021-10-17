// Copyright 2021 SMS
// License(Apache-2.0)

#include <gtest/gtest.h>
#include <Math/Math.hpp>
#include <Math/Vector.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>

TEST(Vector2, subscript)
{
    EXPECT_FLOAT_EQ(Vector2(1, 2)[0], 1.f);
    EXPECT_FLOAT_EQ(Vector2(1, 2)[1], 2.f);
}

TEST(Vector2, size)
{
    EXPECT_FLOAT_EQ(Vector2(3, 4).size(), 5.f);
}

TEST(Vector2, sizeSquared)
{
    EXPECT_FLOAT_EQ(Vector2(3, 4).sizeSquared(), (float)std::pow(5.f, 2));
}

TEST(Vector2, normalize)
{
    EXPECT_FLOAT_EQ(Vector2(3, 4).normalize().size(), 1.f);
    EXPECT_EQ(Vector2(2, 3).normalize(), Vector2(4, 6).normalize());
}

TEST(Vector2, dot)
{
    EXPECT_FLOAT_EQ(Vector2(3, 4).normalized().dot(Vector2(3, 4).normalized()), 1.f);
    EXPECT_FLOAT_EQ(Vector2(3, 4).normalized().dot(Vector2(4, -3).normalized()), 0.f);
    EXPECT_FLOAT_EQ(Vector2(3, 4).normalized().dot(-Vector2(3, 4).normalized()), -1.f);
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

TEST(Vector2, rotate)
{
    // Vector2 v(1, 1);
    // v.rotate(Vector2(0, 0), Math::radians(45.f));
    // EXPECT_FLOAT_EQ(Math::degrees(v.angle()), 90.f);
}

TEST(Vector2, equal)
{
    EXPECT_EQ(Vector2(1, 2), Vector2(1, 2));
    EXPECT_NE(Vector2(1, 2), Vector2(0, 2));
    EXPECT_NE(Vector2(1, 2), Vector2(1, 0));
}


TEST(Vector3, subscript)
{
    EXPECT_FLOAT_EQ(Vector3(1, 2, 3)[0], 1.f);
    EXPECT_FLOAT_EQ(Vector3(1, 2, 3)[1], 2.f);
    EXPECT_FLOAT_EQ(Vector3(1, 2, 3)[2], 3.f);
}

TEST(Vector3, size)
{
    EXPECT_FLOAT_EQ(Vector3(3, 4, 5).size(), 5.f * std::sqrt(2.f));
}

TEST(Vector3, sizeSquared)
{
    EXPECT_FLOAT_EQ(Vector3(3, 4, 5).sizeSquared(), (float)std::pow(5.f * std::sqrt(2.f), 2));
}

TEST(Vector3, normalize)
{
    EXPECT_FLOAT_EQ(Vector3(3, 4, 5).normalize().size(), 1.f);
    EXPECT_EQ(Vector3(2, 3, 4).normalize(), Vector3(4, 6, 8).normalize());
}

TEST(Vector3, dot)
{
    EXPECT_FLOAT_EQ(Vector3(3, 4, 5).normalized().dot(Vector3(3, 4, 5).normalized()), 1.f);
    EXPECT_FLOAT_EQ(Vector3(3, 4, 5).normalized().dot(-Vector3(3, 4, 5).normalized()), -1.f);
}

TEST(Vector3, equal)
{
    EXPECT_EQ(Vector3(1, 2, 3), Vector3(1, 2, 3));
    EXPECT_NE(Vector3(1, 2, 3), Vector3(0, 2, 3));
    EXPECT_NE(Vector3(1, 2, 3), Vector3(1, 0, 3));
    EXPECT_NE(Vector3(1, 2, 3), Vector3(1, 2, 0));
}


TEST(Vector4, subscript)
{
    EXPECT_FLOAT_EQ(Vector4(1, 2, 3, 4)[0], 1.f);
    EXPECT_FLOAT_EQ(Vector4(1, 2, 3, 4)[1], 2.f);
    EXPECT_FLOAT_EQ(Vector4(1, 2, 3, 4)[2], 3.f);
    EXPECT_FLOAT_EQ(Vector4(1, 2, 3, 4)[3], 4.f);
}

TEST(Vector4, normalize)
{
    EXPECT_FLOAT_EQ(Vector4(3, 4, 5, 6).normalize().size(), 1.f);
    EXPECT_EQ(Vector4(2, 3, 4, 5).normalize(), Vector4(4, 6, 8, 10).normalize());
}

TEST(Vector4, dot)
{
    EXPECT_FLOAT_EQ(Vector4(3, 4, 5, 6).normalized().dot(Vector4(3, 4, 5, 6).normalized()), 1.f);
    EXPECT_FLOAT_EQ(Vector4(3, 4, 5, 6).normalized().dot(-Vector4(3, 4, 5, 6).normalized()), -1.f);
}


TEST(Vector4, equal)
{
    EXPECT_EQ(Vector4(1, 2, 3, 4), Vector4(1, 2, 3, 4));
    EXPECT_NE(Vector4(1, 2, 3, 4), Vector4(0, 2, 3, 4));
    EXPECT_NE(Vector4(1, 2, 3, 4), Vector4(1, 0, 3, 4));
    EXPECT_NE(Vector4(1, 2, 3, 4), Vector4(1, 2, 0, 4));
    EXPECT_NE(Vector4(1, 2, 3, 4), Vector4(1, 2, 3, 0));
}

TEST(Vector, subscript)
{
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f})[0], 1.f);
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f})[1], 2.f);
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f})[2], 3.f);
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f})[3], 4.f);
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f})[4], 5.f);
}

TEST(Vector, normalize)
{
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalize().size(), 1.f);
    EXPECT_EQ(Vector<5>({2.f, 3.f, 4.f, 5.f, 6.f}).normalize(), Vector<5>({4.f, 6.f, 8.f, 10.f, 12.f}).normalize());
}

TEST(Vector, dot)
{
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalized().dot(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalized()), 1.f);
    EXPECT_FLOAT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalized().dot(-Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalized()), -1.f);
}

TEST(Vector, equal)
{
    EXPECT_EQ(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}), Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}));
    EXPECT_NE(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}), Vector<5>({0.f, 2.f, 3.f, 4.f, 5.f}));
    EXPECT_NE(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}), Vector<5>({1.f, 0.f, 3.f, 4.f, 5.f}));
    EXPECT_NE(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}), Vector<5>({1.f, 2.f, 0.f, 4.f, 5.f}));
    EXPECT_NE(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}), Vector<5>({1.f, 2.f, 3.f, 0.f, 5.f}));
    EXPECT_NE(Vector<5>({1.f, 2.f, 3.f, 4.f, 5.f}), Vector<5>({1.f, 2.f, 3.f, 4.f, 0.f}));
}