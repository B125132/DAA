#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000.0

int main() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    printf("Enter successful search probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++) {
        scanf("%lf", &p[i]);
    }

    printf("Enter unsuccessful search probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++) {
        scanf("%lf", &q[i]);
    }

    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));

    for (int i = 0; i <= n + 1; i++) {
        e[i] = (double *)calloc(n + 2, sizeof(double));
        w[i] = (double *)calloc(n + 2, sizeof(double));
    }

    // Empty subtrees
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Calculate DP
    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            e[i][j] = INF;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {

                double cost =
                    e[i][r - 1] +
                    e[r + 1][j] +
                    w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.4lf\n",
           e[1][n]);

    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
    }

    free(e);
    free(w);
    free(p);
    free(q);

    return 0;
}