// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam4.cpp

#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES // 数値演算定数

// 関数形式マクロを用いて関数式 f(x0)を定義する
#define f(x0) (7.0 * pow((x0), 4.0) - 5.0 * pow((x0), 3.0) + 3.0 * (x0))
// 書式 #define マクロ名(仮引数,...) (置換後の式)


// 関数式 f(x0)を定義する関数
double f_x(double x0)
{
	// 微分を行う関数の代入
	double fx0 = 7.0 * pow(x0, 4.0) - 5.0 * pow(x0, 3.0) + 3.0 * x0;
	return fx0;
}

// 出力の記述をマクロで書き換え
#define cout(x) printf("\t%lf", (x))
#define fout(x) fprintf(fp,",%lf",(x))

FILE* fp; // ファイルポインタの宣言

int main(void)
{
	// fpを書き込みモードでオープン
	fopen_s(&fp,"Inoue_Akihiro_exam4.csv", "w");
	if (fp == NULL) // エラー処理
		return 1;

	double x0; // 関数式に代入する変数
	const double h = 0.01; // x0の微小間隔

	double u[5], m[5]; // u:自作関数  m:関数形式マクロ に対応して 0:x0  1:fx0  2:h  3:dfdx0  4:d2fdx02 をそれぞれ格納する
	u[2] = h;
	m[2] = h;

	// タイトルをコンソールに出力
	printf("f(x0) = 7.0 * x0^4 - 5.0 * x0^3 + 3.0 * x0\n\n");
	printf("choice : u:自作関数を利用、m:引数つき関数形式マクロを利用\n\n");
	printf("choice\tx0\t\tfx0\t\th\t\tdfdx0\t\td2fdx02\t\n");

	// タイトルをcsvに書き込み
	fprintf(fp, "f(x0) = 7.0 * x0^4 - 5.0 * x0^3 + 3.0 * x0\n\n");
	fprintf(fp, "choice : u:自作関数を利用、m:引数つき関数形式マクロを利用\n\n");
	fprintf(fp, "choice,x0,fx0,h,dfdx0,d2fdx02\n");

	// 関数式を変域 1.99 <= x <= 2.01 の範囲で 0.01 ごとに変化させる
	for (x0 = 1.99; x0 <= 2.01; x0 += h) {

		u[0] = x0;
		m[0] = x0;

		// 現在の x0 での 関数 f(x) を算出
		u[1] = f_x(x0); // 自作関数
		m[1] = f(x0); // マクロ

		// 現在の x0 での 関数 f(x) の 1次微係数の算出
		u[3] = (f_x(x0 + h) - f_x(x0 - h)) / (2.0 * h); // 自作関数
		m[3] = (f(x0 + h) - f(x0 - h)) / (2.0 * h); // マクロ

		// 現在の x0 での 関数 f(x) の 2次微係数の算出
		u[4] = (f_x(x0 + h) - 2.0 * f_x(x0) + f_x(x0 - h)) / pow(h, 2.0); // 自作関数
		m[4] = (f(x0 + h) - 2.0 * f(x0) + f(x0 - h)) / pow(h, 2.0); // マクロ

		// 自作関数を利用した場合のchoiceの選択文字, x0, fx0, h, dfdx0, d2fdx02 の値をコンソールに出力
		printf("u");
		for (int i=0; i < 5; i++)
			cout(u[i]);
		printf("\n");
		// 引数つき関数マクロを利用した場合のchoiceの選択文字, x0, fx0, h, dfdx0, d2fdx02 の値をコンソールに出力
		printf("m");
		for (int i=0; i < 5; i++)
			cout(m[i]);
		printf("\n");

		// 自作関数を利用した場合のchoiceの選択文字,x0, fx0, h, dfdx0, d2fdx02 の値をcsvファイル出力
		fprintf(fp, "u");
		for (int i=0; i < 5; i++)
			fout(u[i]);
		fprintf(fp,"\n");
		// 引数つき関数マクロを利用した場合のchoiceの選択文字,x0, fx0, h, dfdx0, d2fdx02 の値をcsvファイル出力
		fprintf(fp, "m");
		for (int i=0; i < 5; i++)
			fout(m[i]);
		fprintf(fp,"\n");
	}
	fclose(fp); // ファイルクローズ

	return 0;
}