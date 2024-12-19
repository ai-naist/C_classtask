// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam5.cpp

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
	fopen_s(&fp, "Inoue_Akihiro_exam5.csv", "w");
	if (fp == NULL) // エラー処理
		return 1;

	clock_t start = clock(); // 探索開始時刻の取得

	// タイトルの出力
	printf("反復回数n\tx1\tf(x1)\n"); // cmd
	fprintf(fp, "反復回数n,x1,f(x1)\n"); // csv

	double a=0.001; // 探索開始点
	const double delta_x = 0.001; // 探索間隔
	double x1, x2, y1, y2; // x:変数　y:関数値
	int n = 1; // 反復回数

	x1 = a; // x1の初期化

	// 直接探索法で関数f(x)の近似解を探索する処理
	do {
		y1 = f(x1);

		x2 = x1 + delta_x;
		y2 = f(x2);

		// 経過の出力
		printf("%d\t%.3f\t%lf\n",n,x1,y1); // cmd
		fprintf(fp, "%d,%.3f,%lf\n", n, x1, y1); // csv

		x1 = x2; // 探索点を進める
		n++; // 回数のカウント
		
	} while ((y1 * y2) > 0); // 関数値の符号変化で処理を抜ける

	x1 = x2 - delta_x; // 近似解(更新した探索点を一つ前に戻す)

	// 関数式f(x)と近似解の出力
	printf("\nf(x) = log(x) - cos(x) = 0\n\n"
		"直接探索法による近似解：%lf\n\n", x1); // cmd
	fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
		"直接探索法による近似解：%lf\n\n", x1); // csv

	clock_t end = clock(); // 探索終了時刻の取得

	// 処理経過時間の出力
	printf("処理時間\t%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // cmd
	fprintf(fp, "処理時間,%lf 秒\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

	fclose(fp); // ファイルクローズ
	return 0;
}