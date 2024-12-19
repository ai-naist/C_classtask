// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task10.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdbool.h>

// �|�C���^�ƌ^���w�肵�ă������̊m�ۂƏ��������s���}�N��
#define GetArray(ptr, type, N)                                                  \
    {                                                                           \
        ptr = (type *)calloc((N), sizeof(type));                                \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s �^�̔z�� %s �̃��������m�ۂł��܂���B\n", #type, #ptr); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    }

// �������J����������NULL�N���A����}�N��
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
    srand(123); // ���쌟�ؗp

    int S;              // �T�[�r�X������
    double ArrivalRate; // ������
    double ServiceRate; // �T�[�r�X��
    double T;           // �V�~�����[�V��������
    double DeltaT;      // �X�V���ԕ�

    // ���l�̓���
    printf("�q�̕��ϓ�����( �q�̓����l��/ �P�ʎ���(��)) lambda �������l�œ��͂��ĉ������B-->");
    scanf_s("%lf", &ArrivalRate);
    printf("ATM �@�̕��σT�[�r�X��(1�̑����̋q�ւ̃T�[�r�X(�I��)�� / �P�ʎ���(��)) mu �������l�œ��͂��ĉ������B-- >");
    scanf_s("%lf", &ServiceRate);
    printf("ATM �@�̐ݒu�䐔(�T�[�r�X������) s �𐮐��l�œ��͂��ĉ������B-- >");
    scanf_s("%d", &S);
    printf("�V�~�����[�V�������� T �������l�œ��͂��ĉ������B-- >");
    scanf_s("%lf", &T);
    printf("���ԍ��� delta_t �������l�œ��͂��ĉ������B-- >");
    scanf_s("%lf", &DeltaT);

    // ���s�����̏o��
    printf("\n�q�̕��ϓ����� lambda = %g\n"
           "ATM �@ 1�䓖����̕��σT�[�r�X�� mu = %g\n"
           "ATM �@�ݒu�䐔 s = %d\n\n",
           ArrivalRate, ServiceRate, S);

    bool sq = false;
    bool q = false;
    int temp_q = 0;              // ���݂̑҂��q��
    int sum_q = 0;               // ���q����
    int num_teller;              // �q�����蓖�Ă鑋���ԍ�
    int sum_fin_q = 0;           // �T�[�r�X��������
    double t = 0.0;              // ���ݎ���
    double ca_time = 0.0;        // ���̋q�̓�������
    double *fin_time;            // �e�����̃T�[�r�X��������
    double wait_time = 0.0;      // �҂�����
    double operation_rate = 0.0; // �ғ���
    bool available = false;      // �����̗��p��
    bool *occupied;              // �e�����̎g�p��

    GetArray(occupied, bool, S + 1); // ���ׂ� �U�l�i0�j�ŏ�����
    GetArray(fin_time, double, S + 1);

    ca_time += ExpRand(ArrivalRate);
    // �V�~�����[�V�����̎��s
    for (double t = 0.0; t <= T; t += DeltaT)
    {
        // �q�̓�������
        if (t >= ca_time)
        {
            ca_time = t + ExpRand(ArrivalRate);
            sum_q++;
            temp_q++;
            q = true;

            printf("+ ");
            Output_Progress(ARGS_OUTPROGRESS);
        }

        // �҂��q 0 �̂Ƃ��͏������X�L�b�v
        if (temp_q > 0)
        {

            for (int i = 1; i <= S; i++)
            {
                // �T�[�r�X�̋󂫏󋵂��m�F
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

        // �T�[�r�X�̏I���m�F
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

    // �T�[�r�X��
    double cmprate = (double)sum_fin_q / sum_q;

    // ���ʂ̏o��
    printf("�V�~�����[�V�������� T = %g �܂ł̋q�̓������� sum_q = %d\n\n"
           "�V�~�����[�V�������� T = %g �܂ł�ATM�@�ݒu�䐔3 ��ŃT�[�r�X���I�������q�̑��� sum_fin_q = %d\n\n"
           "�����q�ɑ΂���T�[�r�X��( �T�[�r�X���I�������q�̑���/ �q�̓�������) act_ro = %lf\n\n"
           "���ϑ҂����� %lf\n\n"
           "�ғ��� %lf ��\n\n",
           T, sum_q, T, sum_fin_q, cmprate, wait_time, operation_rate);

    // ���������
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