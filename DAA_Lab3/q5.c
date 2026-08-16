#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_power_of_two(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int** allocate_matrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)calloc(n, sizeof(int));
    }
    return mat;
}

void free_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Builds the N x N matrix from the N independent elements mathematically
void build_recursive(int** M, int* arr, int r, int c, int size) {
    if (size == 1) {
        M[r][c] = arr[0];
        return;
    }
    int half = size / 2;
    // M1 Block (Top-Left & Bottom-Right)
    build_recursive(M, arr, r, c, half);
    build_recursive(M, arr, r + half, c + half, half);
    // M2 Block (Top-Right & Bottom-Left)
    build_recursive(M, arr + half, r, c + half, half);
    build_recursive(M, arr + half, r + half, c, half);
}

void fill_manual(int** mat, int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    printf("Because of the recursive pattern, you only need to enter the %d independent elements (the first row).\n", n);
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    build_recursive(mat, arr, 0, 0, n);
    free(arr);
}

void fill_random(int** mat, int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10; // Keep numbers small for readable output
    }
    build_recursive(mat, arr, 0, 0, n);
    free(arr);
}

void print_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// O(n^2) Divide and Conquer Multiplication Function
void multiply_dc(int** A, int** B, int** C, int rA, int cA, int rB, int cB, int rC, int cC, int size) {
    if (size == 1) {
        C[rC][cC] = A[rA][cA] * B[rB][cB];
        return;
    }

    int half = size / 2;
    
    // Allocate temporary space for O(n^2) additions
    int** sumA = allocate_matrix(half);
    int** sumB = allocate_matrix(half);
    int** diffA = allocate_matrix(half);
    int** diffB = allocate_matrix(half);
    int** P = allocate_matrix(half);
    int** Q = allocate_matrix(half);

    // Compute A1+A2, B1+B2, A1-A2, B1-B2
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // A1 is at [rA+i][cA+j], A2 is at [rA+i][cA+half+j]
            sumA[i][j]  = A[rA+i][cA+j] + A[rA+i][cA+half+j]; 
            sumB[i][j]  = B[rB+i][cB+j] + B[rB+i][cB+half+j];
            diffA[i][j] = A[rA+i][cA+j] - A[rA+i][cA+half+j]; 
            diffB[i][j] = B[rB+i][cB+j] - B[rB+i][cB+half+j]; 
        }
    }

    // Recursively compute P = (A1+A2)(B1+B2) and Q = (A1-A2)(B1-B2)
    multiply_dc(sumA, sumB, P, 0, 0, 0, 0, 0, 0, half);
    multiply_dc(diffA, diffB, Q, 0, 0, 0, 0, 0, 0, half);

    // Combine P and Q to get C1 and C2, then place them into the output matrix C
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int c1 = (P[i][j] + Q[i][j]) / 2;
            int c2 = (P[i][j] - Q[i][j]) / 2;

            // Place C1 in Top-Left and Bottom-Right
            C[rC+i][cC+j] = c1;
            C[rC+half+i][cC+half+j] = c1;

            // Place C2 in Top-Right and Bottom-Left
            C[rC+i][cC+half+j] = c2;
            C[rC+half+i][cC+j] = c2;
        }
    }

    // Free temporary memory for this recursion depth
    free_matrix(sumA, half);
    free_matrix(sumB, half);
    free_matrix(diffA, half);
    free_matrix(diffB, half);
    free_matrix(P, half);
    free_matrix(Q, half);
}

int main() {
    int n;

    // 1. Get matrix size from the user
    printf("Enter the size of the matrix n (must be a power of 2): ");
    if (scanf("%d", &n) != 1 || n <= 0 || !is_power_of_two(n)) {
        printf("Invalid size! Size must be a positive power of 2 (e.g., 2, 4, 8, 16).\n");
        return 1;
    }

    // Allocate memory for matrices A, B, and C
    int** A = allocate_matrix(n);
    int** B = allocate_matrix(n);
    int** C = allocate_matrix(n);

    // 2. Choose input method once for both matrices
    int choice;
    printf("\nChoose matrix initialization method:\n");
    printf("1. Generate random values\n");
    printf("2. Enter values manually\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        fill_random(A, n);
        fill_random(B, n);
        printf("\nMatrices generated with random values.\n");
    } else if (choice == 2) {
        printf("\nInput for Matrix A: \n");
        fill_manual(A, n);
        printf("\nInput for Matrix B: \n");
        fill_manual(B, n);
    } else {
        printf("\nInvalid choice! Defaulting to random generation.\n");
        fill_random(A, n);
        fill_random(B, n);
    }

    // Display input matrices
    printf("\nMatrix A:\n");
    print_matrix(A, n);
    printf("Matrix B:\n");
    print_matrix(B, n);

    // Multiply matrices using the O(n^2) Divide and Conquer algorithm
    multiply_dc(A, B, C, 0, 0, 0, 0, 0, 0, n);

    // Display the result matrix
    printf("Resultant Matrix C (A * B):\n");
    print_matrix(C, n);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
    return 0;
}