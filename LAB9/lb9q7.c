/* Q7: Minimise deviation in array
 * Operations: odd x -> 2x ; even x -> x/2.   deviation = max - min.
 * INPUT : n, then n positive integers.
 * KEY IDEA (two-way greedy -> one-way): an odd element can only become 2x, so
 *   first multiply every odd element by 2.  Now every element only needs the
 *   "divide by 2" move, which can only DECREASE it.  Keep a max-heap and the
 *   current minimum.  Repeatedly: record (max - min); if max is even, halve it
 *   (the only move that can lower the maximum), update min, continue; if max
 *   is odd, the maximum can no longer decrease, so stop.
 * VALIDATION: independent sliding-window check over all reachable values
 *   {odd part * 2^j} of every element (smallest window containing one value
 *   of each element).
 * COMPLEXITY: each element is halved at most log2(M) times (M = max value),
 *   each halving costs O(log n)  =>  O(n log n log M) time, O(n) space.
 */
#include <stdio.h>
#include <stdlib.h>

static long long *h; static int hs;
static void push(long long x)
{
    int i = hs++;
    h[i] = x;
    while (i > 0 && h[i] > h[(i - 1) / 2]) {
        long long t = h[i]; h[i] = h[(i - 1) / 2]; h[(i - 1) / 2] = t; i = (i - 1) / 2;
    }
}
static long long pop(void)
{
    long long top = h[0];
    h[0] = h[--hs];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < hs && h[l] > h[m]) m = l;
        if (r < hs && h[r] > h[m]) m = r;
        if (m == i) break;
        long long t = h[i]; h[i] = h[m]; h[m] = t; i = m;
    }
    return top;
}

static long long minDeviation(const long long *a, int n)
{
    hs = 0;
    long long mn = (long long)4e18, best = (long long)4e18;
    for (int i = 0; i < n; i++) {
        long long x = (a[i] & 1) ? a[i] * 2 : a[i];
        push(x);
        if (x < mn) mn = x;
    }
    for (;;) {
        long long mx = pop();
        if (mx - mn < best) best = mx - mn;
        if (mx & 1) break;
        mx /= 2;
        if (mx < mn) mn = mx;
        push(mx);
    }
    return best;
}

/* ---- validator ---- */
typedef struct { long long v; int id; } P;
static int cmpP(const void *a, const void *b)
{
    long long x = ((const P *)a)->v, y = ((const P *)b)->v;
    return (x > y) - (x < y);
}
static long long windowCheck(const long long *a, int n)
{
    P *p = malloc(sizeof(P) * n * 64);
    int m = 0;
    for (int i = 0; i < n; i++) {
        long long o = a[i]; while (!(o & 1)) o /= 2;
        long long top = (a[i] & 1) ? a[i] * 2 : a[i];
        for (long long v = o; v <= top; v *= 2) p[m++] = (P){ v, i };
    }
    qsort(p, m, sizeof(P), cmpP);
    int *cnt = calloc(n, sizeof(int)), have = 0, l = 0;
    long long best = (long long)4e18;
    for (int r = 0; r < m; r++) {
        if (cnt[p[r].id]++ == 0) have++;
        while (have == n) {
            if (p[r].v - p[l].v < best) best = p[r].v - p[l].v;
            if (--cnt[p[l].id] == 0) have--;
            l++;
        }
    }
    free(p); free(cnt);
    return best;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 1) return 1;
    long long *a = malloc(sizeof(long long) * n);
    h = malloc(sizeof(long long) * (n + 1));
    for (int i = 0; i < n; i++) if (scanf("%lld", &a[i]) != 1) return 1;
    long long r = minDeviation(a, n), v = windowCheck(a, n);
    printf("Minimum deviation = %lld  (validator: %lld, %s)\n", r, v, r == v ? "agree" : "MISMATCH");
    free(a); free(h);
    return 0;
}