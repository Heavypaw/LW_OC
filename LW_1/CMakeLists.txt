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
add_executable(${CMAKE_PROJECT_NAME}_tests tests_child.cpp parent.c utils.c)
target_link_libraries(${CMAKE_PROJECT_NAME}_tests PRIVATE GTest::GTest)
target_include_directories(${CMAKE_PROJECT_NAME}_tests PRIVATE include)

add_test(NAME ${CMAKE_PROJECT_NAME}_tests COMMAND ${CMAKE_PROJECT_NAME}_tests)
