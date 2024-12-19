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

// ポインタ変数名、型名、個数を指定してメモリの確保と初期化を行うマクロ
#define get_array(ptr, type, N)                                                 \
    {                                                                           \
        ptr = (type *)calloc((N), sizeof(type));                                \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s 型の配列 %s のメモリを確保できません。\n", #type, #ptr); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    }

// メモリ開放したあとNULLクリアするマクロ
#define free_NULLclear(ptr) \
    {                       \
        free(ptr);          \
        ptr = NULL;         \
    }

#define get_exp_random_number(mu) ((-1.0 / (mu)) * log(((double)rand() + 1) / ((double)RAND_MAX + 1)))

FILE *fp;

int main(void)
{
    srand((unsigned int)time(NULL));
    //srand(123); // 動作検証用

    // fp オープン wモード
    if (fopen_s(&fp, "Inoue_Akihiro_task10.csv", "w") != 0)
        exit(EXIT_FAILURE);

    int ALL_TELLER_NUMBERS; // 窓口の総数
    double ARRIVAL_RATE;    // 到着率
    double SERVICE_RATE;    // サービス率
    double SIMULATION_TIME; // シミュレーション時間
    double TIME_WIDTH;      // 時間刻み幅

    // 諸値の入力
    printf("客の平均到着率( 客の到着人数/ 単位時間(分))lambdaを実数値で入力して下さい。-->");
    scanf_s("%lf", &ARRIVAL_RATE);
    printf("ATM 機の平均サービス率(1つの窓口の客へのサービス(終了)数 / 単位時間(分)) muを実数値で入力して下さい。-- >");
    scanf_s("%lf", &SERVICE_RATE);
    printf("ATM機の設置台数(サービス窓口数) s を整数値で入力して下さい。-- >");
    scanf_s("%d", &ALL_TELLER_NUMBERS);
    printf("シミュレーション時間T を実数値で入力して下さい。-- >");
    scanf_s("%lf", &SIMULATION_TIME);
    printf("時間刻みdelta_t を実数値で入力して下さい。-- >");
    scanf_s("%lf", &TIME_WIDTH);

    // 実行条件の出力
    printf("\n客の平均到着率lambda = %g\n"
           "ATM機1 台当たりの平均サービス率mu = %g\n"
           "ATM機設置台数s = %d\n\n",
           ARRIVAL_RATE, SERVICE_RATE, ALL_TELLER_NUMBERS);
    fprintf(fp, "客の平均到着率lambda = %g\n"
                "ATM機1 台当たりの平均サービス率mu = %g\n"
                "ATM機設置台数s = %d\n\n",
            ARRIVAL_RATE, SERVICE_RATE, ALL_TELLER_NUMBERS);

    int sum_queue = 0;             // 来客総数
    int current_queue = 0;         // 現在の待ち客数
    int sum_completed_service = 0; // サービス完了総数
    double current_time = 0.0;     // 現在時刻
    double arrival_time = 0.0;     // 次の客の到着時刻
    double *completion_time;       // 各窓口のサービス完了時刻
    bool *occupied;                // 各窓口の使用状況

    get_array(occupied, bool, ALL_TELLER_NUMBERS + 1); // すべて 偽値（0）で初期化
    get_array(completion_time, double, ALL_TELLER_NUMBERS + 1);

    // 最初の客の到着時刻の決定
    arrival_time += get_exp_random_number(ARRIVAL_RATE);

    // シミュレーションの実行
    for (double current_time = 0.0; current_time <= SIMULATION_TIME; current_time += TIME_WIDTH)
    {
        // 客の到着処理
        if (arrival_time <= current_time)
        {
            arrival_time += get_exp_random_number(ARRIVAL_RATE);
            sum_queue++;
            current_queue++;
        }

        // サービスの空き状況を確認
        for (int i = 1; i <= ALL_TELLER_NUMBERS; i++)
        {
            if ((current_queue >= 1) && !occupied[i])
            {
                // サービスの割り当て処理
                completion_time[i] = current_time + get_exp_random_number(SERVICE_RATE);
                occupied[i] = true;
                current_queue--;
            }
        }

        // サービスの完了確認
        for (int i = 1; i <= ALL_TELLER_NUMBERS; i++)
        {
            if ((completion_time[i] <= current_time) && occupied[i])
            {
                occupied[i] = false;
                sum_completed_service++;
            }
        }
    }

    // サービス率の計算
    double service_completion_rate = (double)sum_completed_service / sum_queue;

    // 結果の出力
    printf("シミュレーション時間T = %g までの客の到着総数sum_q = %d\n\n"
           "シミュレーション時間T = %g までのATM機設置台数3 台でサービスを終了した客の総数fsq = %d\n\n"
           "到着客に対するサービス率( サービスを終了した客の総数/ 客の到着総数) act_ro = %lf\n\n",
           SIMULATION_TIME, sum_queue, SIMULATION_TIME, sum_completed_service, service_completion_rate);
    fprintf(fp, "シミュレーション時間T = %g までの客の到着総数sum_q = %d\n\n"
                "シミュレーション時間T = %g までのATM機設置台数3 台でサービスを終了した客の総数fsq = %d\n\n"
                "到着客に対するサービス率( サービスを終了した客の総数/ 客の到着総数) act_ro = %lf\n\n",
            SIMULATION_TIME, sum_queue, SIMULATION_TIME, sum_completed_service, service_completion_rate);

    // メモリ解放
    free_NULLclear(completion_time);
    // ファイルクローズ
    fclose(fp);

    return 0;
}