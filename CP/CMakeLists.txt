cmake_minimum_required(VERSION 3.10)
project(MemoryAllocators)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Найти Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавить директорию include для заголовочных файлов
include_directories(include)

# Определяем файлы с исходным кодом (главный файл main.cpp только для исполняемого файла)
set(SOURCE_FILES
    src/simple_allocator.cpp
    src/mkc_allocator.cpp
)

# Определяем заголовочные файлы
set(HEADER_FILES
    include/simple_allocator.h
    include/mkc_allocator.h
)

# Создание исполнимого файла для основного приложения
add_executable(main src/main.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_compile_options(main PRIVATE -Wall -Wextra)

# Создание исполнимого файла для тестов (без main.cpp!)
add_executable(tests tests/test_allocators.cpp tests/test_performance.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(tests GTest::GTest GTest::Main)
target_compile_options(tests PRIVATE -Wall -Wextra)

# Включаем тестирование через CTest
enable_testing()
add_test(NAME allocators_tests COMMAND tests)
