﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.hpp"

inline AABB3::AABB3(const Vector3& a, const Vector3& b)
{
	if(a.x < b.x && a.y < b.y && a.z < b.z)
		min = a, max = b;
	else
		min = b, max = a;
}

inline bool AABB3::contains(const Vector3& p) const
{
	assert(isValid());
	return (min.x <= p.x && p.x <= max.x) && (min.y <= p.y && p.y <= max.y);
}

inline bool AABB3::contains(const AABB3& aabb) const
{
	assert(isValid() && aabb.isValid());
	return contains(aabb.min) && contains(aabb.max);
}

inline bool AABB3::intersects(const AABB3& aabb) const
{
	assert(isValid() && aabb.isValid());
	return contains(aabb.min) || contains(aabb.max);
}

inline void AABB3::expand(const Vector3& point)
{
	min.x = std::min(min.x, point.x);
	min.y = std::min(min.y, point.y);
	min.z = std::min(min.z, point.z);

	max.x = std::max(max.x, point.x);
	max.y = std::max(max.y, point.y);
	max.z = std::max(max.z, point.z);
}

inline void AABB3::expand(const AABB3& aabb)
{
	assert(aabb.isValid());
	expand(aabb.min);
	expand(aabb.max);
}

inline Vector3 AABB3::getCenter() const
{
	return (min + max) / 2.f;
}

inline bool AABB3::isValid() const
{
	return min.x <= max.x && min.y <= max.y && min.z <= max.z;
}

inline bool AABB3::isEmpty() const
{
	return min == max;
}
