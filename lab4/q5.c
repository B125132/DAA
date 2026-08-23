/*
    Problem 5: Application of sorting - V
    ----------------------------------------------------------------
    We are given a list I of n intervals, each written as (x_i, y_i)
    meaning "starts at x_i, ends at y_i".

    Whenever two (or more) intervals overlap, we must merge them
    into a single bigger interval. The final answer is the list of
    all merged intervals.

    Example (from the question):
        I = {(1,3), (2,6), (8,10), (7,8)}
        Merging (1,3) and (2,6) gives (1,6)
        Merging (8,10) and (7,8) gives (7,10)
        Output = {(1,6), (7,10)}

    Required time complexity: O(n log n)  (worst case)

    ----------------------------------------------------------------
    Simple idea:

        Step 1: Sort the n intervals by their START value (x_i).
                  Sorting n intervals takes O(n log n) time.

        Step 2: Walk through the sorted intervals once, from left
                  to right, keeping track of a "current merged
                  interval":
                    - If the next interval's start is less than or
                      equal to the current merged interval's end,
                      they overlap (or just touch) -> merge them by
                      extending the end if needed.
                    - Otherwise, the current merged interval is
                      finished. Save it, and start a new "current
                      merged interval" from this next one.
                  This single pass takes O(n) time.

        Total time:
              O(n log n)  for sorting
            + O(n)        for the single merge pass
            = O(n log n)

    ----------------------------------------------------------------
    Proper input representation:
        Each interval is stored as a simple structure with a start
        and an end value. Sorting an array of such structures by
        start value, then scanning it once, is exactly what an
        O(n log n) algorithm needs - no special data structure is
        required.
*/

#include <stdio.h>
#include <stdlib.h>   /* needed for qsort() */

#define MAX_INTERVALS 100   /* maximum number of intervals allowed */

typedef struct {
    int start;
    int end;
} Interval;

/* ---------- Compare function needed by qsort() ----------
   Sorts intervals by their start value. */
int compareIntervals(const void *p, const void *q) {
    Interval i1 = *(const Interval *) p;
    Interval i2 = *(const Interval *) q;
    return i1.start - i2.start;
}

int main(void) {
    Interval interval[MAX_INTERVALS];
    Interval merged[MAX_INTERVALS];
    int n, i;

    /* -------- Take input from the user -------- */
    printf("Enter number of intervals (n): ");
    scanf("%d", &n);

    printf("Enter each interval as: start end\n");
    for (i = 0; i < n; i++) {
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &interval[i].start, &interval[i].end);
    }

    /* -------- Step 1: Sort intervals by start value (O(n log n)) -------- */
    qsort(interval, n, sizeof(Interval), compareIntervals);

    /* -------- Step 2: Sweep through once, merging overlapping
                 (or touching) intervals -------- */
    int mergedCount = 0;

    /* Start with the first interval as the current merged interval */
    merged[0] = interval[0];
    mergedCount = 1;

    for (i = 1; i < n; i++) {
        Interval current = interval[i];
        Interval *last = &merged[mergedCount - 1];   /* last merged so far */

        if (current.start <= last->end) {
            /* Overlaps (or touches) the last merged interval:
               extend its end if this interval reaches further */
            if (current.end > last->end) {
                last->end = current.end;
            }
        } else {
            /* No overlap: this becomes a brand-new merged interval */
            merged[mergedCount] = current;
            mergedCount++;
        }
    }

    /* -------- Print the result -------- */
    printf("\nMerged intervals:\n");
    for (i = 0; i < mergedCount; i++) {
        printf("(%d, %d)\n", merged[i].start, merged[i].end);
    }

    return 0;
}

/*
    ----------------------------------------------------------------
    EXAMPLE (to understand how the program works)
    ----------------------------------------------------------------

    Suppose the user enters:

        Enter number of intervals (n): 4
        Interval 1: 1 3
        Interval 2: 2 6
        Interval 3: 8 10
        Interval 4: 7 8

    So:
        I = {(1,3), (2,6), (8,10), (7,8)}

    Step 1: Sort intervals by start value
        Sorted I = {(1,3), (2,6), (7,8), (8,10)}

    Step 2: Sweep through and merge:

        Start: current merged interval = (1,3)

        Next = (2,6):
            2 <= 3 (overlaps) -> extend end to max(3,6) = 6
            current merged interval becomes (1,6)

        Next = (7,8):
            7 <= 6? No -> does NOT overlap
            (1,6) is finished and saved.
            new current merged interval = (7,8)

        Next = (8,10):
            8 <= 8 (touches) -> extend end to max(8,10) = 10
            current merged interval becomes (7,10)

        End of list: save the last current merged interval (7,10)

    Final program OUTPUT:

        Merged intervals:
        (1, 6)
        (7, 10)

    This matches the expected result exactly.

    ----------------------------------------------------------------
    Why this is O(n log n):
        - Sorting the n intervals takes O(n log n)
        - The single left-to-right merge pass takes O(n)
        - Total: O(n log n) + O(n) = O(n log n)
    ----------------------------------------------------------------
*/