#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n = 10000;
    int fairHeads = 0;
    int biasedHeads = 0;

    FILE *fp;

    srand((unsigned)time(NULL));

    fp = fopen("coin_data.txt", "w");

    if (fp == NULL)
    {
        printf("Error creating data file.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++)
    {
        double r1 = (double)rand() / RAND_MAX;
        double r2 = (double)rand() / RAND_MAX;

        
        if (r1 < 0.5)
            fairHeads++;

        
        if (r2 < 0.7)
            biasedHeads++;

        double fairProbability = (double)fairHeads / i;
        double biasedProbability = (double)biasedHeads / i;

        fprintf(fp, "%d %lf %lf\n",
                i,
                fairProbability,
                biasedProbability);
    }

    fclose(fp);

    printf("After %d tosses:\n\n", n);

    printf("Fair coin P(HEAD)   = %.4f\n",
           (double)fairHeads / n);

    printf("Biased coin P(HEAD) = %.4f\n",
           (double)biasedHeads / n);

  
    fp = fopen("plot.gp", "w");

    if (fp == NULL)
    {
        printf("Error creating graph file.\n");
        return 1;
    }

    fprintf(fp, "set title 'Fair Coin vs Biased Coin'\n");
    fprintf(fp, "set xlabel 'Number of Tosses'\n");
    fprintf(fp, "set ylabel 'Probability of HEAD'\n");
    fprintf(fp, "set yrange [0:1]\n");
    fprintf(fp, "set grid\n");

    fprintf(fp,
        "plot 'coin_data.txt' using 1:2 with lines title 'Fair Coin (p=0.5)', "
        "'coin_data.txt' using 1:3 with lines title 'Biased Coin (p=0.7)'\n");

    fprintf(fp, "pause -1 'Press Enter to close graph'\n");

    fclose(fp);

  
    system("gnuplot plot.gp");

    return 0;
}