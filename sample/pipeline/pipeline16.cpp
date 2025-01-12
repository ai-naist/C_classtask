#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GetArray(ptr, type, N)                                                  \
    {                                                                           \
        ptr = (type *)calloc((N), sizeof(type));                                \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s 型の配列 %s のメモリを確保できません。\n", #type, #ptr); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    }
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

int main(void)
{
    const int n = 100;
    const unsigned int N = pow(10, 8);
    double *a;
    GetArray(a, double, N);
    for (int i = 0; i < N; i++)
        a[i] = 0.1;

    double c = 0, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15;

    clock_t begin = clock();
    for (int j = 0; j < n; j++)
    {
        d0 = d1 = d2 = d3 = d4 = d5 = d6 = d7 = d8 = d9 = d10 = d11 = d12 = d13 = d14 = d15 = 0.0;
        for (int i = 0; i < N; i += 16)
        {
            d0 += a[i + 0];
            d1 += a[i + 1];
            d2 += a[i + 2];
            d3 += a[i + 3];
            d4 += a[i + 4];
            d5 += a[i + 5];
            d6 += a[i + 6];
            d7 += a[i + 7];
            d8 += a[i + 8];
            d9 += a[i + 9];
            d10 += a[i + 10];
            d11 += a[i + 11];
            d12 += a[i + 12];
            d13 += a[i + 13];
            d14 += a[i + 14];
            d15 += a[i + 15];
        }
        c += d0 + d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8 + d9 + d10 + d11 + d12 + d13 + d14 + d15;
    }
    clock_t end = clock();

    printf("sum:%g\ntime:%g\n", c, ((double)end - (double)begin) / CLOCKS_PER_SEC);
    free_null(a);
    return 0;
}