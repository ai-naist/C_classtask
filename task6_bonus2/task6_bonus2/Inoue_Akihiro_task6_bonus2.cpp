// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task6_bonus2.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>
#include <time.h> // clock関数

// 非線形方程式 f(x) の定義
#define f(x) (log(x) - cos(x))
// f(x)の一階導関数
#define D_f(x) ((1 / (x)) + sin(x))

double newton_recursion(double, const double, int);

FILE *fp; // FILEポインタ

int main(void)
{
    // fpを書き込みモードでオープンしファイルを初期化
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus2.csv", "w");
    if (fp == NULL) // エラー処理
        exit(EXIT_FAILURE);
    fclose(fp); // ファイルクローズ

    clock_t start = clock(); // 探索開始時刻の取得

    const double x0 = 0.001;    // 探索開始点
    const double eps = 0.00001; // 収束判定定数
    double xn, xn1;             // x:変数
    int n = 1;                  // 反復回数

    // 探索開始点の初期化
    xn = x0;

    // ニュートン法で関数f(x)の近似解を探索する処理
    xn1 = newton_recursion(xn, eps, n);

    // fpを追加書き込みモードでファイルオープン
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus2.csv", "a");
    if (fp == NULL) // エラー処理
        exit(EXIT_FAILURE);

    // 関数式f(x)と近似解の出力
    printf("\nf(x) = log(x) - cos(x) = 0\n\n"
           "ニュートン法による近似解：%.8f\n\n",
           xn1); // cmd
    fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
                "ニュートン法による近似解：%.8f\n\n",
            xn1); // csv

    clock_t end = clock(); // 探索終了時刻の取得

    // 処理経過時間の出力
    printf("処理時間\t%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC);     // cmd
    fprintf(fp, "処理時間,%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

    fclose(fp); // ファイルクローズ
    return 0;
}

double newton_recursion(double xn, const double eps, int n)
{
    // fpを追加書き込みモードでファイルオープン
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus2.csv", "a");
    if (fp == NULL) // エラー処理
        exit(EXIT_FAILURE);

    if (n == 1)
    {
        // タイトルの出力
        printf("n\tx_n+1\t\tx_n\t\tf(x_n)\t\tf'(x_n)\t\tx_n+1 - x_n\n"); // cmd
        fprintf(fp, "n,x_n+1,x_n,f(x_n),f'(x_n),x_n+1 - x_n\n"); // csv
    }

    double y = f(xn);           // y:関数値
    double Dy = D_f(xn);        // Dy:一次微係数
    double xn1 = xn - (y / Dy); // 近似解
    double w = fabs(xn1 - xn);  // w:近似解の差

    // 経過の出力
    printf("%d\t%.8f\t%.8f\t%.8f\t%.8f\t%.8f\n", n, xn1, xn, y, Dy, w); // cmd
    fprintf(fp, "%d,%.8f,%.8f,%.8f,%.8f,%.8f\n", n, xn1, xn, y, Dy, w); // csv

    w = w / xn;
    xn = xn1; // 探索点の更新

    // 探索区間幅による再帰処理
    // ベースケース
    if (w < eps)
    {
        fclose(fp); // ファイルクローズ
        return xn1;
    }
    // 再帰ステップ
    else
    {
        n++;        // 回数のカウント
        fclose(fp); // ファイルクローズ
        return newton_recursion(xn, eps, n);
    }
}