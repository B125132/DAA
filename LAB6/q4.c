#include <stdio.h>
#include <stdlib.h>

int cost = 0;

/* Reverse p[i...j] */
void reverse(int p[], int i, int j) {
    cost += j - i + 1;

    while (i < j) {
        int t = p[i];
        p[i] = p[j];
        p[j] = t;
        i++;
        j--;
    }
}

/* Rotate two adjacent parts using 3 reversals */
void rotate(int p[], int l, int m, int r) {
    if (l >= m || m >= r)
        return;

    reverse(p, l, m - 1);
    reverse(p, m, r - 1);
    reverse(p, l, r - 1);
}

/* Divide and conquer partition */
void partitionArray(int p[], int l, int r, int pivot) {
    if (r - l <= 1)
        return;

    int m = (l + r) / 2;

    partitionArray(p, l, m, pivot);
    partitionArray(p, m, r, pivot);

    int i = l, j = m;

    while (i < m && p[i] <= pivot)
        i++;

    while (j < r && p[j] <= pivot)
        j++;

    rotate(p, i, m, j);

    int shift = j - m;
    m += shift;
}

/* Sort using median pivot */
void sortArray(int p[], int l, int r) {
    if (r - l <= 1)
        return;

    int n = r - l;
    int *temp = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        temp[i] = p[l + i];

    /* Find median */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int pivot = temp[n / 2];
    free(temp);

    partitionArray(p, l, r, pivot);

    int mid = l;
    while (mid < r && p[mid] <= pivot)
        mid++;

    sortArray(p, l, mid);
    sortArray(p, mid, r);
}

int main() {
    int p[] = {4, 1, 3, 2, 5};
    int n = 5;

    printf("Original permutation: ");
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    sortArray(p, 0, n);

    printf("\nSorted permutation: ");
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\nTotal reversal cost: %d\n", cost);

    return 0;
}

/*
Time Complexity:
- Finding pivot             - O(n^2) in this implementation
- Divide-and-conquer       - O(n log n) per partition
- Overall sorting           - O(n^2) because the median is found
  using a simple nested loop.

For the required theoretical algorithm:
- Median finding          - O(n log n)
- Partition using reversals - O(n log n)
- Number of levels          - O(log n)
- Overall                   - O(n log^2 n)

Operations:
- reverse(i,j) reverses all elements from i to j.
- Three reversals are used to rotate two adjacent parts.
- Divide-and-conquer is used to partition the array around a pivot.
- The pivot is chosen near the median so that the recursion remains balanced.
- cost stores the total length of all reversal operations.

Input Representation:
- The permutation is represented using a 1D integer array.
- The reversal reverse(i,j) works directly on the array.
*/