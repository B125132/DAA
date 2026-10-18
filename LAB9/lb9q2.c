/* Q2: Huffman Coding with canonical codebook
 * INPUT : n, then n lines:  symbol(char)  frequency
 * OUTPUT: code length and canonical code for every symbol, expected length.
 * Steps : (1) build Huffman tree with a min-heap (ties broken by creation order
 *             so the result is deterministic);
 *         (2) read off code LENGTHS (leaf depths);
 *         (3) sort symbols by (length, symbol) and assign canonical codes:
 *             code = 0 for the first, then code = (code + 1) << (len_i - len_{i-1}).
 * COMPLEXITY: heap build/merges O(n log n); depth traversal O(n);
 *             canonical sort O(n log n)  =>  O(n log n) time, O(n) space.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 256

typedef struct { long long freq; int left, right, order; } Node;
static Node nd[2 * MAXN];
static int heap[2 * MAXN], hs = 0, nodes = 0;

static int lessNode(int a, int b)
{
    if (nd[a].freq != nd[b].freq) return nd[a].freq < nd[b].freq;
    return nd[a].order < nd[b].order;
}
static void push(int x)
{
    int i = hs++;
    heap[i] = x;
    while (i > 0 && lessNode(heap[i], heap[(i - 1) / 2])) {
        int p = (i - 1) / 2, t = heap[i]; heap[i] = heap[p]; heap[p] = t; i = p;
    }
}
static int pop(void)
{
    int top = heap[0];
    heap[0] = heap[--hs];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < hs && lessNode(heap[l], heap[m])) m = l;
        if (r < hs && lessNode(heap[r], heap[m])) m = r;
        if (m == i) break;
        int t = heap[i]; heap[i] = heap[m]; heap[m] = t; i = m;
    }
    return top;
}

static int len[MAXN];
static void depths(int u, int d)
{
    if (nd[u].left < 0) { len[u] = d ? d : 1; return; }   /* single symbol -> 1 bit */
    depths(nd[u].left, d + 1);
    depths(nd[u].right, d + 1);
}

static char sym[MAXN];
static int ord[MAXN];
static int cmp(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    if (len[x] != len[y]) return len[x] - len[y];
    return (unsigned char)sym[x] - (unsigned char)sym[y];
}

int main()
{
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) return 1;
    for (int i = 0; i < n; i++) {
        long long f;
        if (scanf(" %c %lld", &sym[i], &f) != 2) return 1;
        nd[i] = (Node){ f, -1, -1, i };
        push(i);
    }
    nodes = n;
    while (hs > 1) {
        int a = pop(), b = pop();
        nd[nodes] = (Node){ nd[a].freq + nd[b].freq, a, b, nodes };
        push(nodes++);
    }
    depths(pop(), 0);

    for (int i = 0; i < n; i++) ord[i] = i;
    qsort(ord, n, sizeof(int), cmp);

    unsigned long long code = 0;
    long long total = 0, bits = 0;
    double kraft = 0;
    printf("%-6s %-10s %-4s %s\n", "sym", "freq", "len", "canonical code");
    for (int k = 0; k < n; k++) {
        int i = ord[k];
        if (k > 0) code = (code + 1) << (len[i] - len[ord[k - 1]]);
        printf("%-6c %-10lld %-4d ", sym[i], nd[i].freq, len[i]);
        for (int b = len[i] - 1; b >= 0; b--) putchar((code >> b & 1) ? '1' : '0');
        putchar('\n');
        total += nd[i].freq;
        bits += nd[i].freq * len[i];
        kraft += 1.0 / (double)(1ULL << len[i]);
    }
    printf("Total bits = %lld, expected length = %.4f bits/symbol, Kraft sum = %.4f\n",
           bits, (double)bits / total, kraft);
    return 0;
}