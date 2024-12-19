// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task5.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>
#include <time.h> // clock関数

// 非線形方程式 f(x) の定義
#define f(x) (log(x) - cos(x))

double bisection_recursion(double, double, const double, int);

FILE *fp; // FILEポインタ

int main(void)
{
    // fpを書き込みモードでオープンしファイルを初期化
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus1.csv", "w");
    if (fp == NULL) // エラー処理
        exit(EXIT_FAILURE);
    fclose(fp); // ファイルクローズ

    clock_t start = clock(); // 探索開始時刻の取得

    const double a = 0.001, b = 3.0; // 探索開始点
    const double eps = 0.00001;      // 収束判定定数
    double x, xL, xH;                // x:変数
    int n = 1;                       // 反復回数

    // 探索区間と関数値の初期化
    xL = a;
    xH = b;

    // 2分法で関数f(x)の近似解を探索する処理
    x = bisection_recursion(xL, xH, eps, n);

    // fpを追加書き込みモードでファイルオープン
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus1.csv", "a");
    if (fp == NULL) // エラー処理
        exit(EXIT_FAILURE);

    // 関数式f(x)と近似解の出力
    printf("\nf(x) = log(x) - cos(x) = 0\n\n"
           "2分法：a = %lf  b = %lf\n"
           "2分法による近似解：%.8f\n\n",
           a, b, x); // cmd
    fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
                "2分法：a = %lf  b = %lf\n"
                "2分法による近似解：%.8f\n\n",
            a, b, x); // csv

    clock_t end = clock(); // 探索終了時刻の取得

    // 処理経過時間の出力
    printf("処理時間\t%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC);     // cmd
    fprintf(fp, "処理時間,%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

    fclose(fp); // ファイルクローズ
    return 0;
}

double bisection_recursion(double xL, double xH, const double eps, int n)
{
    // fpを追加書き込みモードでファイルオープン
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus1.csv", "a");
    if (fp == NULL) // エラー処理
        exit(EXIT_FAILURE);

    if (n == 1)
    {
        // タイトルの出力
        printf("反復回数n\tx\t\tf(x)\n");  // cmd
        fprintf(fp, "反復回数n,x,f(x)\n"); // csv
    }

    double yL = f(xL);
    double yH = f(xH);
    double w = fabs(xH - xL);       // 探索幅
    double x = x = (xH + xL) / 2.0; // 中点
    double y = f(x);

    // 解の存在場所で判定し、探索区間と関数値を更新する
    if (yL * y < 0)
    { // 解が左半分に存在
        xH = x;
        yH = y;
    }
    else if (yH * y < 0)
    { // 解が右半分に存在
        xL = x;
        yL = y;
    }
    else
        w = 0; // 中点の関数値が0のとき

    // 経過の出力
    printf("%d\t\t%.8f\t%.8f\n", n, x, y);  // cmd
    fprintf(fp, "%d,%.8f,%.8f\n", n, x, y); // csv

    // 探索区間幅による再帰処理
    // ベースケース
    if (w < eps)
    {
        fclose(fp); // ファイルクローズ
        return x;
    }
    // 再帰ステップ
    else
    {
        n++;        // 回数のカウント
        fclose(fp); // ファイルクローズ
        return bisection_recursion(xL, xH, eps, n);
    }
}