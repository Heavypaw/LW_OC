cmake_minimum_required(VERSION 3.10)

project(ParentChildProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GTEST_ROOT /mnt/c/cygwin64/home/user/googletest/googletest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES
    parent.c
)

set(SOURCE_FILES
    child.c
)
add_executable(parent ${SOURCE_FILES})
add_executable(child ${SOURCE_FILES})

enable_testing()
add_executable(test_child test_child.cpp)
target_link_libraries(test_child GTest::GTest GTest::Main)

add_test(NAME RunTests COMMAND test_child)
