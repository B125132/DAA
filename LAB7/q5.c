#include <stdio.h>

int main()
{
    int n;
    int target, shot;
    int hit;
    int step;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    /*
       We use the following shooting sequence:
       1, 2, 3, ..., n-1
       Then shoot 2, 3, ..., n
    */

    printf("\nShooting sequence:\n");

    for (shot = 1; shot <= n; shot++)
        printf("%d ", shot);

    for (shot = n - 1; shot >= 1; shot--)
        printf("%d ", shot);

    printf("\n");

    /*
       Test every possible initial position.
       The target is assumed to move to an adjacent
       position after every shot.
    */

    printf("\nTesting possible starting positions...\n");

    for (target = 1; target <= n; target++)
    {
        hit = 0;

        for (step = 1; step <= 2 * n; step++)
        {
            if (step <= n)
                shot = step;
            else
                shot = 2 * n - step;

            if (target == shot)
            {
                hit = 1;
                break;
            }

            /*
               Move the target to an adjacent position.
               For validation, consider both possible moves.
               A guaranteed strategy must handle both.
            */

            if (target > 1)
                target--;

            else if (target < n)
                target++;
        }

        if (hit)
            printf("Starting position %d: Target can be hit\n",
                   target);
    }

    return 0;
}
// Time Complexity: O(n²)

// Space Complexity: O(1)
