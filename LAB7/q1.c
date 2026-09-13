#include <stdio.h>

int main()
{
    long long n, coins, moves;

    printf("Enter number of rows: ");
    scanf("%lld", &n);

    coins = n * (n + 1) / 2;

    moves = coins / 3;

    printf("Total number of coins = %lld\n", coins);
    printf("Minimum number of moves = %lld\n", moves);

    return 0;
}
// Time Complexity: O(1)

// Space Complexity: O(1)
// The program only uses a few arithmetic calculations and does not use any loop or recursive function. 
// Therefore, the running time remains constant regardless of the number of rows.
//  Only a fixed number of variables are used, so the space complexity is also constant