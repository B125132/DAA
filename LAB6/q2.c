#include <stdio.h>
#include <math.h>

#define N 3

// Matrix Addition
void add(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Matrix Multiplication
void multiply(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Check Zero Matrix
int isZero(int A[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (A[i][j] != 0)
                return 0;
    return 1;
}

// Check Symmetric Matrix
int isSymmetric(int A[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (A[i][j] != A[j][i])
                return 0;
    return 1;
}

// Determinant using Gaussian Elimination
double determinant(int A[N][N]) {
    double B[N][N];
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            B[i][j] = A[i][j];

    double det = 1;

    for (int i = 0; i < N; i++) {
        if (fabs(B[i][i]) < 1e-9)
            return 0;

        for (int j = i + 1; j < N; j++) {
            double r = B[j][i] / B[i][i];

            for (int k = i; k < N; k++)
                B[j][k] -= r * B[i][k];
        }

        det *= B[i][i];
    }

    return det;
}

// Transpose in-place
void transpose(int A[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            int t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
}

// Dominant Eigenvalue and Eigenvector
void eigen(int A[N][N]) {
    double v[N] = {1, 1, 1};
    double lambda = 0;

    for (int step = 0; step < 100; step++) {
        double w[N], max = 0;

        for (int i = 0; i < N; i++) {
            w[i] = 0;
            for (int j = 0; j < N; j++)
                w[i] += A[i][j] * v[j];

            if (fabs(w[i]) > max)
                max = fabs(w[i]);
        }

        for (int i = 0; i < N; i++)
            v[i] = w[i] / max;

        lambda = max;
    }

    printf("Dominant eigenvalue: %.2f\n", lambda);
    printf("Eigenvector: ");

    for (int i = 0; i < N; i++)
        printf("%.2f ", v[i]);

    printf("\n");
}

int main() {
    int A[N][N] = {
        {2, 1, 0},
        {1, 2, 1},
        {0, 1, 2}
    };

    int B[N][N] = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}
    };

    int C[N][N];

    // (i) Matrix Addition
    add(A, B, C);

    printf("Matrix Addition:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    // (ii) Matrix Multiplication
    multiply(A, B, C);

    printf("\nMatrix Multiplication:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    // (iii) Zero Matrix
    printf("\nZero Matrix: %s\n", isZero(A) ? "Yes" : "No");

    // (iv) Symmetric Matrix
    printf("Symmetric Matrix: %s\n",
           isSymmetric(A) ? "Yes" : "No");

    // (v) Determinant
    printf("Determinant: %.2f\n", determinant(A));

    // (vi) Transpose
    transpose(A);

    printf("\nTranspose:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    // (vii) Eigenvalue and Eigenvector
    printf("\n");
    eigen(A);

    return 0;
}

/*
Time Complexity:

1. Matrix Addition          - O(n^2)
2. Matrix Multiplication    - O(n^3)
3. Zero Matrix              - O(n^2)
4. Symmetric Matrix         - O(n^2)
5. Determinant              - O(n^3)
6. Transpose in-place       - O(n^2)
7. Eigenvalue/Eigenvector   - O(n^2)

Operations:
- Addition adds corresponding elements of two matrices.
- Multiplication uses three nested loops.
- Zero matrix checks whether every element is zero.
- Symmetric matrix checks A[i][j] == A[j][i].
- Determinant is calculated using Gaussian elimination.
- Transpose swaps elements across the main diagonal.
- Eigenvalue and eigenvector are estimated using the Power Iteration method.

Input Representation:
- Square matrices are represented using 2D arrays of size N x N.
- Here N = 3, so the matrices contain 3 rows and 3 columns.
*/