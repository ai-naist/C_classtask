// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task2.cpp

#include <stdio.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>

// 任意の変数xに対して、数値解析結果を3つ返す関数
double NumAnaFunc(double x, double* p_y2, double* p_y3)
{
    *p_y2 = cos(x);
    *p_y3 = sin(x);
    return sqrt(x);
}

FILE *fp; // FILEポインタ

int main(void)
{

    // FILEポインタfp に "ファイル名.拡張子" と "ファイル書込みモード" の情報を与える
    fopen_s(&fp, "Inoue_Akihiro_task2.csv", "w");

    double x, y1, y2, y3;

    // コンソールで表示
    printf("x sqrt(x) cos(x) sin(x)\n");
    // csvに出力
    fprintf(fp, "x,sqrt(x),cos(x),sin(x)\n");

    for (int i = 0; i <= 10; i++)
    {
        // xは0からpiまでpi/10きざみで変化
        x = i * M_PI / 10;

        // y1,y2,y3に関数値を代入
        y1 = NumAnaFunc(x, &y2, &y3);

        // コンソールで表示
        printf("%lf %lf %lf %lf\n", x, y1, y2, y3);
        // csv出力
        fprintf(fp, "%lf,%lf,%lf,%lf\n", x, y1, y2, y3);
    }
    fclose(fp); // ファイルクローズ

    return 0;
}