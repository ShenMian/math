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

include_directories(
    ${INCS}
    "${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(unit_test ${SOURCES})

target_link_libraries(unit_test PRIVATE ${LIBS}})

add_test(unit_test unit_test)
