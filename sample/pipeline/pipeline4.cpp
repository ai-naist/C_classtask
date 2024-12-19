#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GetArray(ptr, type, N)                                                  \
    {                                                                           \
        ptr = (type *)calloc((N), sizeof(type));                                \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s å^ÇÃîzóÒ %s ÇÃÉÅÉÇÉäÇämï€Ç≈Ç´Ç‹ÇπÇÒÅB\n", #type, #ptr); \
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

    double c = 0, d0, d1, d2, d3;

    clock_t begin = clock();
    for (int j = 0; j < n; j++)
    {
        d0 = d1 = d2 = d3 = 0.0;
        for (int i = 0; i < N; i += 4)
        {
            d0 += a[i + 0];
            d1 += a[i + 1];
            d2 += a[i + 2];
            d3 += a[i + 3];
        }
        c += d0 + d1 + d2 + d3;
    }

    clock_t end = clock();

    printf("sum:%g\ntime:%g\n", c, ((double)end - (double)begin) / CLOCKS_PER_SEC);
    free_null(a);
    return 0;
}