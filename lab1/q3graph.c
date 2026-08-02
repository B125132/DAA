
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Optimized Bubble Sort
// Stops if array becomes sorted before n-1 passes
long long bubbleSortOptimized(int arr[], int n)
{
    int i, j, temp, swapped;
    long long comparisons = 0;

    for (i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for (j = 0; j < n - 1 - i; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1;
            }
        }

        // Array is already sorted
        if (swapped == 0)
            break;
    }

    return comparisons;
}


// Normal Bubble Sort
// Always completes n-1 passes
long long bubbleSortNormal(int arr[], int n)
{
    int i, j, temp;
    long long comparisons = 0;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}


int main()
{
    int n, i;

    FILE *data;
    FILE *gp;

    srand(time(NULL));

    // File to store graph data
    data = fopen("bubble.dat", "w");

    if (data == NULL)
    {
        printf("Error creating data file.\n");
        return 1;
    }

    printf("n\tOptimized\tNormal\n");

    // Test different array sizes
    for (n = 10; n <= 500; n += 10)
    {
        int *arr1 = malloc(n * sizeof(int));
        int *arr2 = malloc(n * sizeof(int));

        if (arr1 == NULL || arr2 == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        // Generate random array
        for (i = 0; i < n; i++)
        {
            arr1[i] = rand() % 10000;

            // Same data for second algorithm
            arr2[i] = arr1[i];
        }

        long long compOptimized;
        long long compNormal;

        compOptimized = bubbleSortOptimized(arr1, n);
        compNormal = bubbleSortNormal(arr2, n);

        printf("%d\t%lld\t\t%lld\n",
               n, compOptimized, compNormal);

        // Store values for Gnuplot
        fprintf(data, "%d %lld %lld\n",
                n, compOptimized, compNormal);

        free(arr1);
        free(arr2);
    }

    fclose(data);


    // Open Gnuplot
    gp = popen("gnuplot -persistent", "w");

    if (gp == NULL)
    {
        printf("Error opening Gnuplot.\n");
        return 1;
    }

    // Graph settings
    fprintf(gp, "set title 'Performance Analysis of Bubble Sort'\n");

    fprintf(gp, "set xlabel 'Number of Elements (n)'\n");

    fprintf(gp, "set ylabel 'Number of Comparisons'\n");

    fprintf(gp, "set grid\n");

    fprintf(gp, "set key left top\n");


    // Plot both versions
    fprintf(gp,
        "plot 'bubble.dat' using 1:2 "
        "with linespoints title 'Optimized Bubble Sort', "
        "'bubble.dat' using 1:3 "
        "with linespoints title 'Normal Bubble Sort'\n"
    );

    fflush(gp);

    pclose(gp);

    return 0;
}