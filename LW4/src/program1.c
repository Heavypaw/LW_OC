#include <stdio.h>
#include "primecount.h"

int main() {
    int command, A, B;
    while (scanf("%d", &command) == 1) {
        if (command == 1) {
            scanf("%d %d", &A, &B);
            printf("Prime count: %d\n", PrimeCount(A, B));
        }
    }
    return 0;
}
