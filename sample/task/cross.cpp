// �ŋߗז@�Ō�������o�H���������A���S���Y��

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

// 2�s�s�ԋ������Z�o����}�N��
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// �������J����������NULL�N���A����}�N��
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

// x���W��y���W���\���̂Œ�`
typedef struct
{
    int num;  // �s�s�ԍ�
    double x; // x���W
    double y; // y���W
} CityInfo_t;

int main(void)
{

    double a = 0.1;
    double b = 10000.0;
    int N = 20;

    srand(123);

    CityInfo_t *pointdata;
    pointdata = (CityInfo_t *)calloc(N + 1, sizeof(CityInfo_t));

    for (int n = 1; n <= N; n++)
    {
        //�@���W(x,y)��[a,b]�ł̗����ɒu�������Ď擾
        pointdata[n].x = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        pointdata[n].y = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        pointdata[n].num = n;
    }

    int *z;                                // �z��̐擪�v�f�ւ̃|�C���^
    z = (int *)calloc(N + 1, sizeof(int)); // �������̊m��(�A�h���X�̊��蓖��)
    if (z == NULL)
        exit(EXIT_FAILURE);

    int *zz;                                // �z��̐擪�v�f�ւ̃|�C���^
    zz = (int *)calloc(N + 1, sizeof(int)); // �������̊m��(�A�h���X�̊��蓖��)
    if (zz == NULL)
        exit(EXIT_FAILURE);

    int i; // ���݂̓s�s�ԍ�
    int start = 1;
    i = start;                  // �o���s�s�ԍ� start �ŏ�����
    double dij;                 // 2�s�s�ԋ���
    double totaldistance = 0.0; // ���ړ�����

    int k = 1; // �K�⏇��
    z[i] = k;  // �s�s�ɑΉ����鏇��
    zz[k] = i; // �����ɑΉ�����s�s
    int next = 0;

    for (k = 2; k <= N; k++) // �T�������ł��߂��s�s�����̖K��s�s�ɍX�V
    {
        double min = DBL_MAX; // �ŒZ�ړ������̃�����{���x���������_���̍ő�l�ŏ�����

        for (int j = 1; j <= N; j++) // ���ݓs�s����ł��߂��s�s��T��
        {
            if (z[j] == 0)
            {
                // 2�s�s�ԋ���
                dij = distance_func(pointdata[i].x, pointdata[j].x, pointdata[i].y, pointdata[j].y);

                if (dij < min)
                {
                    min = dij;
                    next = j; // �s�s�ԍ��̃���
                }
            }
        }

        z[next] = k;  // ���̖K��s�s�̌���
        zz[k] = next; // �����ɑΉ�����s�s

        totaldistance += min;

        // �r�����ʂ̏o��
        printf("%d\t%d\t%d\t%lf\t%lf\n", k, i, next, min, totaldistance);

        i = next; // ���ݓs�s�̍X�V
    }

    return 0;
}