#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i, j;
    int duplicate = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    int arr[n];

    srand(time(NULL));

    
    for (i = 0; i < n; i++)
    {
        arr[i] = rand();

        printf("%d ", arr[i]);
    }

    
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate == 1)
            break;
    }

    if (duplicate == 1)
        printf("\nDuplicate element found: %d\n", arr[i]);
    else
        printf("\nAll elements are unique.\n");

    return 0;
}