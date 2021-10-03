﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>

template <typename T, size_t N>
inline VectorT<T, N>::VectorT(const T& scalar)
{
    std::fill(std::begin(v_), std::end(v_), scalar);
}

template <typename T, size_t N>
VectorT<T, N>::VectorT(const std::initializer_list<T>& list)
{
    assert(list.size() == N);
    auto it = list.begin();
    for(size_t i = 0; i < N; i++, it++)
        v_[i] = *it;
}

template <typename T, size_t N>
VectorT<T, N>::VectorT(const VectorT& rhs)
{
    std::copy(std::begin(rhs.v_), std::end(rhs.v_), v_);
}

template <typename T, size_t N>
inline T VectorT<T, N>::sizeSquared() const
{
    T result = T();
    for(size_t i = 0; i < N; i++)
        result += v_[i] * v_[i];
    return result;
}

template <typename T, size_t N>
inline T VectorT<T, N>::size() const
{
    return static_cast<T>(std::sqrt(sizeSquared()));
}

template <typename T, size_t N>
inline VectorT<T, N>& VectorT<T, N>::normalize()
{
    const auto len = size();
    if(len < std::numeric_limits<T>::epsilon())
        return *this;
    return *this *= 1.f / len;
}

template <typename T, size_t N>
inline VectorT<T, N> VectorT<T, N>::normalized() const
{
    return VectorT(*this).normalize();
}

template <typename T, size_t N>
inline T VectorT<T, N>::dot(const VectorT& rhs) const
{
    T result = T();
    for(size_t i = 0; i < N; i++)
        result += v_[i] * rhs.v_[i];
    return result;
}

template <typename T, size_t N>
inline T VectorT<T, N>::cross(const VectorT& rhs) const
{
    T result = T();
    for(size_t i = 0; i < N; i++)
        result -= v_[i] * rhs.v_[i];
    return result;
}

template <typename T, size_t N>
inline void* VectorT<T, N>::data()
{
    return v_;
}

template <typename T, size_t N>
inline const void* VectorT<T, N>::data() const
{
    return v_;
}

template <typename T, size_t N>
inline T& VectorT<T, N>::operator[](size_t index)
{
    assert(index < N);
    return *(v_ + index);
}

template <typename T, size_t N>
inline const T& VectorT<T, N>::operator[](size_t index) const
{
    assert(index < N);
    return *(v_ + index);
}

template <typename T, size_t N>
inline bool VectorT<T, N>::operator==(const VectorT<T, N>& rhs) const
{
    if constexpr(std::floating_point<T>)
    {
        for(size_t i = 0; i < N; i++)
            if(std::abs(v_[i] - rhs.v_[i]) >= std::numeric_limits<T>::epsilon())
                return false;
        return true;
    }
    else
    {
        for(size_t i = 0; i < N; i++)
            if(v_[i] != rhs.v_[i])
                return false;
        return true;
    }
}

template <typename T, size_t N>
inline VectorT<T, N>& VectorT<T, N>::operator+=(const VectorT<T, N>& rhs)
{
    for(size_t i = 0; i < N; i++)
        v_[i] += rhs.v_[i];
    return *this;
}

template <typename T, size_t N>
inline VectorT<T, N>& VectorT<T, N>::operator-=(const VectorT<T, N>& rhs)
{
    for(size_t i = 0; i < N; i++)
        v_[i] -= rhs.v_[i];
    return *this;
}

template <typename T, size_t N>
inline VectorT<T, N>& VectorT<T, N>::operator*=(const T& rhs)
{
    for(size_t i = 0; i < N; i++)
        v_[i] *= rhs;
    return *this;
}

template <typename T, size_t N>
inline VectorT<T, N>& VectorT<T, N>::operator/=(const T& rhs)
{
    assert(rhs);
    for(size_t i = 0; i < N; i++)
        v_[i] /= rhs;
    return *this;
}

template <typename T, size_t N>
VectorT<T, N> VectorT<T, N>::operator-() const
{
    VectorT result;
    for(size_t i = 0; i < N; i++)
        result.v_[i] = -v_[i];
    return result;
}