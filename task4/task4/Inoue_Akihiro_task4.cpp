// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task4.cpp

#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES // 数値演算定数

// 関数形式マクロを用いて被積分関数 f(x)を定義する
#define f(x) (4.0/(1.0+pow((x),2.0)))
// 書式 #define マクロ名(仮引数,...) (置換後の式)


FILE* fp; // ファイルポインタの宣言

int main(void)
{
	// fpを書き込みモードでオープン
	fopen_s(&fp, "Inoue_Akihiro_task4.csv", "w");
	if (fp == NULL) // エラー処理
		return 1;

	int n = 400; // 区間分割数(整数値) n の指定
	double a = 0, b = 1;	// 積分区間[a,b]の指定
	double T; // 積分値
	double h = (b - a) / n; // 区間幅

	// タイトルの出力
	printf("台形則による数値計算\n");
	fprintf(fp, "台形則による数値計算\n");

	// 被積分関数 f(x)の表示
	printf("被積分関数 f(x) = 4.0 / ( 1.0 + x*x )\n");
	fprintf(fp,"被積分関数,f(x) = 4.0 / ( 1.0 + x*x )\n");

	// 積分区間[a,b]の表示
	printf("積分区間[a，b]) a=%.2f b=%.2f\n",a,b);
	fprintf(fp, "積分区間[a，b],a=%.2f,b=%.2f\n",a,b);

	// 区間分割数(整数値) n の表示
	printf("数値積分の区間分割数 n=%d\n", n);
	fprintf(fp,"数値積分の区間分割数,n=%d\n", n);

	// 台形則による数値積分の処理
	T = (f(a) + f(b)) / 2.0;
	for (int i = 1; i < n; i++)
		T += f(a + i * h);

	T = h * T;

	// 結果の出力
	printf("f(x)の積分の近似値 T = %.10f\n", T);
	fprintf(fp,"f(x)の積分の近似値,T = %.10f\n", T);

	fclose(fp); // ファイルクローズ

	return 0;
}