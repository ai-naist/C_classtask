#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdbool.h>

#define ExpRand(mu) (-1.0 / (mu)) * log((double)(rand() + 1) / (double)(RAND_MAX + 1))

FILE *fp;
int main(void)
{
    // fp オープン wモード
    if (fopen_s(&fp, "ExpRnd.csv", "w") != 0)
        exit(EXIT_FAILURE); // エラー処理

    srand(123);

    int S = 100;
    for (int i = 0; i < S; i++)
        fprintf(fp, "%lf\n", ExpRand(0.4));

    fclose(fp);
    return 0;
}