﻿// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include "../check.hpp"
#include "../hash_combine.hpp"
#include "../helper.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <span>
#include <sstream>
#include <type_traits>

#include "gcem.hpp"

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

/**
 * @brief N 维向量.
 *
 * @tparam T 数据类型.
 * @tparam N 维数.
 */
template <arithmetic T, size_t N>
class VectorT
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	constexpr VectorT() = default;

	/**
	 * @brief 构造函数.
	 */
	constexpr explicit VectorT(const T& scalar) { std::ranges::fill(v_, scalar); }

	/**
	 * @brief 构造函数.
	 *
	 * @param list 初始化列表, 下标依次为 0 到 N-1.
	 */
	constexpr explicit VectorT(const T (&arr)[N]) { std::copy_n(arr, N, v_); }

	/**
	 * @brief 构造函数.
	 *
	 * @param span 范围.
	 */
	constexpr explicit VectorT(const std::span<T, N>& span) { std::ranges::copy(span, v_); }

	/**
	 * @brief 获取模, 即长度.
	 *
	 * @see normSquared
	 */
	constexpr T norm() const { return static_cast<T>(gcem::sqrt(normSq())); }

	/**
	 * @brief 获取模的平方.
	 *
	 * @see norm
	 */
	constexpr T normSq() const noexcept
	{
		T result = T();
		for(const auto v : *this)
			result += v * v;
		return result;
	}

	/**
	 * @brief 标准化成单位向量.
	 *
	 * @warning 当向量大小太小时, 将会不进行标准化.
	 */
	constexpr VectorT& normalize()
	{
		const auto len = norm();
		if(len < std::numeric_limits<T>::epsilon())
			return *this;
		return *this *= 1.f / len;
	}

	/**
	 * @brief 获取单位向量.
	 *
	 * @warning 当向量大小太小时, 将会不进行标准化.
	 */
	constexpr VectorT normalized() const { return VectorT(*this).normalize(); }

	/**
	 * @brief 计算向量点积.
	 *
	 * @param rhs 要点乘的向量.
	 */
	constexpr T dot(const VectorT& rhs) const noexcept { return std::inner_product(begin(), end(), rhs.begin(), T(0)); }

	/**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
	constexpr VectorT cross(const VectorT& rhs) const
	{
		// TODO
		check(false);
		return VectorT<T, N>();
	}

	/**
	 * @brief 获取所有元素之和.
	 */
	constexpr T sum() const noexcept { return std::accumulate(begin(), end(), T(0)); }

	/**
	 * @brief 获取最小元素的值.
	 */
	constexpr T minCoeff() const noexcept { return std::ranges::min(*this); }

	/**
	 * @brief 获取最大元素的值.
	 */
	constexpr T maxCoeff() const noexcept { return std::ranges::max(*this); }

	/**
	 * @brief 裁剪到指定范围内.
	 *
	 * @param min 最小值.
	 * @param max 最大值.
	 */
	constexpr const VectorT& clamp(const VectorT& min, const VectorT& max) noexcept
	{
		for(size_t i = 0; i < N; i++)
			v_[i] = std::clamp(v_[i], min[i], max[i]);
		return *this;
	}

	/**
	 * @brief 获取分量数.
	 */
	constexpr size_t components() const { return components_; }

	/**
	 * @brief 获取原始数据.
	 */
	constexpr T*       data() { return v_; }
	constexpr const T* data() const { return v_; }

	auto begin() noexcept { return std::span(v_).begin(); }
	auto end() noexcept { return std::span(v_).end(); }
	auto begin() const noexcept { return std::span(v_).begin(); }
	auto end() const noexcept { return std::span(v_).end(); }

	constexpr T& operator[](size_t index)
	{
		check(index < components(), "subscript out of range");
		return *(v_ + index);
	}

	constexpr const T& operator[](size_t index) const
	{
		check(index < components(), "subscript out of range");
		return *(v_ + index);
	}

	constexpr bool operator==(const VectorT& rhs) const
	{
		for(size_t i = 0; i < N; i++)
			if(!equal(v_[i], rhs.v_[i]))
				return false;
		return true;
	}

	constexpr VectorT& operator+=(const VectorT& rhs)
	{
		for(size_t i = 0; i < N; i++)
			v_[i] += rhs.v_[i];
		return *this;
	}

	constexpr VectorT& operator-=(const VectorT& rhs)
	{
		for(size_t i = 0; i < N; i++)
			v_[i] -= rhs.v_[i];
		return *this;
	}

	constexpr VectorT& operator*=(const T& rhs)
	{
		std::ranges::transform(*this, begin(), [&](T v) { return v * rhs; });
		return *this;
	}

	constexpr VectorT& operator/=(const T& rhs)
	{
		check(rhs, "divisor cannot be zero"); // TODO: 添加 T 为浮点数时的判断
		std::ranges::transform(*this, begin(), [&](T v) { return v / rhs; });
		return *this;
	}

	constexpr VectorT operator-() const
	{
		VectorT result;
		std::ranges::transform(*this, result.begin(), [](T v) { return -v; });
		return result;
	}

	template <typename C>
	operator VectorT<C, N>()
	{
		VectorT<C, N> result;
		for(size_t i = 0; i < N; i++)
			result[i] = static_cast<C>(v_[i]);
		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, const VectorT& vec)
	{
		size_t max = 0;
		for(size_t i = 0; i < N; i++)
		{
			std::ostringstream stm;
			stm << vec[i];
			const auto size = stm.str().size();
			max             = std::max(max, size);
		}
		max = std::min<size_t>(max, 6);
		for(size_t i = 0; i < N; i++)
		{
			std::ostringstream stm;
			stm.setf(std::ios::fixed);
			stm.precision(6);
			stm << vec[i];
			auto str = stm.str();
			str.erase(str.find_last_not_of('0') + 1);
			if(str.back() == '.')
				str.pop_back();
			stream.width(max);
			stream << str << ' ';
		}
		return stream;
	}

	static constexpr VectorT lerp(const VectorT& from, const VectorT& to, T t)
	{
		VectorT result;
		for(size_t i = 0; i < N; i++)
			result[i] = std::lerp(from[i], to[i], t);
		return result;
	}

	T&       x() { return (*this)[0]; };
	T&       y() { return (*this)[1]; };
	T&       z() { return (*this)[2]; };
	T&       w() { return (*this)[3]; };
	const T& x() const { return (*this)[0]; };
	const T& y() const { return (*this)[1]; };
	const T& z() const { return (*this)[2]; };
	const T& w() const { return (*this)[3]; };

private:
	T v_[N] = {};

	static constexpr size_t components_ = N;
};

template <size_t N>
using Vectorf = VectorT<float, N>;

template <size_t N>
using Vectord = VectorT<float, N>;

template <size_t N>
using Vectori = VectorT<int32_t, N>;

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator+(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) += rhs;
}

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator-(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) -= rhs;
}

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator*(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) *= rhs;
}

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator/(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
	return VectorT(lhs) /= rhs;
}

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator*(const VectorT<T, N>& lhs, const T& rhs)
{
	return VectorT(lhs) *= rhs;
}

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator/(const VectorT<T, N>& lhs, const T& rhs)
{
	return VectorT(lhs) /= rhs;
}

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator*(const T& lhs, const VectorT<T, N>& rhs)
{
	return rhs * lhs;
}

template <arithmetic T, size_t N>
VectorT<T, N> constexpr operator/(const T& lhs, const VectorT<T, N>& rhs)
{
	return rhs / lhs;
}

template <arithmetic T, size_t N>
struct std::hash<VectorT<T, N>>
{
	std::size_t operator()(const VectorT<T, N>& v) const
	{
		std::size_t ret = 0;
		for(size_t i = 0; i < N; i++)
			hash_combine(ret, v[i]);
		return ret;
	}
};

template <arithmetic T>
T distanceSq(const VectorT<T, 2>& a, const VectorT<T, 2>& b)
{
	const auto dx = gcem::abs(a.x - b.x);
	const auto dy = gcem::abs(a.y - b.y);
	return dx * dx + dy * dy;
}

/*
template <arithmetic T>
using Vector2T = VectorT<T, 2>;

using Vector2f = VectorT<float, 2>;
using Vector2d = VectorT<double, 2>;
using Vector2i = VectorT<int32_t, 2>;
using Vector2  = Vector2f;
using Size2    = VectorT<size_t, 2>;

template <arithmetic T>
using Vector3T = VectorT<T, 3>;

using Vector3f = VectorT<float, 3>;
using Vector3d = VectorT<double, 3>;
using Vector3i = VectorT<int32_t, 3>;
using Vector3  = Vector3f;
using Size3    = VectorT<size_t, 3>;

template <arithmetic T>
using Vector4T = VectorT<T, 4>;

using Vector4f = VectorT<float, 4>;
using Vector4d = VectorT<double, 4>;
using Vector4i = VectorT<int32_t, 4>;
using Vector4  = Vector4f;
using Size4    = VectorT<size_t, 4>;
*/

/**
 * @class VectorT
 *
 * @details 大小固定的向量, 可以用于表示位置/速度/方向等.
 *
 * 例子:
 *
 * ```cpp
 * // 创建
 * Vector2i v(1, 2); // 创建一个 2 维向量, 类型为 int32_t, 初始值为 (1, 2)
 *
 * // 操作
 * v.x = 3;  // 设置 x 分量为 3
 * v[1] = 4; // 设置 y 分量为 4
 * std::cout << v.size() << std::endl; // 输出向量的长度, 结果为: 5
 * ```
 */
