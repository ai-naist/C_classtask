#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(void)
{
    srand((unsigned int)time(NULL));
    //srand(123);               // ���쌟�ؗp
    int S = 3;                // �T�[�r�X������
    double ArrivalRate = 0.4; // ������
    double ServiceRate = 0.2; // �T�[�r�X��
    double T = 360;           // �V�~�����[�V��������
    double DeltaT = 0.1;      // ���ԍ���
    double uA = (double)(rand() + 1) / (double)(RAND_MAX + 1);
    double xA = (-1.0 / ArrivalRate) * log(uA);
    printf("%lf\n", xA);
    double uS = (double)(rand() + 1) / (double)(RAND_MAX + 1);
    double xS = (-1.0 / ServiceRate) * log(uS);
    printf("%lf\n", xS);
    return 0;
}