#include <gtest/gtest.h>
#include <cstring>
#include "simple_allocator.h"
#include "mkc_allocator.h"

// Проверка выделения и освобождения памяти в SimpleAllocator
TEST(SimpleAllocatorTests, MallocFree) {
    SimpleAllocator allocator(1024);
    void* ptr = allocator.my_malloc(100);
    ASSERT_NE(ptr, nullptr);
    allocator.my_free(ptr);
}

// Проверка выделения и освобождения памяти в MKCAllocator
TEST(MKCAllocatorTests, MallocFree) {
    MKCAllocator allocator(1024);
    void* ptr = allocator.my_malloc(100);
    ASSERT_NE(ptr, nullptr);
    allocator.my_free(ptr);
}

// Проверка работы realloc в SimpleAllocator
TEST(SimpleAllocatorTests, ReallocTest) {
    SimpleAllocator allocator(1024);
    void* ptr = allocator.my_malloc(100);
    ASSERT_NE(ptr, nullptr);

    void* new_ptr = allocator.my_realloc(ptr, 200);
    ASSERT_NE(new_ptr, nullptr);
    allocator.my_free(new_ptr);
}

// Проверка работы realloc в MKCAllocator
TEST(MKCAllocatorTests, ReallocTest) {
    MKCAllocator allocator(1024);
    void* ptr = allocator.my_malloc(100);
    ASSERT_NE(ptr, nullptr);

    void* new_ptr = allocator.my_realloc(ptr, 200);
    ASSERT_NE(new_ptr, nullptr);
    allocator.my_free(new_ptr);
}

// Проверка выделения памяти больше доступного объема
TEST(SimpleAllocatorTests, AllocateTooLarge) {
    SimpleAllocator allocator(1024);
    void* ptr = allocator.my_malloc(2048); // Больше доступного
    ASSERT_EQ(ptr, nullptr);
}

// Проверка повторного использования освобожденной памяти
TEST(SimpleAllocatorTests, ReuseFreedMemory) {
    SimpleAllocator allocator(1024);
    void* ptr1 = allocator.my_malloc(100);
    allocator.my_free(ptr1);
    void* ptr2 = allocator.my_malloc(100);
    ASSERT_EQ(ptr1, ptr2);
}

// Оставляем `main()` только в одном файле
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
