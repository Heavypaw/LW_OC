#include <gtest/gtest.h>
#include <chrono>
#include <sched.h>
#include "simple_allocator.h"
#include "mkc_allocator.h"

// Функция для привязки теста к 1 ядру (минимизация накладных расходов)
void set_affinity() {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
}

// Функция для измерения времени выполнения кода
template<typename Func>
double measure_time(Func function) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

// Тест скорости выделения памяти в SimpleAllocator
TEST(PerformanceTests, SimpleAllocatorAllocationSpeed) {
    set_affinity();
    SimpleAllocator allocator(1024 * 1024);

    double time_taken = measure_time([&]() {
        for (int i = 0; i < 10000; i++) {
            void* ptr = allocator.my_malloc(64);
            allocator.my_free(ptr);
        }
    });

    std::cout << "SimpleAllocator Allocation/Free Time: " << time_taken << " ms\n";
    ASSERT_LT(time_taken, 500.0);
}

// Тест скорости освобождения памяти
TEST(PerformanceTests, SimpleAllocatorFreeSpeed) {
    set_affinity();
    SimpleAllocator allocator(1024 * 1024);

    void* ptrs[10000];
    for (int i = 0; i < 10000; i++) {
        ptrs[i] = allocator.my_malloc(64);
    }

    double time_taken = measure_time([&]() {
        for (int i = 0; i < 10000; i++) {
            allocator.my_free(ptrs[i]);
        }
    });

    std::cout << "SimpleAllocator Free Time: " << time_taken << " ms\n";
    ASSERT_LT(time_taken, 300.0);
}

// Тест фрагментации памяти
TEST(FragmentationTests, SimpleAllocatorFragmentation) {
    SimpleAllocator allocator(1024 * 1024);
    void* ptr1 = allocator.my_malloc(256);
    void* ptr2 = allocator.my_malloc(256);
    allocator.my_free(ptr1);
    void* ptr3 = allocator.my_malloc(128); // Должно использовать освобожденный блок

    ASSERT_NE(ptr3, nullptr);
    ASSERT_LT(ptr3, ptr2);
}

// Проверка устойчивости аллокатора при большом количестве операций
TEST(StressTests, SimpleAllocatorStressTest) {
    SimpleAllocator allocator(1024 * 1024);
    void* ptrs[5000];

    for (int i = 0; i < 5000; i++) {
        ptrs[i] = allocator.my_malloc(128);
        ASSERT_NE(ptrs[i], nullptr);
    }

    for (int i = 0; i < 5000; i++) {
        allocator.my_free(ptrs[i]);
    }
}

// Проверка эффективности перераспределения блоков
TEST(SimpleAllocatorTests, EfficientRealloc) {
    SimpleAllocator allocator(1024);
    void* ptr = allocator.my_malloc(200);
    ASSERT_NE(ptr, nullptr);

    void* new_ptr = allocator.my_realloc(ptr, 100);
    ASSERT_NE(new_ptr, nullptr);

    ASSERT_EQ(ptr, new_ptr); // Должен использовать тот же блок, если уменьшился
    allocator.my_free(new_ptr);
}
