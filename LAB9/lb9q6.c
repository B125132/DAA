/* Q6: Rearrange string so equal characters are at least K apart
 * INPUT : K, then the string S (no spaces).
 * ALGORITHM (greedy + max-heap + cooldown):
 *   - count frequencies; max-heap keyed by (remaining count, smaller char first);
 *   - for position i = 0..n-1 take the available character with the largest
 *     remaining count, write it, decrement its count;
 *   - that character is "cooling": it is re-inserted into the heap (if count>0)
 *     only after position i+K-1 has been filled, i.e. when position i+K is next;
 *   - if the heap is empty at some position before n, no arrangement exists.
 *   Using the most frequent character first is safe by an exchange argument:
 *   it is the one most likely to run out of legal slots.
 * COMPLEXITY: n positions * O(log sigma) heap work (sigma <= 256 distinct chars)
 *             => O(n log sigma) time, O(n + sigma) space.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int cnt; unsigned char ch; } E;
static E heap[256];
static int hs;

static int better(E a, E b)               /* a should be above b */
{
    if (a.cnt != b.cnt) return a.cnt > b.cnt;
    return a.ch < b.ch;
}
static void push(E x)
{
    int i = hs++;
    heap[i] = x;
    while (i > 0 && better(heap[i], heap[(i - 1) / 2])) {
        E t = heap[i]; heap[i] = heap[(i - 1) / 2]; heap[(i - 1) / 2] = t; i = (i - 1) / 2;
    }
}
static E pop(void)
{
    E top = heap[0];
    heap[0] = heap[--hs];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < hs && better(heap[l], heap[m])) m = l;
        if (r < hs && better(heap[r], heap[m])) m = r;
        if (m == i) break;
        E t = heap[i]; heap[i] = heap[m]; heap[m] = t; i = m;
    }
    return top;
}

/* returns malloc'ed result, or NULL when impossible */
static char *rearrange(const char *s, int K)
{
    int n = (int)strlen(s), cnt[256] = {0};
    if (K < 1) K = 1;                               /* K <= 1 means no restriction */
    char *res = malloc(n + 1);
    for (int i = 0; i < n; i++) cnt[(unsigned char)s[i]]++;
    hs = 0;
    for (int c = 0; c < 256; c++) if (cnt[c]) push((E){ cnt[c], (unsigned char)c });
    for (int i = 0; i < n; i++) {
        if (hs == 0) { free(res); return NULL; }
        E e = pop();
        res[i] = (char)e.ch;
        cnt[e.ch]--;
        if (i - K + 1 >= 0) {                       /* release char placed at i-K+1 */
            unsigned char r = (unsigned char)res[i - K + 1];
            if (cnt[r] > 0) push((E){ cnt[r], r });
        }
    }
    res[n] = '\0';
    return res;
}

static int verify(const char *s, const char *r, int K)
{
    int a[256] = {0}, b[256] = {0}, last[256];
    int n = (int)strlen(s);
    if ((int)strlen(r) != n) return 0;
    for (int i = 0; i < n; i++) { a[(unsigned char)s[i]]++; b[(unsigned char)r[i]]++; }
    for (int c = 0; c < 256; c++) { if (a[c] != b[c]) return 0; last[c] = -1000000000; }
    for (int i = 0; i < n; i++) {
        unsigned char c = (unsigned char)r[i];
        if (K > 0 && i - last[c] < K) return 0;
        last[c] = i;
    }
    return 1;
}

int main(void)
{
    static char S[1 << 20];
    int K;
    if (scanf("%d %1048575s", &K, S) != 2) return 1;
    char *r = rearrange(S, K);
    if (K < 1) K = 1;
    if (!r) printf("Result: \"\" (impossible)\n");
    else {
        printf("Result: %s  [%s]\n", r, verify(S, r, K) ? "verified" : "INVALID");
        free(r);
    }
    return 0;
}