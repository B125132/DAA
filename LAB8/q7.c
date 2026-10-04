#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *price = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 1; i <= n; i++) {
        printf("Price of length %d: ", i);
        scanf("%d", &price[i]);
    }

    int *dp = (int *)malloc((n + 1) * sizeof(int));
    int *cut = (int *)malloc((n + 1) * sizeof(int));

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {

        dp[i] = price[i];
        cut[i] = i;

        for (int j = 1; j < i; j++) {

            if (price[j] + dp[i - j] > dp[i]) {

                dp[i] = price[j] + dp[i - j];

                cut[i] = j;
            }
        }
    }

    printf("\nMaximum Revenue = %d\n", dp[n]);

    printf("Optimal pieces: ");

    int length = n;

    while (length > 0) {

        printf("%d ", cut[length]);

        length = length - cut[length];
    }

    printf("\n");

    free(price);
    free(dp);
    free(cut);

    return 0;
}