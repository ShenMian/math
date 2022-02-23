// Copyright 2021 SMS
// License(Apache-2.0)

#include "../Helper.hpp"
#include "../Assert.hpp"
#include <algorithm>
#include <cmath>
#include <concepts>
#include <ranges>
#include "Vector.hpp"

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>::VectorT(const T& scalar)
{
	std::ranges::fill(v_, scalar);
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>::VectorT(const std::initializer_list<T>& list)
{
	assert(list.size() <= N, "Too many initializers");
	auto it = list.begin();
	for(size_t i = 0; i < list.size(); i++)
		v_[i] = *it++;
}

template <arithmetic T, size_t N>
inline T VectorT<T, N>::norm() const
{
	return static_cast<T>(std::sqrt(normSquared()));
}

template <arithmetic T, size_t N>
inline constexpr T VectorT<T, N>::normSquared() const
{
	T result = T();
	for(size_t i = 0; i < N; i++)
		result += v_[i] * v_[i];
	return result;
}

template <arithmetic T, size_t N>
inline VectorT<T, N>& VectorT<T, N>::normalize()
{
	const auto len = norm();
	if(len < std::numeric_limits<T>::epsilon())
		return *this;
	return *this *= 1.f / len;
}

template <arithmetic T, size_t N>
inline VectorT<T, N> VectorT<T, N>::normalized() const
{
	return VectorT(*this).normalize();
}

template <arithmetic T, size_t N>
inline constexpr T VectorT<T, N>::dot(const VectorT& rhs) const
{
	T result = T();
	for(size_t i = 0; i < N; i++)
		result += v_[i] * rhs.v_[i];
	return result;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N> VectorT<T, N>::cross(const VectorT& rhs) const
{
	// TODO
	return VectorT<T, N>();
}

template <arithmetic T, size_t N>
inline constexpr T VectorT<T, N>::sum() const
{
	T sum = T(0);
	for(size_t i = 0; i < N; i++)
		sum += v_[i];
	return sum;
}

template <arithmetic T, size_t N>
inline constexpr const VectorT<T, N>& VectorT<T, N>::clamp(const VectorT& min, const VectorT& max)
{
	for(size_t i = 0; i < N; i++)
		v_[i] = std::clamp(v_[i], min[i], max[i]);
    return *this;
}

template <arithmetic T, size_t N>
inline constexpr T* VectorT<T, N>::data()
{
	return v_;
}

template <arithmetic T, size_t N>
inline constexpr const T* VectorT<T, N>::data() const
{
	return v_;
}

template <arithmetic T, size_t N>
inline constexpr T& VectorT<T, N>::operator[](size_t index)
{
	assert(index < components, "subscript out of range");
	return *(v_ + index);
}

template <arithmetic T, size_t N>
inline constexpr const T& VectorT<T, N>::operator[](size_t index) const
{
	assert(index < components, "subscript out of range");
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
	for(size_t i = 0; i < N; i++)
		v_[i] *= rhs;
	return *this;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N>& VectorT<T, N>::operator/=(const T& rhs)
{
	assert(rhs, "divisor cannot be zero");
	for(size_t i = 0; i < N; i++)
		v_[i] /= rhs;
	return *this;
}

template <arithmetic T, size_t N>
inline constexpr VectorT<T, N> VectorT<T, N>::operator-() const
{
	VectorT result;
	for(size_t i = 0; i < N; i++)
		result.v_[i] = -v_[i];
	return result;
}

template <arithmetic T, size_t N>
constexpr T VectorT<T, N>::minCoeff() const
{
    T min = std::numeric_limits<T>::max();
    for(size_t i = 0; i < N; i++)
        if(v_[i] < min)
            min = v_[i];
    return min;
}

template <arithmetic T, size_t N>
constexpr T VectorT<T, N>::maxCoeff() const
{
    T max = std::numeric_limits<T>::min();
    for(size_t i = 0; i < N; i++)
        if(v_[i] > max)
            max = v_[i];
    return max;
}
