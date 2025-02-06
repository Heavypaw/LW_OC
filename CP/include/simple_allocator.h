#ifndef SIMPLE_ALLOCATOR_H
#define SIMPLE_ALLOCATOR_H

#include <stddef.h>

class SimpleAllocator {
public:
    SimpleAllocator(size_t size);
    ~SimpleAllocator();

    void* my_malloc(size_t size);
    void* my_realloc(void* ptr, size_t size);
    void my_free(void* ptr);

private:
    void* memoryPool;
    size_t poolSize;
};

#endif
