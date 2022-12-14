# Copyright 2022 ShenMian
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.16)

# 默认生成 compilation databases
if(NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# 指定默认编译类型
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(math
    VERSION      0.0.0
    DESCRIPTION  "A simple linear algebra header-only library."
    HOMEPAGE_URL "https://github.com/ShenMian/Math"
    LANGUAGES    CXX C)

  # 选项
option(MATH_BUILD_TESTS "Build tests" ON)

include(scripts/display_info.cmake)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/deps/gcem/include")

if(MATH_BUILD_TESTS)
    enable_testing()
    add_subdirectory("tests")
endif()
