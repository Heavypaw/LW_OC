#include "primecount.h"
#include <math.h>
#include <stdio.h>

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int PrimeCount(int A, int B) {
    int count = 0;
    for (int i = A; i <= B; i++) {
        count += isPrime(i);
    }
    return count;
}
