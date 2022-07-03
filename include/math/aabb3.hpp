// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "vector/vector3.hpp"
#include "hash_combine.hpp"

/**
 * @brief 3 维轴对齐包围盒.
 */
class AABB3
{
public:
	Vector3 min; ///< 最小点.
	Vector3 max; ///< 最大点.

	/**
	 * @brief 默认构造函数.
	 */
	AABB3() = default;

	/**
	 * @brief 构造函数, 通过最小点和最大点创建包围盒.
	 *
	 * @param a 第一个点.
	 * @param b 第二个点.
	 */
	AABB3(const Vector3& a, const Vector3& b);

	/**
	 * @brief 判断是否包含指定点.
	 *
	 * @param point  判断是否包含的点.
	 * @return true  包含.
	 * @return false 不包含.
	 */
	bool contains(const Vector3& point) const;

	/**
	 * @brief 判断是否包含指定 AABB.
	 *
	 * @param aabb   判断是否包含的 AABB.
	 *
	 * @return true  包含.
	 * @return false 不包含.
	 */
	bool contains(const AABB3& aabb) const;

	/**
	 * @brief 判断是否与 AABB 相交.
	 *
	 * @param  aabb  判断是否相交的 AABB.
	 *
	 * @return true  相交.
	 * @return false 不相交.
	 */
	bool intersects(const AABB3& aabb) const;

	/**
	 * @brief 拓展到包含指定点.
	 *
	 * @param point 指定点.
	 */
	void expand(const Vector3& point) noexcept;

	/**
	 * @brief 拓展到包含指定 AABB.
	 *
	 * @param point AABB.
	 */
	void expand(const AABB3& aabb);

	/**
	 * @brief 获取几何中心.
	 */
	Vector3 center() const noexcept;

	/**
	 * @brief 获取体积.
	 */
	float volume() const noexcept;

	/**
	 * @brief 判断大小是否为空.
	 *
	 * @return true  空.
	 * @return false 非空.
	 */
	bool empty() const noexcept;

	/**
	 * @brief 判断是否有效.
	 *
	 * @return true  有效.
	 * @return false 无效.
	 */
	bool valid() const noexcept;

	/**
	 * @brief 设置包围盒为空.
	 */
	void clear();

	bool operator==(const AABB3& rhs) const = default;
};

#include "aabb3.inl"

MAKE_HASHABLE(AABB3, t.min, t.max)

/**
 * @class AABB3
 *
 * @details 在碰撞检测中用于简化物体外形. 包围盒的边都与坐标轴平行, 因此可以利用分离轴定理快速进行碰撞检测.
 *
 * 例子:
 *
 * ```cpp
 * AABB3 a({0, 0, 0}, {1, 1, 1}); // 通过最大点和最小点创建包围盒
 * AABB3 b({1, 1, 1}, {2, 2, 2});
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
 *  AABB3 c;
 *  for(const auto& vertex : vertices)
 *      c.expand(vertex); // 将包围盒 c 拓展到可以包围 vertex
 * ```
 */
