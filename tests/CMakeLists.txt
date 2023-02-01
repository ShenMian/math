# Copyright 2023 ShenMian
# License(Apache-2.0)

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

add_executable(unit_test ${SOURCES})

# target_link_libraries(unit_test INTERFACE math)
target_include_directories(unit_test PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/deps/gcem/include")
target_include_directories(unit_test PRIVATE "${PROJECT_SOURCE_DIR}/deps/doctest")
target_compile_definitions(unit_test PUBLIC ${MATH_DEFINES})
target_compile_features(unit_test PRIVATE cxx_std_20)

add_test(NAME unit_test COMMAND unit_test)
