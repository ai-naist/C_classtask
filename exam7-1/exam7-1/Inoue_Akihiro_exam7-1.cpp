// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam7-1.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>

// �s�s��
const int N = 2;

// 2�s�s�ԋ����̎Z�o
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

FILE *fp; // �t�@�C���|�C���^

// x���W��y���W���\���̂Œ�`
typedef struct
{
    double x; // x���W
    double y; // y���W
} point_t;

int main(void)
{
    // fp���������݃��[�h�ŃI�[�v�����t�@�C����������
    fopen_s(&fp, "Inoue_Akihiro_exam7-1.csv", "w");
    if (fp == NULL) // �G���[����
        exit(EXIT_FAILURE);

    point_t city[N + 1] = {{0.0, 0.0}, {90.06, 14.19}, {18.80, 30.24}}; // �����o�̏�����

    int i, j;   // �s�s�ԍ��̃���
    double dij; // 2�s�s�ԋ���

    // �s�s�ԍ��̑��
    i = 1;
    j = 2;

    // 2�s�s�ԋ������Z�o
    if (i != j)
        dij = distance_func(city[i].x, city[j].x, city[i].y, city[j].y);

    // �^�C�g���̏o��
    printf("�s�s�ԍ�\tx���W\ty���W\n");    // cmd
    fprintf(fp, "�s�s�ԍ�,x���W,y���W\n"); // csv

    for (int k = 1; k <= N; k++)
    {
        // �����o���o��
        printf("%d\t\t%.2lf\t%.2lf\n", k, city[k].x, city[k].y);
        fprintf(fp, "%d,%.2lf,%.2lf\n", k, city[k].x, city[k].y);
    }
    // ���ʏo��:�K�₵��2�s�s�̓s�s�ԍ���2�s�s�ԋ���
    printf("\n�o���s�s�ԍ� i\t���̖K��s�s j\t2�s�s�ԋ��� dij\n"
           "\t%d\t\t%d\t\t%.2lf\n",
           i, j, dij); // cmd
    fprintf(fp, "\n�o���s�s�ԍ� i,���̖K��s�s j,2�s�s�ԋ��� dij\n"
                "%d,%d,%.2lf\n",
            i, j, dij); // csv

    fclose(fp); // �t�@�C���N���[�Y
    return 0;
}