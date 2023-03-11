// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <functional>

template <typename T>
constexpr void hash_combine(std::size_t& seed, const T& v) noexcept
{
	seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T, typename... Ts>
constexpr void hash_combine(std::size_t& seed, const T& v, Ts... rest) noexcept
{
	hash_combine(seed, v);
	if constexpr(sizeof...(Ts) > 1)
		hash_combine(seed, rest...);
}

#define MAKE_HASHABLE(type, ...)                                                                                       \
	template <>                                                                                                        \
	struct std::hash<type>                                                                                             \
	{                                                                                                                  \
		std::size_t operator()(const type& t) const noexcept                                                           \
		{                                                                                                              \
			std::size_t ret = 0;                                                                                       \
			hash_combine(ret, __VA_ARGS__);                                                                            \
			return ret;                                                                                                \
		}                                                                                                              \
	};
