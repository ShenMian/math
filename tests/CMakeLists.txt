# Copyright 2021 SMS
# License(Apache-2.0)

find_package(GTest)
if(GTEST_FOUND)
    list(APPEND LIBS ${GTEST_LIBRARY})
else()
    add_subdirectory("${PROJECT_SOURCE_DIR}/deps/googletest" "googletest")
    list(APPEND LIBS gtest gtest_main)
endif()
list(APPEND INCS "${PROJECT_SOURCE_DIR}/deps/googletest/googletest/include")

file(GLOB_RECURSE SOURCES "*.cpp")

# 添加可执行文件
add_executable(unit_test ${SOURCES})

# 指定头文件目录
target_include_directories(unit_test PUBLIC ${INCS} "${PROJECT_SOURCE_DIR}/include")

# 指定库文件目录
target_link_libraries(unit_test PRIVATE ${LIBS})

# 添加宏
target_compile_definitions(unit_test PUBLIC ${DEFINES})

# 指定 C++ 标准
set_property(TARGET unit_test PROPERTY CXX_STANDARD          23)
set_property(TARGET unit_test PROPERTY CXX_STANDARD_REQUIRED ON)

# 添加测试
add_test(NAME unit_test COMMAND unit_test)
