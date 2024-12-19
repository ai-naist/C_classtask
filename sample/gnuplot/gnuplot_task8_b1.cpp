// task8_bonus1 ���v���b�g����

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <windows.h>

#define GNUPLOT_PATH "C:/PROGRA~1/gnuplot/bin/gnuplot.exe" // gnuplot �̃t���p�X

// 2�s�s�ԋ������Z�o����}�N��
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// �|�C���^�ƌ^���w�肵�ă������̊m�ۂƏ��������s���}�N��
#define array_func(ptr, type, N)                                                \
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

// x���W��y���W���\���̂Œ�`
typedef struct
{
    int num;  // �s�s�ԍ�
    double x; // x���W
    double y; // y���W
} CityInfo_t;

// �v���g�^�C�v�錾
void create_data(const double, const double, const int, CityInfo_t *const);
void nearest_TSP(FILE **, const int, const int, const CityInfo_t *const, int *const, int *const, double *const, double *const);
void plot_set(const int, FILE **, const double, const double, const int, const CityInfo_t *const, int *);
inline void plot_line(const int, const int, FILE **, const int N, const CityInfo_t *const data, int *zz);
void plot_end(FILE **);

int main(void)
{
    int N = 100;
    double a = 0.1, b = 10000;

    CityInfo_t *cityinfodata;                // �\���̌^�z��̐擪�v�f�ւ̃|�C���^
    array_func(cityinfodata, CityInfo_t, N); // �������̊m�ۂƏ�����

    // �^�C�g���̏o��
    printf("\n�s�s�ԍ�\tx���W\t\ty���W\n");
    create_data(a, b, N, cityinfodata);

    int *z;                // �z��̐擪�v�f�ւ̃|�C���^
    array_func(z, int, N); // �������̊m�ۂƏ�����

    int *zz;                // �z��̐擪�v�f�ւ̃|�C���^
    array_func(zz, int, N); // �������̊m�ۂƏ�����

    // �o���s�s�����
    int start = 4;

    double totaldistance = 0.0; // ���ړ�����
    double serching_time = 0.0; // �����o�ߎ���

    FILE *gp;
    if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL)
        exit(EXIT_FAILURE);

    // ���W���v���b�g����
    plot_set(start, &gp, a, b, N, cityinfodata, zz);

    nearest_TSP(&gp, N, start, cityinfodata, z, zz, &totaldistance, &serching_time);

    // �s�s�ԍ�����
    printf("\n�s�s�ԍ�\t�K�⏇��\n");
    for (int l = 1; l <= N; l++)
        printf("%d\t\t%d\n", l, z[l]);

    // �K�⏇������
    printf("\n�K�⏇��\t�s�s�ԍ�\n");
    for (int l = 1; l <= N; l++)
        printf("%d\t\t%d\n", l, zz[l]);

    // ���ړ������̏o��
    printf("\n���ړ�����\t%lf\n", totaldistance);

    // �����o�ߎ��Ԃ̏o��
    printf("\n�T����������\t%lf �b\n", serching_time);

    plot_end(&gp);

    // ���������
    free_null(cityinfodata);
    free_null(z);
    free_null(zz);

    return 0;
}

void create_data(const double a, const double b, const int N, CityInfo_t *const data)
{
    // srand((unsigned int)time(NULL)); // �V�[�h�ltime(NULL)�ŗ����n��̐���
    srand(123); // ���쌟�ؗp

    for (int n = 1; n <= N; n++)
    {
        data[n].num = n;
        data[n].x = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        data[n].y = a + (b - a) * ((double)rand() / (double)RAND_MAX);

        printf("%d\t\t%lf\t%lf\n", data[n].num, data[n].x, data[n].y);
    }
}

// �ŋߗז@�Ōo�H�T���@�T���o�߂̏o�́@�T�����Ԃ̌v��
void nearest_TSP(FILE **gpp, const int N, const int start, const CityInfo_t *const data, int *const z, int *const zz, double *const ptdis, double *const ptime)
{

    // �T�����Ԍv���̊J�n
    clock_t begin = clock();

    int i;            // ���݂̓s�s�ԍ�
    int next = 0;     // ���ɖK�₷��s�s�ԍ�
    int k = 1;        // �K�⏇�� 1�ŏ�����
    double dij = 0.0; // 2�s�s�ԋ���

    i = start; // �o���s�s�ԍ� start �ŏ�����
    z[i] = k;  // �s�s�ɑΉ����鏇���̏�����
    zz[k] = i; // �����ɑΉ�����s�s�̏�����

    // ���ʃ^�C�g���̏o��
    printf("\nk\ti\tnext\tmin\t\ttdis\n");

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

        plot_line(start, k, gpp, N, data, zz);

        i = next; // ���ݓs�s�̍X�V
    }

    // �ŏI���B�s�s����o���s�s�֖߂鋗���̌v�Z
    dij = distance_func(data[i].x, data[start].x, data[i].y, data[start].y);
    *ptdis += dij;

    // �r�����ʂ̏o��
    printf("\t%d\t%d\t%lf\t%lf\n", i, start, dij, *ptdis);

    // �T�����Ԍv���̏I���
    clock_t end = clock();
    *ptime = ((double)end - (double)begin) / CLOCKS_PER_SEC;
}

void plot_set(const int start, FILE **gpp, const double a, const double b, const int N, const CityInfo_t *const data, int *zz)
{

    fprintf(*gpp, "set multiplot\n"); // �}���`�v���b�g���[�h

    // �͈͂̎w��
    fprintf(*gpp, "set xrange [%lf:%lf]\n", a, b);
    fprintf(*gpp, "set yrange [%lf:%lf]\n", a, b);
    fprintf(*gpp, "unset key\n");  // �}����\��
    fprintf(*gpp, "set notics\n"); // �ڐ�����\��

    // �_�̃v���b�g
    FILE *fp_p;
    if (fopen_s(&fp_p, "point0.dat", "w") != 0)
        exit(EXIT_FAILURE);
    fprintf(fp_p, "%lf %lf\n", data[start].x, data[start].y);
    fprintf(*gpp, "plot 'point0.dat' with points pointtype 7 pointsize 1.5 linetype rgbcolor 'red'\n");
    fclose(fp_p);
    fflush(*gpp);
    Sleep(1500);

    if (fopen_s(&fp_p, "point.dat", "w") != 0)
        exit(EXIT_FAILURE);
    for (int m = 1; m <= N; m++)
    {
        fprintf(fp_p, "%lf %lf\n", data[m].x, data[m].y);
    }
    fprintf(*gpp, "plot 'point.dat' with points pointtype 6 pointsize 1.5 linetype rgbcolor 'black'\n");
    fclose(fp_p);
    fflush(*gpp);
}

inline void plot_line(const int start, const int k, FILE **gpp, const int N, const CityInfo_t *const data, int *zz)
{
    FILE *fp_l;
    if (fopen_s(&fp_l, "linesim.dat", "w") != 0)
        exit(EXIT_FAILURE);

    fprintf(fp_l, "%lf %lf\n", data[zz[k - 1]].x, data[zz[k - 1]].y);
    fprintf(fp_l, "%lf %lf\n", data[zz[k]].x, data[zz[k]].y);

    //�J�n�_�ւ̐ܕԂ�
    if (k == N)
        fprintf(fp_l, "%lf %lf\n", data[zz[1]].x, data[zz[1]].y);

    // �����̃v���b�g
    fprintf(*gpp, "plot 'linesim.dat' with lines linetype rgbcolor 'web-green' linewidth 2\n");
    fclose(fp_l);
    fflush(*gpp);
    Sleep(30 + k / 10);
}

void plot_end(FILE **gpp)
{
    system("pause");
    fprintf(*gpp, "set nomultiplot\n");
    fprintf(*gpp, "exit\n"); // gnuplot�̏I��
    fflush(*gpp);            // �o�b�t�@�Ɋi�[����Ă���f�[�^��f���o��
    _pclose(*gpp);
}