// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_exam3.cpp
#include<stdio.h>
 #include<stdlib.h> // EOF処理に必要
 #define _USE_MATH_DEFINES
 #include<math.h>

const int N_Max = 100; // 定数

//平均値計算関数
double AvgFunc(int N_Data, double sum_x, double sum_y, double* p_x)
{
	*p_x = sum_x / N_Data;
	return sum_y / N_Data;
}

FILE* fp1;
FILE* fp2;

int main(void)
{
	double x[N_Max] = { 0 }, y[N_Max] = { 0 }; // 配列x,yを0で初期化
	double sum_x = 0, sum_y = 0; // 合計値のメモ

	int N_Data;

	// fp1を読み取りモードでオープン
	fopen_s(&fp1, "data3.csv", "r");
	if (fp1 == NULL) //エラー処理
		return 1;

	// fp2を書き込みモードでオープン
	fopen_s(&fp2, "Inoue_Akihiro_exam3.csv", "w");
	if (fp2 == NULL) //エラー処理
		return 1;

	printf("No.\t\tx\t\ty\n");
	fprintf(fp2, "No.,x,y\n"); // csvに書き込み



	// csvからセル単位で読み込み
	int i = 0;
	while ((fscanf_s(fp1, "%lf,%lf", &x[i], &y[i])) != EOF) // EOFはファイルの終端
	{

		printf("%d\t%lf\t%lf\n", i+1, x[i], y[i]);
		fprintf(fp2, "%d,%lf,%lf\n", i+1, x[i], y[i]); // csvに書き込み

		//x,yそれぞれの合計
		sum_x += x[i];
		sum_y += y[i];

		i++;
	}

	fclose(fp1); // ファイルクローズ

	N_Data = i; //データ数

	printf("データ数\t%d\t\t%d\n", N_Data, N_Data); // データ数の表示
	fprintf(fp2, "データ数,%d,%d\n", N_Data, N_Data); // csvにデータ数の書き込み

	double avg_x,avg_y = AvgFunc(N_Data, sum_x, sum_y, &avg_x);

	printf("平均\t%lf\t%lf\n", avg_x, avg_y); // 平均の表示
	fprintf(fp2, "平均,%lf,%lf\n", avg_x, avg_y); // csvに平均の書き込み


	fclose(fp2); //ファイルクローズ

	return 0;
}