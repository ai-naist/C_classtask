#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// �������J����������NULL�N���A����}�N��
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

// �|�C���^�ƌ^���w�肵�ă������̊m�ۂƏ��������s���}�N��
#define array_func(ptr, type, N)                                                \
    {                                                                           \
        ptr = (type *)calloc(N, sizeof(type));                                  \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s �^�̔z�� %s �̃��������m�ۂł��܂���B\n", #type, #ptr); \
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
