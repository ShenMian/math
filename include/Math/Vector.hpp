// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <initializer_list>

/**
 * @brief N 维向量.
 */
template <typename T, size_t N>
class VectorT
{
public:
    /**
	 * @brief 默认构造函数.
	 */
    VectorT() = default;

    /**
	 * @brief 构造函数.
	 */
    explicit VectorT(const T& scalar);

    /**
	 * @brief 构造函数.
     * 
     * @param list 初始化列表, 下标依次为 0 到 N-1.
	 */
    explicit VectorT(const std::initializer_list<T>& list);

    /**
	 * @brief 拷贝构造函数.
	 */
    VectorT(const VectorT& rhs);

    /**
	 * @brief 获取长度平方.
	 *
	 * @see size
	 */
    T sizeSquared() const;

    /**
	 * @brief 获取长度.
	 *
	 * @see sizeSquared
	 */
    T size() const;

    /**
	 * @brief 标准化成单位向量.
	 */
    VectorT& normalize();

    /**
	 * @brief 获取标准化单位向量.
	 */
    VectorT normalized() const;

    /**
	 * @brief 计算向量点积.
	 *
	 * @param rhs 要点乘的向量.
	 */
    T dot(const VectorT& rhs) const;

    /**
	 * @brief 计算向量叉积.
	 *
	 * @param rhs 要叉乘的向量.
	 */
    VectorT cross(const VectorT& rhs) const;

    /**
	 * @brief 获取原始数据.
	 */
    T*       data();
    const T* data() const;

    template <typename C>
    operator VectorT<C, N>()
    {
        VectorT<C, N> result;
        for(size_t i = 0; i < N; i++)
            result[i] = static_cast<C>(v_[i]);
        return result;
    }

    T&       operator[](size_t index);
    const T& operator[](size_t index) const;

    bool     operator==(const VectorT&) const;
    VectorT& operator+=(const VectorT&);
    VectorT& operator-=(const VectorT&);
    VectorT& operator*=(const T&);
    VectorT& operator/=(const T&);
    VectorT  operator-() const;

    static const size_t components = N;

private:
    T v_[N] = {};
};

#include "Vector.inl"

template <size_t N>
using Vector = VectorT<float, N>;

template <typename T, size_t N>
VectorT<T, N> operator+(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
    return VectorT(lhs) += rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator-(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
    return VectorT(lhs) -= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator*(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
    return VectorT(lhs) *= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator/(const VectorT<T, N>& lhs, const VectorT<T, N>& rhs)
{
    return VectorT(lhs) /= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator*(const VectorT<T, N>& lhs, const T& rhs)
{
    return VectorT(lhs) *= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator/(const VectorT<T, N>& lhs, const T& rhs)
{
    return VectorT(lhs) /= rhs;
}

template <typename T, size_t N>
VectorT<T, N> operator*(const T& lhs, const VectorT<T, N>& rhs)
{
    return rhs * lhs;
}

template <typename T, size_t N>
VectorT<T, N> operator/(const T& lhs, const VectorT<T, N>& rhs)
{
    return rhs / lhs;
}
