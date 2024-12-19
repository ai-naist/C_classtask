// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam6.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>
#include <time.h> // clock関数

// 非線形方程式 f(x) の定義
#define f(x) (log(x) - cos(x))

// プロトタイプ宣言
double direct_recursion(double, const double, int);

FILE *fp; // FILEポインタ

int main(void)
{
	// fpを書き込みモードでオープンしファイルを初期化
	fopen_s(&fp, "Inoue_Akihiro_exam6.csv", "w");
	if (fp == NULL) // エラー処理
		exit(EXIT_FAILURE);
	fclose(fp); // ファイルクローズ

	clock_t start = clock(); // 探索開始時刻の取得

	const double delta_x = 0.001; // 探索間隔
	const double a = 0.001;		  // 探索開始点
	double x1;					  // 探索点
	int n = 1;					  // 反復回数
	x1 = a;						  // 探索点を開始点で初期化

	// 直接探索法で関数f(x)の近似解を再帰呼び出しによるループで探索する処理
	x1 = direct_recursion(x1, delta_x, n);

	// fpを追加書き込みモードでファイルオープン
	fopen_s(&fp, "Inoue_Akihiro_exam6.csv", "a");
	if (fp == NULL) // エラー処理
		exit(EXIT_FAILURE);

	// 関数式f(x)と近似解の出力
	printf("\nf(x) = log(x) - cos(x) = 0\n\n"
		   "直接探索法による近似解：%lf\n\n",
		   x1); // cmd
	fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
				"直接探索法による近似解：%lf\n\n",
			x1); // csv

	clock_t end = clock(); // 探索終了時刻の取得

	// 処理経過時間の出力
	printf("処理時間\t%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC);	  // cmd
	fprintf(fp, "処理時間,%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

	fclose(fp); // ファイルクローズ
	return 0;
}

double direct_recursion(double x1, const double delta_x, int n)
{
	// fpを追加書き込みモードでファイルオープン
	fopen_s(&fp, "Inoue_Akihiro_exam6.csv", "a");
	if (fp == NULL) // エラー処理
		exit(EXIT_FAILURE);

	double y1 = f(x1);
	double x2 = x1 + delta_x;
	double y2 = f(x2);

	if (n == 1)
	{
		// タイトルの出力
		printf("反復回数n\tx1\tf(x1)\n");	 // cmd
		fprintf(fp, "反復回数n,x1,f(x1)\n"); // csv
	}

	// 経過の出力
	printf("%d\t\t%.3f\t%.8f\n", n, x1, y1);  // cmd
	fprintf(fp, "%d,%.3f,%.8f\n", n, x1, y1); // csv

	// y1とy2の符号変化を検証
	// ベースケース(異符号のとき)
	if (y1 * y2 <= 0)
	{
		fclose(fp); // ファイルクローズ
		return x1;
	}
	// 再帰ステップ(同符号のとき)
	else
	{
		x1 = x2;	// 探索点を進める
		n++;		// 回数のカウント
		fclose(fp); // ファイルクローズ
		return direct_recursion(x1, delta_x, n);
	}
}