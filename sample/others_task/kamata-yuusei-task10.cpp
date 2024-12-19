//学籍番号　1201201038
//ポータルID　seb01038
//氏名　鎌田祐誠
//プログラム名　kamata_yuusei_task10.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

FILE *fp;

int main(void)
{

	fopen_s(&fp, "kamata_yuusei_task10.csv", "a");

	double ramda = 0.4;
	double myu = 0.2;
	int s = 3;
	double T = 0.0;
	double delta_t = 0.0;

	printf("シミュレーション時間Tを実数値で入力してください。→");
	scanf_s("%.2f", &T);
	printf("\n時間の刻みdelta_tを実数値で入力してください。→");
	scanf_s("%.2f", &delta_t);

	printf("客の平均到着率 ramda = %.1f\nATM機1台当たりの平均サービス率 myu = %.1f\nATM機の設置台数 s = %d\n", ramda, myu, s);
	fprintf(fp, "客の平均到着率 ramda = %.1f\nATM機1台当たりの平均サービス率 myu = %.1f\nATM機の設置台数 s %d\n", ramda, myu, s);

	int q = 0;	   //客の到着の有無を確認する変数の定義
	int sum_q = 0; // 客の到着人数をカウントする変数の定義

	srand((unsigned int)time(NULL));

	double u, ca, ca_time; // 分布関数値，客の到着時間間隔と客の到着時間を格納する変数の定義

	u = (double)(rand() + 1) / (double)(RAND_MAX + 1);

	ca = (-1.0 / ramda) * log(u);

	ca_time = ca;

	int *sv; // ATM機s 台の空き状況を記録する一次元配列sv の定義と0 に初期化

	sv = (int *)malloc((s + 1) * sizeof(int));

	int win;

	for (win = 0; win < (s + 1); win++)
	{ //一次元配列sv [s] の定義-- AT M機s 台が全て空きとする0  に初期設定
		sv[win] = 0;
	}

	int sq = 0; // 客のサービス窓口の割当有無をチェックする変数定義と0に初期化

	double st_win; //客が割り当てられた各ATM機のサービス時間を格納する変数の定義

	double *stime; //客が割り当てられた各ATM機のサービス終了時間を格納する配列の定義と初期化

	stime = (double *)malloc((s + 1) * sizeof(double));

	for (win = 0; win < (s + 1); win++)
	{ //
		stime[win] = 0;
	}

	int fsq = 0;

	double t; //  現在のシミュレーション時間を格納する変数の定義

	for (t = 0.0; t <= T; t = t + delta_t)
	{

		if (t >= ca_time)
		{
			q = 1;
			sum_q = sum_q + 1;

			u = (double)(rand() + 1) / (double)(RAND_MAX + 1);

			ca = (-1.0 / ramda) * log(u);

			ca_time = ca + t;
		}

		for (win = 1; win < (s + 1); win++)
		{
			if (q = 1)
			{
				if (sv[win] = 0)
				{

					sv[win] = 1;
					sq = 1;
					q = 0;

					u = (double)(rand() + 1) / (double)(RAND_MAX + 1);

					st_win = (-1.0 / myu) * log(u);

					stime[win] = st_win + t; //客が割り当てられたATM機win のサービス終了時間の算出
				}
			}

			if (sq = 1)
			{
				if (stime[win] <= t + delta_t)
				{

					sv[win] = 0;

					stime[win] = 0.0;

					sq = 0;

					fsq = fsq + 1;
				}
			}
		}
	}

	double act_ro;

	act_ro = sum_q / fsq;

	printf("\n\nシミュレーション時間 T = %.1fまでの客の到着総数 sum_q = %d\n\nシミュレーション時間T = %.1f までのATM機設置台数３台でサービスを終了した客の総数 fsq = %d\n\n", T, sum_q, T, fsq);
	fprintf(fp, "\n\nシミュレーション時間 T = %.1fまでの客の到着総数 sum_q = %d\n\nシミュレーション時間T = %.1f までのATM機設置台数３台でサービスを終了した客の総数 fsq = %d\n\n", T, sum_q, T, fsq);

	printf("到着客に対するサービス率 act_ro= %lf\n\n", act_ro);
	fprintf(fp, "到着客に対するサービス率 act_ro= %lf\n\n", act_ro);

	free(sv);
	free(stime);

	return (0);
}