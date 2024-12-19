// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam/task.cpp

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int num;  // 都市番号
    double x; // x座標
    double y; // y座標
} CityInfo_t;

int main(void)
{
    int N;
    scanf_s("%d", &N);
    CityInfo_t *ptr;
    ptr = (CityInfo_t *)calloc(N + 1, sizeof(CityInfo_t));
    /*
    for (int i = 0; i <= N; i++)
    {
        ptr[i] = 0;
    }
*/
    for (int k = 0; k <= N; k++)
        printf("%d\t%d\t%lf\t%lf\n", k, ptr[k].num, ptr[k].x, ptr[k].y);

    free(ptr);

    return 0;
}