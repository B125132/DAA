#include <stdio.h>

void selectionSort(int A[], int n) {
    int i, j, min_index, temp;
    
    // Run for the first n-1 elements
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        
        // Find the smallest element in the remaining unsorted array
        for (j = i + 1; j < n; j++) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
        }
        
        // Exchange the found minimum element with the first element of the unsorted part
        if (min_index != i) {
            temp = A[i];
            A[i] = A[min_index];
            A[min_index] = temp;
        }
    }
}

void printArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {64, 25, 12, 22, 11};
    int n = sizeof(A) / sizeof(A[0]);
    
    printf("Original array: \n");
    printArray(A, n);
    
    selectionSort(A, n);
    
    printf("Sorted array: \n");
    printArray(A, n);
    
    return 0;
}