#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

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

    int *dp = (int *)malloc((V + 1) * sizeof(int));

    dp[0] = 0;

    for (int i = 1; i <= V; i++) {
        dp[i] = INF;

        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INF) {
                int current = dp[i - coins[j]] + 1;

                if (current < dp[i]) {
                    dp[i] = current;
                }
            }
        }
    }

    if (dp[V] == INF)
        printf("Minimum number of coins = -1\n");
    else
        printf("Minimum number of coins = %d\n", dp[V]);

    free(coins);
    free(dp);

    return 0;
}
// Complexity
// - Time: O(nV)
// - Space: O(V)
// The problem assumes unlimited supply of every 
// denomination and returns -1 when the target cannot be formed.     