// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Vector/Vector3.hpp"

/**
 * @brief 3 维轴对齐包围盒.
 */
class AABB3
{
public:
	Vector3 min;
	Vector3 max;

	/**
	 * @brief 默认构造函数.
	 */
	AABB3() = default;

	/**
	 * @brief 构造函数, 通过最小点和最大点创建包围盒.
	 *
	 * @param min 指定点.
	 */
	AABB3(const Vector3& min, const Vector3& max);

	/**
	 * @brief 拓展到包含指定点.
	 *
	 * @param point 指定点.
	 */
	void expand(const Vector3& point);

	/**
	 * @brief 拓展到包含指定 AABB.
	 *
	 * @param point AABB.
	 */
	void expand(const AABB3& aabb);

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
	 * @return true  包含.
	 * @return false 不包含.
	 */
	bool contains(const AABB3& aabb) const;

	/**
	 * @brief 判断是否与 AABB 相交.
	 *
	 * @param  aabb  判断是否相交的 AABB.
	 * @return true  相交.
	 * @return false 不相交.
	 */
	bool intersects(const AABB3& aabb) const;

	/**
	 * @brief 获取几何中心.
	 */
	Vector3 getCenter() const;

	/**
	 * @brief 判断是否有效.
	 *
	 * @return true  有效.
	 * @return false 无效.
	 */
	bool isValid() const;

	/**
	 * @brief 判断大小是否为空.
	 *
	 * @return true  空.
	 * @return false 非空.
	 */
	bool isEmpty() const;

	bool operator==(const AABB3& rhs) const = default;
};

#include "AABB3.inl"
