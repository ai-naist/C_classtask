// wÐÔ 1201201010
// |[^ID : seb01010
// ¼  äã¾_
// vO¼ : Inoue_Akihiro_exam7-1.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // lZè
#include <math.h>

// ss
const int N = 2;

// 2ssÔ£ÌZo
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

FILE *fp; // t@C|C^

// xÀWÆyÀWð\¢ÌÅè`
typedef struct
{
    double x; // xÀW
    double y; // yÀW
} point_t;

int main(void)
{
    // fpð«Ý[hÅI[vµt@Cðú»
    fopen_s(&fp, "Inoue_Akihiro_exam7-1.csv", "w");
    if (fp == NULL) // G[
        exit(EXIT_FAILURE);

    point_t city[N + 1] = {{0.0, 0.0}, {90.06, 14.19}, {18.80, 30.24}}; // oÌú»

    int i, j;   // ssÔÌ
    double dij; // 2ssÔ£

    // ssÔÌãü
    i = 1;
    j = 2;

    // 2ssÔ£ðZo
    if (i != j)
        dij = distance_func(city[i].x, city[j].x, city[i].y, city[j].y);

    // ^CgÌoÍ
    printf("ssÔ\txÀW\tyÀW\n");    // cmd
    fprintf(fp, "ssÔ,xÀW,yÀW\n"); // csv

    for (int k = 1; k <= N; k++)
    {
        // oðoÍ
        printf("%d\t\t%.2lf\t%.2lf\n", k, city[k].x, city[k].y);
        fprintf(fp, "%d,%.2lf,%.2lf\n", k, city[k].x, city[k].y);
    }
    // ÊoÍ:Kâµ½2ssÌssÔÆ2ssÔ£
    printf("\no­ssÔ i\tÌKâss j\t2ssÔ£ dij\n"
           "\t%d\t\t%d\t\t%.2lf\n",
           i, j, dij); // cmd
    fprintf(fp, "\no­ssÔ i,ÌKâss j,2ssÔ£ dij\n"
                "%d,%d,%.2lf\n",
            i, j, dij); // csv

    fclose(fp); // t@CN[Y
    return 0;
}