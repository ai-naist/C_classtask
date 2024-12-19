// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task7.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>

// データ読み込み用配列の最大数
const int N_Max = 100;

// プロトタイプ宣言
inline double distance_func(double, double, double, double);

FILE *fp_r, *fp_w; // ファイルポインタ

// x座標とy座標を構造体で定義
typedef struct
{
    double x; // x座標
    double y; // y座標
} point_t;

int main(void)
{
    point_t city[N_Max + 1] = {0.0}; // 構造体の初期化

    // fp_rを読み取りモードでオープン
    fopen_s(&fp_r, "task7_citydata.csv", "r");
    if (fp_r == NULL) // エラー処理
        exit(EXIT_FAILURE);

    // メンバの読み込み
    int k = 1;
    while ((fscanf_s(fp_r, "%lf,%lf", &city[k].x, &city[k].y)) != EOF)
    {
        k++;
    }

    int N = k - 1; // 訪問都市数
    fclose(fp_r);  // ファイルクローズ

    // fp_wを書き込みモードでオープン
    fopen_s(&fp_w, "Inoue_Akihiro_task7.csv", "w");
    if (fp_w == NULL) // エラー処理
        exit(EXIT_FAILURE);

    // タイトルの出力
    printf("訪問する都市が %d 都市あります。\n\n"
           "訪問する %d 都市の都市番号 1 ～ %d の位置座標は次の通りです。\n\n"
           "都市番号\tx座標\t\ty座標\n",
           N, N, N); // cmd
    fprintf(fp_w, "訪問する都市が %d 都市あります。\n\n"
                  "訪問する %d 都市の都市番号 1 ～ %d の位置座標は次の通りです。\n\n"
                  "都市番号,x座標,y座標\n",
            N, N, N); // csv

    // 都市番号と対応するメンバを出力
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%lf\t%lf\n", k, city[k].x, city[k].y);
        fprintf(fp_w, "%d,%lf,%lf\n", k, city[k].x, city[k].y);
    }

    int i;      // 都市番号のメモ
    double dij; // 2都市間距離

    // 出発都市番号を入力
    printf("\n最初に出発する都市 i を 1 ～ %d の中から選択して下さい。start -> ", N);
    scanf_s("%d", &i);

    // 結果タイトルの出力
    printf("\n最初に出発する都市 i を都市番号 %d にした場合の結果を示します。\n"
           "\n出発都市 i\t訪問都市 j\t2都市間距離 dij\n",
           i); // cmd
    fprintf(fp_w, "\n最初に出発する都市 i を都市番号 %d にした場合の結果を示します。\n"
                  "\n出発都市 i,訪問都市 j,2都市間距離 dij\n",
            i); // csv

    for (int j = 1; j <= N; j++)
    {
        // 2都市間距離を算出
        if (i != j)
        {
            dij = distance_func(city[i].x, city[j].x, city[i].y, city[j].y);

            // 結果出力(訪問した2都市の都市番号と2都市間距離)
            printf(
                "\t%d\t\t%d\t\t%.2f\n",
                i, j, dij); // cmd
            fprintf(fp_w, "%d,%d,%.2f\n",
                    i, j, dij); // csv
        }
    }

    fclose(fp_w); // ファイルクローズ
    return 0;
}

// 2都市間距離を算出する関数
inline double distance_func(double xi, double xj, double yi, double yj)
{
    return sqrt(pow(xi - xj, 2) + pow(yi - yj, 2));
}