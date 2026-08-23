/*
    Problem 4: Application of sorting - IV
    ----------------------------------------------------------------
    A camera at the door records, for each of n people at a party:
        - entry time  a[i]
        - exit  time  b[i]        (always  b[i] > a[i])

    We want to find the TIME when the LARGEST NUMBER of people were
    simultaneously present at the party (all entry/exit times are
    distinct - no ties).

    Required time complexity: O(n log n)

    ----------------------------------------------------------------
    Simple idea:

        Think of every entry as a "+1" event (one more person walks
        in) and every exit as a "-1" event (one person walks out).

        Step 1: Make a single list of 2n events:
                  n arrival events   (time = a[i], change = +1)
                  n departure events (time = b[i], change = -1)

        Step 2: Sort all 2n events by time.
                  Sorting 2n events takes O(n log n) time.

        Step 3: Walk through the sorted events from earliest to
                  latest, keeping a running counter of how many
                  people are currently inside:
                      arrival   -> counter = counter + 1
                      departure -> counter = counter - 1
                  While doing this single pass (O(n)), remember the
                  highest value the counter ever reached, and the
                  time at which that happened.

        Total time:
              O(n log n)  for sorting
            + O(n)        for the single sweep
            = O(n log n)

    ----------------------------------------------------------------
    Proper input representation:
        Every event is stored as a simple structure containing just
        a time and a type (+1 for arrival, -1 for departure). This
        turns the whole problem into "sort 2n numbers and sweep
        through them once," which is exactly what an O(n log n)
        algorithm needs.
*/

#include <stdio.h>
#include <stdlib.h>   /* needed for qsort() */

#define MAX_PEOPLE 100   /* maximum number of people allowed */

typedef struct {
    int time;
    int type;   /* +1 = arrival (entry), -1 = departure (exit) */
} Event;

/* ---------- Compare function needed by qsort() ----------
   Sorts events purely by time (all times are given as distinct). */
int compareEvents(const void *p, const void *q) {
    Event e1 = *(const Event *) p;
    Event e2 = *(const Event *) q;
    return e1.time - e2.time;
}

int main(void) {
    int a[MAX_PEOPLE], b[MAX_PEOPLE];
    Event events[2 * MAX_PEOPLE];
    int n, i;

    /* -------- Take input from the user -------- */
    printf("Enter number of people (n): ");
    scanf("%d", &n);

    printf("Enter entry time and exit time for each person:\n");
    for (i = 0; i < n; i++) {
        printf("Person %d (entry exit): ", i + 1);
        scanf("%d %d", &a[i], &b[i]);
    }

    /* -------- Step 1: Build the list of 2n events -------- */
    for (i = 0; i < n; i++) {
        events[2 * i].time     = a[i];
        events[2 * i].type     = +1;   /* arrival  */

        events[2 * i + 1].time = b[i];
        events[2 * i + 1].type = -1;   /* departure */
    }

    int totalEvents = 2 * n;

    /* -------- Step 2: Sort all events by time (O(n log n)) -------- */
    qsort(events, totalEvents, sizeof(Event), compareEvents);

    /* -------- Step 3: Sweep through events once, tracking the
                 running count of people present, and remembering
                 the best (maximum) count and the time it happened
                 -------- */
    int currentCount = 0;
    int maxCount = 0;
    int bestTime = 0;

    for (i = 0; i < totalEvents; i++) {
        currentCount += events[i].type;

        if (currentCount > maxCount) {
            maxCount = currentCount;
            bestTime = events[i].time;
        }
    }

    /* -------- Print the result -------- */
    printf("\nMaximum number of people present at the same time: %d\n", maxCount);
    printf("This maximum first occurs at time: %d\n", bestTime);

    return 0;
}

/*
    ----------------------------------------------------------------
    EXAMPLE (to understand how the program works)
    ----------------------------------------------------------------

    Suppose the user enters:

        Enter number of people (n): 4
        Person 1 (entry exit): 1 3
        Person 2 (entry exit): 2 5
        Person 3 (entry exit): 4 6
        Person 4 (entry exit): 7 9

    So:
        a = {1, 2, 4, 7}
        b = {3, 5, 6, 9}

    Step 1: Build events (time, type)
        (1,+1) (3,-1) (2,+1) (5,-1) (4,+1) (6,-1) (7,+1) (9,-1)

    Step 2: Sort events by time
        (1,+1) (2,+1) (3,-1) (4,+1) (5,-1) (6,-1) (7,+1) (9,-1)

    Step 3: Sweep through and track the running count:

        time 1: +1  -> count = 1   (new max = 1, bestTime = 1)
        time 2: +1  -> count = 2   (new max = 2, bestTime = 2)
        time 3: -1  -> count = 1
        time 4: +1  -> count = 2   (not greater than current max)
        time 5: -1  -> count = 1
        time 6: -1  -> count = 0
        time 7: +1  -> count = 1
        time 9: -1  -> count = 0

    The highest value the count ever reached is 2, and it first
    happened at time 2 (right after person 2 arrived, while person 1
    was still inside).

    Final program OUTPUT:

        Maximum number of people present at the same time: 2
        This maximum first occurs at time: 2

    ----------------------------------------------------------------
    Why this is O(n log n):
        - Building the 2n events takes O(n)
        - Sorting the 2n events takes O(n log n)
        - The single sweep through the events takes O(n)
        - Total: O(n log n) + O(n) = O(n log n)
    ----------------------------------------------------------------
*/