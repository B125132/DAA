// Quick sort of random elements stored in a file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int a[], int low, int high)
{
    if(low < high)
    {
        int pivot = a[high];
        int i = low - 1, temp;

        for(int j = low; j < high; j++)
        {
            if(a[j] <= pivot)
            {
                i++;
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }

        temp = a[i + 1];
        a[i + 1] = a[high];
        a[high] = temp;

        int p = i + 1;

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    srand(time(0));

    FILE *fp = fopen("random.txt", "w");

    printf("Random elements:\n");

    for(int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    quickSort(a, 0, n - 1);

    printf("\n\nSorted elements:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}