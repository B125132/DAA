#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = (int *)malloc(n * sizeof(int));

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    long long *dp = (long long *)calloc(V + 1, sizeof(long long));

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= V; j++) {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    printf("Total number of ways = %lld\n", dp[V]);

    free(coins);
    free(dp);

    return 0;
}