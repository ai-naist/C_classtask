// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam/task.cpp

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int num;  // �s�s�ԍ�
    double x; // x���W
    double y; // y���W
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