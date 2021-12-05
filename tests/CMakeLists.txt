# Copyright 2021 SMS
# License(Apache-2.0)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/deps/googletest/googletest/include")

file(GLOB_RECURSE sources "*.cpp")

add_executable(unit_test ${sources})

target_link_libraries(unit_test PRIVATE gtest gtest_main)
