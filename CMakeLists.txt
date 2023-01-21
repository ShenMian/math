# Copyright 2023 ShenMian
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.16)

project(math
    VERSION      0.0.0
    DESCRIPTION  "A simple linear algebra header-only library."
    HOMEPAGE_URL "https://github.com/ShenMian/Math"
    LANGUAGES    CXX)

option(MATH_BUILD_TESTS "Build tests" ON)

include(scripts/display_info.cmake)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/deps/gcem/include")

if(MATH_BUILD_TESTS)
    enable_testing()

    if(WIN32)
        list(APPEND MATH_DEFINES _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX)
    endif()

    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()

    if(UNIX)
        add_link_options("-ldl")
    endif()

    file(GLOB_RECURSE SOURCES "tests/*.cpp")
    add_executable(unit_test)
    target_sources(unit_test PRIVATE ${SOURCES})
    target_include_directories(unit_test PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/deps/gcem/include"
        "${PROJECT_SOURCE_DIR}/deps/doctest")
    target_compile_features(unit_test PRIVATE cxx_std_20)
    add_test(NAME unit_test COMMAND unit_test)
endif()
