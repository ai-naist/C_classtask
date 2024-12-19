// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task5_bonus.cpp

#include <stdio.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>
#include <time.h> // clock関数

// 非線形方程式 f(x) の定義
#define f(x) (log(x) - cos(x))
// f(x)の一階導関数
#define D_f(x) ((1 / (x)) + sin(x))

FILE *fp; // FILEポインタ

int main(void)
{
	// fpを書き込みモードでオープン
	fopen_s(&fp, "Inoue_Akihiro_task5_bonus.csv", "w");
	if (fp == NULL) // エラー処理
		return 1;

	clock_t start = clock(); // 探索開始時刻の取得

	// タイトルの出力
	printf("n\tx_n+1\tx_n\tf(x_n)\tf'(x_n)\tx_n+1 - x_n\n"); // cmd
	fprintf(fp, "n,x_n+1,x_n,f(x_n),f'(x_n),x_n+1 - x_n\n"); // csv

	const double x0 = 0.001;	// 探索開始点
	const double eps = 0.00001; // 収束判定定数
	double xn, xn1, y, Dy, w;	// x:変数 y:関数値 Dy:一次微係数 w:近似解の相対差
	int n = 1;					// 反復回数

	// 探索開始点の初期化
	xn = x0;

	// ニュートン法で関数f(x)の近似解を探索する処理
	do
	{
		y = f(xn);
		Dy = D_f(xn);
		xn1 = xn - (y / Dy);
		w = fabs(xn1 - xn);

		// 経過の出力
		printf("%d\t%.8f\t%.8f\t%.8f\t%.8f\t%.8f\n", n, xn1, xn, y, Dy, w); // cmd
		fprintf(fp, "%d,%.8f,%.8f,%.8f,%.8f,%.8f\n", n, xn1, xn, y, Dy, w); // csv

		w = w / xn;
		xn = xn1;	   // 探索点の更新
		n++;		   // 回数のカウント
	} while (w > eps); // 近似解の相対差が収束判定定数を下回るときに処理を抜ける

	// 関数式f(x)と近似解の出力
	printf("\nf(x) = log(x) - cos(x) = 0\n\n"
		   "ニュートン法による近似解：%.8f\n\n",
		   xn1); // cmd
	fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
				"ニュートン法による近似解：%.8f\n\n",
			xn1); // csv

	clock_t end = clock(); // 探索終了時刻の取得

	// 処理経過時間の出力
	printf("処理時間\t%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC);	  // cmd
	fprintf(fp, "処理時間,%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

	fclose(fp); // ファイルクローズ
	return 0;
}