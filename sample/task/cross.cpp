// 最近隣法で交差する経路を回避するアルゴリズム

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

// 2都市間距離を算出するマクロ
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// メモリ開放したあとNULLクリアするマクロ
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

// x座標とy座標を構造体で定義
typedef struct
{
    int num;  // 都市番号
    double x; // x座標
    double y; // y座標
} CityInfo_t;

int main(void)
{

    double a = 0.1;
    double b = 10000.0;
    int N = 20;

    srand(123);

    CityInfo_t *pointdata;
    pointdata = (CityInfo_t *)calloc(N + 1, sizeof(CityInfo_t));

    for (int n = 1; n <= N; n++)
    {
        //　座標(x,y)を[a,b]での乱数に置き換えて取得
        pointdata[n].x = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        pointdata[n].y = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        pointdata[n].num = n;
    }

    int *z;                                // 配列の先頭要素へのポインタ
    z = (int *)calloc(N + 1, sizeof(int)); // メモリの確保(アドレスの割り当て)
    if (z == NULL)
        exit(EXIT_FAILURE);

    int *zz;                                // 配列の先頭要素へのポインタ
    zz = (int *)calloc(N + 1, sizeof(int)); // メモリの確保(アドレスの割り当て)
    if (zz == NULL)
        exit(EXIT_FAILURE);

    int i; // 現在の都市番号
    int start = 1;
    i = start;                  // 出発都市番号 start で初期化
    double dij;                 // 2都市間距離
    double totaldistance = 0.0; // 総移動距離

    int k = 1; // 訪問順序
    z[i] = k;  // 都市に対応する順序
    zz[k] = i; // 順序に対応する都市
    int next = 0;

    for (k = 2; k <= N; k++) // 探索した最も近い都市を次の訪問都市に更新
    {
        double min = DBL_MAX; // 最短移動距離のメモを倍精度浮動小数点数の最大値で初期化

        for (int j = 1; j <= N; j++) // 現在都市から最も近い都市を探索
        {
            if (z[j] == 0)
            {
                // 2都市間距離
                dij = distance_func(pointdata[i].x, pointdata[j].x, pointdata[i].y, pointdata[j].y);

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

        i = next; // 現在都市の更新
    }

    return 0;
}