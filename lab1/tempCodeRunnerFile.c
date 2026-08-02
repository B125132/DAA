#include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// int main() {
//     int n, i;
//     int fairHeads = 0, biasedHeads = 0;
//     double fairProbability, biasedProbability;

//     printf("Enter number of coin tosses: ");
//     scanf("%d", &n);

//     srand(time(NULL));

//     for (i = 0; i < n; i++) {

//         // Fair coin: P(HEAD) = 0.5
//         if (rand() % 2 == 0) {
//             fairHeads++;
//         }

//         // Biased coin: P(HEAD) = 0.7
//         if ((rand() % 100) < 70) {
//             biasedHeads++;
//         }
//     }

//     fairProbability = (double)fairHeads / n;
//     biasedProbability = (double)biasedHeads / n;

//     printf("\nFair Coin:\n");
//     printf("Heads = %d\n", fairHeads);
//     printf("Estimated P(HEAD) = %.4f\n", fairProbability);

//     printf("\nBiased Coin:\n");
//     printf("Heads = %d\n", biasedHeads);
//     printf("Estimated P(HEAD) = %.4f\n", biasedProbability);

//     return 0;
// }