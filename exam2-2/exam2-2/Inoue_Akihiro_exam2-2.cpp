// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam2-2.cpp

# include<stdio.h>
# define _USE_MATH_DEFINES // 数値演算定数
# include<math.h>

FILE* fp; // FILEポインタ

int main(void) {

	// FILEポインタfp に "ファイル名.拡張子" と "ファイル書込みモード" の情報を与える
	fopen_s(&fp, "Inoue_Akihiro_exam2-2.csv", "w");

	double x, y;

	//コンソールで表示
	printf("x (5x)^0.3\n");
	//csvに出力
	fprintf(fp, "x,(5x)^0.3\n");

	for (x = 0.5; x <= 10.5; x += 1.0) { // x を 0.5 <= x <= 10.5 の範囲で 刻み 1.0で変化させる
		y = pow(5.0 * x, 0.3); //べき乗 a^b  書式 double pow(double a, double b);

		//コンソールで表示
		printf("%.1lf %lf\n", x, y);
		//csv出力
		fprintf(fp, "%.1lf,%lf\n", x, y);

	}
	fclose(fp); //ファイルをクローズする

	return 0;
}