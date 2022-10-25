// Copyright 2021 SMS
// License(Apache-2.0)

#include "../check.hpp"
#include "../helper.hpp"
#include "gcem.hpp"
#include <algorithm>
#include <cmath>
#include <ranges>

using gcem::sqrt;
namespace rng = std::ranges;

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>::VectorT(const T& scalar)
{
	rng::fill(v_, scalar);
}

template <arithmetic T, size_t N>
constexpr VectorT<T, N>::VectorT(const T (&arr)[N])
{
	std::copy_n(arr, N, v_);
}

template <arithmetic T, size_t N>
constexpr VectorT<T, N>::VectorT(const std::span<T, N>& span)
{
	rng::copy(span, v_);
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr T VectorT<T, N>::norm() const
{
	return static_cast<T>(sqrt(normSq()));
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr T VectorT<T, N>::normSq() const noexcept
{
	T result = T();
	for(const auto v : *this)
		result += v * v;
	return result;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>& VectorT<T, N>::normalize()
{
	const auto len = norm();
	if(len < std::numeric_limits<T>::epsilon())
		return *this;
	return *this *= 1.f / len;
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr VectorT<T, N> VectorT<T, N>::normalized() const
{
	return VectorT(*this).normalize();
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr T VectorT<T, N>::dot(const VectorT& rhs) const noexcept
{
	return std::inner_product(begin(), end(), rhs.begin(), T(0));
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr VectorT<T, N> VectorT<T, N>::cross(const VectorT& rhs) const
{
	// TODO
	check(false);
	return VectorT<T, N>();
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr T VectorT<T, N>::sum() const noexcept
{
	return std::accumulate(begin(), end(), T(0));
}

template <arithmetic T, size_t N>
[[nodiscard]] constexpr T VectorT<T, N>::minCoeff() const noexcept
{
	return rng::min(*this);
}

template <arithmetic T, size_t N>
[[nodiscard]] constexpr T VectorT<T, N>::maxCoeff() const noexcept
{
	return rng::max(*this);
}

template <arithmetic T, size_t N>
inline constexpr const VectorT<T, N>& VectorT<T, N>::clamp(const VectorT& min, const VectorT& max) noexcept
{
	for(size_t i = 0; i < N; i++)
		v_[i] = std::clamp(v_[i], min[i], max[i]);
	return *this;
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr size_t VectorT<T, N>::components() const
{
	return components_;
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr T* VectorT<T, N>::data()
{
	return v_;
}

template <arithmetic T, size_t N>
[[nodiscard]] inline constexpr const T* VectorT<T, N>::data() const
{
	return v_;
}

template <arithmetic T, size_t N>
inline auto VectorT<T, N>::begin() noexcept
{
	return std::span(v_).begin();
}

template <arithmetic T, size_t N>
inline auto VectorT<T, N>::end() noexcept
{
	return std::span(v_).end();
}

template <arithmetic T, size_t N>
inline auto VectorT<T, N>::begin() const noexcept
{
	return std::span(v_).begin();
}

template <arithmetic T, size_t N>
inline auto VectorT<T, N>::end() const noexcept
{
	return std::span(v_).end();
}

template <arithmetic T, size_t N>
inline constexpr T& VectorT<T, N>::operator[](size_t index)
{
	check(index < components(), "subscript out of range");
	return *(v_ + index);
}

template <arithmetic T, size_t N>
inline constexpr const T& VectorT<T, N>::operator[](size_t index) const
{
	check(index < components(), "subscript out of range");
	return *(v_ + index);
}

template <arithmetic T, size_t N>
inline constexpr bool VectorT<T, N>::operator==(const VectorT<T, N>& rhs) const
{
	for(size_t i = 0; i < N; i++)
		if(!equal(v_[i], rhs.v_[i]))
			return false;
	return true;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator+=(const VectorT<T, N>& rhs)
{
	for(size_t i = 0; i < N; i++)
		v_[i] += rhs.v_[i];
	return *this;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator-=(const VectorT<T, N>& rhs)
{
	for(size_t i = 0; i < N; i++)
		v_[i] -= rhs.v_[i];
	return *this;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator*=(const T& rhs)
{
	rng::transform(*this, begin(), [&](T v) { return v * rhs; });
	return *this;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator/=(const T& rhs)
{
	check(rhs, "divisor cannot be zero"); // TODO: 添加 T 为浮点数时的判断
	rng::transform(*this, begin(), [&](T v) { return v / rhs; });
	return *this;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N> VectorT<T, N>::operator-() const
{
	VectorT result;
	rng::transform(*this, result.begin(), [](T v) { return -v; });
	return result;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N> VectorT<T, N>::lerp(const VectorT& from, const VectorT& to, T t)
{
	VectorT result;
	for(size_t i = 0; i < N; i++)
		result[i] = std::lerp(from[i], to[i], t);
	return result;
}
