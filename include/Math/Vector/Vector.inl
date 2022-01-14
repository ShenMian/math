﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "../Helper.hpp"
#include "../Assert.hpp"
#include <algorithm>
#include <cmath>
#include <concepts>
#include <ranges>
#include "Vector.hpp"

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N>::VectorT(const T& scalar)
{
	std::ranges::fill(v_, scalar);
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N>::VectorT(const std::initializer_list<T>& list)
{
	assert(list.size() <= N, "Too many initializers");
	auto it = list.begin();
	for(size_t i = 0; i < list.size(); i++)
		v_[i] = *it++;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline T VectorT<T, N>::norm() const
{
	return static_cast<T>(std::sqrt(normSquared()));
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr T VectorT<T, N>::normSquared() const
{
	T result = T();
	for(size_t i = 0; i < N; i++)
		result += v_[i] * v_[i];
	return result;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline VectorT<T, N>& VectorT<T, N>::normalize()
{
	const auto len = norm();
	if(len < std::numeric_limits<T>::epsilon())
		return *this;
	return *this *= 1.f / len;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline VectorT<T, N> VectorT<T, N>::normalized() const
{
	return VectorT(*this).normalize();
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr T VectorT<T, N>::dot(const VectorT& rhs) const
{
	T result = T();
	for(size_t i = 0; i < N; i++)
		result += v_[i] * rhs.v_[i];
	return result;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N> VectorT<T, N>::cross(const VectorT& rhs) const
{
	// TODO
	return VectorT<T, N>();
}

template<typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr T VectorT<T, N>::sum() const
{
	T sum = T(0);
	for(size_t i = 0; i < N; i++)
		sum += v_[i];
	return sum;
}

template<typename T, size_t N> requires std::is_arithmetic_v<T>
inline void VectorT<T, N>::clamp(const VectorT& min, const VectorT& max)
{
	for(size_t i = 0; i < N; i++)
		v_[i] = std::clamp(v_[i], min[i], max[i]);
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr T* VectorT<T, N>::data()
{
	return v_;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr const T* VectorT<T, N>::data() const
{
	return v_;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr T& VectorT<T, N>::operator[](size_t index)
{
	assert(index < components, "subscript out of range");
	return *(v_ + index);
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr const T& VectorT<T, N>::operator[](size_t index) const
{
	assert(index < components, "subscript out of range");
	return *(v_ + index);
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr bool VectorT<T, N>::operator==(const VectorT<T, N>& rhs) const
{
	for(size_t i = 0; i < N; i++)
		if(!equal(v_[i], rhs.v_[i]))
			return false;
	return true;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator+=(const VectorT<T, N>& rhs)
{
	for(size_t i = 0; i < N; i++)
		v_[i] += rhs.v_[i];
	return *this;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator-=(const VectorT<T, N>& rhs)
{
	for(size_t i = 0; i < N; i++)
		v_[i] -= rhs.v_[i];
	return *this;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator*=(const T& rhs)
{
	for(size_t i = 0; i < N; i++)
		v_[i] *= rhs;
	return *this;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator/=(const T& rhs)
{
	assert(rhs, "divisor cannot be zero");
	for(size_t i = 0; i < N; i++)
		v_[i] /= rhs;
	return *this;
}

template <typename T, size_t N> requires std::is_arithmetic_v<T>
inline constexpr VectorT<T, N> VectorT<T, N>::operator-() const
{
	VectorT result;
	for(size_t i = 0; i < N; i++)
		result.v_[i] = -v_[i];
	return result;
}