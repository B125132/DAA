#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Helper function to find the next power of 2
int nextPowerOf2(int n) {
    int power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

// Function to allocate memory for a 2D matrix
int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free allocated memory for a 2D matrix
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's algorithm for matrix multiplication
void strassenMultiply(int** A, int** B, int** C, int n) {
    // Base Case: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    // Allocate memory for quadrants of A, B, and C
    int **A11 = allocateMatrix(newSize), **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize), **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize), **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize), **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize), **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize), **C22 = allocateMatrix(newSize);

    // Allocate memory for the 7 Strassen products (M1 to M7) and temp matrices
    int **M1 = allocateMatrix(newSize), **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize), **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize), **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);
    int **temp1 = allocateMatrix(newSize), **temp2 = allocateMatrix(newSize);

    // Divide matrices A and B into 4 sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculate M1 to M7
    addMatrix(A11, A22, temp1, newSize);
    addMatrix(B11, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, M1, newSize);

    addMatrix(A21, A22, temp1, newSize);
    strassenMultiply(temp1, B11, M2, newSize);

    subMatrix(B12, B22, temp1, newSize);
    strassenMultiply(A11, temp1, M3, newSize);

    subMatrix(B21, B11, temp1, newSize);
    strassenMultiply(A22, temp1, M4, newSize);

    addMatrix(A11, A12, temp1, newSize);
    strassenMultiply(temp1, B22, M5, newSize);

    subMatrix(A21, A11, temp1, newSize);
    addMatrix(B11, B12, temp2, newSize);
    strassenMultiply(temp1, temp2, M6, newSize);

    subMatrix(A12, A22, temp1, newSize);
    addMatrix(B21, B22, temp2, newSize);
    strassenMultiply(temp1, temp2, M7, newSize);

    // Calculate sub-matrices C11, C12, C21, C22
    addMatrix(M1, M4, temp1, newSize);
    subMatrix(temp1, M5, temp2, newSize);
    addMatrix(temp2, M7, C11, newSize);

    addMatrix(M3, M5, C12, newSize);

    addMatrix(M2, M4, C21, newSize);

    subMatrix(M1, M2, temp1, newSize);
    addMatrix(temp1, M3, temp2, newSize);
    addMatrix(temp2, M6, C22, newSize);

    // Combine sub-matrices back into C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free all dynamically allocated memory to prevent memory leaks
    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(M1, newSize);  freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);  freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);  freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(temp1, newSize); freeMatrix(temp2, newSize);
}

// Function to print a matrix
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Updated to handle zero padding
void generateRandomMatrices(int** A, int** B, int n, int m) {
    srand(time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i < n && j < n) {
                A[i][j] = rand() % 10; // Real values
                B[i][j] = rand() % 10;
            } else {
                A[i][j] = 0;           // Zero padding
                B[i][j] = 0;
            }
        }
    }
    printf("\nMatrices generated with random values (internal size padded to %dx%d).\n", m, m);
}

// Updated to handle zero padding
void inputMatricesManually(int** A, int** B, int n, int m) {
    printf("\nEnter values for Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i < n && j < n) {
                printf("A[%d][%d] = ", i, j);
                scanf("%d", &A[i][j]);
            } else {
                A[i][j] = 0; // Zero padding
            }
        }
    }

    printf("\nEnter values for Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i < n && j < n) {
                printf("B[%d][%d] = ", i, j);
                scanf("%d", &B[i][j]);
            } else {
                B[i][j] = 0; // Zero padding
            }
        }
    }
}

int main() {
    int n;

    // 1. Get matrix size from the user
    printf("Enter the size of the matrix: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size entered.\n");
        return 1;
    }

    // Calculate padded size
    int m = nextPowerOf2(n);
 
    // Allocate memory using the padded size (m)
    int** A = allocateMatrix(m);
    int** B = allocateMatrix(m);
    int** C = allocateMatrix(m);

    // 2. Choose input method
    int choice;
    printf("\nChoose matrix initialization method:\n");
    printf("1. Generate random values\n");
    printf("2. Enter values manually\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Pass both n (actual) and m (padded)
    if (choice == 1) {
        generateRandomMatrices(A, B, n, m);
    } else if (choice == 2) {
        inputMatricesManually(A, B, n, m);
    } else {
        printf("Invalid choice! Defaulting to random generation.\n");
        generateRandomMatrices(A, B, n, m);
    }

    // Display input matrices using the original size (n)
    printf("\nMatrix A:\n");
    printMatrix(A, n);
    
    printf("\nMatrix B:\n");
    printMatrix(B, n);

    // Multiply matrices using Strassen's algorithm on padded size (m)
    strassenMultiply(A, B, C, m);

    // Display the result using the original size (n)
    printf("\nResultant Matrix C (A * B):\n");
    printMatrix(C, n);

    // Clean up allocated memory using padded size (m)
    freeMatrix(A, m);
    freeMatrix(B, m);
    freeMatrix(C, m);

    return 0;
}