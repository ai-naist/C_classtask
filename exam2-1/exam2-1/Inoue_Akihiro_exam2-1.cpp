// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam2-1.cpp

# include<stdio.h>
# define _USE_MATH_DEFINES // 数値演算定数の定義
# include<math.h>

FILE* fp; // FILEポインタ　fpは慣例の関数名

int main(void) {

	// Open for write
	// FILEポインタfp に "ファイル名.拡張子" と "ファイル書込みモード" の情報を与える
	//ファイルが存在しないときはソースと同じディレクトリに新規作成される
	fopen_s(&fp, "Inoue_Akihiro_exam2-1.csv", "w");

	double x1 = 1.73;
	double y1 = log(2 * x1); // x1 に対する log(2*x1) の算出値を 変数 y1 に代入

	//CUIでの表示
	printf("x1 log(2x1)\n");
	printf("%.2lf %.8lf\n", x1, y1);

	//csvファイルへの操作
	fprintf(fp, "x1,log(2x1)\n"); // 表タイトルをcsvファイルへ上書き保存
	fprintf(fp, "%.2lf,%.8lf\n", x1, y1); // x1 と y1 の データをcsvファイルへ上書き保存

	fclose(fp); //ファイルを閉じる

	return 0;
}
