/* Q4: Minimum cost to connect sticks
 * INPUT : n, then n stick lengths.
 * ALGORITHM (Huffman-style greedy): always connect the two shortest sticks,
 *   put the result back into a min-heap.  Exchange argument: a stick merged
 *   early is paid for once per merge it takes part in, so short sticks must be
 *   merged first (same proof as Huffman coding).
 * COMPLEXITY: n-1 iterations, each 2 pops + 1 push = O(log n)
 *             => O(n log n) time, O(n) space.
 */
#include <stdio.h>
#include <stdlib.h>

static long long *h; static int hs;
static void push(long long x)
{
    int i = hs++;
    h[i] = x;
    while (i > 0 && h[i] < h[(i - 1) / 2]) {
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
        if (l < hs && h[l] < h[m]) m = l;
        if (r < hs && h[r] < h[m]) m = r;
        if (m == i) break;
        long long t = h[i]; h[i] = h[m]; h[m] = t; i = m;
    }
    return top;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 1) return 1;
    h = malloc(sizeof(long long) * (n + 1));
    for (int i = 0; i < n; i++) { long long x; if (scanf("%lld", &x) != 1) return 1; push(x); }
    long long cost = 0;
    while (hs > 1) {
        long long a = pop(), b = pop();
        printf("connect %lld + %lld -> cost %lld\n", a, b, a + b);
        cost += a + b;
        push(a + b);
    }
    printf("Minimum total cost = %lld\n", cost);
    free(h);
    return 0;
}