#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    else if (b <= a && b <= c)
        return b;
    else
        return c;
}

int main() {
    char A[1000], B[1000];

    printf("Enter first string: ");
    scanf("%999s", A);

    printf("Enter second string: ");
    scanf("%999s", B);

    int m = strlen(A);
    int n = strlen(B);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // Initialization
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    // Fill DP table
    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                int insert = dp[i][j - 1] + 1;
                int delete = dp[i - 1][j] + 1;
                int replace = dp[i - 1][j - 1] + 1;

                dp[i][j] = min3(insert, delete, replace);
            }
        }
    }

    printf("\nMinimum Edit Distance = %d\n", dp[m][n]);

    printf("\nTraceback:\n");

    int i = m;
    int j = n;

    while (i > 0 || j > 0) {

        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1] &&
            dp[i][j] == dp[i - 1][j - 1]) {

            printf("Keep '%c'\n", A[i - 1]);

            i--;
            j--;
        }

        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1) {

            printf("Replace '%c' with '%c'\n",
                   A[i - 1], B[j - 1]);

            i--;
            j--;
        }

        else if (j > 0 &&
                 dp[i][j] == dp[i][j - 1] + 1) {

            printf("Insert '%c'\n", B[j - 1]);

            j--;
        }

        else {

            printf("Delete '%c'\n", A[i - 1]);

            i--;
        }
    }

    for (i = 0; i <= m; i++)
        free(dp[i]);

    free(dp);

    return 0;
}