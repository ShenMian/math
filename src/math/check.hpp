// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <cstdio>
#include <string_view>
#include <exception>
// #include <source_location>
// TODO: 等待 apple-clang 支持 std::source_location. 

#if _MSC_VER
#define breakpoint() __debugbreak()
#else
#define breakpoint() __builtin_trap()
#endif

/**
 * @brief 断言.
 *
 * @param cond 条件.
 */
constexpr void check(bool cond)
{
	if(cond)
		return;

	breakpoint(); // debug
	// terminate(); // release
}

/**
 * @brief 断言.
 *
 * @param cond    条件.
 * @param message 描述.
 */
constexpr void check(bool cond, std::string_view message)
{
	if(cond)
		return;

	std::puts(message.data());
	breakpoint(); // debug
	// terminate(); // release
}
 
/**
 * @brief 断言.
 *
 * @param cond 条件.
 */
/*
inline void check(bool cond, const std::source_location& loc = std::source_location::current())
{
	if(cond)
		return;

	std::printf("Assertion failed %s:%s(%u:%u)\n", loc.file_name(), loc.function_name(), loc.line(), loc.column());
	breakpoint(); // debug
	// terminate(); // release
}
*/

/**
 * @brief 断言.
 *
 * @param cond    条件.
 * @param message 描述.
 */
/*
inline void check(bool cond, std::string_view message,
                  const std::source_location& loc = std::source_location::current())
{
	if(cond)
		return;

	std::printf("Assertion failed %s:%s(%u:%u): %s\n", loc.file_name(), loc.function_name(), loc.line(), loc.column(),
	            message.data());
	breakpoint(); // debug
	// terminate(); // release
}
*/
