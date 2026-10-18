/* Q8: Minimum number of meeting rooms
 * INPUT : n, then n lines: start end   (interval is half-open [s, e), so a
 *         meeting ending at 10 and another starting at 10 can share a room).
 * ALGORITHM (chronological ordering): sort the start times and the end times
 *   separately.  Sweep over starts; if the next meeting starts before the
 *   earliest unfinished end, a new room is needed, otherwise a room is freed
 *   and reused (advance the end pointer).  Rooms ever needed = max overlap.
 * VALIDATION: O(n^2) brute force counting overlaps at each start time.
 * COMPLEXITY: two sorts O(n log n) + one linear sweep O(n)
 *             => O(n log n) time, O(n) space.
 */
#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *a, const void *b)
{
    long long x = *(const long long *)a, y = *(const long long *)b;
    return (x > y) - (x < y);
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 0) return 1;
    long long *s = malloc(sizeof(long long) * (n + 1)), *e = malloc(sizeof(long long) * (n + 1));
    long long *os = malloc(sizeof(long long) * (n + 1)), *oe = malloc(sizeof(long long) * (n + 1));
    for (int i = 0; i < n; i++) {
        if (scanf("%lld %lld", &s[i], &e[i]) != 2) return 1;
        os[i] = s[i]; oe[i] = e[i];
    }
    qsort(s, n, sizeof(long long), cmp);
    qsort(e, n, sizeof(long long), cmp);

    int rooms = 0, j = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] < e[j]) rooms++;      /* overlap with every unfinished meeting */
        else j++;                      /* a room became free: reuse it          */
    }

    int brute = 0;                     /* validator */
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int k = 0; k < n; k++) if (os[k] <= os[i] && os[i] < oe[k]) c++;
        if (c > brute) brute = c;
    }
    printf("Minimum rooms = %d  (validator: %d, %s)\n", rooms, brute,
           rooms == brute ? "agree" : "MISMATCH");
    free(s); free(e); free(os); free(oe);
    return 0;
}