#include "simple_allocator.h"
#include "mkc_allocator.h"
#include <iostream>

int main() {
    std::cout << "=== SimpleAllocator Test ===\n";
    SimpleAllocator simpleAllocator(1024);

    void* ptr1 = simpleAllocator.my_malloc(100);
    std::cout << "Allocated 100 bytes at " << ptr1 << "\n";

    ptr1 = simpleAllocator.my_realloc(ptr1, 200);
    std::cout << "Reallocated to 200 bytes at " << ptr1 << "\n";

    simpleAllocator.my_free(ptr1);
    std::cout << "Memory freed\n";

    std::cout << "\n=== MKCAllocator Test ===\n";
    MKCAllocator mkcAllocator(1024);

    void* ptr2 = mkcAllocator.my_malloc(200);
    std::cout << "Allocated 200 bytes at " << ptr2 << "\n";

    ptr2 = mkcAllocator.my_realloc(ptr2, 300);
    std::cout << "Reallocated to 300 bytes at " << ptr2 << "\n";

    mkcAllocator.my_free(ptr2);
    std::cout << "Memory freed\n";

    std::cout << "Test completed.\n";
    return 0;
}
