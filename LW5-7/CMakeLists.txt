cmake_minimum_required(VERSION 3.10)
project(DistributedSystem)

set(CMAKE_CXX_STANDARD 17)

# Find GTest
find_package(GTest REQUIRED)

# Путь к исходным файлам
set(SOURCE_FILES
    src/Node.cpp
    src/ControlNode.cpp
)

# Путь к заголовочным файлам
set(HEADER_FILES
    include/Node.h
    include/ControlNode.h
)

# Добавить основную библиотеку
add_library(DistributedSystemLib ${SOURCE_FILES})

# Добавить основной исполняемый файл
add_executable(DistributedSystem
    src/main.cpp
)

# Связать основной исполняемый файл с библиотекой
target_link_libraries(DistributedSystem DistributedSystemLib)

# Добавить исполняемый файл для тестов
add_executable(DistributedSystemTests
    test/test_main.cpp
)

# Связать исполняемый файл для тестов с библиотекой и GTest
target_link_libraries(DistributedSystemTests DistributedSystemLib GTest::GTest GTest::Main)

# Включить директории заголовочных файлов
target_include_directories(DistributedSystemLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(DistributedSystemTests PUBLIC ${CMAKE_SOURCE_DIR}/include)
