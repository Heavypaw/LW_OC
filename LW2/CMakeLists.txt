cmake_minimum_required(VERSION 3.10)
project(ParallelQuickSort)

set(CMAKE_C_STANDARD 99)

add_executable(ParallelQuickSort main.c)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ParallelQuickSortTests test.cpp)
target_link_libraries(ParallelQuickSortTests gtest_main pthread)

add_test(NAME ParallelQuickSortTest COMMAND ParallelQuickSortTests)
