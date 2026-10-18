/* Q3: Minimum number of refuelling stops
 * INPUT : F D n, then n lines: d_i f_i  (distance from origin, fuel available)
 *         (1 unit of fuel = 1 unit of distance; vehicle starts with F)
 * ALGORITHM (greedy with max-heap): drive as far as possible; every station
 *   passed is remembered in a max-heap of fuel amounts.  When the fuel is not
 *   enough to reach D, retroactively refuel at the passed station with the
 *   largest fuel (this is the "reverse greedy" step).  If the heap is empty
 *   the target is unreachable.
 * COMPLEXITY: sort O(n log n) + each station pushed/popped once O(n log n)
 *             => O(n log n) time, O(n) space.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct { long long d, f; } St;

static int cmp(const void *a, const void *b)
{
    long long x = ((const St *)a)->d, y = ((const St *)b)->d;
    return (x > y) - (x < y);
}

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

int main(void)
{
    long long F, D; int n;
    if (scanf("%lld %lld %d", &F, &D, &n) != 3) return 1;
    St *s = malloc(sizeof(St) * (n + 1));
    h = malloc(sizeof(long long) * (n + 1));
    for (int i = 0; i < n; i++) if (scanf("%lld %lld", &s[i].d, &s[i].f) != 2) return 1;
    qsort(s, n, sizeof(St), cmp);

    long long reach = F;           /* farthest point reachable so far */
    int i = 0, stops = 0;
    while (reach < D) {
        while (i < n && s[i].d <= reach) push(s[i++].f);
        if (hs == 0) { printf("Target unreachable (-1)\n"); return 0; }
        long long got = pop();
        reach += got;
        stops++;
        printf("Stop %d: refuel %lld, can now reach %lld\n", stops, got, reach);
    }
    printf("Minimum refuelling stops = %d\n", stops);
    free(s); free(h);
    return 0;
}