#include <gtest/gtest.h>
#include <cstdlib>
#include <dlfcn.h>
#include "primecount.h"

extern "C" {
    #include "primecount.h"
}

TEST(PrimeCountNaive, Test1) {
    EXPECT_EQ(PrimeCount(10, 20), 4);
}

TEST(PrimeCountSieve, Test1) {
    void *handle = dlopen("./libprimecount_sieve.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    int (*PrimeCountFunc)(int, int) = dlsym(handle, "PrimeCount");
    EXPECT_EQ(PrimeCountFunc(10, 20), 4);
    dlclose(handle);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
