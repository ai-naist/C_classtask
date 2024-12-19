// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task8_bonus2.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

// 2都市間距離を算出するマクロ
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// ポインタと型を指定してメモリの確保と初期化を行うマクロ
#define get_array(ptr, type, N)                                                 \
    {                                                                           \
        ptr = (type *)calloc((N) + 1, sizeof(type));                            \
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

FILE *fp3; // 結果出力用

// x座標とy座標を構造体で定義
typedef struct
{
    int num;  // 都市番号
    double x; // x座標
    double y; // y座標
} CityInfo_t;

/**************
プロトタイプ宣言
***************/
void generate_data(const double, const double, const int);
void read_data(CityInfo_t *);
inline void nearest_TSP(const int, const int, const CityInfo_t *, int *, int *, double *);
inline void add_opt2_dis(const int, const int, double *, double *, const CityInfo_t *, const int *);
void opt2_TSP(bool *, const int, double *, const CityInfo_t *, int *, int *);
/*
型名[] は、配列であることを明示的にするが、内部的には 型名* と同義で、配列の先頭要素へのポインタである
const 型名* はポインタを介した参照先を、型名 *const はポインタ変数を、それぞれ書き換え禁止にする    
ただし、前者はポインタ経由でなければ、ポインタの指す値を書き換え可能である
*/

int main(void)
{
    /*  §1
    都市の座標範囲[a,b]を指定
    その範囲でN個の座標を乱数で取得
    取得した座標を citydata_info.csv に出力
    */
    double a, b;
    int N;
    // a,b,N の入力
    printf("訪問都市の位置座標 x 座標と y 座標の範囲( 下限 a , 上限 b )の設定について\n"
           "範囲 の下限 a を指定して下さい。 --- > ");
    scanf_s("%lf", &a);
    printf("範囲 の上限 b を指定して下さい。 --- > ");
    scanf_s("%lf", &b);
    do
    {
        printf("訪問都市数 N を指定して下さい. 。--- > ");
        scanf_s("%d", &N);
    } while ((N <= 0) || (N > INT_MAX)); // 不正な値の回避

    // 範囲[a,b]で乱数生成したN個の都市座標を citydata_info.csv に出力
    generate_data(a, b, N);
    // §1   -----おわり-----

    /*  §2
    構造体配列を citydata_info.csv から読み込んだ値で書き換え
    メンバの値を Inoue_Akihiro_task8_bonus1.csv に出力
    */
    CityInfo_t *cityinfodata;               // 構造体型配列の先頭要素へのポインタ
    get_array(cityinfodata, CityInfo_t, N); // メモリの確保と初期化

    // fp3を書き込みモードでオープン
    if (fopen_s(&fp3, "Inoue_Akihiro_task8_bonus2.csv", "w") != 0)
        exit(EXIT_FAILURE); // エラー処理

    // タイトルの出力
    printf("\n都市番号\tx座標\t\ty座標\n");
    fprintf(fp3, "都市番号,x座標,y座標\n");

    read_data(cityinfodata);
    fclose(fp3); // ファイルクローズ
    // §2   -----おわり-----

    /*  §3 
    都市番号と訪問順序番号をメモする配列を定義
    */
    // 配列 z[都市番号] = その都市の訪問順序番号(全体で何番目に訪問する都市か)　初期値0はその都市が未訪問を表す
    int *z;               // 配列の先頭要素へのポインタ
    get_array(z, int, N); // メモリの確保と初期化

    // 配列 zz[訪問順序番号] = 都市番号　初期値0はその順序番号で訪問する都市が未定を表す
    int *zz;               // 配列の先頭要素へのポインタ
    get_array(zz, int, N); // メモリの確保と初期化
    // §3   -----おわり-----

    /*  §4 
    出発都市を入力で取得　
    最近隣法で経路探索　
    探索経過の出力　
    探索時間の計測
    */
    // 出発都市を入力
    int start;
    do
    {
        printf("\n最初の出発都市 start を都市番号 1 ～ %d より指定して下さい。---> ", N);
        scanf_s("%d", &start);
    } while ((start <= 0) || (start > N)); // 不正な値の回避

    double totaldistance = 0.0; // 総移動距離

    // 探索時間計測の開始
    clock_t begin = clock();

    nearest_TSP(N, start, cityinfodata, z, zz, &totaldistance);
    // §4   -----おわり-----

    /*  §5
    最近隣法による探索結果、都市番号、訪問順序の出力
    */
    // fp3を追加書き込みモードでオープン
    if (fopen_s(&fp3, "Inoue_Akihiro_task8_bonus2.csv", "a") != 0)
        exit(EXIT_FAILURE); // エラー処理

    // 都市番号昇順
    printf("\n都市番号\t訪問順序\n");
    fprintf(fp3, "\n都市番号,訪問順序\n");
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%d\n", k, z[k]);
        fprintf(fp3, "%d,%d\n", k, z[k]);
    }

    // 訪問順序昇順
    printf("\n訪問順序\t都市番号\n");
    fprintf(fp3, "\n訪問順序,都市番号\n");
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%d\n", k, zz[k]);
        fprintf(fp3, "%d,%d\n", k, zz[k]);
    }
    // §5   -----おわり-----

    /*  §6
    2opt法の実行
    */
    int *zz_old;
    int *zz_new;
    get_array(zz_old, int, N);
    get_array(zz_new, int, N);

    // 訪問順を最近隣法の結果で初期化
    for (int k = 1; k <= N; k++)
    {
        zz_old[k] = zz[k];
        zz_new[k] = zz[k];
    }

    double tdis_new = totaldistance;
    bool check;
    do
    {
        check = false;
        opt2_TSP(&check, N, &tdis_new, cityinfodata, zz_old, zz_new);
    } while (check); // 改善のチェック

    // 探索時間計測の終わり
    clock_t end = clock();
    // §6   -----おわり-----

    /*  §7
    2opt法の結果出力
    */
    // 巡回経路の出力
    printf("\n\n最近隣法での巡回経路\t\t2opt法での巡回経路\n"
           "*********************************************************\n"
           "訪問順序\t都市番号\t訪問順序\t都市番号\n"
           "*********************************************************\n");
    fprintf(fp3, "\n最近隣法での巡回経路,,2opt法での巡回経路\n"
                 "訪問順序,都市番号,訪問順序,都市番号\n");
    for (int k = 1; k <= N; k++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", k, zz[k], k, zz_new[k]);
        fprintf(fp3, "%d,%d,%d,%d\n", k, zz[k], k, zz_new[k]);
    }

    // 始点と距離の比較
    printf("\n\nstart = %d\ttdis = %lf\ttdis_new = %lf\n", start, totaldistance, tdis_new);
    fprintf(fp3, "\nstart = %d,tdis = %lf,tdis_new = %lf\n", start, totaldistance, tdis_new);

    //　改善度
    double imp_rate = ((totaldistance - tdis_new) / totaldistance) * 100;
    printf("\n改善度 = %lf（％）", imp_rate);
    fprintf(fp3, "\n改善度 = %lf（％）\n", imp_rate);

    // 2opt法での総移動距離の出力
    printf("\n2opt 法適用 総移動距離（改善後）\t%lf\n", tdis_new);
    fprintf(fp3, "\n2opt 法適用,総移動距離（改善後）,%lf\n", tdis_new);

    // 処理経過時間
    double serching_time = ((double)end - (double)begin) / CLOCKS_PER_SEC;
    // 処理経過時間の出力
    printf("\n探索処理時間\t%lf 秒\n", serching_time);
    fprintf(fp3, "\n探索処理時間,%lf 秒\n", serching_time);

    fclose(fp3); // ファイルクローズ
    // §7   -----おわり-----

    // メモリ解放
    free_null(cityinfodata);
    free_null(z);
    free_null(zz);
    free_null(zz_old);
    free_null(zz_new);

    return 0;
}

/**************
ユーザー定義関数
***************/
// 範囲[a,b]で乱数生成したN個の都市座標を citydata_info.csv に出力
void generate_data(const double a, const double b, const int N)
{
    FILE *fp1;
    // fp1を書き込みモードでオープン
    if (fopen_s(&fp1, "citydata_info.csv", "w") != 0)
        exit(EXIT_FAILURE); // エラー処理

    //srand((unsigned int)time(NULL)); // シード値time(NULL)で乱数系列の生成
    srand(65535); // 動作検証用

    for (int n = 1; n <= N; n++)
    {
        //　座標(x,y)を[a,b]での乱数に置き換えて取得
        double x_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        double y_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);

        // citydata_info.csv に出力
        fprintf(fp1, "%d,%lf,%lf\n", n, x_point, y_point);
    }
    fclose(fp1); // ファイルクローズ
}

// citydata_info.csv から構造体配列に読み込み、Inoue_Akihiro_task8_bonus2.csv に書き込む
void read_data(CityInfo_t *const data)
{
    FILE *fp2;
    // fp2を読み取りモードでオープン
    if (fopen_s(&fp2, "citydata_info.csv", "r") != 0)
        exit(EXIT_FAILURE); // エラー処理

    // メンバの値(都市番号、x座標、y座標)を citydata_info.csv から読み込み、 Inoue_Akihiro_task8_bonus2.csv に書き込み
    int n = 1;
    while ((fscanf_s(fp2, "%d,%lf,%lf", &data[n].num, &data[n].x, &data[n].y)) != EOF)
    {
        // 読み込んだメンバを出力
        printf("%d\t\t%lf\t%lf\n", data[n].num, data[n].x, data[n].y);
        fprintf(fp3, "%d,%lf,%lf\n", data[n].num, data[n].x, data[n].y);
        n++;
    }
    fclose(fp2); // ファイルクローズ
}

// 最近隣法で経路探索　探索経過の出力　探索時間の計測
inline void nearest_TSP(const int N, const int start, const CityInfo_t *const data, int *const z, int *const zz, double *const ptdis)
{
    // fp3を追加書き込みモードでオープン
    if (fopen_s(&fp3, "Inoue_Akihiro_task8_bonus2.csv", "a") != 0)
        exit(EXIT_FAILURE); // エラー処理

    int i;            // 現在の都市番号
    int next = 0;     // 次に訪問する都市番号
    int k = 1;        // 訪問順序 1で初期化
    double dij = 0.0; // 2都市間距離

    i = start; // 出発都市番号 start で初期化
    z[i] = k;  // 都市に対応する順序の初期化
    zz[k] = i; // 順序に対応する都市の初期化

    // 結果タイトルの出力
    printf("\nk\ti\tnext\tmin\t\ttdis\n");
    fprintf(fp3, "\nk,i,next,min,tdis\n");

    // 最近隣法による最短移動距離の探索
    for (k = 2; k <= N; k++) // 探索した最も近い都市を次の訪問都市に更新
    {
        double min = DBL_MAX; // 最短移動距離のメモを倍精度浮動小数点数の最大値で初期化

        for (int j = 1; j <= N; j++) // 現在都市から最も近い都市を探索
        {
            if (z[j] == 0)
            {
                // 2都市間距離
                dij = distance_func(data[i].x, data[j].x, data[i].y, data[j].y);

                if (dij < min)
                {
                    min = dij;
                    next = j; // 都市番号のメモ
                }
            }
        }

        z[next] = k;  // 次の訪問都市の決定
        zz[k] = next; // 順序に対応する都市

        *ptdis += min;

        // 途中結果の出力
        printf("%d\t%d\t%d\t%lf\t%lf\n", k, i, next, min, *ptdis);
        fprintf(fp3, "%d,%d,%d,%lf,%lf\n", k, i, next, min, *ptdis);

        i = next; // 現在都市の更新
    }

    // 最終到達都市から出発都市へ戻る距離の計算
    dij = distance_func(data[i].x, data[start].x, data[i].y, data[start].y);
    *ptdis += dij;

    // 途中結果の出力
    printf("\t%d\t%d\t%lf\t%lf\n", i, start, dij, *ptdis);
    fprintf(fp3, ",%d,%d,%lf,%lf\n", i, start, dij, *ptdis);

    fclose(fp3); // ファイルクローズ
}

// 2opt法で入れ替える都市間距離の和を計算する
inline void add_opt2_dis(const int i, const int j, double *pdis_old, double *pdis_new, const CityInfo_t *data, const int *zz)
{
    double i_to_i1 = distance_func(data[zz[i]].x, data[zz[i + 1]].x, data[zz[i]].y, data[zz[i + 1]].y);
    double j_to_j1 = distance_func(data[zz[j]].x, data[zz[j + 1]].x, data[zz[j]].y, data[zz[j + 1]].y);
    *pdis_old = i_to_i1 + j_to_j1;

    double i_to_j = distance_func(data[zz[i]].x, data[zz[j]].x, data[zz[i]].y, data[zz[j]].y);
    double i1_to_j1 = distance_func(data[zz[i + 1]].x, data[zz[j + 1]].x, data[zz[i + 1]].y, data[zz[j + 1]].y);
    *pdis_new = i_to_j + i1_to_j1;
}

// 2opt法で経路を最適化する
void opt2_TSP(bool *pcheck, const int N, double *ptdis_new, const CityInfo_t *data, int *zz_old, int *zz_new)
{
    for (int i = 1; i <= N - 3; i++)
    {
        for (int j = i + 2; j <= N - 1; j++)
        {
            double dis_old;
            double dis_new;
            add_opt2_dis(i, j, &dis_old, &dis_new, data, zz_old);

            if (dis_new < dis_old)
            {
                for (int m = 0; m <= j - (i + 1); m++)
                    zz_new[i + 1 + m] = zz_old[j - m];

                *ptdis_new = *ptdis_new - dis_old + dis_new;

                for (int m = i + 1; m <= j; m++)
                    zz_old[m] = zz_new[m];

                *pcheck = true;
            }
        }
    }
}