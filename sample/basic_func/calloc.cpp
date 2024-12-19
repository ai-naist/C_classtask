#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// メモリ開放したあとNULLクリアするマクロ
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

// ポインタと型を指定してメモリの確保と初期化を行うマクロ
#define array_func(ptr, type, N)                                                \
    {                                                                           \
        ptr = (type *)calloc(N, sizeof(type));                                  \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s 型の配列 %s のメモリを確保できません。\n", #type, #ptr); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    }

int main(void)
{
    int S = 3;
    bool *sv;
    array_func(sv, bool, S + 1);
    for (int i = 1; i <= S; i++)
    {
        if (!sv[i])
            printf("%d\n", sv[i]);
    }
    free_null(sv);

    return 0;
}
