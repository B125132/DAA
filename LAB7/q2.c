#include <stdio.h>

#define MAX_EGGS 50
#define MAX_FLOORS 1000

int main()
{
    int E, F;
    int dp[MAX_EGGS + 1][MAX_FLOORS + 1];

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    // 0 floors need 0 drops
    for (int e = 1; e <= E; e++)
    {
        dp[e][0] = 0;
    }

    // 1 floor needs 1 drop
    for (int e = 1; e <= E; e++)
    {
        dp[e][1] = 1;
    }

    // With one egg, we have to check every floor
    for (int f = 0; f <= F; f++)
    {
        dp[1][f] = f;
    }

    // Fill the DP table
    for (int e = 2; e <= E; e++)
    {
        for (int f = 2; f <= F; f++)
        {
            dp[e][f] = F + 1;

            for (int x = 1; x <= f; x++)
            {
                int breaks = dp[e - 1][x - 1];
                int survives = dp[e][f - x];

                int worst;

                if (breaks > survives)
                    worst = breaks;
                else
                    worst = survives;

                int drops = worst + 1;

                if (drops < dp[e][f])
                    dp[e][f] = drops;
            }
        }
    }

    printf("\nMinimum number of drops required = %d\n",
           dp[E][F]);

    return 0;
}
// Time Complexity: O(E × F²)

// Space Complexity: O(E × F)
// The program uses three nested loops.
//  The first loop runs for E eggs,
//  the second runs for F floors,
//  and the innermost loop tries every possible floor as the dropping point,
//  which takes O(F) time. Therefore, the total time complexity is O(E × F²).