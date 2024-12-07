cmake_minimum_required(VERSION 3.10)
project(LabWork)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Find Google Test
find_package(GTest REQUIRED)
include(${GTEST_CMAKE_DIR}/GoogleTest.cmake)

# PrimeCount Naive library
add_library(primecount_naive SHARED src/primecount_naive.c)
target_include_directories(primecount_naive PUBLIC include)

# PrimeCount Sieve library
add_library(primecount_sieve SHARED src/primecount_sieve.c)
target_include_directories(primecount_sieve PUBLIC include)

# Program No1
add_executable(program1 src/program1.c)
target_link_libraries(program1 primecount_naive)

# Program No2
add_executable(program2 src/program2.c)
target_link_libraries(program2 dl)

# Tests
add_executable(primecount_tests tests/primecount_tests.cpp)
target_link_libraries(primecount_tests GTest::GTest GTest::Main)
