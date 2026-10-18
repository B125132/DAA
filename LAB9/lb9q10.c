/* Q10: Greedy superstring (shortest common superstring heuristic)
 * INPUT : n, then n strings (no spaces, length <= 63).
 * GREEDY: repeatedly merge the ordered pair (a,b) with the LARGEST overlap
 *   ov(a,b) = longest suffix of a that is a prefix of b, replacing both with
 *   a + b[ov..].  (Ties: smallest i, then smallest j.)  Strings that are
 *   substrings of another input string are removed first.
 * OPTIMAL (for the study of the conjecture, n <= 16): exact shortest superstring
 *   by bitmask DP over visiting order:  dp[mask][last] = shortest length of a
 *   string that contains the set `mask` and ends with string `last`.
 *   The program prints |greedy|, |optimal| and the ratio, so counter-examples to
 *   the "ratio <= 2" conjecture (the recent claim reports ratios up to 9/4 for
 *   long even-length strings) can be tested on any instance one constructs.
 * COMPLEXITY: overlaps O(n^2 L); greedy O(n^3 L) naive (n merges x n^2 pairs x
 *   overlap cost; O(n L) per merge after caching overlaps, O(L n log n) with the
 *   classical suffix-tree/heap implementation); exact DP O(2^n n^2).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 16
#define MAXL 64

static int overlap(const char *a, const char *b)
{
    int la = (int)strlen(a), lb = (int)strlen(b);
    int m = la < lb ? la : lb;
    for (int k = m; k > 0; k--)
        if (strncmp(a + la - k, b, k) == 0) return k;
    return 0;
}

static char *greedy(char **s, int n)
{
    char **v = malloc(sizeof(char *) * n);
    int m = n;
    for (int i = 0; i < n; i++) v[i] = strdup(s[i]);
    while (m > 1) {
        int bi = 0, bj = 1, bo = -1;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++) {
                if (i == j) continue;
                int o = overlap(v[i], v[j]);
                if (o > bo) { bo = o; bi = i; bj = j; }
            }
        char *t = malloc(strlen(v[bi]) + strlen(v[bj]) + 1);
        strcpy(t, v[bi]);
        strcat(t, v[bj] + bo);
        free(v[bi]); free(v[bj]);
        v[bi] = t;
        v[bj] = v[m - 1];
        m--;
    }
    char *res = v[0];
    free(v);
    return res;
}

static int optimalLength(char **s, int n)
{
    static int ov[MAXN][MAXN], dp[1 << MAXN][MAXN];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) ov[i][j] = (i == j) ? 0 : overlap(s[i], s[j]);
    for (int mask = 0; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++) dp[mask][i] = 1 << 28;
    for (int i = 0; i < n; i++) dp[1 << i][i] = (int)strlen(s[i]);
    for (int mask = 1; mask < (1 << n); mask++)
        for (int last = 0; last < n; last++) {
            if (!(mask >> last & 1) || dp[mask][last] >= (1 << 28)) continue;
            for (int nx = 0; nx < n; nx++) {
                if (mask >> nx & 1) continue;
                int c = dp[mask][last] + (int)strlen(s[nx]) - ov[last][nx];
                if (c < dp[mask | 1 << nx][nx]) dp[mask | 1 << nx][nx] = c;
            }
        }
    int best = 1 << 28;
    for (int i = 0; i < n; i++)
        if (dp[(1 << n) - 1][i] < best) best = dp[(1 << n) - 1][i];
    return best;
}

int main(void)
{
    int n0, n = 0;
    char *in[MAXN * 4], *s[MAXN];
    if (scanf("%d", &n0) != 1 || n0 < 1 || n0 > MAXN * 4) return 1;
    for (int i = 0; i < n0; i++) {
        char buf[MAXL + 1];
        if (scanf("%64s", buf) != 1) return 1;
        in[i] = strdup(buf);
    }
    /* remove duplicates and strings contained in another string */
    for (int i = 0; i < n0; i++) {
        int drop = 0;
        for (int j = 0; j < n0 && !drop; j++) {
            if (i == j) continue;
            if (strstr(in[j], in[i]) && (strlen(in[j]) > strlen(in[i]) || j < i)) drop = 1;
        }
        if (!drop && n < MAXN) s[n++] = in[i];
    }
    char *g = greedy(s, n);
    printf("Greedy superstring  (%zu): %s\n", strlen(g), g);
    for (int i = 0; i < n; i++)
        if (!strstr(g, s[i])) { printf("ERROR: %s missing\n", s[i]); return 1; }
    int opt = optimalLength(s, n);
    printf("Optimal length      (%d)\n", opt);
    printf("Approximation ratio = %.4f\n", (double)strlen(g) / opt);
    free(g);
    return 0;
}