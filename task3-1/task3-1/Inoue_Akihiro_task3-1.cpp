// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task3-1.cpp
#include<stdio.h>
#include<stdlib.h> // EOF処理に必要
#define _USE_MATH_DEFINES
#include<math.h>

const int N_Max = 100; // 定数

// 平均値計算関数
double AvgFunc(int N_Data, double sum)
{
	return sum / N_Data;
}

// 最大値
double MaxFunc(int N_Data, double* array)
{
	double max = array[0]; // 配列の先頭の値で初期化

	for (int i = 1; i < N_Data; i++)
	{
		if (array[i] > max)
			max = array[i];
	}

	return max;
}

// 最小値
double MinFunc(int N_Data, double* array)
{
	double min = array[0]; // 配列の先頭の値で初期化

	for (int i = 1; i < N_Data; i++)
	{
		if (array[i] < min)
			min = array[i];
	}

	return min;
}

// 分散
double VarFunc(int N_Data, double avg, double* array)
{
	double var = 0;

	for (int i = 0; i < N_Data; i++)
	{
		var += (avg - array[i]) * (avg - array[i]);
	}

	return var / (N_Data - 1);
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
	if (fp1 == NULL) // エラー処理
		return 1;

	// fp2を書き込みモードでオープン
	fopen_s(&fp2, "Inoue_Akihiro_task3-1.csv", "w");
	if (fp2 == NULL) // エラー処理
		return 1;

	printf("No.\t\tx\t\ty\n");
	fprintf(fp2, "No.,x,y\n"); // csvに書き込み



	// csvからセル単位で読み込み
	int i = 0;
	while ((fscanf_s(fp1, "%lf,%lf", &x[i], &y[i])) != EOF) // EOFはファイルの終端
	{

		printf("%d\t%lf\t%lf\n", i + 1, x[i], y[i]);
		fprintf(fp2, "%d,%lf,%lf\n", i + 1, x[i], y[i]); // csvに書き込み

		// x,yそれぞれの合計
		sum_x += x[i];
		sum_y += y[i];

		i++;
	}

	fclose(fp1); // ファイルクローズ

	N_Data = i; // データ数

	printf("データ数\t%d\t\t%d\n", N_Data, N_Data); // データ数の表示
	fprintf(fp2, "データ数,%d,%d\n", N_Data, N_Data); // csvにデータ数の書き込み

	double max_x = MaxFunc(N_Data, x), min_x = MinFunc(N_Data, x), max_y = MaxFunc(N_Data, y), min_y = MinFunc(N_Data, y);

	printf("最大\t%lf\t%lf\n", max_x, max_y); // 最大の表示
	fprintf(fp2, "最大,%lf,%lf\n", max_x, max_y); // csvに最大の書き込み

	printf("最小\t%lf\t%lf\n", min_x, min_y); // 最小の表示
	fprintf(fp2, "最小,%lf,%lf\n", min_x, min_y); // csvに最小の書き込み

	printf("範囲\t%lf\t%lf\n", max_x - min_x, max_y - min_y); // 範囲の表示
	fprintf(fp2, "範囲,%lf,%lf\n", max_x - min_x, max_y - min_y); // csvに範囲の書き込み

	double avg_x = AvgFunc(N_Data, sum_x), avg_y = AvgFunc(N_Data, sum_y);

	printf("平均\t%lf\t%lf\n", avg_x, avg_y); // 平均の表示
	fprintf(fp2, "平均,%lf,%lf\n", avg_x, avg_y); // csvに平均の書き込み

	double var_x = VarFunc(N_Data, avg_x, x), var_y = VarFunc(N_Data, avg_y, y);

	printf("分散\t%lf\t%lf\n", var_x, var_y); // 分散の表示
	fprintf(fp2, "分散,%lf,%lf\n", var_x, var_y); // csvに分散の書き込み

	printf("標準偏差\t%lf\t%lf\n", sqrt(var_x), sqrt(var_y)); // 標準偏差の表示
	fprintf(fp2, "標準偏差,%lf,%lf\n", sqrt(var_x), sqrt(var_y)); // csvに標準偏差の書き込み


	fclose(fp2); //ファイルクローズ

	return 0;
}