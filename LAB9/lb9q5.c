/* Q5: Candy distribution
 * INPUT : n, then n ratings.
 * Method 1 (two passes): left->right enforces "rating > left neighbour => more
 *   candy"; right->left enforces the same for the right neighbour with max().
 * Method 2 (one pass, O(1) extra space, "slope" greedy): the ratings are a
 *   sequence of up-slopes and down-slopes.  A slope of length k contributes
 *   1+2+...+k candies; the peak is counted in the longer of its two slopes.
 * Both are compared at run time.
 * COMPLEXITY: Method 1 O(n) time, O(n) space; Method 2 O(n) time, O(1) space.
 */
#include <stdio.h>
#include <stdlib.h>

static long long twoPass(const int *r, int n)
{
    int *c = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) c[i] = 1;
    for (int i = 1; i < n; i++) if (r[i] > r[i - 1]) c[i] = c[i - 1] + 1;
    for (int i = n - 2; i >= 0; i--)
        if (r[i] > r[i + 1] && c[i] <= c[i + 1]) c[i] = c[i + 1] + 1;
    long long s = 0;
    printf("candies: ");
    for (int i = 0; i < n; i++) { s += c[i]; printf("%d ", c[i]); }
    printf("\n");
    free(c);
    return s;
}

static long long slope(const int *r, int n)
{
    long long total = 1;
    int up = 0, down = 0, peak = 0;
    for (int i = 1; i < n; i++) {
        if (r[i] > r[i - 1]) { up++; down = 0; peak = up; total += 1 + up; }
        else if (r[i] == r[i - 1]) { up = down = peak = 0; total += 1; }
        else { up = 0; down++; total += down + (peak >= down ? 0 : 1); }
    }
    return total;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 1) return 1;
    int *r = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) if (scanf("%d", &r[i]) != 1) return 1;
    long long a = twoPass(r, n), b = slope(r, n);
    printf("Two-pass total = %lld, slope total = %lld  (%s)\n", a, b, a == b ? "agree" : "MISMATCH");
    free(r);
    return 0;
}