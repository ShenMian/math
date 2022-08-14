# Copyright 2021 SMS
# License(Apache-2.0)

# 指定构建目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

# 指定 Win32 下要定义的宏
if(WIN32)
    list(APPEND MATH_DEFINES _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX)
endif()

# 静态链接 MSVC 运行库
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(UNIX)
    add_link_options("-ldl")
endif()

file(GLOB_RECURSE SOURCES "*.cpp")

# 添加可执行文件
add_executable(unit_test ${SOURCES})

# 指定库文件目录
# target_link_libraries(unit_test INTERFACE math)
target_include_directories(unit_test PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/deps/gcem/include")
target_include_directories(unit_test PRIVATE "${PROJECT_SOURCE_DIR}/deps/doctest")

# 添加宏定义
target_compile_definitions(unit_test PUBLIC ${MATH_DEFINES})

# 指定 C++ 标准
target_compile_features(unit_test PRIVATE cxx_std_20)

# 添加测试
add_test(NAME unit_test COMMAND unit_test)
