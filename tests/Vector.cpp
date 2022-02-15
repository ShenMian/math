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

TEST(Vector, norm)
{
	// TODO: 以下代码目前测试的是 VectorT<T, 2>的实现
	EXPECT_FLOAT_EQ(Vectorf<2>({3.f, 4.f}).norm(), 5.f);
	EXPECT_FLOAT_EQ(Vectorf<2>({6.f, 8.f}).norm(), 10.f);
	EXPECT_FLOAT_EQ(Vectorf<2>({7.f, 24.f}).norm(), 25.f);
	EXPECT_FLOAT_EQ(Vectorf<2>({8.f, 15.f}).norm(), 17.f);
	EXPECT_FLOAT_EQ(Vectorf<2>({9.f, 40.f}).norm(), 41.f);
}

TEST(Vector, normalize)
{
	EXPECT_FLOAT_EQ(Vectorf<5>({1.f, 2.f, 3.f, 4.f, 5.f}).normalize().norm(), 1.f);
	EXPECT_EQ(Vectorf<5>({2.f, 3.f, 4.f, 5.f, 6.f}).normalize(), Vectorf<5>({4.f, 6.f, 8.f, 10.f, 12.f}).normalize());
}

TEST(Vector, dot)
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	EXPECT_FLOAT_EQ(vec.normalized().dot(vec.normalized()), 1.f);
	EXPECT_FLOAT_EQ(vec.normalized().dot(-vec.normalized()), -1.f);
}

TEST(Vector, sum)
{
    Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
    EXPECT_FLOAT_EQ(vec.sum(), 15.f);
}

TEST(Vector, minCoeff)
{
    Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
    EXPECT_FLOAT_EQ(vec.minCoeff(), 1.f);
}

TEST(Vector, maxCoeff)
{
    Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
    EXPECT_FLOAT_EQ(vec.maxCoeff(), 5.f);
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

TEST(Vector, io)
{
	Vectorf<5> vec({1.f, 2.f, 3.f, 4.f, 5.f});
	std::ostringstream stream;
	stream << vec;
	EXPECT_EQ(stream.str(), " 1.00  2.00  3.00  4.00  5.00");
}
