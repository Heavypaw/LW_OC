#include "simple_allocator.h"
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

SimpleAllocator::SimpleAllocator(size_t size) {
    memoryPool = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memoryPool == MAP_FAILED) {
        std::cerr << "Error: mmap failed!\n";
        memoryPool = nullptr;
    }
    poolSize = size;
}

SimpleAllocator::~SimpleAllocator() {
    if (memoryPool) {
        munmap(memoryPool, poolSize);
    }
}

void* SimpleAllocator::my_malloc(size_t size) {
    return memoryPool ? memoryPool : nullptr;
}

void* SimpleAllocator::my_realloc(void* ptr, size_t size) {
    if (!ptr) return my_malloc(size);
    void* newPtr = my_malloc(size);
    if (newPtr) {
        std::memcpy(newPtr, ptr, size);
        my_free(ptr);
    }
    return newPtr;
}

void SimpleAllocator::my_free(void* ptr) {
    // Освобождение памяти пока не реализовано
}
