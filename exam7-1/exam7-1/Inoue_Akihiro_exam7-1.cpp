// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam7-1.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>

// 都市数
const int N = 2;

// 2都市間距離の算出
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

FILE *fp; // ファイルポインタ

// x座標とy座標を構造体で定義
typedef struct
{
    double x; // x座標
    double y; // y座標
} point_t;

int main(void)
{
    // fpを書き込みモードでオープンしファイルを初期化
    fopen_s(&fp, "Inoue_Akihiro_exam7-1.csv", "w");
    if (fp == NULL) // エラー処理
        exit(EXIT_FAILURE);

    point_t city[N + 1] = {{0.0, 0.0}, {90.06, 14.19}, {18.80, 30.24}}; // メンバの初期化

    int i, j;   // 都市番号のメモ
    double dij; // 2都市間距離

    // 都市番号の代入
    i = 1;
    j = 2;

    // 2都市間距離を算出
    if (i != j)
        dij = distance_func(city[i].x, city[j].x, city[i].y, city[j].y);

    // タイトルの出力
    printf("都市番号\tx座標\ty座標\n");    // cmd
    fprintf(fp, "都市番号,x座標,y座標\n"); // csv

    for (int k = 1; k <= N; k++)
    {
        // メンバを出力
        printf("%d\t\t%.2lf\t%.2lf\n", k, city[k].x, city[k].y);
        fprintf(fp, "%d,%.2lf,%.2lf\n", k, city[k].x, city[k].y);
    }
    // 結果出力:訪問した2都市の都市番号と2都市間距離
    printf("\n出発都市番号 i\t次の訪問都市 j\t2都市間距離 dij\n"
           "\t%d\t\t%d\t\t%.2lf\n",
           i, j, dij); // cmd
    fprintf(fp, "\n出発都市番号 i,次の訪問都市 j,2都市間距離 dij\n"
                "%d,%d,%.2lf\n",
            i, j, dij); // csv

    fclose(fp); // ファイルクローズ
    return 0;
}