/*
    Program: Check if there exists a pair (one element from S1, one
             element from S2) whose sum equals a given number x.
    ----------------------------------------------------------------
    We are given:
        - Set S1 with n numbers
        - Set S2 with n numbers
        - A number x

    We want to find out whether there exist:
        a (from S1) and b (from S2)
    such that:
        a + b = x

    Simple idea (this gives O(n log n) time):

        Step 1: Sort the set S2.
                 Sorting n numbers takes O(n log n) time.

        Step 2: For every number 'a' in S1 (there are n of them),
                 we need a partner number 'b' from S2 such that
                     b = x - a
                 Instead of checking every element of S2 one by one
                 (which would be slow), we use BINARY SEARCH on the
                 already-sorted S2 to look for (x - a).
                 Binary search takes O(log n) time per lookup.

        Since we do this lookup for all n elements of S1:
            Total time = n * O(log n) = O(n log n)

        Adding the O(n log n) for sorting:
            Overall time = O(n log n) + O(n log n) = O(n log n)

    Proper input representation:
        Both S1 and S2 are stored as simple arrays of integers.
        Arrays allow direct sorting and binary searching, which is
        exactly what this algorithm needs - no special structure
        is required.
*/

#include <stdio.h>
#include <stdlib.h>   /* needed for qsort() */

#define MAX_SIZE 100   /* maximum size allowed for each set */

/* ---------- Compare function needed by qsort() ----------
   qsort() is a ready-made, standard C library function that sorts
   an array in O(n log n) time (it uses an efficient sorting method
   internally, so we don't have to write our own). We just tell it
   how to compare two elements using this small helper function.
------------------------------------------------------------------- */
int compare(const void *a, const void *b) {
    int numA = *(const int *) a;
    int numB = *(const int *) b;
    return numA - numB;   /* negative if a<b, 0 if equal, positive if a>b */
}

/* ---------- Binary search: returns 1 if 'target' is found in arr[], else 0 ---------- */
int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target) {
            return 1;   /* found */
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;   /* not found */
}

int main(void) {
    int S1[MAX_SIZE], S2[MAX_SIZE];
    int n, x, i;

    /* -------- Take input from the user -------- */
    printf("Enter the size of each set (n): ");
    scanf("%d", &n);

    printf("Enter %d numbers of set S1:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &S1[i]);
    }

    printf("Enter %d numbers of set S2:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &S2[i]);
    }

    printf("Enter the value of x: ");
    scanf("%d", &x);

    /* -------- Step 1: Sort S2 (O(n log n) using standard library qsort) -------- */
    qsort(S2, n, sizeof(int), compare);

    /* -------- Step 2: For each element in S1, search for (x - a) in S2 -------- */
    int found = 0;
    int pairA = 0, pairB = 0;

    for (i = 0; i < n; i++) {
        int need = x - S1[i];   /* the value we need from S2 */

        if (binarySearch(S2, n, need) == 1) {
            found = 1;
            pairA = S1[i];
            pairB = need;
            break;   /* stop as soon as one valid pair is found */
        }
    }

    /* -------- Print the result -------- */
    if (found == 1) {
        printf("\nYes, a pair exists: %d (from S1) + %d (from S2) = %d\n",
               pairA, pairB, x);
    } else {
        printf("\nNo pair exists in S1 and S2 whose sum is %d\n", x);
    }

    return 0;
}

/*
    ----------------------------------------------------------------
    EXAMPLE (to understand how the program works)
    ----------------------------------------------------------------

    Suppose the user enters:

        Enter the size of each set (n): 4
        Enter 4 numbers of set S1:
        2 4 7 10
        Enter 4 numbers of set S2:
        1 5 9 3
        Enter the value of x: 13

    So:
        S1 = {2, 4, 7, 10}
        S2 = {1, 5, 9, 3}
        x  = 13

    Step 1: Sort S2
        S2 sorted = {1, 3, 5, 9}

    Step 2: For each element 'a' in S1, look for (x - a) in sorted S2
    using binary search:

        a = 2   -> need = 13 - 2  = 11   -> search 11 in S2 -> not found
        a = 4   -> need = 13 - 4  = 9    -> search 9  in S2 -> FOUND!
                    (4 from S1) + (9 from S2) = 13

    Since a pair is found, the program stops here.

    Final program OUTPUT:

        Yes, a pair exists: 4 (from S1) + 9 (from S2) = 13

    ----------------------------------------------------------------
    Why this is O(n log n):
        - Sorting S2 takes O(n log n)
        - Each binary search takes O(log n), and we do this at most
          n times (once for each element of S1) -> O(n log n)
        - Total: O(n log n) + O(n log n) = O(n log n)
    ----------------------------------------------------------------
*/