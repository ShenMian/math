// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "check.hpp"
#include "hash_combine.hpp"
#include "vector.hpp"
#include <cstddef>

// TODO: template <size_t N> N 维度包围盒

/**
 * @brief N 维轴对齐包围盒.
 */
template <size_t N>
class AABB
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	constexpr AABB() = default;

	/**
	 * @brief 构造函数, 通过两个点创建包围盒.
	 *
	 * 将根据给出的两个点推断出最小点和最大点.
	 *
	 * @param a 第一个点.
	 * @param b 第二个点.
	 */
	constexpr AABB(const Vectorf<N>& a, const Vectorf<N>& b)
	{
		min_ = Vectorf<N>(std::numeric_limits<float>::max());
		max_ = Vectorf<N>(std::numeric_limits<float>::min());
		expand(a);
		expand(b);
	}

	/**
	 * @brief 获取最小点.
	 */
	constexpr const Vectorf<N>& min() const noexcept { return min_; };

	/**
	 * @brief 获取最大点.
	 */
	constexpr const Vectorf<N>& max() const noexcept { return max_; };

	/**
	 * @brief 判断是否包含指定点.
	 *
	 * @param point 判断是否包含的点.
	 *
	 * @return true  包含.
	 * @return false 不包含.
	 */
	constexpr bool contains(const Vectorf<N>& point) const
	{
		for(size_t i = 0; i < N; i++)
		{
			if(!(min_[i] <= point[i] && point[i] <= max_[i]))
				return false;
		}
		return true;
	}

	/**
	 * @brief 判断是否包含指定 AABB.
	 *
	 * @param aabb 判断是否包含的 AABB.
	 *
	 * @return true  包含.
	 * @return false 不包含.
	 */
	constexpr bool contains(const AABB& aabb) const { return contains(aabb.min_) && contains(aabb.max_); }

	/**
	 * @brief 判断是否与 AABB 相交.
	 *
	 * @param aabb 判断是否相交的 AABB.
	 *
	 * @return true  相交.
	 * @return false 不相交.
	 */
	constexpr bool intersects(const AABB& aabb) const
	{
		for(size_t i = 0; i < N; i++)
		{
			if(max_[i] <= aabb.min_[i] || aabb.max_[i] <= min_[i])
				return false;
		}
		return true;
	}

	/**
	 * @brief 拓展到包含指定点.
	 *
	 * @param point 指定点.
	 */
	constexpr void expand(const Vectorf<N>& point) noexcept
	{
		for(size_t i = 0; i < N; i++)
			min_[i] = std::min(min_[i], point[i]);
		for(size_t i = 0; i < N; i++)
			max_[i] = std::max(max_[i], point[i]);
	}

	/**
	 * @brief 拓展到包含指定 AABB.
	 *
	 * @param point AABB.
	 */
	constexpr void expand(const AABB& aabb)
	{
		expand(aabb.min_);
		expand(aabb.max_);
	}

	/**
	 * @brief 获取几何中心.
	 */
	constexpr Vectorf<N> center() const noexcept { return (min_ + max_) * .5f; }

	/**
	 * @brief 获取尺寸.
	 */
	constexpr Vectorf<N> extent() const noexcept { return max_ - min_; }

	/**
	 * @brief 获取体积.
	 */
	constexpr float volume() const noexcept
	{
		const auto e = extent();

		float result = e[0];
		for(size_t i = 1; i < N; i++)
			result *= e[i];
		return result;
	}

	/**
	 * @brief 判断大小是否为空.
	 *
	 * @return true  空.
	 * @return false 非空.
	 */
	constexpr bool empty() const noexcept { return min_ == max_; }

	constexpr bool operator==(const AABB& rhs) const = default;

private:
	Vectorf<N> min_; ///< 最小点.
	Vectorf<N> max_; ///< 最大点.
};

MATH_MAKE_HASHABLE(AABB<2>, t.min(), t.max())
MATH_MAKE_HASHABLE(AABB<3>, t.min(), t.max())

/**
 * @class AABB
 *
 * 在碰撞检测中用于简化物体外形.
 * 包围盒的边都与坐标轴平行, 因此可以利用分离轴定理快速进行碰撞检测.
 *
 * 例子:
 *
 * ```cpp
 * AABB<3> a({0, 0, 0}, {1, 1, 1}); // 通过最大点和最小点创建包围盒
 * AABB<3> b({1, 1, 1}, {2, 2, 2});
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
 *  AABB<3> c;
 *  for(const auto& vertex : vertices)
 *      c.expand(vertex); // 将包围盒 c 拓展到可以包围 vertex
 * ```
 */
