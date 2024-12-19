#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(void)
{
    srand((unsigned int)time(NULL));
    //srand(123);               // 動作検証用
    int S = 3;                // サービス窓口数
    double ArrivalRate = 0.4; // 到着率
    double ServiceRate = 0.2; // サービス率
    double T = 360;           // シミュレーション時間
    double DeltaT = 0.1;      // 時間刻み
    double uA = (double)(rand() + 1) / (double)(RAND_MAX + 1);
    double xA = (-1.0 / ArrivalRate) * log(uA);
    printf("%lf\n", xA);
    double uS = (double)(rand() + 1) / (double)(RAND_MAX + 1);
    double xS = (-1.0 / ServiceRate) * log(uS);
    printf("%lf\n", xS);
    return 0;
}