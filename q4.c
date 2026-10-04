#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = (int *)malloc(n * sizeof(int));
    int *dp = (int *)malloc(n * sizeof(int));

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        dp[i] = 1;
    }

    int maxLength = 1;

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (A[j] < A[i]) {

                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }

        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    printf("Length of Longest Increasing Subsequence = %d\n",
           maxLength);

    free(A);
    free(dp);

    return 0;
}