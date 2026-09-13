#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int year;
    int type;
};

/*
   type = -1 -> death
   type =  1 -> birth
*/

int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    /*
       Death (-1) comes before birth (+1)
       when both happen in the same year.
    */
    return e1->type - e2->type;
}

int main()
{
    int n;
    struct Event events[200];

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("Enter birth and death year of scientist %d: ",
               i + 1);

        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    /*
       Sort all birth and death events.
    */
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        alive += events[i].type;

        if (alive > maximum)
        {
            maximum = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nBest year = %d\n", bestYear);
    printf("Maximum number of scientists alive = %d\n",
           maximum);

    return 0;
}