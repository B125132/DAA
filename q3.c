#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char X[1000], Y[1000];

    printf("Enter first sequence: ");
    scanf("%999s", X);

    printf("Enter second sequence: ");
    scanf("%999s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
    }

    // Build LCS table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                if (dp[i - 1][j] > dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
    }

    int length = dp[m][n];

    char *lcs = (char *)malloc((length + 1) * sizeof(char));

    lcs[length] = '\0';

    int i = m;
    int j = n;
    int index = length - 1;

    // Reconstruct LCS
    while (i > 0 && j > 0) {

        if (X[i - 1] == Y[j - 1]) {
            lcs[index] = X[i - 1];
            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    printf("Length of LCS = %d\n", length);
    printf("LCS = %s\n", lcs);

    for (i = 0; i <= m; i++)
        free(dp[i]);

    free(dp);
    free(lcs);

    return 0;
}