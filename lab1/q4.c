#include <stdio.h>

long long moves = 0;

void towerOfHanoi(int n, char source, char auxiliary, char destination)
{
    if (n == 1)
    {
        moves++;
        return;
    }

    towerOfHanoi(n - 1, source, destination, auxiliary);

    moves++;

    
    towerOfHanoi(n - 1, auxiliary, source, destination);
}

int main()
{
    int n, i;

    printf("Enter maximum number of disks: ");
    scanf("%d", &n);

    printf("\nDisks\tNumber of Moves\n");

    for (i = 1; i <= n; i++)
    {
        moves = 0;

        towerOfHanoi(i, 'A', 'B', 'C');

        printf("%d\t%lld\n", i, moves);
    }

    return 0;
}