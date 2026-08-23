/*
    Problem 3: Application of sorting - III
    ----------------------------------------------------------------
    We are given:
        - A set S of n integers
        - An integer k
        - An integer T

    We want to find out whether there exist k numbers from S that
    add up exactly to T.

    Required time complexity: O(n^(k-1) * log n)

    ----------------------------------------------------------------
    Simple idea:

        Step 1: Sort the array S.
                  Sorting n numbers takes O(n log n) time.

        Step 2: Choose (k-1) numbers from S in every possible way
                  (using nested loops / recursion), always picking
                  numbers in increasing order of position so that we
                  never pick the same number twice and never repeat
                  the same combination twice.

                  The number of ways to choose (k-1) numbers out of
                  n is about O(n^(k-1)).

        Step 3: For each such choice of (k-1) numbers, we know what
                  the LAST (kth) number must be:

                       remainder = T - (sum of the k-1 chosen numbers)

                  Instead of scanning to look for this remainder, we
                  use BINARY SEARCH on the (already sorted) remaining
                  part of the array. Binary search takes O(log n).

        Total time:
              O(n^(k-1)) combinations  *  O(log n) binary search each
            = O(n^(k-1) * log n)

          (Sorting only adds O(n log n), which is smaller and does
           not change the final complexity for k >= 2.)

    ----------------------------------------------------------------
    Proper input representation:
        The set S is simply stored as an integer array. Sorting and
        binary search both work directly and efficiently on a plain
        array, so no special structure is needed.
*/

#include <stdio.h>
#include <stdlib.h>   /* needed for qsort() */

#define MAX_SIZE 100   /* maximum size allowed for the set S */
#define MAX_K    20    /* maximum value allowed for k */

int S[MAX_SIZE];        /* the sorted set of numbers            */
int chosen[MAX_K];      /* stores the k numbers found (if any)  */
int n, k;
long long T;
int found = 0;           /* becomes 1 as soon as an answer is found */

/* ---------- Compare function needed by qsort() ---------- */
int compare(const void *a, const void *b) {
    int numA = *(const int *) a;
    int numB = *(const int *) b;
    return numA - numB;
}

/* ---------- Binary search for 'target' within S[left..right] ----------
   Returns the index of target if found, otherwise -1.                */
int binarySearch(int left, int right, int target) {
    while (left <= right) {
        int mid = (left + right) / 2;
        if (S[mid] == target) {
            return mid;
        } else if (S[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

/* ----------------------------------------------------------------
   Recursive function to try every way of picking (k-1) numbers.

   startIndex : where to start picking from (keeps combinations
                unique and avoids reusing an earlier number)
   count      : how many numbers picked so far
   sumSoFar   : sum of the numbers picked so far
   ---------------------------------------------------------------- */
void tryCombinations(int startIndex, int count, long long sumSoFar) {
    if (found) return;   /* already found an answer, stop early */

    if (count == k - 1) {
        /* We have chosen k-1 numbers. Find out what the last
           (kth) number must be, and binary-search for it in the
           remaining part of the sorted array (from startIndex
           onward), so we never reuse an already-chosen number. */
        long long remainder = T - sumSoFar;

        int pos = binarySearch(startIndex, n - 1, (int) remainder);
        if (pos != -1) {
            chosen[k - 1] = S[pos];
            found = 1;
        }
        return;
    }

    for (int i = startIndex; i < n && !found; i++) {
        chosen[count] = S[i];
        tryCombinations(i + 1, count + 1, sumSoFar + S[i]);
    }
}

int main(void) {
    int i;

    /* -------- Take input from the user -------- */
    printf("Enter the size of set S (n): ");
    scanf("%d", &n);

    printf("Enter %d integers of set S:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }

    printf("Enter k (how many numbers should add up to T): ");
    scanf("%d", &k);

    printf("Enter T (the target sum): ");
    scanf("%lld", &T);

    /* Special, trivial case: k = 1 just means "is T itself in S?" */
    if (k < 1 || k > n) {
        printf("\nInvalid value of k.\n");
        return 0;
    }

    /* -------- Step 1: Sort S (O(n log n)) -------- */
    qsort(S, n, sizeof(int), compare);

    /* -------- Step 2 & 3: Try all combinations of (k-1) numbers,
                 and binary-search for the kth number -------- */
    if (k == 1) {
        int pos = binarySearch(0, n - 1, (int) T);
        if (pos != -1) {
            found = 1;
            chosen[0] = S[pos];
        }
    } else {
        tryCombinations(0, 0, 0);
    }

    /* -------- Print the result -------- */
    if (found) {
        printf("\nYes, %d numbers exist that add up to %lld: ", k, T);
        for (i = 0; i < k; i++) {
            printf("%d ", chosen[i]);
        }
        printf("\n");
    } else {
        printf("\nNo, no %d numbers in S add up to %lld.\n", k, T);
    }

    return 0;
}
