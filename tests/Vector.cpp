// Copyright 2021 SMS
// License(Apache-2.0)

#include <Math/Math.hpp>
#include <gtest/gtest.h>

TEST(Vector, subscript)
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	EXPECT_FLOAT_EQ(vec[0], 1.f);
	EXPECT_FLOAT_EQ(vec[1], 2.f);
	EXPECT_FLOAT_EQ(vec[2], 3.f);
	EXPECT_FLOAT_EQ(vec[3], 4.f);
	EXPECT_FLOAT_EQ(vec[4], 5.f);
}

TEST(Vector, normalize)
{
	EXPECT_FLOAT_EQ(Vectorf<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalize().size(), 1.f);
	EXPECT_EQ(Vectorf<5>({2.f, 3.f, 4.f, 5.f, 6.f}).normalize(), Vectorf<5>({4.f, 6.f, 8.f, 10.f, 12.f}).normalize());
}

TEST(Vector, dot)
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	EXPECT_FLOAT_EQ(vec.normalized().dot(vec.normalized()), 1.f);
	EXPECT_FLOAT_EQ(vec.normalized().dot(-vec.normalized()), -1.f);
}

TEST(Vector, equal)
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	EXPECT_EQ(vec, Vectorf<5>({1.f, 2.f, 3.f, 4.f, 5.f}));
	EXPECT_NE(vec, Vectorf<5>({0.f, 2.f, 3.f, 4.f, 5.f}));
	EXPECT_NE(vec, Vectorf<5>({1.f, 0.f, 3.f, 4.f, 5.f}));
	EXPECT_NE(vec, Vectorf<5>({1.f, 2.f, 0.f, 4.f, 5.f}));
	EXPECT_NE(vec, Vectorf<5>({1.f, 2.f, 3.f, 0.f, 5.f}));
	EXPECT_NE(vec, Vectorf<5>({1.f, 2.f, 3.f, 4.f, 0.f}));
}


TEST(Vector2, subscript)
{
	Vector2 vec(1.f, 2.f);
	EXPECT_FLOAT_EQ(vec[0], 1.f);
	EXPECT_FLOAT_EQ(vec[1], 2.f);
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
	Vector2 vec(3, 4);
	EXPECT_FLOAT_EQ(vec.normalized().dot(Vector2(3, 4).normalized()), 1.f);
	EXPECT_FLOAT_EQ(vec.normalized().dot(Vector2(4, -3).normalized()), 0.f);
	EXPECT_FLOAT_EQ(vec.normalized().dot(-Vector2(3, 4).normalized()), -1.f);
}

TEST(Vector2, cross)
{
}

TEST(Vector2, angle)
{
	EXPECT_FLOAT_EQ(degrees(Vector2(1, 1).angle()), 45.f);
	EXPECT_FLOAT_EQ(degrees(Vector2(1, std::sqrt(3.f)).angle()), 60.f);
	EXPECT_FLOAT_EQ(degrees(Vector2(std::sqrt(3.f), 1).angle()), 30.f);
}

TEST(Vector2, rotate)
{
	Vector2 v(1, 1);
	v.rotate(Vector2(0, 0), radians(45.f));
	EXPECT_FLOAT_EQ(degrees(v.angle()), 90.f);
}

TEST(Vector2, equal)
{
	Vector2 vec(1, 2);
	EXPECT_EQ(vec, Vector2(1, 2));
	EXPECT_NE(vec, Vector2(0, 2));
	EXPECT_NE(vec, Vector2(1, 0));
}


TEST(Vector3, subscript)
{
	Vector3 vec(1, 2, 3);
	EXPECT_FLOAT_EQ(vec[0], 1.f);
	EXPECT_FLOAT_EQ(vec[1], 2.f);
	EXPECT_FLOAT_EQ(vec[2], 3.f);
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
	Vector3 vec(3, 4, 5);
	EXPECT_FLOAT_EQ(vec.normalized().dot(vec.normalized()), 1.f);
	EXPECT_FLOAT_EQ(vec.normalized().dot(-vec.normalized()), -1.f);
}

TEST(Vector3, equal)
{
	Vector3 vec(1, 2, 3);
	EXPECT_EQ(vec, Vector3(1, 2, 3));
	EXPECT_NE(vec, Vector3(0, 2, 3));
	EXPECT_NE(vec, Vector3(1, 0, 3));
	EXPECT_NE(vec, Vector3(1, 2, 0));
}


TEST(Vector4, subscript)
{
	Vector4 vec(1, 2, 3, 4);
	EXPECT_FLOAT_EQ(vec[0], 1.f);
	EXPECT_FLOAT_EQ(vec[1], 2.f);
	EXPECT_FLOAT_EQ(vec[2], 3.f);
	EXPECT_FLOAT_EQ(vec[3], 4.f);
}

TEST(Vector4, normalize)
{
	EXPECT_FLOAT_EQ(Vector4(3, 4, 5, 6).normalize().size(), 1.f);
	EXPECT_EQ(Vector4(2, 3, 4, 5).normalize(), Vector4(4, 6, 8, 10).normalize());
}

TEST(Vector4, dot)
{
	Vector4 vec(3, 4, 5, 6);
	EXPECT_FLOAT_EQ(vec.normalized().dot(vec.normalized()), 1.f);
	EXPECT_FLOAT_EQ(vec.normalized().dot(-vec.normalized()), -1.f);
}

TEST(Vector4, equal)
{
	Vector4 vec(1, 2, 3, 4);
	EXPECT_EQ(vec, Vector4(1, 2, 3, 4));
	EXPECT_NE(vec, Vector4(0, 2, 3, 4));
	EXPECT_NE(vec, Vector4(1, 0, 3, 4));
	EXPECT_NE(vec, Vector4(1, 2, 0, 4));
	EXPECT_NE(vec, Vector4(1, 2, 3, 0));
}
