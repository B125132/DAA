#include <stdio.h>

#define MAX 50

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int main()
{
    int n;
    int p[MAX];
    int dp[MAX][MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    printf("Enter dimensions:\n");

    /*
       For n matrices, we need n+1 dimensions.

       Example:
       A1 = 10 x 20
       A2 = 20 x 30

       Input: 10 20 30
    */

    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    /*
       Cost of multiplying one matrix is zero.
    */
    for (int i = 1; i <= n; i++)
    {
        dp[i][i] = 0;
    }

    /*
       chainLength represents the number of matrices
       in the current chain.
    */
    for (int chainLength = 2;
         chainLength <= n;
         chainLength++)
    {
        for (int i = 1;
             i <= n - chainLength + 1;
             i++)
        {
            int j = i + chainLength - 1;

            dp[i][j] = 999999999;

            /*
               Try every possible splitting point.
            */
            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n",
           dp[1][n]);

    return 0;
}
// Time Complexity: O(n³)

// Space Complexity: O(n²)
// Explanation:
// The DP solution uses three nested loops:

// The first loop considers the chain length.
// The second loop considers the starting matrix.
// The third loop tries every possible splitting position k.

// Therefore, the time complexity is:O(N^3)