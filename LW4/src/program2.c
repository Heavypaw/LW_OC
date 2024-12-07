#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "primecount.h"

int main() {
    void *handle = NULL;
    int (*PrimeCountFunc)(int, int) = NULL;
    char *error;
    int current_lib = 0; // 0 for naive, 1 for sieve

    while (1) {
        int command, A, B;
        scanf("%d", &command);
        if (command == 0) {
            if (handle) dlclose(handle);
            current_lib = 1 - current_lib;
            if (current_lib == 0) {
                handle = dlopen("./libprimecount_naive.so", RTLD_LAZY);
            } else {
                handle = dlopen("./libprimecount_sieve.so", RTLD_LAZY);
            }
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                break;
            }
            PrimeCountFunc = dlsym(handle, "PrimeCount");
            error = dlerror();
            if (error) {
                fprintf(stderr, "%s\n", error);
                break;
            }
        } else if (command == 1 || command == 2) {
            scanf("%d %d", &A, &B);
            if (!handle) {
                handle = dlopen("./libprimecount_naive.so", RTLD_LAZY);
                PrimeCountFunc = dlsym(handle, "PrimeCount");
            }
            printf("Prime count: %d\n", PrimeCountFunc(A, B));
        }
    }
    if (handle) dlclose(handle);
    return 0;
}
