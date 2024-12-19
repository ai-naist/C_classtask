// task8_bonus2 ���v���b�g����

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

/**************
�v���g�^�C�v�錾
***************/
void create_data(const int, const double, const double, const int, CityInfo_t *const);
inline void nearest_TSP(FILE **, const int, const int, const CityInfo_t *const, int *const, int *const, double *const);
inline void add_opt2_dis(const int, const int, double *, double *, const CityInfo_t *, const int *);
inline void opt2_TSP(bool *, const int, double *, const CityInfo_t *, int *, int *);
void plot_set(const int, FILE **, const double, const double, const int, const CityInfo_t *const, int *);
inline void plot_point(const int, FILE **, const int, const CityInfo_t *const);
inline void plot_line(const int, const int, FILE **, const CityInfo_t *const, int *);
void plot_end(FILE **);

int main(void)
{
    const int N = 100;
    const int start = 4;
    const int seed = 65535;
    const double a = 0.1, b = 10000;

    CityInfo_t *cityinfodata;
    array_func(cityinfodata, CityInfo_t, N);

    // �^�C�g���̏o��
    printf("\n�s�s�ԍ�\tx���W\t\ty���W\n");
    create_data(seed, a, b, N, cityinfodata);

    int *z;
    int *zz;
    array_func(z, int, N);
    array_func(zz, int, N + 1);
    double totaldistance = 0.0; // ���ړ�����

    FILE *gp;
    if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL)
        exit(EXIT_FAILURE);

    // ���W���v���b�g����
    plot_set(start, &gp, a, b, N, cityinfodata, zz);

    // �T�����Ԍv���̊J�n
    clock_t begin = clock();

    nearest_TSP(&gp, N, start, cityinfodata, z, zz, &totaldistance);

    // �s�s�ԍ�����
    printf("\n�s�s�ԍ�\t�K�⏇��\n");
    for (int l = 1; l <= N; l++)
        printf("%d\t\t%d\n", l, z[l]);

    // �K�⏇������
    printf("\n�K�⏇��\t�s�s�ԍ�\n");
    for (int l = 1; l <= N; l++)
        printf("%d\t\t%d\n", l, zz[l]);

    Sleep(2000);
    plot_set(start, &gp, a, b, N, cityinfodata, zz);

    // 2opt method
    int *zz_old;
    int *zz_new;
    array_func(zz_old, int, N + 1);
    array_func(zz_new, int, N + 1);

    // �K�⏇���ŋߗז@�̌��ʂŏ�����
    for (int k = 1; k <= N + 1; k++)
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

    for (int k = 2; k <= N + 1; k++)
    {
        //plot_point(start, &gp, N, cityinfodata);
        plot_line(start, k, &gp, cityinfodata, zz_new);
    }

    // �n�_�\���Ƌ����̔�r
    printf("\n\nstart = %d\ttdis = %lf\ttdis_new = %lf\n", start, totaldistance, tdis_new);

    //�@���P�x
    double imp_rate = ((totaldistance - tdis_new) / totaldistance) * 100;
    printf("\n���P�x = %lf�i���j", imp_rate);

    // 2opt�@�ł̑��ړ������̏o��
    printf("\n2opt �@�K�p ���ړ������i���P��j\t%lf\n", tdis_new);

    // �T�����Ԍv���̏I���
    clock_t end = clock();
    double serching_time = ((double)end - (double)begin) / CLOCKS_PER_SEC; // �����o�ߎ���
    // �����o�ߎ��Ԃ̏o��
    printf("\n�T����������\t%lf �b\n", serching_time);

    plot_end(&gp);

    // ���������
    free_null(cityinfodata);
    free_null(z);
    free_null(zz);
    free_null(zz_old);
    free_null(zz_new);

    return 0;
}

void create_data(const int seed, const double a, const double b, const int N, CityInfo_t *const data)
{
    // srand((unsigned int)time(NULL)); // �V�[�h�ltime(NULL)�ŗ����n��̐���
    srand(seed); // ���쌟�ؗp

    for (int n = 1; n <= N; n++)
    {
        data[n].num = n;
        data[n].x = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        data[n].y = a + (b - a) * ((double)rand() / (double)RAND_MAX);

        printf("%d\t\t%lf\t%lf\n", data[n].num, data[n].x, data[n].y);
    }
}

// �ŋߗז@�Ōo�H�T���@�T���o�߂̏o�́@�T�����Ԃ̌v��
inline void nearest_TSP(FILE **gpp, const int N, const int start, const CityInfo_t *const data, int *const z, int *const zz, double *const ptdis)
{
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
    for (k = 2; k <= N + 1; k++) // �T�������ł��߂��s�s�����̖K��s�s�ɍX�V
    {
        double min = DBL_MAX; // �ŒZ�ړ������̃�����{���x���������_���̍ő�l�ŏ�����
        if (k <= N)
        {
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

            z[next] = k; // ���̖K��s�s�̌���
        }
        else
        {
            min = distance_func(data[i].x, data[start].x, data[i].y, data[start].y);
            next = start;
        }
        zz[k] = next; // �����ɑΉ�����s�s
        *ptdis += min;

        // �r�����ʂ̏o��
        printf("%d\t%d\t%d\t%lf\t%lf\n", k, i, next, min, *ptdis);

        //plot_point(start, gpp, N, data);
        plot_line(start, k, gpp, data, zz);

        i = next; // ���ݓs�s�̍X�V
    }
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
inline void opt2_TSP(bool *pcheck, const int N, double *ptdis_new, const CityInfo_t *data, int *zz_old, int *zz_new)
{
    for (int i = 1; i <= N - 2; i++)
    {
        for (int j = i + 2; j <= N; j++)
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

void plot_set(const int start, FILE **gpp, const double a, const double b, const int N, const CityInfo_t *const data, int *zz)
{

    fprintf(*gpp, "set multiplot\n"); // �}���`�v���b�g���[�h

    // �͈͂̎w��
    fprintf(*gpp, "set xrange [%lf:%lf]\n", a, b);
    fprintf(*gpp, "set yrange [%lf:%lf]\n", a, b);
    fprintf(*gpp, "unset key\n");  // �}����\��
    fprintf(*gpp, "set notics\n"); // �ڐ�����\��

    // �n�_�̃v���b�g
    FILE *fp_p;
    if (fopen_s(&fp_p, "point0.dat", "w") != 0)
        exit(EXIT_FAILURE);
    fprintf(fp_p, "%lf %lf\n", data[start].x, data[start].y);
    fprintf(*gpp, "plot 'point0.dat' with points pointtype 7 pointsize 1.5 linetype rgbcolor 'red'\n");
    fclose(fp_p);
    fflush(*gpp);
    Sleep(2000);

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

inline void plot_point(const int start, FILE **gpp, const int N, const CityInfo_t *const data)
{
    // �_�̃v���b�g
    FILE *fp_p;
    if (fopen_s(&fp_p, "point0.dat", "w") != 0)
        exit(EXIT_FAILURE);
    fprintf(fp_p, "%lf %lf\n", data[start].x, data[start].y);
    fprintf(*gpp, "plot 'point0.dat' with points pointtype 7 pointsize 1.5 linetype rgbcolor 'red'\n");
    fclose(fp_p);
    fflush(*gpp);

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

inline void plot_line(const int start, const int k, FILE **gpp, const CityInfo_t *const data, int *zz)
{
    FILE *fp_l;
    if (fopen_s(&fp_l, "linesim.dat", "w") != 0)
        exit(EXIT_FAILURE);

    fprintf(fp_l, "%lf %lf\n", data[zz[k - 1]].x, data[zz[k - 1]].y);
    fprintf(fp_l, "%lf %lf\n", data[zz[k]].x, data[zz[k]].y);

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