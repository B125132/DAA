/* Q1: Fractional Knapsack with Deterioration Rate
 *
 * MODEL (stated assumption): items are consumed one after another at 1 unit of
 * weight per unit time.  An item whose consumption starts at time t
 * (t = weight consumed so far) has effective density e_i(t) = v_i/w_i - lam_i*t.
 *
 * FACTS USED
 *  (L1) Order lemma  : if A is consumed right before B, swapping them changes
 *       the value by  wA*wB*(lamA - lamB) in favour of "A first".  Hence the
 *       consumed items should be scheduled in NON-INCREASING decay rate.
 *  (L2) Fractional lemma: value is linear in each x_i and convex along the
 *       direction (x_i+s, x_j-s), so some optimum has at most ONE fractional item.
 *
 * ALGORITHM (greedy with time probing)
 *  For each probe time p in {0, W/G, 2W/G, ..., W}:
 *     rank items by density at p (v_i/w_i - lam_i*p), fill the knapsack greedily
 *     (only the last item is fractional), then schedule the chosen items by
 *     decreasing lam (L1) and evaluate the true value.  Keep the best probe.
 *  A pairwise "shift weight from item i to item j" improvement pass follows.
 *  When all lam = 0 this is exactly the classical fractional knapsack.
 *
 * VALIDATION: exact optimum by subset enumeration (L1+L2), for n <= 16.
 *
 * INPUT : n W, then n lines: v_i w_i lam_i
 * COMPLEXITY: probing O(G n log n); improvement pass O(n^3) per round
 *             (O(G n log n) alone for the pure greedy part);
 *             validator O(2^n * n^2).  The general problem is a quadratic
 *             knapsack in disguise, so no exact polynomial greedy is claimed.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define G 64

typedef struct { double v, w, lam, d; } Item;
static Item it[MAXN];
static int n;
static double W;

static int byLam(const void *a, const void *b)       /* lam descending */
{
    double x = ((const Item *)a)->lam, y = ((const Item *)b)->lam;
    return (x < y) - (x > y);
}

static double probe;                                  /* current probe time */
static int idxByDensity(const void *a, const void *b)
{
    const Item *x = &it[*(const int *)a], *y = &it[*(const int *)b];
    double ex = x->d - x->lam * probe, ey = y->d - y->lam * probe;
    return (ex < ey) - (ex > ey);
}

/* value of consuming items (already in lam-desc order) with amounts x[] */
static double evaluate(const double *x)
{
    double t = 0, val = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] <= 0) continue;
        val += x[i] * (it[i].d - it[i].lam * t);
        t += x[i];
    }
    return val;
}

static double solve(double *bestx)
{
    static double x[MAXN];
    static int idx[MAXN];
    double best = -1e300;
    for (int g = 0; g <= G; g++) {
        probe = W * g / G;
        for (int i = 0; i < n; i++) { idx[i] = i; x[i] = 0; }
        qsort(idx, n, sizeof(int), idxByDensity);
        double rem = W;
        for (int k = 0; k < n && rem > 1e-12; k++) {
            int i = idx[k];
            if (it[i].d - it[i].lam * probe <= 0) break;
            x[i] = it[i].w < rem ? it[i].w : rem;
            rem -= x[i];
        }
        double v = evaluate(x);          /* items are stored in lam-desc order */
        if (v > best) { best = v; for (int i = 0; i < n; i++) bestx[i] = x[i]; }
    }
    /* local improvement: move weight from item i to item j, or use spare room */
    int improved = 1;
    while (improved) {
        improved = 0;
        double used = 0;
        for (int i = 0; i < n; i++) used += bestx[i];
        for (int j = 0; j < n; j++) {                       /* fill spare room */
            double add = it[j].w - bestx[j];
            if (add > W - used) add = W - used;
            if (add <= 1e-12) continue;
            bestx[j] += add;
            double v = evaluate(bestx);
            if (v > best + 1e-9) { best = v; used += add; improved = 1; }
            else bestx[j] -= add;
        }
        for (int i = 0; i < n; i++)                         /* shift i -> j   */
            for (int j = 0; j < n; j++) {
                if (i == j || bestx[i] <= 1e-12) continue;
                double d = bestx[i];
                if (d > it[j].w - bestx[j]) d = it[j].w - bestx[j];
                if (d <= 1e-12) continue;
                bestx[i] -= d; bestx[j] += d;
                double v = evaluate(bestx);
                if (v > best + 1e-9) { best = v; improved = 1; }
                else { bestx[i] += d; bestx[j] -= d; }
            }
    }
    return best;
}

/* exact optimum: subset of full items + at most one fractional item */
static double exact(void)
{
    double best = 0, x[16];
    for (int mask = 0; mask < (1 << n); mask++) {
        double ws = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) ws += it[i].w;
        if (ws > W + 1e-12) continue;
        for (int j = -1; j < n; j++) {
            if (j >= 0 && (mask >> j & 1)) continue;
            for (int i = 0; i < n; i++) x[i] = (mask >> i & 1) ? it[i].w : 0;
            if (j >= 0) {
                x[j] = it[j].w < W - ws ? it[j].w : W - ws;
                if (x[j] <= 1e-12) continue;
            }
            double v = evaluate(x);
            if (v > best) best = v;
        }
    }
    return best;
}

int main(void)
{
    if (scanf("%d %lf", &n, &W) != 2) return 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%lf %lf %lf", &it[i].v, &it[i].w, &it[i].lam) != 3) return 1;
        it[i].d = it[i].v / it[i].w;
    }
    int orig[MAXN];                      /* remember original numbering */
    static Item copy[MAXN];
    for (int i = 0; i < n; i++) copy[i] = it[i];
    /* sort by lam descending, keeping original index via a stable lookup */
    qsort(it, n, sizeof(Item), byLam);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (it[i].v == copy[j].v && it[i].w == copy[j].w && it[i].lam == copy[j].lam) { orig[i] = j + 1; break; }

    static double x[MAXN];
    double g = solve(x);
    printf("Consumption schedule (decreasing decay rate):\n");
    printf("%-5s %-9s %-10s %-10s\n", "item", "start t", "amount", "value");
    double t = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] <= 0) continue;
        double e = it[i].d - it[i].lam * t;
        printf("%-5d %-9.3f %-10.3f %-10.3f%s\n", orig[i], t, x[i], x[i] * e,
               x[i] < it[i].w ? "  (fractional)" : "");
        t += x[i];
    }
    printf("Greedy (probing) total value = %.4f\n", g);
    if (n <= 16) {
        double ex = exact();
        printf("Exact optimum (enumeration)  = %.4f  -> %s\n", ex,
               g + 1e-6 >= ex ? "greedy is optimal on this input"
                              : "greedy is a heuristic: gap on this input");
    }
    return 0;
}