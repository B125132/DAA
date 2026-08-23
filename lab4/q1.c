/*
 * Application of sorting - I
 * ---------------------------
 * Input: n pairs of items. First item = a number, second item = a colour
 *        (red, blue, or yellow). Items are already sorted by number.
 *
 * Task:  Sort the items by colour (all reds, then all blues, then all
 *        yellows) such that, within items of the same colour, the numbers
 *        remain sorted (i.e. the sort must be STABLE).
 *
 * Idea:  Since the array is already sorted by number, all we need is a
 *        STABLE bucketing of items by colour. A single left-to-right pass
 *        that places each item into the next free slot of its colour's
 *        bucket automatically preserves the relative (numeric) order of
 *        items sharing a colour. This is essentially a counting sort on
 *        the colour field.
 *
 * Steps:
 *   1) Count how many items are red, blue, and yellow      -> O(n)
 *   2) Compute starting index of each colour's block in
 *      the output array (red block first, then blue,
 *      then yellow)                                        -> O(1)
 *   3) Scan the input array once more; place each item at
 *      the current "next free position" for its colour and
 *      advance that pointer                                 -> O(n)
 *
 * Total time complexity: O(n)
 * Total space complexity: O(n) (for the output array)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { RED = 0, BLUE = 1, YELLOW = 2, INVALID = -1 } Colour;

typedef struct {
    int number;
    Colour colour;
} Item;

/* Convert a colour string (case-insensitive) to the Colour enum */
Colour parseColour(const char *s) {
    char buf[20];
    int i = 0;
    while (s[i] && i < 19) {
        buf[i] = (char) tolower((unsigned char) s[i]);
        i++;
    }
    buf[i] = '\0';

    if (strcmp(buf, "red") == 0)    return RED;
    if (strcmp(buf, "blue") == 0)   return BLUE;
    if (strcmp(buf, "yellow") == 0) return YELLOW;
    return INVALID;
}

const char* colourName(Colour c) {
    switch (c) {
        case RED:    return "red";
        case BLUE:   return "blue";
        case YELLOW: return "yellow";
        default:     return "invalid";
    }
}

/*
 * Stable O(n) sort of items by colour (red < blue < yellow),
 * preserving the relative order of items with the same colour.
 */
void sortByColour(Item arr[], int n) {
    if (n <= 0) return;

    int count[3] = {0, 0, 0};   /* counts for RED, BLUE, YELLOW */
    int i;

    /* Pass 1: count occurrences of each colour -> O(n) */
    for (i = 0; i < n; i++) {
        count[arr[i].colour]++;
    }

    /* Compute starting position (offset) of each colour's block -> O(1) */
    int startIndex[3];
    startIndex[RED]    = 0;
    startIndex[BLUE]   = count[RED];
    startIndex[YELLOW] = count[RED] + count[BLUE];

    /* "next free slot" pointer for each colour, initialised to its start */
    int nextPos[3];
    nextPos[RED]    = startIndex[RED];
    nextPos[BLUE]   = startIndex[BLUE];
    nextPos[YELLOW] = startIndex[YELLOW];

    Item *result = (Item *) malloc(n * sizeof(Item));
    if (!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Pass 2: place each item into its colour's next free slot -> O(n)
       Because we scan left-to-right and always take the NEXT free slot,
       items of the same colour keep their original relative order,
       i.e. they stay sorted by number. This is what makes it stable. */
    for (i = 0; i < n; i++) {
        Colour c = arr[i].colour;
        result[nextPos[c]] = arr[i];
        nextPos[c]++;
    }

    /* Copy the sorted result back into the original array */
    memcpy(arr, result, n * sizeof(Item));
    free(result);
}

int main(void) {
    int n;

    printf("Enter number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid value of n.\n");
        return EXIT_FAILURE;
    }

    Item *arr = (Item *) malloc(n * sizeof(Item));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d pairs as: <number> <colour(red/blue/yellow)>\n", n);
    printf("(Items are assumed to already be sorted by number.)\n");

    for (int i = 0; i < n; i++) {
        char colourStr[20];
        printf("Item %d: ", i + 1);
        if (scanf("%d %19s", &arr[i].number, colourStr) != 2) {
            printf("Invalid input.\n");
            free(arr);
            return EXIT_FAILURE;
        }
        Colour c = parseColour(colourStr);
        if (c == INVALID) {
            printf("Invalid colour '%s'. Use red, blue, or yellow.\n", colourStr);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i].colour = c;
    }

    sortByColour(arr, n);

    printf("\nItems sorted by colour (red, then blue, then yellow),\n");
    printf("with numbers kept sorted within each colour:\n\n");
    for (int i = 0; i < n; i++) {
        printf("%d %s\n", arr[i].number, colourName(arr[i].colour));
    }

    free(arr);
    return EXIT_SUCCESS;
}