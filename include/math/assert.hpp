// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdio>
#include <string_view>
// #include <source_location>
#include <type_traits>

#if _MSC_VER
#    define breakpoint() __debugbreak()
#else
#    define breakpoint() __builtin_trap()
#endif

// TODO: clang 暂时不支持 std::source_location.

#ifndef assert

inline constexpr void assert(bool condition)
{
	if(condition)
		return;
	breakpoint();
}

inline constexpr void assert(bool condition, std::string_view message)
{
	if(condition)
		return;
	std::puts(message.data());
	breakpoint();
}

/*
inline void assert(bool condition, const std::source_location& loc = std::source_location::current())
{
	if(condition)
		return;

	std::printf("Assertion failed %s:%s(%u:%u)\n",
		loc.file_name(), loc.function_name(), loc.line(), loc.column());
	breakpoint();
}

inline void assert(bool condition, std::string_view message, const std::source_location& loc = std::source_location::current())
{
	if(condition)
		return;

	std::printf("Assertion failed %s:%s(%u:%u): %s\n",
		loc.file_name(), loc.function_name(), loc.line(), loc.column(), message.data());
	breakpoint();
}
*/

#endif
