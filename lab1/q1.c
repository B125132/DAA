#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *gp;

    // to Open Gnuplot
    gp = popen("gnuplot -persistent", "w");

    if (gp == NULL)
    {
        printf("Error: Gnuplot could not be opened.\n");
        return 1;
    }

   
    fprintf(gp, "set title 'Growth of Functions'\n");
    fprintf(gp, "set xlabel 'n'\n");
    fprintf(gp, "set ylabel 'Function Value'\n");
    fprintf(gp, "set grid\n");

   
    fprintf(gp, "set logscale y\n");

    // Plot all functions directly
    fprintf(gp,
        "plot [1:50] "
        "x*log(x)/log(2) title 'n log2(n)' with lines, "
        "12*sqrt(x) title '12 sqrt(n)' with lines, "
        "1/x title '1/n' with lines, "
        "x**(log(x)/log(2)) title 'n^(log2 n)' with lines, "
        "100*x*x+6*x title '100n^2+6n' with lines, "
        "x title 'n^(n/n)' with lines, "
        "x*x-324 title 'n^2-324' with lines, "
        "50*sqrt(x) title '50 sqrt(n)' with lines, "
        "2*x*x*x title '2n^3' with lines, "
        "3**x title '3^n' with lines, "
        "2**32 title '2^32 n/n' with lines, "
        "log(x)/log(2) title 'log2(n)' with lines\n"
    );

    fflush(gp);

    pclose(gp);

    return 0;
}