// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

template <typename T>
class Vector2
{
public:
	Vector2() = default;

	explicit Vector2(const T& x, const T& y)
	{}

	static const size_t size = 2;

private:
	T v_[2];
};
