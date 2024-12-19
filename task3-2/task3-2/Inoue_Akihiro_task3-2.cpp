// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task3-2.cpp
#include<stdio.h>
#include<stdlib.h> // EOF処理に必要
#define _USE_MATH_DEFINES
#include<math.h>

const int N_Max = 100; // 定数(データ読み込み用配列の大きさ)

// BMI
double BMIFunc(double height, double weight)
{
	return weight / height / height * 10000;
}

// 平均
double AvgFunc(int N_Data, double sum)
{
	return sum / N_Data;
}

// 分散と平均を上回ったデータのカウント
double VarFunc(int N_Data, double avg, double* array, double* pN_ex_avg)
{
	double var = 0;
	int N_ex_avg = 0;

	for (int i = 0; i < N_Data; i++)
	{
		var += (avg - array[i]) * (avg - array[i]); // 差の2乗和

		if ((avg - array[i]) < 0)
			N_ex_avg++; // 平均を上回ったデータのカウント

	}

	*pN_ex_avg = N_ex_avg;

	return var / (N_Data - 1);
}

// 体型別割合をカウントし、受け取った配列の値を書き換える
void getDivArray(int div[5],int N_Data, double avg, double* bmi)
{
	for (int i = 0; i < N_Data; i++)
	{
		if (bmi[i] < 18.5)
			div[0]++;
		else if ((bmi[i] >= 18.5) && (bmi[i] < 20))
			div[1]++;
		else if ((bmi[i] >= 20) && (bmi[i] < 25))
			div[2]++;
		else if ((bmi[i] >= 25) && (bmi[i] < 30))
			div[3]++;
		else
			div[4]++;
	}
}


FILE* fp1;
FILE* fp2;

int main(void)
{
	double height[N_Max] = { 0 }, weight[N_Max] = { 0 }, bmi[N_Max] = { 0 }; // 配列を0で初期化
	double sum_height = 0, sum_weight = 0, sum_bmi = 0; // 合計値のメモ

	int N_Data; // データ数

	// fp1を読み取りモードでオープン
	fopen_s(&fp1, "healthdata.csv", "r");
	if (fp1 == NULL) // エラー処理
		return 1;

	// fp2を書き込みモードでオープン
	fopen_s(&fp2, "Inoue_Akihiro_task3-2.csv", "w");
	if (fp2 == NULL) // エラー処理
		return 1;

	printf("検査No.\t\t\t身長\t体重\tBMI\n"); // タイトルの表示
	fprintf(fp2, "検査No.,身長,体重,BMI\n"); // csvに書き込み



	// csvからセル単位で読み込み
	int i = 0;
	while ((fscanf_s(fp1, "%lf,%lf", &height[i], &weight[i])) != EOF) // EOFはファイルの終端
	{

		bmi[i] = BMIFunc(height[i], weight[i]);

		printf("%d\t\t\t%.2f\t%.2f\t%.2f\n", i + 1, height[i], weight[i], bmi[i]); // 各データの表示
		fprintf(fp2, "%d,%.2f,%.2f,%.2f\n", i + 1, height[i], weight[i], bmi[i]); // csvに書き込み

		// 各データそれぞれの合計
		sum_height += height[i];
		sum_weight += weight[i];
		sum_bmi += bmi[i];

		i++;
	}

	fclose(fp1); // ファイルクローズ

	N_Data = i; // データ数

	printf("データ数\t\t%d\t%d\t%d\n", N_Data, N_Data,N_Data); // データ数の表示
	fprintf(fp2, "データ数,%d,%d,%d\n", N_Data, N_Data,N_Data); // csvにデータ数の書き込み

	// 平均を代入
	double avg_height = AvgFunc(N_Data, sum_height), avg_weight = AvgFunc(N_Data, sum_weight), avg_bmi = AvgFunc(N_Data, sum_bmi);

	printf("平均\t\t\t%.2f\t%.2f\t%.2f\n", avg_height, avg_weight,avg_bmi); // 平均の表示
	fprintf(fp2, "平均,%.2f,%.2f,%.2f\n", avg_height, avg_weight,avg_bmi); // csvに平均の書き込み

	double hei_ex_avg, wei_ex_avg, bmi_ex_avg; // 平均を上回ったデータ用の変数

	// 分散を代入
	double var_height = VarFunc(N_Data, avg_height, height, &hei_ex_avg), var_weight = VarFunc(N_Data, avg_weight, weight, &wei_ex_avg), var_bmi = VarFunc(N_Data, avg_bmi, bmi, &bmi_ex_avg);

	printf("標準偏差\t\t%.2f\t%.2f\t%.2f\n", sqrt(var_height), sqrt(var_weight),sqrt(var_bmi)); // 標準偏差の表示
	fprintf(fp2, "標準偏差,%.2f,%.2f,%.2f\n", sqrt(var_height), sqrt(var_weight),sqrt(var_bmi)); // csvに標準偏差の書き込み

	printf("平均を上回った割合(％)\t%.2f\t%.2f\t%.2f\n", hei_ex_avg/N_Data*100,wei_ex_avg/N_Data*100,bmi_ex_avg/N_Data*100); // 平均を上回った割合の表示
	fprintf(fp2, "平均を上回った割合(％),%.2f,%.2f,%.2f\n", hei_ex_avg / N_Data * 100, wei_ex_avg / N_Data * 100, bmi_ex_avg / N_Data * 100); // csvに平均を上回った割合の書き込み

	int div[5] = { 0 }; // 配列要素 0:痩せ過ぎ 1:美容体型 2:適正 3:太り気味 4:太り過ぎ に対応する
	char pattern[6][100] = { "痩せすぎの割合(％)","美容体型の割合(％)","適正体格の割合(％)","太り気味の割合(％)","太りすぎの割合(％)" ,"割合の合計(％)"};
	// 2次元配列書式 char array[個数][長さ]

	getDivArray(div, N_Data, avg_bmi, bmi); // 配列divにポインタ渡し
	
	double sum_rate = 0; // 合計割合のメモ

	for (i = 0; i < 5; i++)
	{
		double div_rate = div[i]; // 浮動小数点数に変換
		div_rate = div_rate / N_Data * 100;


		printf("%s\t\t\t%.2f\n", pattern[i], div_rate); // 体型別割合の表示
		fprintf(fp2, "%s,,,%.2f\n", pattern[i], div_rate); // csvに体型別割合の書き込み

		sum_rate += div_rate;
	}

	printf("%s\t\t\t\t%.f\n", pattern[i], sum_rate); // 合計割合の表示
	fprintf(fp2, "%s,,,%.f\n", pattern[i], sum_rate); // csvに合計割合の書き込み


	fclose(fp2); //ファイルクローズ

	return 0;
}