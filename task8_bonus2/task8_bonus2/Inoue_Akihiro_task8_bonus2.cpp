// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task8_bonus2.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

// 2�s�s�ԋ������Z�o����}�N��
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// �|�C���^�ƌ^���w�肵�ă������̊m�ۂƏ��������s���}�N��
#define get_array(ptr, type, N)                                                 \
    {                                                                           \
        ptr = (type *)calloc((N) + 1, sizeof(type));                            \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s �^�̔z�� %s �̃��������m�ۂł��܂���B\n", #type, #ptr); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    }

// �������J����������NULL�N���A����}�N��
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

FILE *fp3; // ���ʏo�͗p

// x���W��y���W���\���̂Œ�`
typedef struct
{
    int num;  // �s�s�ԍ�
    double x; // x���W
    double y; // y���W
} CityInfo_t;

/**************
�v���g�^�C�v�錾
***************/
void generate_data(const double, const double, const int);
void read_data(CityInfo_t *);
inline void nearest_TSP(const int, const int, const CityInfo_t *, int *, int *, double *);
inline void add_opt2_dis(const int, const int, double *, double *, const CityInfo_t *, const int *);
void opt2_TSP(bool *, const int, double *, const CityInfo_t *, int *, int *);
/*
�^��[] �́A�z��ł��邱�Ƃ𖾎��I�ɂ��邪�A�����I�ɂ� �^��* �Ɠ��`�ŁA�z��̐擪�v�f�ւ̃|�C���^�ł���
const �^��* �̓|�C���^������Q�Ɛ���A�^�� *const �̓|�C���^�ϐ����A���ꂼ�ꏑ�������֎~�ɂ���    
�������A�O�҂̓|�C���^�o�R�łȂ���΁A�|�C���^�̎w���l�����������\�ł���
*/

int main(void)
{
    /*  ��1
    �s�s�̍��W�͈�[a,b]���w��
    ���͈̔͂�N�̍��W�𗐐��Ŏ擾
    �擾�������W�� citydata_info.csv �ɏo��
    */
    double a, b;
    int N;
    // a,b,N �̓���
    printf("�K��s�s�̈ʒu���W x ���W�� y ���W�͈̔�( ���� a , ��� b )�̐ݒ�ɂ���\n"
           "�͈� �̉��� a ���w�肵�ĉ������B --- > ");
    scanf_s("%lf", &a);
    printf("�͈� �̏�� b ���w�肵�ĉ������B --- > ");
    scanf_s("%lf", &b);
    do
    {
        printf("�K��s�s�� N ���w�肵�ĉ�����. �B--- > ");
        scanf_s("%d", &N);
    } while ((N <= 0) || (N > INT_MAX)); // �s���Ȓl�̉��

    // �͈�[a,b]�ŗ�����������N�̓s�s���W�� citydata_info.csv �ɏo��
    generate_data(a, b, N);
    // ��1   -----�����-----

    /*  ��2
    �\���̔z��� citydata_info.csv ����ǂݍ��񂾒l�ŏ�������
    �����o�̒l�� Inoue_Akihiro_task8_bonus1.csv �ɏo��
    */
    CityInfo_t *cityinfodata;               // �\���̌^�z��̐擪�v�f�ւ̃|�C���^
    get_array(cityinfodata, CityInfo_t, N); // �������̊m�ۂƏ�����

    // fp3���������݃��[�h�ŃI�[�v��
    if (fopen_s(&fp3, "Inoue_Akihiro_task8_bonus2.csv", "w") != 0)
        exit(EXIT_FAILURE); // �G���[����

    // �^�C�g���̏o��
    printf("\n�s�s�ԍ�\tx���W\t\ty���W\n");
    fprintf(fp3, "�s�s�ԍ�,x���W,y���W\n");

    read_data(cityinfodata);
    fclose(fp3); // �t�@�C���N���[�Y
    // ��2   -----�����-----

    /*  ��3 
    �s�s�ԍ��ƖK�⏇���ԍ�����������z����`
    */
    // �z�� z[�s�s�ԍ�] = ���̓s�s�̖K�⏇���ԍ�(�S�̂ŉ��ԖڂɖK�₷��s�s��)�@�����l0�͂��̓s�s�����K���\��
    int *z;               // �z��̐擪�v�f�ւ̃|�C���^
    get_array(z, int, N); // �������̊m�ۂƏ�����

    // �z�� zz[�K�⏇���ԍ�] = �s�s�ԍ��@�����l0�͂��̏����ԍ��ŖK�₷��s�s�������\��
    int *zz;               // �z��̐擪�v�f�ւ̃|�C���^
    get_array(zz, int, N); // �������̊m�ۂƏ�����
    // ��3   -----�����-----

    /*  ��4 
    �o���s�s����͂Ŏ擾�@
    �ŋߗז@�Ōo�H�T���@
    �T���o�߂̏o�́@
    �T�����Ԃ̌v��
    */
    // �o���s�s�����
    int start;
    do
    {
        printf("\n�ŏ��̏o���s�s start ��s�s�ԍ� 1 �` %d ���w�肵�ĉ������B---> ", N);
        scanf_s("%d", &start);
    } while ((start <= 0) || (start > N)); // �s���Ȓl�̉��

    double totaldistance = 0.0; // ���ړ�����

    // �T�����Ԍv���̊J�n
    clock_t begin = clock();

    nearest_TSP(N, start, cityinfodata, z, zz, &totaldistance);
    // ��4   -----�����-----

    /*  ��5
    �ŋߗז@�ɂ��T�����ʁA�s�s�ԍ��A�K�⏇���̏o��
    */
    // fp3��ǉ��������݃��[�h�ŃI�[�v��
    if (fopen_s(&fp3, "Inoue_Akihiro_task8_bonus2.csv", "a") != 0)
        exit(EXIT_FAILURE); // �G���[����

    // �s�s�ԍ�����
    printf("\n�s�s�ԍ�\t�K�⏇��\n");
    fprintf(fp3, "\n�s�s�ԍ�,�K�⏇��\n");
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%d\n", k, z[k]);
        fprintf(fp3, "%d,%d\n", k, z[k]);
    }

    // �K�⏇������
    printf("\n�K�⏇��\t�s�s�ԍ�\n");
    fprintf(fp3, "\n�K�⏇��,�s�s�ԍ�\n");
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%d\n", k, zz[k]);
        fprintf(fp3, "%d,%d\n", k, zz[k]);
    }
    // ��5   -----�����-----

    /*  ��6
    2opt�@�̎��s
    */
    int *zz_old;
    int *zz_new;
    get_array(zz_old, int, N);
    get_array(zz_new, int, N);

    // �K�⏇���ŋߗז@�̌��ʂŏ�����
    for (int k = 1; k <= N; k++)
    {
        zz_old[k] = zz[k];
        zz_new[k] = zz[k];
    }

    double tdis_new = totaldistance;
    bool check;
    do
    {
        check = false;
        opt2_TSP(&check, N, &tdis_new, cityinfodata, zz_old, zz_new);
    } while (check); // ���P�̃`�F�b�N

    // �T�����Ԍv���̏I���
    clock_t end = clock();
    // ��6   -----�����-----

    /*  ��7
    2opt�@�̌��ʏo��
    */
    // ����o�H�̏o��
    printf("\n\n�ŋߗז@�ł̏���o�H\t\t2opt�@�ł̏���o�H\n"
           "*********************************************************\n"
           "�K�⏇��\t�s�s�ԍ�\t�K�⏇��\t�s�s�ԍ�\n"
           "*********************************************************\n");
    fprintf(fp3, "\n�ŋߗז@�ł̏���o�H,,2opt�@�ł̏���o�H\n"
                 "�K�⏇��,�s�s�ԍ�,�K�⏇��,�s�s�ԍ�\n");
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", k, zz[k], k, zz_new[k]);
        fprintf(fp3, "%d,%d,%d,%d\n", k, zz[k], k, zz_new[k]);
    }

    // �n�_�Ƌ����̔�r
    printf("\n\nstart = %d\ttdis = %lf\ttdis_new = %lf\n", start, totaldistance, tdis_new);
    fprintf(fp3, "\nstart = %d,tdis = %lf,tdis_new = %lf\n", start, totaldistance, tdis_new);

    //�@���P�x
    double imp_rate = ((totaldistance - tdis_new) / totaldistance) * 100;
    printf("\n���P�x = %lf�i���j", imp_rate);
    fprintf(fp3, "\n���P�x = %lf�i���j\n", imp_rate);

    // 2opt�@�ł̑��ړ������̏o��
    printf("\n2opt �@�K�p ���ړ������i���P��j\t%lf\n", tdis_new);
    fprintf(fp3, "\n2opt �@�K�p,���ړ������i���P��j,%lf\n", tdis_new);

    // �����o�ߎ���
    double serching_time = ((double)end - (double)begin) / CLOCKS_PER_SEC;
    // �����o�ߎ��Ԃ̏o��
    printf("\n�T����������\t%lf �b\n", serching_time);
    fprintf(fp3, "\n�T����������,%lf �b\n", serching_time);

    fclose(fp3); // �t�@�C���N���[�Y
    // ��7   -----�����-----

    // ���������
    free_null(cityinfodata);
    free_null(z);
    free_null(zz);
    free_null(zz_old);
    free_null(zz_new);

    return 0;
}

/**************
���[�U�[��`�֐�
***************/
// �͈�[a,b]�ŗ�����������N�̓s�s���W�� citydata_info.csv �ɏo��
void generate_data(const double a, const double b, const int N)
{
    FILE *fp1;
    // fp1���������݃��[�h�ŃI�[�v��
    if (fopen_s(&fp1, "citydata_info.csv", "w") != 0)
        exit(EXIT_FAILURE); // �G���[����

    //srand((unsigned int)time(NULL)); // �V�[�h�ltime(NULL)�ŗ����n��̐���
    srand(65535); // ���쌟�ؗp

    for (int n = 1; n <= N; n++)
    {
        //�@���W(x,y)��[a,b]�ł̗����ɒu�������Ď擾
        double x_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        double y_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);

        // citydata_info.csv �ɏo��
        fprintf(fp1, "%d,%lf,%lf\n", n, x_point, y_point);
    }
    fclose(fp1); // �t�@�C���N���[�Y
}

// citydata_info.csv ����\���̔z��ɓǂݍ��݁AInoue_Akihiro_task8_bonus2.csv �ɏ�������
void read_data(CityInfo_t *const data)
{
    FILE *fp2;
    // fp2��ǂݎ�胂�[�h�ŃI�[�v��
    if (fopen_s(&fp2, "citydata_info.csv", "r") != 0)
        exit(EXIT_FAILURE); // �G���[����

    // �����o�̒l(�s�s�ԍ��Ax���W�Ay���W)�� citydata_info.csv ����ǂݍ��݁A Inoue_Akihiro_task8_bonus2.csv �ɏ�������
    int n = 1;
    while ((fscanf_s(fp2, "%d,%lf,%lf", &data[n].num, &data[n].x, &data[n].y)) != EOF)
    {
        // �ǂݍ��񂾃����o���o��
        printf("%d\t\t%lf\t%lf\n", data[n].num, data[n].x, data[n].y);
        fprintf(fp3, "%d,%lf,%lf\n", data[n].num, data[n].x, data[n].y);
        n++;
    }
    fclose(fp2); // �t�@�C���N���[�Y
}

// �ŋߗז@�Ōo�H�T���@�T���o�߂̏o�́@�T�����Ԃ̌v��
inline void nearest_TSP(const int N, const int start, const CityInfo_t *const data, int *const z, int *const zz, double *const ptdis)
{
    // fp3��ǉ��������݃��[�h�ŃI�[�v��
    if (fopen_s(&fp3, "Inoue_Akihiro_task8_bonus2.csv", "a") != 0)
        exit(EXIT_FAILURE); // �G���[����

    int i;            // ���݂̓s�s�ԍ�
    int next = 0;     // ���ɖK�₷��s�s�ԍ�
    int k = 1;        // �K�⏇�� 1�ŏ�����
    double dij = 0.0; // 2�s�s�ԋ���

    i = start; // �o���s�s�ԍ� start �ŏ�����
    z[i] = k;  // �s�s�ɑΉ����鏇���̏�����
    zz[k] = i; // �����ɑΉ�����s�s�̏�����

    // ���ʃ^�C�g���̏o��
    printf("\nk\ti\tnext\tmin\t\ttdis\n");
    fprintf(fp3, "\nk,i,next,min,tdis\n");

    // �ŋߗז@�ɂ��ŒZ�ړ������̒T��
    for (k = 2; k <= N; k++) // �T�������ł��߂��s�s�����̖K��s�s�ɍX�V
    {
        double min = DBL_MAX; // �ŒZ�ړ������̃�����{���x���������_���̍ő�l�ŏ�����

        for (int j = 1; j <= N; j++) // ���ݓs�s����ł��߂��s�s��T��
        {
            if (z[j] == 0)
            {
                // 2�s�s�ԋ���
                dij = distance_func(data[i].x, data[j].x, data[i].y, data[j].y);

                if (dij < min)
                {
                    min = dij;
                    next = j; // �s�s�ԍ��̃���
                }
            }
        }

        z[next] = k;  // ���̖K��s�s�̌���
        zz[k] = next; // �����ɑΉ�����s�s

        *ptdis += min;

        // �r�����ʂ̏o��
        printf("%d\t%d\t%d\t%lf\t%lf\n", k, i, next, min, *ptdis);
        fprintf(fp3, "%d,%d,%d,%lf,%lf\n", k, i, next, min, *ptdis);

        i = next; // ���ݓs�s�̍X�V
    }

    // �ŏI���B�s�s����o���s�s�֖߂鋗���̌v�Z
    dij = distance_func(data[i].x, data[start].x, data[i].y, data[start].y);
    *ptdis += dij;

    // �r�����ʂ̏o��
    printf("\t%d\t%d\t%lf\t%lf\n", i, start, dij, *ptdis);
    fprintf(fp3, ",%d,%d,%lf,%lf\n", i, start, dij, *ptdis);

    fclose(fp3); // �t�@�C���N���[�Y
}

// 2opt�@�œ���ւ���s�s�ԋ����̘a���v�Z����
inline void add_opt2_dis(const int i, const int j, double *pdis_old, double *pdis_new, const CityInfo_t *data, const int *zz)
{
    double i_to_i1 = distance_func(data[zz[i]].x, data[zz[i + 1]].x, data[zz[i]].y, data[zz[i + 1]].y);
    double j_to_j1 = distance_func(data[zz[j]].x, data[zz[j + 1]].x, data[zz[j]].y, data[zz[j + 1]].y);
    *pdis_old = i_to_i1 + j_to_j1;

    double i_to_j = distance_func(data[zz[i]].x, data[zz[j]].x, data[zz[i]].y, data[zz[j]].y);
    double i1_to_j1 = distance_func(data[zz[i + 1]].x, data[zz[j + 1]].x, data[zz[i + 1]].y, data[zz[j + 1]].y);
    *pdis_new = i_to_j + i1_to_j1;
}

// 2opt�@�Ōo�H���œK������
void opt2_TSP(bool *pcheck, const int N, double *ptdis_new, const CityInfo_t *data, int *zz_old, int *zz_new)
{
    for (int i = 1; i <= N - 3; i++)
    {
        for (int j = i + 2; j <= N - 1; j++)
        {
            double dis_old;
            double dis_new;
            add_opt2_dis(i, j, &dis_old, &dis_new, data, zz_old);

            if (dis_new < dis_old)
            {
                for (int m = 0; m <= j - (i + 1); m++)
                    zz_new[i + 1 + m] = zz_old[j - m];

                *ptdis_new = *ptdis_new - dis_old + dis_new;

                for (int m = i + 1; m <= j; m++)
                    zz_old[m] = zz_new[m];

                *pcheck = true;
            }
        }
    }
}