/*
    Problem 6: Application of sorting - VI
    ----------------------------------------------------------------
    We are given a set S of n intervals on a line. Each interval i
    is described by its left and right endpoints (l_i, r_i), and a
    point that is EQUAL to an endpoint is considered to be inside
    that interval (endpoints are inclusive).

    We want to find a point p on the line that lies inside the
    LARGEST number of intervals, and report that largest count.

    Example (from the question):
        S = {(10,40), (20,60), (50,90), (15,70)}
        No point lies in all 4 intervals.
        p = 50 is an example of a point that lies in 3 intervals.

    Required time complexity: O(n log n)

    ----------------------------------------------------------------
    Simple idea (very similar to the "party attendance" problem):

        Think of each interval's left endpoint as a "+1" event
        (one more interval starts covering the line here) and each
        right endpoint as a "-1" event (one interval stops covering
        the line after this point).

        Step 1: Make a single list of 2n events:
                  n "start" events   (point = l_i, change = +1)
                  n "end"   events   (point = r_i, change = -1)

        Step 2: Sort all 2n events by their point value.
                  IMPORTANT: since endpoints are inclusive, if a
                  "start" and an "end" happen to fall on the exact
                  same point, the "start" must be processed first.
                  This makes sure that a point where one interval
                  ends and another begins is correctly counted as
                  being inside BOTH intervals.
                  Sorting 2n events takes O(n log n) time.

        Step 3: Walk through the sorted events once, keeping a
                  running counter of how many intervals currently
                  cover the line at this point:
                      start event -> counter = counter + 1
                      end   event -> counter = counter - 1
                  (We check for a new maximum right after a start,
                  and also right before an end -- both cases catch
                  the point where the counter is at its highest.)
                  This single pass takes O(n) time.

        Total time:
              O(n log n)  for sorting
            + O(n)        for the single sweep
            = O(n log n)

    ----------------------------------------------------------------
    Proper input representation:
        Every event is stored as a simple structure containing a
        point value and a type (+1 for start, -1 for end). This
        turns the problem into "sort 2n numbers and sweep through
        them once," which is exactly what an O(n log n) algorithm
        needs.
*/

#include <stdio.h>
#include <stdlib.h>   /* needed for qsort() */

#define MAX_INTERVALS 100   /* maximum number of intervals allowed */

typedef struct {
    int point;
    int type;   /* +1 = start of interval, -1 = end of interval */
} Event;

/* ---------- Compare function needed by qsort() ----------
   Sorts events by point value. If two events share the same point,
   a "start" (+1) is placed BEFORE an "end" (-1), so that endpoints
   are correctly treated as inclusive. */
int compareEvents(const void *p, const void *q) {
    Event e1 = *(const Event *) p;
    Event e2 = *(const Event *) q;

    if (e1.point != e2.point) {
        return e1.point - e2.point;
    }
    /* same point: start (+1) comes before end (-1) */
    return e2.type - e1.type;
}

int main(void) {
    int l[MAX_INTERVALS], r[MAX_INTERVALS];
    Event events[2 * MAX_INTERVALS];
    int n, i;

    /* -------- Take input from the user -------- */
    printf("Enter number of intervals (n): ");
    scanf("%d", &n);

    printf("Enter left and right endpoint for each interval:\n");
    for (i = 0; i < n; i++) {
        printf("Interval %d (left right): ", i + 1);
        scanf("%d %d", &l[i], &r[i]);
    }

    /* -------- Step 1: Build the list of 2n events -------- */
    for (i = 0; i < n; i++) {
        events[2 * i].point     = l[i];
        events[2 * i].type      = +1;   /* start */

        events[2 * i + 1].point = r[i];
        events[2 * i + 1].type  = -1;   /* end   */
    }

    int totalEvents = 2 * n;

    /* -------- Step 2: Sort all events (O(n log n)) -------- */
    qsort(events, totalEvents, sizeof(Event), compareEvents);

    /* -------- Step 3: Sweep through events once, tracking the
                 running count of intervals covering each point,
                 and remembering the best (maximum) count and a
                 point where it happens -------- */
    int currentCount = 0;
    int maxCount = 0;
    int bestPoint = 0;

    for (i = 0; i < totalEvents; i++) {
        if (events[i].type == +1) {
            /* a new interval starts: it covers this point too */
            currentCount++;
            if (currentCount > maxCount) {
                maxCount = currentCount;
                bestPoint = events[i].point;
            }
        } else {
            /* an interval ends here, but this point is still
               inside it (inclusive), so check BEFORE removing it */
            if (currentCount > maxCount) {
                maxCount = currentCount;
                bestPoint = events[i].point;
            }
            currentCount--;
        }
    }

    /* -------- Print the result -------- */
    printf("\nMaximum number of intervals covering a single point: %d\n", maxCount);
    printf("One such point is: %d\n", bestPoint);

    return 0;
}

/*
    ----------------------------------------------------------------
    EXAMPLE (to understand how the program works)
    ----------------------------------------------------------------

    Suppose the user enters:

        Enter number of intervals (n): 4
        Interval 1 (left right): 10 40
        Interval 2 (left right): 20 60
        Interval 3 (left right): 50 90
        Interval 4 (left right): 15 70

    So:
        S = {(10,40), (20,60), (50,90), (15,70)}

    Step 1: Build events (point, type)
        (10,+1) (40,-1) (20,+1) (60,-1) (50,+1) (90,-1) (15,+1) (70,-1)

    Step 2: Sort events by point (starts before ends on ties)
        (10,+1) (15,+1) (20,+1) (40,-1) (50,+1) (60,-1) (70,-1) (90,-1)

    Step 3: Sweep through and track the running count:

        point 10: start -> count = 1   (new max = 1, bestPoint = 10)
        point 15: start -> count = 2   (new max = 2, bestPoint = 15)
        point 20: start -> count = 3   (new max = 3, bestPoint = 20)
        point 40: end   -> check first: 3 is not > 3, no update
                            then count = 2
        point 50: start -> count = 3   (3 is not > current max 3, no update)
        point 60: end   -> check: 3 not > 3, no update; count = 2
        point 70: end   -> check: 2 not > 3, no update; count = 1
        point 90: end   -> check: 1 not > 3, no update; count = 0

    The highest value the count ever reached is 3, first occurring
    at point 20 (where intervals (10,40), (20,60) and (15,70) all
    overlap).

    Final program OUTPUT:

        Maximum number of intervals covering a single point: 3
        One such point is: 20

    (Point 50, mentioned in the question, is ALSO a valid point that
    lies inside exactly 3 intervals - (20,60), (50,90), (15,70) - so
    both answers are correct; the program simply reports the first
    point at which the maximum is reached.)

    ----------------------------------------------------------------
    Why this is O(n log n):
        - Building the 2n events takes O(n)
        - Sorting the 2n events takes O(n log n)
        - The single sweep through the events takes O(n)
        - Total: O(n log n) + O(n) = O(n log n)
    ----------------------------------------------------------------
*/