#include "primecount.h"
#include <stdlib.h>
#include <stdio.h>

int PrimeCount(int A, int B) {
    if (B < 2) return 0;
    int limit = B + 1;
    char *sieve = calloc(limit, sizeof(char));
    if (!sieve) return -1; // Memory error

    for (int i = 2; i * i <= B; i++) {
        if (!sieve[i]) {
            for (int j = i * i; j < limit; j += i) {
                sieve[j] = 1;
            }
        }
    }

    int count = 0;
    for (int i = (A < 2) ? 2 : A; i <= B; i++) {
        if (!sieve[i]) count++;
    }

    free(sieve);
    return count;
}
