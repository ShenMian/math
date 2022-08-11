# Copyright 2021 SMS
# License(Apache-2.0)

file(GLOB_RECURSE SOURCES "*.cpp")

# 添加可执行文件
add_executable(unit_test ${SOURCES})

# 指定头文件目录
target_include_directories(unit_test PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/deps/doctest"
    "${PROJECT_SOURCE_DIR}/deps/gcem/include")

# 指定库文件目录
target_link_libraries(unit_test PRIVATE ${LIBS})

# 添加宏定义
target_compile_definitions(unit_test PUBLIC ${MATH_DEFINES})

# 指定 C++ 标准
if(MSVC)
    set_property(TARGET unit_test PROPERTY
        CXX_STANDARD          23
        CXX_STANDARD_REQUIRED ON) # MSVC
elseif(APPLE)
    target_compile_options(unit_test PRIVATE -std=c++2a) # AppleClang
else()
    set_property(TARGET unit_test PROPERTY
        CXX_STANDARD          20
        CXX_STANDARD_REQUIRED ON) # GCC/Clang
endif()

# 添加测试
add_test(NAME unit_test COMMAND unit_test)
