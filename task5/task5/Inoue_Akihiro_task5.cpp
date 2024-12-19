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
#define f(x) (log(x)-cos(x))

FILE* fp; // FILEポインタ

int main(void)
{
	// fpを書き込みモードでオープン
	fopen_s(&fp, "Inoue_Akihiro_task5.csv", "w");
	if (fp == NULL) // エラー処理
		return 1;

	clock_t start = clock(); // 探索開始時刻の取得

	// タイトルの出力
	printf("反復回数n\tx\tf(x)\n"); // cmd
	fprintf(fp, "反復回数n,x,f(x)\n"); // csv

	const double a = 0.001, b = 3.0; // 探索開始点
	const double eps = 0.00001; // 収束判定定数
	double x, xL, xH, y, yL, yH, w; // x:変数 y:関数値 w:探索区間幅
	int n = 1; // 反復回数

	// 探索区間と関数値の初期化
	xL = a;
	xH = b;
	yL = f(xL);
	yH = f(xH);

	// 2分法で関数f(x)の近似解を探索する処理
	do {

		w = fabs(xH - xL); // 探索幅
		x = (xH + xL) / 2.0; // 中点
		y = f(x);

		// 解の存在場所で判定し、探索区間と関数値を更新する
		if (yL * y < 0) { // 解が左半分に存在
			xH = x;
			yH = y;
		}else if (yH * y < 0) { // 解が右半分に存在
			xL = x;
			yL = y;
		}else
			w = 0; // 中点の関数値が0のとき

		// 経過の出力(中点と中点での関数値)
		printf("%d\t%.8f\t%.8f\n", n, x, y); // cmd
		fprintf(fp, "%d,%.8f,%.8f\n", n, x, y); // csv

		n++; // 回数のカウント
	} while (w > eps); // 探索幅が収束判定定数を下回るとき処理を抜ける

	// 関数式f(x)と近似解の出力
	printf("\nf(x) = log(x) - cos(x) = 0\n\n"
		"2分法：a = %lf  b = %lf\n"
		"2分法による近似解：%.8f\n\n", a, b, x); // cmd
	fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
		"2分法：a = %lf  b = %lf\n"
		"2分法による近似解：%.8f\n\n", a, b, x); // csv

	clock_t end = clock(); // 探索終了時刻の取得

	// 処理経過時間の出力
	printf("処理時間\t%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // cmd
	fprintf(fp, "処理時間,%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

	fclose(fp); // ファイルクローズ
	return 0;
}