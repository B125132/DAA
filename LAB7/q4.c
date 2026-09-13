#include <stdio.h>

long long powerOfTwo(int n)
{
    long long result = 1;

    for (int i = 0; i < n; i++)
        result = result * 2;

    return result;
}

int main()
{
    int n;
    long long moves;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    moves = powerOfTwo(n + 1) / 3;

    printf("Minimum number of moves = %lld\n", moves);

    return 0;
}
// Time Complexity: O(n)

// Space Complexity: O(1)
// Explanation:
// The powerOfTwo() function uses a loop that runs n + 1 times.
//  Therefore, the time complexity is O(n).

// Only a few variables such as n, moves, and result are used, so the space complexity is O(1).

// Note: The formula uses integer division, which automatically gives the floor value in C
//  for positive integers.