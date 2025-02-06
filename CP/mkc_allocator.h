#ifndef MKC_ALLOCATOR_H
#define MKC_ALLOCATOR_H

#include <stddef.h>

class MKCAllocator {
public:
    MKCAllocator(size_t size);
    ~MKCAllocator();

    void* my_malloc(size_t size);
    void* my_realloc(void* ptr, size_t size);
    void my_free(void* ptr);

private:
    void* memoryPool;
    size_t poolSize;
};

#endif
