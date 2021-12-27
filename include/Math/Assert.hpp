// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdio>
#include <string_view>
// #include <source_location>

#if _MSC_VER
#    define breakpoint() __debugbreak()
#else
#    define breakpoint() __builtin_trap()
#endif

// TODO: clang 暂时不支持 std::source_location.

#include <stdlib.h>

// constexpr 修饰的函数使用的断言
#define VERIFY(cond, msg) \
    do {                  \
        if (cond) {       \
		} else {          \
            abort();      \
        }                 \
    } while (false)

inline void assert(bool condition)
{
	if(condition)
		return;
	abort();
}

inline void assert(bool condition, std::string_view message)
{
	if(condition)
		return;
	std::puts(message.data());
	abort();
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
