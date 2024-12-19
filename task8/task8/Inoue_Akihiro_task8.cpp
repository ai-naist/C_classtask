// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue_Akihiro_task8.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // 数値演算定数
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>

// 2都市間距離を算出するマクロ
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// メモリ開放したあとNULLクリアするマクロ
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

// ファイルポインタ
FILE *fp1, *fp2, *fp3; // fp1:乱数生成した都市座標の一次保存用　fp2:都市座標の読み込み用　fp3:結果出力用

// x座標とy座標を構造体で定義
typedef struct
{
    int num;  // 都市番号
    double x; // x座標
    double y; // y座標
} CityInfo_t;

int main(void)
{
    // §1 都市の座標範囲[a,b]を指定　その範囲でN個の座標を乱数で取得　取得した座標を citydata_info.csv に出力
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

    // fp1を書き込みモードでオープン
    if (fopen_s(&fp1, "citydata_info.csv", "w") != 0)
        exit(EXIT_FAILURE); // エラー処理

    srand((unsigned int)time(NULL)); // シード値time(NULL)で乱数系列の生成
    //srand(123); // 動作検証用

    for (int n = 1; n <= N; n++)
    {
        //　座標(x,y)を[a,b]での乱数に置き換えて取得
        double x_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        double y_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);

        // citydata_info.csv に出力
        fprintf(fp1, "%d,%lf,%lf\n", n, x_point, y_point);
    }
    fclose(fp1); // ファイルクローズ
    // §1 おわり

    // §2 構造体配列を citydata_info.csv から読み込んだ値で書き換え　メンバの値を Inoue_Akihiro_task8.csv に出力
    CityInfo_t *cityinfodata;                                       // 構造体型配列の先頭要素へのポインタ
    cityinfodata = (CityInfo_t *)calloc(N + 1, sizeof(CityInfo_t)); // メモリの確保(ポインタが指すアドレスを[0]～[N+1]まで割り当てる)
    /*  calloc(個数,メモリサイズ) は 指定したサイズで確保したメモリの先頭アドレスをvoid型へのポインタで返し、割り当てられた要素を0クリアする
        (CityInfo_t *) でtypedefされた構造体型へのポインタにキャストして返している
        ポインタ cityinfodata に割り当てられたアドレスを指定することで配列として扱える   */
    if (cityinfodata == NULL)
    {
        // エラー処理
        printf("構造体型配列のメモリを確保できません。\n");
        exit(EXIT_FAILURE);
    }

    // fp2を読み取りモードでオープン
    if (fopen_s(&fp2, "citydata_info.csv", "r") != 0)
        exit(EXIT_FAILURE); // エラー処理

    // fp3を書き込みモードでオープン
    if (fopen_s(&fp3, "Inoue_Akihiro_task8.csv", "w") != 0)
        exit(EXIT_FAILURE); // エラー処理

    // タイトルの出力
    printf("\n都市番号\tx座標\t\ty座標\n");
    fprintf(fp3, "都市番号,x座標,y座標\n");

    // メンバの値(都市番号、x座標、y座標)を citydata_info.csv から読み込み、 Inoue_Akihiro_task8.csv に書き込み
    int n = 1;
    while ((fscanf_s(fp2, "%d,%lf,%lf", &cityinfodata[n].num, &cityinfodata[n].x, &cityinfodata[n].y)) != EOF)
    {
        // 読み込んだメンバを出力
        printf("%d\t\t%lf\t%lf\n", cityinfodata[n].num, cityinfodata[n].x, cityinfodata[n].y);
        fprintf(fp3, "%d,%lf,%lf\n", cityinfodata[n].num, cityinfodata[n].x, cityinfodata[n].y);
        n++;
    }
    fclose(fp2); // ファイルクローズ
    // §2 おわり

    // §3 都市番号と訪問順序番号をメモする配列を定義
    // 配列 z[都市番号] = その都市の訪問順序番号(全体で何番目に訪問する都市か)　初期値0はその都市が未訪問を表す
    int *z;                                // 配列の先頭要素へのポインタ
    z = (int *)calloc(N + 1, sizeof(int)); // メモリの確保(アドレスの割り当て)
    if (z == NULL)
    {
        // エラー処理
        printf("一次元配列 z のメモリを確保できません。\n");
        exit(EXIT_FAILURE);
    }

    // 配列 zz[訪問順序番号] = 都市番号　初期値0はその順序番号で訪問する都市が未定を表す
    int *zz;                                // 配列の先頭要素へのポインタ
    zz = (int *)calloc(N + 1, sizeof(int)); // メモリの確保(アドレスの割り当て)
    if (zz == NULL)
    {
        // エラー処理
        printf("一次元配列 zz のメモリを確保できません。\n");
        exit(EXIT_FAILURE);
    }
    // §3 おわり

    // §4 出発都市を入力で取得　最近隣法で経路探索　探索経過の出力　探索時間の計測
    // 出発都市を入力
    int start;
    do
    {
        printf("\n最初の出発都市 start を都市番号 1 ～ %d より指定して下さい。---> ", N);
        scanf_s("%d", &start);
    } while ((start <= 0) || (start > N)); // 不正な値の回避

    // 探索時間計測の開始
    clock_t begin = clock();

    int i;     // 現在の都市番号
    i = start; // 出発都市番号 start で初期化

    double dij;                 // 2都市間距離
    double totaldistance = 0.0; // 総移動距離

    int k = 1; // 訪問順序
    z[i] = k;  // 都市に対応する順序
    zz[k] = i; // 順序に対応する都市

    int next = 0;

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
                dij = distance_func(cityinfodata[i].x, cityinfodata[j].x, cityinfodata[i].y, cityinfodata[j].y);

                if (dij < min)
                {
                    min = dij;
                    next = j; // 都市番号のメモ
                }
            }
        }

        z[next] = k;  // 次の訪問都市の決定
        zz[k] = next; // 順序に対応する都市

        totaldistance += min;

        // 途中結果の出力
        printf("%d\t%d\t%d\t%lf\t%lf\n", k, i, next, min, totaldistance);
        fprintf(fp3, "%d,%d,%d,%lf,%lf\n", k, i, next, min, totaldistance);

        i = next; // 現在都市の更新
    }

    // 最終到達都市から出発都市へ戻る距離の計算
    dij = distance_func(cityinfodata[i].x, cityinfodata[start].x, cityinfodata[i].y, cityinfodata[start].y);
    totaldistance += dij;

    // 途中結果の出力
    printf("\t%d\t%d\t%lf\t%lf\n", i, start, dij, totaldistance);
    fprintf(fp3, ",%d,%d,%lf,%lf\n", i, start, dij, totaldistance);

    // 探索時間計測の終わり
    clock_t end = clock();
    // §4 おわり

    // §5 探索結果と探索処理時間の出力
    // 都市番号昇順
    printf("\n都市番号\t訪問順序\n");
    fprintf(fp3, "\n都市番号,訪問順序\n");
    for (int l = 1; l <= N; l++)
    {
        printf("%d\t\t%d\n", l, z[l]);
        fprintf(fp3, "%d,%d\n", l, z[l]);
    }

    // 訪問順序昇順
    printf("\n訪問順序\t都市番号\n");
    fprintf(fp3, "\n訪問順序,都市番号\n");
    for (int l = 1; l <= N; l++)
    {
        printf("%d\t\t%d\n", l, zz[l]);
        fprintf(fp3, "%d,%d\n", l, zz[l]);
    }

    // 総移動距離の出力
    printf("\n総移動距離\t%lf\n", totaldistance);
    fprintf(fp3, "\n総移動距離,%lf\n", totaldistance);

    // 処理経過時間の出力
    printf("\n探索処理時間\t%lf 秒\n", ((double)end - (double)begin) / CLOCKS_PER_SEC);
    fprintf(fp3, "\n探索処理時間,%lf 秒\n", ((double)end - (double)begin) / CLOCKS_PER_SEC);

    fclose(fp3); // ファイルクローズ
    // §5 おわり

    // メモリ解放
    free_null(cityinfodata);
    free_null(z);
    free_null(zz);

    return 0;
}
