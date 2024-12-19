// task8_bonus2 をプロットする

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <windows.h>

#define GNUPLOT_PATH "C:/PROGRA~1/gnuplot/bin/gnuplot.exe" // gnuplot のフルパス

// 2都市間距離を算出するマクロ
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// ポインタと型を指定してメモリの確保と初期化を行うマクロ
#define array_func(ptr, type, N)                                                \
    {                                                                           \
        ptr = (type *)calloc((N) + 1, sizeof(type));                            \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s 型の配列 %s のメモリを確保できません。\n", #type, #ptr); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    }

// メモリ開放したあとNULLクリアするマクロ
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

// x座標とy座標を構造体で定義
typedef struct
{
    int num;  // 都市番号
    double x; // x座標
    double y; // y座標
} CityInfo_t;

/**************
プロトタイプ宣言
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

    // タイトルの出力
    printf("\n都市番号\tx座標\t\ty座標\n");
    create_data(seed, a, b, N, cityinfodata);

    int *z;
    int *zz;
    array_func(z, int, N);
    array_func(zz, int, N + 1);
    double totaldistance = 0.0; // 総移動距離

    FILE *gp;
    if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL)
        exit(EXIT_FAILURE);

    // 座標をプロットする
    plot_set(start, &gp, a, b, N, cityinfodata, zz);

    // 探索時間計測の開始
    clock_t begin = clock();

    nearest_TSP(&gp, N, start, cityinfodata, z, zz, &totaldistance);

    // 都市番号昇順
    printf("\n都市番号\t訪問順序\n");
    for (int l = 1; l <= N; l++)
        printf("%d\t\t%d\n", l, z[l]);

    // 訪問順序昇順
    printf("\n訪問順序\t都市番号\n");
    for (int l = 1; l <= N; l++)
        printf("%d\t\t%d\n", l, zz[l]);

    Sleep(2000);
    plot_set(start, &gp, a, b, N, cityinfodata, zz);

    // 2opt method
    int *zz_old;
    int *zz_new;
    array_func(zz_old, int, N + 1);
    array_func(zz_new, int, N + 1);

    // 訪問順を最近隣法の結果で初期化
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
    } while (check); // 改善のチェック

    for (int k = 2; k <= N + 1; k++)
    {
        //plot_point(start, &gp, N, cityinfodata);
        plot_line(start, k, &gp, cityinfodata, zz_new);
    }

    // 始点表示と距離の比較
    printf("\n\nstart = %d\ttdis = %lf\ttdis_new = %lf\n", start, totaldistance, tdis_new);

    //　改善度
    double imp_rate = ((totaldistance - tdis_new) / totaldistance) * 100;
    printf("\n改善度 = %lf（％）", imp_rate);

    // 2opt法での総移動距離の出力
    printf("\n2opt 法適用 総移動距離（改善後）\t%lf\n", tdis_new);

    // 探索時間計測の終わり
    clock_t end = clock();
    double serching_time = ((double)end - (double)begin) / CLOCKS_PER_SEC; // 処理経過時間
    // 処理経過時間の出力
    printf("\n探索処理時間\t%lf 秒\n", serching_time);

    plot_end(&gp);

    // メモリ解放
    free_null(cityinfodata);
    free_null(z);
    free_null(zz);
    free_null(zz_old);
    free_null(zz_new);

    return 0;
}

void create_data(const int seed, const double a, const double b, const int N, CityInfo_t *const data)
{
    // srand((unsigned int)time(NULL)); // シード値time(NULL)で乱数系列の生成
    srand(seed); // 動作検証用

    for (int n = 1; n <= N; n++)
    {
        data[n].num = n;
        data[n].x = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        data[n].y = a + (b - a) * ((double)rand() / (double)RAND_MAX);

        printf("%d\t\t%lf\t%lf\n", data[n].num, data[n].x, data[n].y);
    }
}

// 最近隣法で経路探索　探索経過の出力　探索時間の計測
inline void nearest_TSP(FILE **gpp, const int N, const int start, const CityInfo_t *const data, int *const z, int *const zz, double *const ptdis)
{
    int i;            // 現在の都市番号
    int next = 0;     // 次に訪問する都市番号
    int k = 1;        // 訪問順序 1で初期化
    double dij = 0.0; // 2都市間距離

    i = start; // 出発都市番号 start で初期化
    z[i] = k;  // 都市に対応する順序の初期化
    zz[k] = i; // 順序に対応する都市の初期化

    // 結果タイトルの出力
    printf("\nk\ti\tnext\tmin\t\ttdis\n");

    // 最近隣法による最短移動距離の探索
    for (k = 2; k <= N + 1; k++) // 探索した最も近い都市を次の訪問都市に更新
    {
        double min = DBL_MAX; // 最短移動距離のメモを倍精度浮動小数点数の最大値で初期化
        if (k <= N)
        {
            for (int j = 1; j <= N; j++) // 現在都市から最も近い都市を探索
            {
                if (z[j] == 0)
                {
                    // 2都市間距離
                    dij = distance_func(data[i].x, data[j].x, data[i].y, data[j].y);

                    if (dij < min)
                    {
                        min = dij;
                        next = j; // 都市番号のメモ
                    }
                }
            }

            z[next] = k; // 次の訪問都市の決定
        }
        else
        {
            min = distance_func(data[i].x, data[start].x, data[i].y, data[start].y);
            next = start;
        }
        zz[k] = next; // 順序に対応する都市
        *ptdis += min;

        // 途中結果の出力
        printf("%d\t%d\t%d\t%lf\t%lf\n", k, i, next, min, *ptdis);

        //plot_point(start, gpp, N, data);
        plot_line(start, k, gpp, data, zz);

        i = next; // 現在都市の更新
    }
}

// 2opt法で入れ替える都市間距離の和を計算する
inline void add_opt2_dis(const int i, const int j, double *pdis_old, double *pdis_new, const CityInfo_t *data, const int *zz)
{
    double i_to_i1 = distance_func(data[zz[i]].x, data[zz[i + 1]].x, data[zz[i]].y, data[zz[i + 1]].y);
    double j_to_j1 = distance_func(data[zz[j]].x, data[zz[j + 1]].x, data[zz[j]].y, data[zz[j + 1]].y);
    *pdis_old = i_to_i1 + j_to_j1;

    double i_to_j = distance_func(data[zz[i]].x, data[zz[j]].x, data[zz[i]].y, data[zz[j]].y);
    double i1_to_j1 = distance_func(data[zz[i + 1]].x, data[zz[j + 1]].x, data[zz[i + 1]].y, data[zz[j + 1]].y);
    *pdis_new = i_to_j + i1_to_j1;
}

// 2opt法で経路を最適化する
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

    fprintf(*gpp, "set multiplot\n"); // マルチプロットモード

    // 範囲の指定
    fprintf(*gpp, "set xrange [%lf:%lf]\n", a, b);
    fprintf(*gpp, "set yrange [%lf:%lf]\n", a, b);
    fprintf(*gpp, "unset key\n");  // 凡例を非表示
    fprintf(*gpp, "set notics\n"); // 目盛りを非表示

    // 始点のプロット
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
    // 点のプロット
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

    // 線分のプロット
    fprintf(*gpp, "plot 'linesim.dat' with lines linetype rgbcolor 'web-green' linewidth 2\n");
    fclose(fp_l);
    fflush(*gpp);
    Sleep(30 + k / 10);
}

void plot_end(FILE **gpp)
{
    system("pause");
    fprintf(*gpp, "set nomultiplot\n");
    fprintf(*gpp, "exit\n"); // gnuplotの終了
    fflush(*gpp);            // バッファに格納されているデータを吐き出す
    _pclose(*gpp);
}