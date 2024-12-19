// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task10.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdbool.h>

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
#define FreeNull(ptr) \
    {                 \
        free(ptr);    \
        ptr = NULL;   \
    }

#define ExpRand(mu) (-1.0 / (mu)) * log(((double)rand() + 1) / ((double)RAND_MAX + 1))

#define ARGS_OUTPROGRESS occupied, S, temp_q, t, sum_q, sum_fin_q, fin_time

void Output_Progress(bool *, int, int, double, int, int, double *);

int main(void)
{
    //srand((unsigned int)time(NULL));
    srand(123); // 動作検証用

    int S;              // サービス窓口数
    double ArrivalRate; // 到着率
    double ServiceRate; // サービス率
    double T;           // シミュレーション時間
    double DeltaT;      // 更新時間幅

    // 諸値の入力
    printf("客の平均到着率( 客の到着人数/ 単位時間(分)) lambda を実数値で入力して下さい。-->");
    scanf_s("%lf", &ArrivalRate);
    printf("ATM 機の平均サービス率(1つの窓口の客へのサービス(終了)数 / 単位時間(分)) mu を実数値で入力して下さい。-- >");
    scanf_s("%lf", &ServiceRate);
    printf("ATM 機の設置台数(サービス窓口数) s を整数値で入力して下さい。-- >");
    scanf_s("%d", &S);
    printf("シミュレーション時間 T を実数値で入力して下さい。-- >");
    scanf_s("%lf", &T);
    printf("時間刻み delta_t を実数値で入力して下さい。-- >");
    scanf_s("%lf", &DeltaT);

    // 実行条件の出力
    printf("\n客の平均到着率 lambda = %g\n"
           "ATM 機 1台当たりの平均サービス率 mu = %g\n"
           "ATM 機設置台数 s = %d\n\n",
           ArrivalRate, ServiceRate, S);

    bool sq = false;
    bool q = false;
    int temp_q = 0;              // 現在の待ち客数
    int sum_q = 0;               // 来客総数
    int num_teller;              // 客を割り当てる窓口番号
    int sum_fin_q = 0;           // サービス完了総数
    double t = 0.0;              // 現在時刻
    double ca_time = 0.0;        // 次の客の到着時刻
    double *fin_time;            // 各窓口のサービス完了時刻
    double wait_time = 0.0;      // 待ち時間
    double operation_rate = 0.0; // 稼働率
    bool available = false;      // 窓口の利用可否
    bool *occupied;              // 各窓口の使用状況

    GetArray(occupied, bool, S + 1); // すべて 偽値（0）で初期化
    GetArray(fin_time, double, S + 1);

    ca_time += ExpRand(ArrivalRate);
    // シミュレーションの実行
    for (double t = 0.0; t <= T; t += DeltaT)
    {
        // 客の到着処理
        if (t >= ca_time)
        {
            ca_time = t + ExpRand(ArrivalRate);
            sum_q++;
            temp_q++;
            q = true;

            printf("+ ");
            Output_Progress(ARGS_OUTPROGRESS);
        }

        // 待ち客 0 のときは処理をスキップ
        if (temp_q > 0)
        {

            for (int i = 1; i <= S; i++)
            {
                // サービスの空き状況を確認
                if (q && !occupied[i])
                {
                    fin_time[i] = t + ExpRand(ServiceRate);
                    occupied[i] = true;
                    temp_q--;
                    q = false;
                    sq = true;

                    printf("- ");
                    Output_Progress(ARGS_OUTPROGRESS);
                }
            }
        }

        // サービスの終了確認
        for (int i = 1; i <= S; i++)
        {
            if ((fin_time[i] <= t + DeltaT) && sq)
            {
                occupied[i] = false;
                fin_time[i] = 0;
                sum_fin_q++;
                sq = false;

                printf("# ");
                Output_Progress(ARGS_OUTPROGRESS);
            }
            if (occupied[i])
                operation_rate++;
        }
        wait_time += DeltaT * temp_q;
    }
    wait_time = wait_time / sum_q;
    operation_rate = operation_rate / (S * T / DeltaT) * 100;

    // サービス率
    double cmprate = (double)sum_fin_q / sum_q;

    // 結果の出力
    printf("シミュレーション時間 T = %g までの客の到着総数 sum_q = %d\n\n"
           "シミュレーション時間 T = %g までのATM機設置台数3 台でサービスを終了した客の総数 sum_fin_q = %d\n\n"
           "到着客に対するサービス率( サービスを終了した客の総数/ 客の到着総数) act_ro = %lf\n\n"
           "平均待ち時間 %lf\n\n"
           "稼働率 %lf ％\n\n",
           T, sum_q, T, sum_fin_q, cmprate, wait_time, operation_rate);

    // メモリ解放
    FreeNull(fin_time);
    FreeNull(occupied);

    return 0;
}

void Output_Progress(bool *occupied, int S, int temp_q, double t, int sum_q, int fsq, double *fin_time)
{
    printf(" %.1f \t%d\t%d\t", t, sum_q, fsq);
    for (int j = 1; j <= S; j++)
        printf("%.1f\t", fin_time[j]);
    for (int j = 0; j < temp_q; j++)
        printf("|");
    printf("\n");
}