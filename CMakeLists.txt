# Copyright 2023 ShenMian
# License(Apache-2.0)

cmake_minimum_required(VERSION 3.16)

project(math
    VERSION      0.0.0
    DESCRIPTION  "A simple linear algebra header-only library."
    HOMEPAGE_URL "https://github.com/ShenMian/Math"
    LANGUAGES    CXX)

option(BUILD_TESTS "Build tests" ON)

include(scripts/display_info.cmake)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/deps/gcem/include")

if(BUILD_TESTS)
    enable_testing()
    
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") # 静态链接 MSVC 运行库
    endif()

    add_executable(${PROJECT_NAME}_unit_test)

    # target_link_libraries(${PROJECT_NAME}_unit_test INTERFACE math)
    file(GLOB_RECURSE SOURCES "tests/*.cpp" "tests/*.ixx")
    target_sources(${PROJECT_NAME}_unit_test PRIVATE ${SOURCES})
    target_include_directories(${PROJECT_NAME}_unit_test PRIVATE
        "${PROJECT_SOURCE_DIR}/deps/doctest"
        "${PROJECT_SOURCE_DIR}/deps/nanobench/src/include"
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/deps/gcem/include")
    target_compile_features(${PROJECT_NAME}_unit_test PRIVATE cxx_std_20)

    if(WIN32)
        target_compile_definitions(${PROJECT_NAME}_unit_test PUBLIC _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX)
    endif()

    if(UNIX)
        target_link_options(${PROJECT_NAME}_unit_test PRIVATE "-ldl")
    endif()

    find_package(OpenMP)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${PROJECT_NAME}_unit_test PUBLIC OpenMP::OpenMP_CXX)
    endif()

    add_test(NAME unit_test COMMAND ${PROJECT_NAME}_unit_test)
    add_test(NAME benchmark COMMAND ${PROJECT_NAME}_unit_test -ns -ts=benchmark)
endif()
