cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(MyProject)

# Указываем, что проект использует C и C++
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Добавляем исходные файлы
set(SOURCES
    main.c
    utils.c
    child1.c
    child2.c
    parent.c
)

# Добавляем библиотеку с исходными файлами
add_library(my_project_lib ${SOURCES})

# Добавляем директорию с заголовочными файлами
target_include_directories(my_project_lib PRIVATE ${CMAKE_SOURCE_DIR})

# Добавляем исполняемый файл
add_executable(my_project main.c)

# Линкуем исполняемый файл с библиотекой
target_link_libraries(my_project PRIVATE my_project_lib)

# Добавляем директорию с заголовочными файлами для исполняемого файла
target_include_directories(my_project PRIVATE ${CMAKE_SOURCE_DIR})

# Добавляем исполняемые файлы для дочерних процессов
add_executable(child1 child1.c utils.c)
add_executable(child2 child2.c utils.c)

# Добавляем директорию с заголовочными файлами для дочерних процессов
target_include_directories(child1 PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(child2 PRIVATE ${CMAKE_SOURCE_DIR})

# Добавляем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Добавляем тесты
add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE my_project_lib gtest_main)

# Добавляем директорию с заголовочными файлами для тестов
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})

# Добавляем цель для запуска тестов
add_test(NAME RunTests COMMAND tests)