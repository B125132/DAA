/* Q9: Hu-Tucker algorithm (optimal alphabetic binary tree)
 * INPUT : n, then weights w_1..w_n (leaves keep their left-to-right order).
 * PHASE 1 (combination): keep a working sequence of nodes; leaves are
 *   "terminal" (square), merged nodes are "internal" (circle).  Two nodes are
 *   COMPATIBLE when no terminal node lies strictly between them.  Repeatedly
 *   merge the compatible pair of minimum total weight (ties: leftmost left
 *   node, then leftmost right node); the merged node replaces the pair at the
 *   position of the RIGHT node.  This is repeated n-1 times.
 * PHASE 2 (levels): the depth of every leaf in the combination tree is its level.
 * PHASE 3 (recombination): leaves in index order with these levels form a valid
 *   alphabetic tree; codes are assigned by code_{i+1} = (code_i + 1) shifted to
 *   the new level (so the left-to-right order is preserved).
 * VALIDATION: Knuth-style O(n^3) dynamic programme for the optimal alphabetic
 *   tree cost  C[i][j] = W(i..j) + min_k (C[i][k] + C[k+1][j]).
 * COMPLEXITY (as implemented): each of the n-1 rounds scans compatible pairs
 *   O(n^2) naive  => O(n^3) worst case; scanning only until the next terminal
 *   node makes it O(n^2) typically.  With the Hu-Tucker/Knuth-Hu-Tucker priority
 *   structures it drops to O(n log n); the output cost is sum(w_i * depth_i).
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 200

static long long w[MAXN];
static int n;

/* working sequence */
static long long sw[MAXN];      /* weight  */
static int sleaf[MAXN];         /* 1 = terminal */
static int sid[MAXN];           /* tree node id */
static int par[2 * MAXN], depth_[MAXN];

static void phase1(void)
{
    int m = n, next = n;
    for (int i = 0; i < n; i++) { sw[i] = w[i]; sleaf[i] = 1; sid[i] = i; par[i] = -1; }
    while (m > 1) {
        long long best = (long long)4e18;
        int bi = -1, bj = -1;
        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < m; j++) {
                if (sw[i] + sw[j] < best) { best = sw[i] + sw[j]; bi = i; bj = j; }
                if (sleaf[j]) break;           /* a terminal blocks anything beyond it */
            }
        par[sid[bi]] = par[sid[bj]] = next;
        par[next] = -1;
        sw[bj] = best; sleaf[bj] = 0; sid[bj] = next++;   /* new node at RIGHT position */
        for (int k = bi; k < m - 1; k++) {                /* delete position bi        */
            sw[k] = sw[k + 1]; sleaf[k] = sleaf[k + 1]; sid[k] = sid[k + 1];
        }
        m--;
    }
}

static long long optimalDP(void)
{
    static long long C[MAXN][MAXN], pre[MAXN + 1];
    pre[0] = 0;
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + w[i];
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            long long b = (long long)4e18;
            for (int k = i; k < j; k++) {
                long long c = C[i][k] + C[k + 1][j];
                if (c < b) b = c;
            }
            C[i][j] = b + pre[j + 1] - pre[i];
        }
    return n > 1 ? C[0][n - 1] : 0;
}

int main(void)
{
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) return 1;
    for (int i = 0; i < n; i++) if (scanf("%lld", &w[i]) != 1) return 1;
    phase1();

    long long cost = 0;
    for (int i = 0; i < n; i++) {
        int d = 0;
        for (int u = par[i]; u != -1; u = par[u]) d++;
        depth_[i] = d;
        cost += w[i] * d;
    }
    printf("%-5s %-8s %-6s %s\n", "leaf", "weight", "level", "alphabetic code");
    unsigned long long code = 0;
    int ok = 1;
    for (int i = 0; i < n; i++) {
        int d = depth_[i] ? depth_[i] : 1;
        if (i > 0) {
            code++;
            int pd = depth_[i - 1] ? depth_[i - 1] : 1;
            if (d >= pd) code <<= (d - pd);
            else { if (code & ((1ULL << (pd - d)) - 1)) ok = 0; code >>= (pd - d); }
        }
        printf("%-5d %-8lld %-6d ", i + 1, w[i], d);
        for (int b = d - 1; b >= 0; b--) putchar((code >> b & 1) ? '1' : '0');
        putchar('\n');
    }
    long long opt = optimalDP();
    printf("Hu-Tucker cost = %lld, DP optimum = %lld  (%s)%s\n", cost, opt,
           cost == opt ? "agree" : "MISMATCH", ok ? "" : "  [code assignment problem]");
    return 0;
}