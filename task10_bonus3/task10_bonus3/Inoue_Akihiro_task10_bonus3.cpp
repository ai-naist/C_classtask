// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task10_bonus3.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>

const double UOM = 1.0; // 測定単位 : Unit of Measure の 略

// ポインタと型を指定してメモリの確保と初期化を行うマクロ
#define GetArray(ptr, type, N)                                                  \
	{                                                                           \
		ptr = (type *)calloc((N), sizeof(type));                                \
		if (ptr == NULL)                                                        \
		{                                                                       \
			printf("%s 型の配列 %s のメモリを確保できません。\n", #type, #ptr); \
			exit(EXIT_FAILURE);                                                 \
		}                                                                       \
	}

// メモリ開放したあとNULLクリアするマクロ
#define free_null(ptr) \
	{                  \
		free(ptr);     \
		ptr = NULL;    \
	}

FILE *fp; // CSV出力用

// switch-case の分岐用
enum PRN_Type
{
	UniformRN = 1,
	NormalRN,
	ExpRN,
	PoissonRN
};

// プロトタイプ宣言
inline double Uni(const int);
inline double Normal(const char *);
void InputAB(double *, double *);
void InputMuSig(double *, double *);
void Generate_U_RN(const int, const double, const double, double *);
void Generate_N_RN(const int, const double, const double, double *);
void Generate_Exp_RN(const int, const double, double *);
void Generate_Poisson_RN(const int, const double, double *);
void CulcData(const int, double *, double *, double *, double *, double *, double *, double *);
void OutputData(const int, const int, const double, const double, const double, const double, const double,
				double *, double *, double *, double *, double *, double *, double *);
void OutputFreq(const int, const int, const double, const double *, const double *, const double *, int *, int *, double *, double *);
void CreateRN(const int, double *, double *, double *, double *, double *, double *, int *);

int main(void)
{
	srand((unsigned int)time(NULL));
	//srand(123); // 動作検証用

	// fp オープン aモード
	if (fopen_s(&fp, "Inoue_Akihiro_task10_bonus3.csv", "a") != 0)
		exit(EXIT_FAILURE);

	int N; // 乱数の生成数
	do
	{
		printf("乱数の生成数 N を 整数値で指定して下さい ---> ");
		scanf_s("%d", &N);
	} while (N % 2 == 1); // 偶数指定

	double *x;
	GetArray(x, double, N);

	double a, b;	   // 一様乱数の範囲
	double mu, sigma;  // 正規乱数の初期条件（真値）
	double lambda;	   // 事象の平均発生数
	int choice;		   // 乱数の型（ 1 : 一様乱数	2 : 正規乱数 ）
	bool check = true; // 乱数の型選択ループ用

	// 乱数の型を選択して生成
	CreateRN(N, &a, &b, &mu, &sigma, &lambda, x, &choice);

	double xmax = -DBL_MAX; // 最大値
	double xmin = DBL_MAX;	// 最小値
	double sum = 0;			// 和
	double avx = 0;			// 平均
	double vx = 0;			// 分散
	double sx = 0;			// 標準偏差

	// 乱数のデータを計算
	CulcData(N, &xmax, &xmin, &sum, &avx, &vx, &sx, x);

	// 乱数の型で分岐してタイトルと、乱数のデータを出力
	OutputData(N, choice, a, b, mu, sigma, lambda, &xmax, &xmin, &sum, &avx, &vx, &sx, x);

	int k; // 級の数
	printf("\n級の数 k を 整数値 で 指定して下さい ---> ");
	scanf_s("%d", &k);

	// 級の区間幅 h の設定
	double h = ceil((xmax - xmin) / (double)k);

	double *x_interval; // 級の区間値
	GetArray(x_interval, double, k + 1);
	x_interval[0] = xmin - (UOM / 2);		   // データ区間の下限値設定
	for (int i = 1; i < k + 1; i++)			   //
		x_interval[i] = x_interval[i - 1] + h; // 各級のデータ区間値の設定

	double *x_midval; // 区間の真ん中の値
	GetArray(x_midval, double, k);
	for (int i = 0; i < k; i++)
		x_midval[i] = (x_interval[i] + x_interval[i + 1]) / 2;

	int *freq;			  // 度数
	int *cum_freq;		  // 累積度数
	double *rel_freq;	  // 相対度数
	double *cum_rel_freq; // 累積相対度数

	GetArray(freq, int, k);
	GetArray(cum_freq, int, k);
	GetArray(rel_freq, double, k);
	GetArray(cum_rel_freq, double, k);

	// 級の表示と度数テーブルの出力
	OutputFreq(N, k, h, x, x_interval, x_midval, freq, cum_freq, rel_freq, cum_rel_freq);

	// ファイルクローズ
	fclose(fp);
	// メモリ解放
	free_null(x);
	free_null(x_interval);
	free_null(x_midval);
	free_null(freq);
	free_null(rel_freq);
	free_null(cum_freq);
	free_null(cum_rel_freq);

	return 0;
}

// 一様乱数の計算
inline double Uni(const int d)
{
	return ((double)rand() + d) / ((double)RAND_MAX + d);
}

// 正規乱数生成の計算
inline double Normal(const char *tri)
{
	if (strcmp(tri, "sin") == 0)
		return sqrt(-2.0 * log(Uni(1))) * sin(2.0 * M_PI * Uni(1));
	else if (strcmp(tri, "cos") == 0)
		return sqrt(-2.0 * log(Uni(1))) * cos(2.0 * M_PI * Uni(1));
	else
		exit(EXIT_FAILURE);
}

// 指数乱数生成の計算
inline double ExpRand(const double lambda)
{
	return (-1.0 / (lambda)) * log(Uni(1));
}

// 範囲[a,b]の入力
void InputAB(double *p_a, double *p_b)
{
	do
	{
		do
		{
			printf("\n実数型一様乱数の範囲 [ a , b ] を指定して下さい\n"
				   "a ---> ");
			scanf_s("%lf", p_a);
		} while (*p_a < 1.0);
		printf("b ---> ");
		scanf_s("%lf", p_b);
	} while (*p_a > *p_b); // 1.0 ≦ a ＜ b の条件指定入力
}

// 平均 μ と 標準偏差 σ の入力
void InputMuSig(double *p_mu, double *p_sigma)
{
	do
	{
		printf("\n正規乱数の平均 μ と 標準偏差 σ を指定して下さい\n"
			   "μ ---> ");
		scanf_s("%lf", p_mu);
		printf("σ ---> ");
		scanf_s("%lf", p_sigma);
	} while ((*p_mu - 3 * (*p_sigma)) <= 0); // μ > 3σ の条件指定入力
}

void InputExpLambda(double *p_lambda)
{
	printf("\n指数乱数の生成に対する事象の平均発生率 lambda を指定してください\n"
		   "lambda ---> ");
	scanf_s("%lf", p_lambda);
}

void InputPoissonLambda(double *p_lambda)
{
	printf("\nポアソン乱数の生成に対する事象の平均発生率 lambda を指定してください\n"
		   "lambda ---> ");
	scanf_s("%lf", p_lambda);
}

// 一様乱数を生成
void Generate_U_RN(const int N, const double a, const double b, double *x)
{
	// 範囲[a,b]の実数型一様乱数を N 個生成
	for (int i = 0; i < N; i++)
		x[i] = a + (b - a) * Uni(0);
}

// 正規乱数を生成
void Generate_N_RN(const int N, const double mu, const double sigma, double *x)
{
	// 平均 μ と 標準偏差 σ の正規分布に従う正規乱数 (ボックス・ミュラー法)を N 個生成
	for (int i = 0; i < N; i = i + 2)
	{
		x[i] = mu + sigma * Normal("cos");
		x[i + 1] = mu + sigma * Normal("sin");
	}
}

// 指数乱数を生成
void Generate_Exp_RN(const int N, const double lambda, double *x)
{
	for (int i = 0; i < N; i++)
	{
		x[i] = ExpRand(lambda);
	}
}

// ポアソン乱数を生成
void Generate_Poisson_RN(const int N, const double lambda, double *x)
{
	for (int i = 0; i < N; i++)
	{
		double sum_ti = 0.0;
		int j = 0;
		for (; sum_ti < 1; j++)
			sum_ti += ExpRand(lambda);

		x[i] = --j;
	}
}

// 乱数のデータを計算
void CulcData(const int N, double *pmax, double *pmin, double *psum, double *pavx, double *pvx, double *psx, double *x)
{
	for (int i = 0; i < N; i++)
	{
		// 和
		*psum += x[i];
		// 最大値
		if (*pmax < x[i])
			*pmax = x[i];
		// 最小値
		if (*pmin > x[i])
			*pmin = x[i];
	}
	// 平均値
	*pavx = *psum / N;
	// 分散
	for (int i = 0; i < N; i++)
		*pvx += pow((x[i] - *pavx), 2);
	*pvx = *pvx / N;
	// 標準偏差
	*psx = sqrt(*pvx);
}

// 乱数の型で分岐してタイトルと、乱数のデータテーブルを出力
void OutputData(const int N, const int choice, const double a, const double b, const double mu, const double sigma, const double lambda,
				double *pmax, double *pmin, double *psum, double *pavx, double *pvx, double *psx, double *x)
{
	switch (choice)
	{
	case UniformRN:
		printf("\n実数型一様乱数データの統計処理結果\n"
			   "\nデータ範囲\ta\tb\n"
			   "\t\t%g\t%g\n\n",
			   a, b);
		fprintf(fp, "実数型一様乱数データの統計処理結果\n"
					"\nデータ範囲,a,b\n"
					",%g,%g\n\n",
				a, b);
		break;

	case NormalRN:
		printf("\n正規乱数データの統計処理結果\n"
			   "\n正規分布\t平均\t標準偏差\n"
			   "真の値\t\t%g\t%g\n\n",
			   mu, sigma);
		fprintf(fp, "正規乱数データの統計処理結果\n"
					"\n正規分布,平均,標準偏差\n"
					"真の値,%g,%g\n\n",
				mu, sigma);
		break;

	case ExpRN:
		printf("\n指数乱数データの統計処理結果\n"
			   "\n事象の平均発生率\t%g\n"
			   "事象の平均発生間隔\t%g\n",
			   lambda, 1 / lambda);
		fprintf(fp, "\n指数乱数データの統計処理結果\n"
					"\n事象の平均発生率,%g\n"
					"事象の平均発生間隔,%g\n",
				lambda, 1 / lambda);
		break;

	case PoissonRN:
		printf("\nポアソン乱数データの統計処理結果\n"
			   "\n事象の平均発生数\t%g\n",
			   lambda);
		fprintf(fp, "\nポアソン乱数データの統計処理結果\n"
					"\n事象の平均発生数,%g\n",
				lambda);
		break;
	}

	// データ情報テーブル
	printf("データ数\t\t%d\n"
		   "データの平均\t\t%lf\n"
		   "データの不偏分散\t%lf\n"
		   "データの標準偏差\t%lf\n"
		   "データの最大値\t\t%lf\n"
		   "データの最小値\t\t%lf\n",
		   N, *pavx, *pvx, *psx, *pmax, *pmin);
	fprintf(fp, "データ数,%d\n"
				"データの平均,%lf\n"
				"データの不偏分散,%lf\n"
				"データの標準偏差,%lf\n"
				"データの最大値,%lf\n"
				"データの最小値,%lf\n",
			N, *pavx, *pvx, *psx, *pmax, *pmin);
}

// 度数テーブルの出力
void OutputFreq(const int N, const int k, const double h, const double *x, const double *x_interval, const double *x_midval,
				int *freq, int *cum_freq, double *rel_freq, double *cum_rel_freq)
{
	// 級の表示と度数テーブルのタイトル
	printf("\n級の数\t\t%d\n"
		   "級の区間幅\t%g\n"
		   "\nデータ区間\t\t\t中間の値\t度数\t累積度数\t相対度数\t累積相対度数\n",
		   k, h);
	fprintf(fp, "\n級の数,%d\n"
				"級の区間幅,%g\n"
				"\nデータ区間,中間の値,度数,累積度数,相対度数,累積相対度数\n",
			k, h);

	int temp_freq = 0;			// 累積度数の一時記憶
	for (int i = 0; i < k; i++) // 級の更新
	{
		for (int j = 0; j < N; j++) // データの検索
		{
			if ((x_interval[i] <= x[j]) && (x[j] < x_interval[i + 1]))
				freq[i]++; // 現在の級にある数値をカウント（度数）
		}
		cum_freq[i] = temp_freq + freq[i];				   // 累積度数
		rel_freq[i] = (double)freq[i] / (double)N;		   // 相対度数の算出
		cum_rel_freq[i] = (double)cum_freq[i] / (double)N; // 累積相対度数の算出
		temp_freq = cum_freq[i];						   // 累積度数の更新用

		// 度数テーブルの出力
		printf("%lf － %lf\t%lf\t%d\t%d\t\t%lf\t%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
		fprintf(fp, "%lf － %lf,%lf,%d,%d,%lf,%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
	}
	// 累計の出力
	printf("\t\t\t\t\t\t累計\t%d\t\t累計\t\t%g\n", cum_freq[k - 1], cum_rel_freq[k - 1]);
	fprintf(fp, ",,累計,%d,累計,%g\n\n", cum_freq[k - 1], cum_rel_freq[k - 1]);
}

// 乱数の型を選択して生成
void CreateRN(const int N, double *p_a, double *p_b, double *p_mu, double *p_sigma, double *p_lambda, double *x, int *pchoice)
{
	bool check = true;
	do
	{
		printf("\n1 : 範囲[a,b]の実数型一様乱数の生成\n"			  // Uniform Random Number
			   "\n2 : 平均 μ と 標準偏差 σ の正規乱数の生成\n"		  // Normal Random Number
			   "\n3 : 事象の平均発生時間間隔 1 / lambda の指数乱数\n" // Exponential Random Number
			   "\n4 : 事象の平均発生数 lambda のポアソン乱数\n"		  // Poisson Random Number
			   "\n生成する乱数の選択番号を 1 ～ 4 より 1 つ入力下さい. ---> ");
		scanf_s("%d", pchoice);

		// 乱数の型で条件分岐して、擬似乱数生成
		switch (*pchoice)
		{
		case UniformRN:
			InputAB(p_a, p_b);
			Generate_U_RN(N, *p_a, *p_b, x);
			check = false;
			break;

		case NormalRN:
			InputMuSig(p_mu, p_sigma);
			Generate_N_RN(N, *p_mu, *p_sigma, x);
			check = false;
			break;

		case ExpRN:
			InputExpLambda(p_lambda);
			Generate_Exp_RN(N, *p_lambda, x);
			check = false;
			break;

		case PoissonRN:
			InputPoissonLambda(p_lambda);
			Generate_Poisson_RN(N, *p_lambda, x);
			check = false;
			break;

		default:
			printf("\n選択番号に誤りがあります．再度，選択番号を入力しなおして下さい．\n");
		}
	} while (check);
}