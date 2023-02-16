// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "check.hpp"
#include "hash_combine.hpp"
#include "vector/vector3.hpp"

/**
 * @brief 3 维轴对齐包围盒.
 */
class AABB
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	AABB() = default;

	/**
	 * @brief 构造函数, 通过两个点创建包围盒.
	 *
	 * 将根据给出的两个点推断出最小点和最大点.
	 *
	 * @param a 第一个点.
	 * @param b 第二个点.
	 */
	AABB(const Vector3& a, const Vector3& b)
	{
		check((a.x <= b.x && a.y <= b.y && a.z <= b.z) || (a.x > b.x && a.y > b.y && a.z > b.z));
		if(a.x < b.x)
			min_ = a, max_ = b;
		else
			min_ = b, max_ = a;
	}

	const Vector3& min() const noexcept { return min_; };
	const Vector3& max() const noexcept { return max_; };

	/**
	 * @brief 判断是否包含指定点.
	 *
	 * @param point 判断是否包含的点.
	 *
	 * @return true  包含.
	 * @return false 不包含.
	 */
	bool contains(const Vector3& point) const
	{
		check(valid());
		return (min_.x <= point.x && point.x <= max_.x) && (min_.y <= point.y && point.y <= max_.y);
	}

	/**
	 * @brief 判断是否包含指定 AABB.
	 *
	 * @param aabb 判断是否包含的 AABB.
	 *
	 * @return true  包含.
	 * @return false 不包含.
	 */
	bool contains(const AABB& aabb) const
	{
		check(valid() && aabb.valid());
		return contains(aabb.min_) && contains(aabb.max_);
	}

	/**
	 * @brief 判断是否与 AABB 相交.
	 *
	 * @param aabb 判断是否相交的 AABB.
	 *
	 * @return true  相交.
	 * @return false 不相交.
	 */
	bool intersects(const AABB& aabb) const
	{
		check(valid() && aabb.valid());
		return contains(aabb.min_) || contains(aabb.max_);
	}

	/**
	 * @brief 拓展到包含指定点.
	 *
	 * @param point 指定点.
	 */
	void expand(const Vector3& point) noexcept
	{
		min_.x = std::min(min_.x, point.x);
		min_.y = std::min(min_.y, point.y);
		min_.z = std::min(min_.z, point.z);

		max_.x = std::max(max_.x, point.x);
		max_.y = std::max(max_.y, point.y);
		max_.z = std::max(max_.z, point.z);
	}

	/**
	 * @brief 拓展到包含指定 AABB.
	 *
	 * @param point AABB.
	 */
	void expand(const AABB& aabb)
	{
		check(aabb.valid());
		expand(aabb.min_);
		expand(aabb.max_);
	}

	/**
	 * @brief 获取几何中心.
	 */
	Vector3 center() const noexcept { return (min_ + max_) * .5f; }

	/**
	 * @brief 获取体积.
	 */
	float volume() const noexcept
	{
		const auto extent = max_ - min_;
		return extent.x * extent.y * extent.z;
	}

	/**
	 * @brief 判断大小是否为空.
	 *
	 * @return true  空.
	 * @return false 非空.
	 */
	bool empty() const noexcept { return min_ == max_; }

	/**
	 * @brief 判断包围盒是否有效.
	 *
	 * 若包围盒无效, 则部分成员函数也会无效, 进行无效的操作或返回无效的结果.
	 * TODO: 将 min_, max_ 私有化, 防止被破坏.
	 *
	 * @return true  有效.
	 * @return false 无效.
	 */
	bool valid() const noexcept { return min_.x <= max_.x && min_.y <= max_.y && min_.z <= max_.z; }

	bool operator==(const AABB& rhs) const = default;

private:
	Vector3 min_; ///< 最小点.
	Vector3 max_; ///< 最大点.
};

MAKE_HASHABLE(AABB, t.min(), t.max())

/**
 * @class AABB
 *
 * 在碰撞检测中用于简化物体外形.
 * 包围盒的边都与坐标轴平行, 因此可以利用分离轴定理快速进行碰撞检测.
 *
 * 例子:
 *
 * ```cpp
 * AABB a({0, 0, 0}, {1, 1, 1}); // 通过最大点和最小点创建包围盒
 * AABB b({1, 1, 1}, {2, 2, 2});
 *
 * if(a.contains(b))        // 判断 a 是否包含 b
 *   std::cout << "a contains b";
 * else if(a.intersects(b)) // 判断 a 是否与 b 相交
 *   std::cout << "a and b intersect";
 * else                     // a 与 b 没有交集
 *   std::cout << "a and b have no intersection";
 *
 *  // 创建包含全部顶点的包围盒
 *  std::vector<Vector3> vertices = {
 *      {0, 1, 2}, {2, 0, 1}, {-1, 2, 3}
 *  };
 *  AABB c;
 *  for(const auto& vertex : vertices)
 *      c.expand(vertex); // 将包围盒 c 拓展到可以包围 vertex
 * ```
 */
