#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

void collatz(ull n) {

    ull capacity = 10;
    ull size = 0;

    ull *sequence =
        (ull *)malloc(capacity * sizeof(ull));

    if (sequence == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    while (n != 1) {

        if (size == capacity) {

            capacity *= 2;

            ull *temp =
                (ull *)realloc(sequence,
                               capacity * sizeof(ull));

            if (temp == NULL) {
                printf("Memory allocation failed.\n");
                free(sequence);
                return;
            }

            sequence = temp;
        }

        sequence[size++] = n;

        if (n % 2 == 0) {
            n = n / 2;
        }
        else {

            if (n > (ULLONG_MAX - 1) / 3) {
                printf("Overflow detected.\n");
                free(sequence);
                return;
            }

            n = 3 * n + 1;
        }
    }

    if (size == capacity) {

        capacity++;

        ull *temp =
            (ull *)realloc(sequence,
                           capacity * sizeof(ull));

        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            free(sequence);
            return;
        }

        sequence = temp;
    }

    sequence[size++] = 1;

    printf("Trajectory:\n");

    for (ull i = 0; i < size; i++) {
        printf("%llu", sequence[i]);

        if (i < size - 1)
            printf(" -> ");
    }

    printf("\n");

    printf("Number of terms = %llu\n", size);
    printf("Number of steps = %llu\n", size - 1);

    free(sequence);
}

int main() {

    ull start;

    printf("Enter starting value n: ");
    scanf("%llu", &start);

    if (start < 1) {
        printf("Starting value must be positive.\n");
        return 1;
    }

    collatz(start);

    printf("\n");

    ull a, b;

    printf("Enter interval [a, b]: ");
    scanf("%llu %llu", &a, &b);

    if (a < 1 || b < a) {
        printf("Invalid interval.\n");
        return 1;
    }

    printf("\nCollatz analysis for [%llu, %llu]\n",
           a, b);

    for (ull n = a; n <= b; n++) {

        printf("\nn = %llu\n", n);

        collatz(n);

        if (n == ULLONG_MAX)
            break;
    }

    return 0;
}