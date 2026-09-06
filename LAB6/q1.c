#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 1. Find maximum
int maximum(int a[], int n) {
    int max = a[0];

    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    return max;
}

// 2. First and second largest
void secondLargest(int a[], int n) {
    int first = a[0], second = -2147483648;

    for (int i = 1; i < n; i++) {
        if (a[i] > first) {
            second = first;
            first = a[i];
        } else if (a[i] > second && a[i] != first) {
            second = a[i];
        }
    }

    printf("Largest = %d, Second largest = %d\n", first, second);
}

// 3. Mean
float mean(int a[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return (float)sum / n;
}

// For median
int compare(const void *x, const void *y) {
    return (*(int *)x - *(int *)y);
}

// 4. Median
float median(int a[], int n) {
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    qsort(b, n, sizeof(int), compare);

    float m;
    if (n % 2)
        m = b[n / 2];
    else
        m = (b[n / 2 - 1] + b[n / 2]) / 2.0;

    free(b);
    return m;
}

// 5. Standard deviation
float standardDeviation(int a[], int n) {
    float avg = mean(a, n);
    float sum = 0;

    for (int i = 0; i < n; i++)
        sum += (a[i] - avg) * (a[i] - avg);

    return sqrt(sum / n);
}

// 6. Mode
int mode(int a[], int n) {
    int mode = a[0], maxCount = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;

        for (int j = 0; j < n; j++)
            if (a[i] == a[j])
                count++;

        if (count > maxCount) {
            maxCount = count;
            mode = a[i];
        }
    }

    return mode;
}

// 7. Remove duplicates
int removeDuplicates(int a[], int n) {
    int k = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < k; j++)
            if (a[i] == a[j])
                found = 1;

        if (!found)
            a[k++] = a[i];
    }

    return k;
}

// 8. Reverse array
void reverse(int a[], int n) {
    int i = 0, j = n - 1;

    while (i < j) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }
}

// 9. Partition around pivot
int partition(int a[], int n, int pivot) {
    int i = 0;

    for (int j = 0; j < n; j++) {
        if (a[j] <= pivot) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
        }
    }

    return i;
}

int main() {
    int a[] = {4, 2, 7, 2, 9, 4, 5};
    int n = 7;

    printf("Maximum = %d\n", maximum(a, n));

    secondLargest(a, n);

    printf("Mean = %.2f\n", mean(a, n));
    printf("Median = %.2f\n", median(a, n));
    printf("Standard deviation = %.2f\n", standardDeviation(a, n));
    printf("Mode = %d\n", mode(a, n));

    n = removeDuplicates(a, n);

    printf("After removing duplicates: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    reverse(a, n);

    printf("\nReversed array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
/*
Time Complexity:
1. Finding maximum          - O(n)
2. First and second largest - O(n)
3. Finding mean             - O(n)
4. Finding median           - O(n log n)
5. Standard deviation       - O(n)
6. Finding mode             - O(n^2)
7. Removing duplicates      - O(n^2)
8. Reversing array          - O(n)
9. Partitioning array       - O(n)

Operations:
- Maximum, mean and standard deviation require one traversal.
- Median uses sorting, so its complexity is O(n log n).
- Mode and duplicate removal use nested loops, giving O(n^2).
- Reversing uses two pointers and swaps elements in-place.
- Partition rearranges elements around the pivot in one traversal.
*/