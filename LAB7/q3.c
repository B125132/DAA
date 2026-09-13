#include <stdio.h>

#define MAX 20

long long dp[MAX + 1];

long long powerOfTwo(int n)
{
    long long result = 1;

    for (int i = 0; i < n; i++)
        result = result * 2;

    return result;
}

void findMoves(int n)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        dp[1] = 1;
        return;
    }

    dp[0] = 0;
    dp[1] = 1;

    for (int disks = 2; disks <= n; disks++)
    {
        dp[disks] = 999999999;
        
        for (int k = 1; k < disks; k++)
        {
            long long firstPart = 2 * dp[k];

            long long secondPart = powerOfTwo(disks - k) - 1;

            long long total = firstPart + secondPart;

            if (total < dp[disks])
                dp[disks] = total;
        }
    }
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    findMoves(n);

    printf("Minimum number of moves = %lld\n", dp[n]);

    return 0;
}
// Time Complexity: O(n^3)

// Space Complexity: O(n)
// Explanation:
// There are n values of disks, and for every value we try all possible values of k. 
// The powerOfTwo() function takes O(n) time in the worst case. 
//    -Therefore, the overall time complexity is O(n³).

// The dp array stores the minimum number of moves for each number of disks, so it requires O(n) space.