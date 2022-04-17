// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.hpp"
#include "AABB3.hpp"

inline AABB3::AABB3(const Vector3& a, const Vector3& b)
{
	if(a.x < b.x && a.y < b.y && a.z < b.z)
		min = a, max = b;
	else
		min = b, max = a;
}

inline bool AABB3::contains(const Vector3& p) const
{
	assert(valid());
	return (min.x <= p.x && p.x <= max.x) && (min.y <= p.y && p.y <= max.y);
}

[[nodiscard]] inline bool AABB3::contains(const AABB3& aabb) const
{
	assert(valid() && aabb.valid());
	return contains(aabb.min) && contains(aabb.max);
}

[[nodiscard]] inline bool AABB3::intersects(const AABB3& aabb) const
{
	assert(valid() && aabb.valid());
	return contains(aabb.min) || contains(aabb.max);
}

inline void AABB3::expand(const Vector3& point) noexcept
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
	assert(aabb.valid());
	expand(aabb.min);
	expand(aabb.max);
}

inline Vector3 AABB3::center() const noexcept
{
	return (min + max) / 2.f;
}

[[nodiscard]] inline bool AABB3::empty() const noexcept
{
	return min == max;
}

[[nodiscard]] inline bool AABB3::valid() const noexcept
{
	return min.x <= max.x && min.y <= max.y && min.z <= max.z;
}

inline void AABB3::clear()
{
	min = max = Vector3::zero;
}
