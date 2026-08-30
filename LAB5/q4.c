// Heap sort of random elements stored in a file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    int temp;

    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for(int i = n - 1; i > 0; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    srand(time(0));

    FILE *fp = fopen("heapdata.txt", "w");

    printf("Random elements:\n");

    for(int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    heapSort(a, n);

    printf("\n\nSorted elements:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}