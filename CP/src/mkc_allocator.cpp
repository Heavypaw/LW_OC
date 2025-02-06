#include "mkc_allocator.h"
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

MKCAllocator::MKCAllocator(size_t size) {
    memoryPool = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memoryPool == MAP_FAILED) {
        std::cerr << "Error: mmap failed!\n";
        memoryPool = nullptr;
    }
    poolSize = size;
}

MKCAllocator::~MKCAllocator() {
    if (memoryPool) {
        munmap(memoryPool, poolSize);
    }
}

void* MKCAllocator::my_malloc(size_t size) {
    return memoryPool ? memoryPool : nullptr;
}

void* MKCAllocator::my_realloc(void* ptr, size_t size) {
    if (!ptr) return my_malloc(size);
    void* newPtr = my_malloc(size);
    if (newPtr) {
        std::memcpy(newPtr, ptr, size);
        my_free(ptr);
    }
    return newPtr;
}

void MKCAllocator::my_free(void* ptr) {
    // Освобождение памяти пока не реализовано
}
