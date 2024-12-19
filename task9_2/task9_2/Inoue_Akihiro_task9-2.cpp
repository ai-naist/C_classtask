// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task9-2.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdbool.h>

const double UOM = 1.0; // 測定単位 : Unit of Measure の 略

// ポインタと型を指定してメモリの確保と初期化を行うマクロ
#define get_array(ptr, type, N)                                                 \
    {                                                                           \
        ptr = (type *)calloc((N), sizeof(type));                                \
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

FILE *fp; // CSV出力用

// switch-case の分岐用
enum PRN_Type
{
    UniformRN = 1,
    NormalRN
};

int main(void)
{
    srand((unsigned int)time(NULL));
    //srand(123); // 動作検証用

    // fp オープン wモード
    if (fopen_s(&fp, "Inoue_Akihiro_task9-2.csv", "w") != 0)
        exit(EXIT_FAILURE); // エラー処理

    int N; // 乱数生成数
    printf("乱数の生成数 N を 整数値で指定して下さい---- > ");
    scanf_s("%d", &N);

    double *x;
    get_array(x, double, N);

    double a, b;       // 一様乱数の範囲
    double mu, sigma;  // 正規乱数の初期条件（真値）
    int choice;        // 乱数の型（ 1 : 一様乱数   2 : 正規乱数 ）
    bool check = true; // 乱数の型選択ループ用

    do
    {
        printf("\n1 : 範囲[a,b]の実数型一様乱数の生成\n"       // Uniform Random Number
               "\n2 : 平均 μ と 標準偏差 σ の正規乱数の生成\n" // Normal Random Number
               "\n生成する乱数の選択番号を 1 と 2 より 1 つ入力下さい. ---> ");
        scanf_s("%d", &choice);

        // 乱数の型で条件分岐して、擬似乱数生成
        switch (choice)
        {
        case UniformRN:
            do
            {
                do
                {
                    printf("\n実数型一様乱数の範囲 [ a , b ] を指定して下さい\n"
                           "a ---> ");
                    scanf_s("%lf", &a);
                } while (a < 1.0);
                printf("b ---> ");
                scanf_s("%lf", &b);
            } while (a > b); // 1.0 ≦ a ＜ b の条件指定入力

            // 範囲[a,b]の実数型一様乱数を N 個生成
            for (int i = 0; i < N; i++)
                x[i] = a + (b - a) * ((double)rand() / (double)RAND_MAX);
            check = false;
            break;

        case NormalRN:
            do
            {
                printf("\n正規乱数の平均 μ と 標準偏差 σ を指定して下さい\n"
                       "μ ---> ");
                scanf_s("%lf", &mu);
                printf("σ ---> ");
                scanf_s("%lf", &sigma);
            } while ((mu - 3 * sigma) <= 0); // μ > 3σ の条件指定入力

            // 平均 μ と 標準偏差 σ の正規分布に従う正規乱数 (ボックス・ミュラー法)を N 個生成
            for (int i = 0; i < N; i = i + 2)
            {
                double r1 = ((double)rand() + 1) / ((double)RAND_MAX + 1);
                double r2 = ((double)rand() + 1) / ((double)RAND_MAX + 1);
                x[i] = mu + sigma * sqrt(-2.0 * log(r1)) * cos(2.0 * M_PI * r2);
                x[i + 1] = mu + sigma * sqrt(-2.0 * log(r1)) * sin(2.0 * M_PI * r2);
            }
            check = false;
            break;

        default:
            printf("\n選択番号に誤りがあります．再度，選択番号を入力しなおして下さい．\n");
        }
    } while (check);

    double xmax = -DBL_MAX;
    double xmin = DBL_MAX;
    double sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += x[i];     // 和
        if (xmax < x[i]) //
            xmax = x[i]; // 最大値
        if (xmin > x[i]) //
            xmin = x[i]; // 最小値
    }
    double avx = sum / N; // 平均値
    double vx = 0;
    for (int i = 0; i < N; i++)
        vx += pow((x[i] - avx), 2);
    vx = vx / N;          // 分散
    double sx = sqrt(vx); // 標準偏差

    // 乱数の型で分岐してタイトルと、データの初期条件を出力
    switch (choice)
    {
    case UniformRN:
        printf("\n実数型一様乱数データの統計処理結果\n"
               "\nデータ範囲\ta\tb\n"
               "\t\t%g\t%g\n\n",
               a, b);
        fprintf(fp, "実数型一様乱数データの統計処理結果\n"
                    "\nデータ範囲,a,b\n"
                    ",%g,%g\n\n",
                a, b);
        break;

    case NormalRN:
        printf("\n正規乱数データの統計処理結果\n"
               "\n正規分布\t平均\t標準偏差\n"
               "真の値\t\t%g\t%g\n\n",
               mu, sigma);
        fprintf(fp, "正規乱数データの統計処理結果\n"
                    "\n正規分布,平均,標準偏差\n"
                    "真の値,%g,%g\n\n",
                mu, sigma);
        break;
    }

    // データ情報テーブル
    printf("データ数\t\t%d\n"
           "データの平均\t\t%lf\n"
           "データの不偏分散\t%lf\n"
           "データの標準偏差\t%lf\n"
           "データの最大値\t\t%lf\n"
           "データの最小値\t\t%lf\n",
           N, avx, vx, sx, xmax, xmin);
    fprintf(fp, "データ数,%d\n"
                "データの平均,%lf\n"
                "データの不偏分散,%lf\n"
                "データの標準偏差,%lf\n"
                "データの最大値,%lf\n"
                "データの最小値,%lf\n",
            N, avx, vx, sx, xmax, xmin);

    int k; // 級の数
    printf("\n級の数 k を 整数値 で 指定して下さい---- > ");
    scanf_s("%d", &k);

    double h = ceil((xmax - xmin) / (double)k); // 級の区間幅 h の設定

    double *x_interval; // 級の区間値
    get_array(x_interval, double, k + 1);
    x_interval[0] = xmin - (UOM / 2);          // データ区間の下限値設定
    for (int i = 1; i < k + 1; i++)            //
        x_interval[i] = x_interval[i - 1] + h; // 各級のデータ区間値の設定

    double *x_midval; // 区間の真ん中の値
    get_array(x_midval, double, k);
    for (int i = 0; i < k; i++)
        x_midval[i] = (x_interval[i] + x_interval[i + 1]) / 2;

    int *freq;            // 度数
    int *cum_freq;        // 累積度数
    double *rel_freq;     // 相対度数
    double *cum_rel_freq; // 累積相対度数
    // 配列の初期化
    get_array(freq, int, k);
    get_array(cum_freq, int, k);
    get_array(rel_freq, double, k);
    get_array(cum_rel_freq, double, k);

    // 級の表示と度数テーブルのタイトル
    printf("\n級の数\t\t%d\n"
           "級の区間幅\t%g\n"
           "\nデータ区間\t\t\t中間の値\t度数\t累積度数\t相対度数\t累積相対度数\n",
           k, h);
    fprintf(fp, "\n級の数,%d\n"
                "級の区間幅,%g\n"
                "\nデータ区間,中間の値,度数,累積度数,相対度数,累積相対度数\n",
            k, h);

    int temp_freq = 0;          // 累積度数の一時記憶
    for (int i = 0; i < k; i++) // 級の更新
    {
        for (int j = 0; j < N; j++) // データの検索
        {
            if ((x_interval[i] <= x[j]) && (x[j] < x_interval[i + 1]))
                freq[i]++; // 現在の級にある数値をカウント（度数）
        }
        cum_freq[i] = temp_freq + freq[i];                 // 累積度数
        rel_freq[i] = (double)freq[i] / (double)N;         // 相対度数の算出
        cum_rel_freq[i] = (double)cum_freq[i] / (double)N; // 累積相対度数の算出
        temp_freq = cum_freq[i];                           // 累積度数の更新用

        // 度数テーブルの出力
        printf("%lf － %lf\t%lf\t%d\t%d\t\t%lf\t%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
        fprintf(fp, "%lf － %lf,%lf,%d,%d,%lf,%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
    }

    // 累計の出力
    printf("\t\t\t\t\t\t累計\t%d\t\t累計\t\t%lf\n", cum_freq[k - 1], cum_rel_freq[k - 1]);
    fprintf(fp, ",,累計,%d,累計,%lf\n", cum_freq[k - 1], cum_rel_freq[k - 1]);

    // ファイルクローズ
    fclose(fp);
    // メモリ解放
    free_null(x);
    free_null(x_interval);
    free_null(x_midval);
    free_null(freq);
    free_null(rel_freq);
    free_null(cum_freq);
    free_null(cum_rel_freq);

    return 0;
}