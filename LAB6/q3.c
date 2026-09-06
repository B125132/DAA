#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

// FFT using divide and conquer
void fft(double complex a[], int n, int invert) {
    if (n == 1)
        return;

    double complex even[n / 2], odd[n / 2];

    for (int i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    double complex w = 1;
    double complex wn = cos(angle) + I * sin(angle);

    for (int i = 0; i < n / 2; i++) {
        double complex t = w * odd[i];

        a[i] = even[i] + t;
        a[i + n / 2] = even[i] - t;

        w *= wn;
    }

    free(NULL);

    for (int i = 0; i < n; i++)
        if (invert)
            a[i] /= 2;
}

// Convolution of two vectors
void convolution(double A[], int m, double B[], int n) {
    int size = 1;

    while (size < m + n - 1)
        size *= 2;

    double complex *a = calloc(size, sizeof(double complex));
    double complex *b = calloc(size, sizeof(double complex));

    for (int i = 0; i < m; i++)
        a[i] = A[i];

    for (int i = 0; i < n; i++)
        b[i] = B[i];

    fft(a, size, 0);
    fft(b, size, 0);

    for (int i = 0; i < size; i++)
        a[i] *= b[i];

    fft(a, size, 1);

    printf("Convolution: ");
    for (int i = 0; i < m + n - 1; i++)
        printf("%.0f ", creal(a[i]));

    printf("\n");

    free(a);
    free(b);
}

int main() {
    double A[] = {1, 2, 3};
    double B[] = {4, 5, 6};

    int m = 3, n = 3;

    convolution(A, m, B, n);

    return 0;
}

/*
Input Representation:
- Vectors A and B are represented using 1D arrays.
- m and n store their respective lengths.
- The result contains m + n - 1 elements.

Time Complexity:
- FFT: O(n log n)
- Inverse FFT: O(n log n)
- Point-wise multiplication: O(n)
- Overall convolution: O(n log n)

Operations:
- FFT recursively divides the array into even and odd elements.
- The transformed vectors are multiplied element by element.
- Inverse FFT converts the result back to the original domain.
- The final result is the convolution of A and B.
*/