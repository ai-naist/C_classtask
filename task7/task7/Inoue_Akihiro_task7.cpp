// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task7.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>

// �f�[�^�ǂݍ��ݗp�z��̍ő吔
const int N_Max = 100;

// �v���g�^�C�v�錾
inline double distance_func(double, double, double, double);

FILE *fp_r, *fp_w; // �t�@�C���|�C���^

// x���W��y���W���\���̂Œ�`
typedef struct
{
    double x; // x���W
    double y; // y���W
} point_t;

int main(void)
{
    point_t city[N_Max + 1] = {0.0}; // �\���̂̏�����

    // fp_r��ǂݎ�胂�[�h�ŃI�[�v��
    fopen_s(&fp_r, "task7_citydata.csv", "r");
    if (fp_r == NULL) // �G���[����
        exit(EXIT_FAILURE);

    // �����o�̓ǂݍ���
    int k = 1;
    while ((fscanf_s(fp_r, "%lf,%lf", &city[k].x, &city[k].y)) != EOF)
    {
        k++;
    }

    int N = k - 1; // �K��s�s��
    fclose(fp_r);  // �t�@�C���N���[�Y

    // fp_w���������݃��[�h�ŃI�[�v��
    fopen_s(&fp_w, "Inoue_Akihiro_task7.csv", "w");
    if (fp_w == NULL) // �G���[����
        exit(EXIT_FAILURE);

    // �^�C�g���̏o��
    printf("�K�₷��s�s�� %d �s�s����܂��B\n\n"
           "�K�₷�� %d �s�s�̓s�s�ԍ� 1 �` %d �̈ʒu���W�͎��̒ʂ�ł��B\n\n"
           "�s�s�ԍ�\tx���W\t\ty���W\n",
           N, N, N); // cmd
    fprintf(fp_w, "�K�₷��s�s�� %d �s�s����܂��B\n\n"
                  "�K�₷�� %d �s�s�̓s�s�ԍ� 1 �` %d �̈ʒu���W�͎��̒ʂ�ł��B\n\n"
                  "�s�s�ԍ�,x���W,y���W\n",
            N, N, N); // csv

    // �s�s�ԍ��ƑΉ����郁���o���o��
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%lf\t%lf\n", k, city[k].x, city[k].y);
        fprintf(fp_w, "%d,%lf,%lf\n", k, city[k].x, city[k].y);
    }

    int i;      // �s�s�ԍ��̃���
    double dij; // 2�s�s�ԋ���

    // �o���s�s�ԍ������
    printf("\n�ŏ��ɏo������s�s i �� 1 �` %d �̒�����I�����ĉ������Bstart -> ", N);
    scanf_s("%d", &i);

    // ���ʃ^�C�g���̏o��
    printf("\n�ŏ��ɏo������s�s i ��s�s�ԍ� %d �ɂ����ꍇ�̌��ʂ������܂��B\n"
           "\n�o���s�s i\t�K��s�s j\t2�s�s�ԋ��� dij\n",
           i); // cmd
    fprintf(fp_w, "\n�ŏ��ɏo������s�s i ��s�s�ԍ� %d �ɂ����ꍇ�̌��ʂ������܂��B\n"
                  "\n�o���s�s i,�K��s�s j,2�s�s�ԋ��� dij\n",
            i); // csv

    for (int j = 1; j <= N; j++)
    {
        // 2�s�s�ԋ������Z�o
        if (i != j)
        {
            dij = distance_func(city[i].x, city[j].x, city[i].y, city[j].y);

            // ���ʏo��(�K�₵��2�s�s�̓s�s�ԍ���2�s�s�ԋ���)
            printf(
                "\t%d\t\t%d\t\t%.2f\n",
                i, j, dij); // cmd
            fprintf(fp_w, "%d,%d,%.2f\n",
                    i, j, dij); // csv
        }
    }

    fclose(fp_w); // �t�@�C���N���[�Y
    return 0;
}

// 2�s�s�ԋ������Z�o����֐�
inline double distance_func(double xi, double xj, double yi, double yj)
{
    return sqrt(pow(xi - xj, 2) + pow(yi - yj, 2));
}