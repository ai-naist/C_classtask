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

// �|�C���^�ϐ����A�^���A�����w�肵�ă������̊m�ۂƏ��������s���}�N��
#define get_array(ptr, type, N)                                                 \
    {                                                                           \
        ptr = (type *)calloc((N), sizeof(type));                                \
        if (ptr == NULL)                                                        \
        {                                                                       \
            printf("%s �^�̔z�� %s �̃��������m�ۂł��܂���B\n", #type, #ptr); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    }

// �������J����������NULL�N���A����}�N��
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
    //srand(123); // ���쌟�ؗp

    // fp �I�[�v�� w���[�h
    if (fopen_s(&fp, "Inoue_Akihiro_task10.csv", "w") != 0)
        exit(EXIT_FAILURE);

    int ALL_TELLER_NUMBERS; // �����̑���
    double ARRIVAL_RATE;    // ������
    double SERVICE_RATE;    // �T�[�r�X��
    double SIMULATION_TIME; // �V�~�����[�V��������
    double TIME_WIDTH;      // ���ԍ��ݕ�

    // ���l�̓���
    printf("�q�̕��ϓ�����( �q�̓����l��/ �P�ʎ���(��))lambda�������l�œ��͂��ĉ������B-->");
    scanf_s("%lf", &ARRIVAL_RATE);
    printf("ATM �@�̕��σT�[�r�X��(1�̑����̋q�ւ̃T�[�r�X(�I��)�� / �P�ʎ���(��)) mu�������l�œ��͂��ĉ������B-- >");
    scanf_s("%lf", &SERVICE_RATE);
    printf("ATM�@�̐ݒu�䐔(�T�[�r�X������) s �𐮐��l�œ��͂��ĉ������B-- >");
    scanf_s("%d", &ALL_TELLER_NUMBERS);
    printf("�V�~�����[�V��������T �������l�œ��͂��ĉ������B-- >");
    scanf_s("%lf", &SIMULATION_TIME);
    printf("���ԍ���delta_t �������l�œ��͂��ĉ������B-- >");
    scanf_s("%lf", &TIME_WIDTH);

    // ���s�����̏o��
    printf("\n�q�̕��ϓ�����lambda = %g\n"
           "ATM�@1 �䓖����̕��σT�[�r�X��mu = %g\n"
           "ATM�@�ݒu�䐔s = %d\n\n",
           ARRIVAL_RATE, SERVICE_RATE, ALL_TELLER_NUMBERS);
    fprintf(fp, "�q�̕��ϓ�����lambda = %g\n"
                "ATM�@1 �䓖����̕��σT�[�r�X��mu = %g\n"
                "ATM�@�ݒu�䐔s = %d\n\n",
            ARRIVAL_RATE, SERVICE_RATE, ALL_TELLER_NUMBERS);

    int sum_queue = 0;             // ���q����
    int current_queue = 0;         // ���݂̑҂��q��
    int sum_completed_service = 0; // �T�[�r�X��������
    double current_time = 0.0;     // ���ݎ���
    double arrival_time = 0.0;     // ���̋q�̓�������
    double *completion_time;       // �e�����̃T�[�r�X��������
    bool *occupied;                // �e�����̎g�p��

    get_array(occupied, bool, ALL_TELLER_NUMBERS + 1); // ���ׂ� �U�l�i0�j�ŏ�����
    get_array(completion_time, double, ALL_TELLER_NUMBERS + 1);

    // �ŏ��̋q�̓��������̌���
    arrival_time += get_exp_random_number(ARRIVAL_RATE);

    // �V�~�����[�V�����̎��s
    for (double current_time = 0.0; current_time <= SIMULATION_TIME; current_time += TIME_WIDTH)
    {
        // �q�̓�������
        if (arrival_time <= current_time)
        {
            arrival_time += get_exp_random_number(ARRIVAL_RATE);
            sum_queue++;
            current_queue++;
        }

        // �T�[�r�X�̋󂫏󋵂��m�F
        for (int i = 1; i <= ALL_TELLER_NUMBERS; i++)
        {
            if ((current_queue >= 1) && !occupied[i])
            {
                // �T�[�r�X�̊��蓖�ď���
                completion_time[i] = current_time + get_exp_random_number(SERVICE_RATE);
                occupied[i] = true;
                current_queue--;
            }
        }

        // �T�[�r�X�̊����m�F
        for (int i = 1; i <= ALL_TELLER_NUMBERS; i++)
        {
            if ((completion_time[i] <= current_time) && occupied[i])
            {
                occupied[i] = false;
                sum_completed_service++;
            }
        }
    }

    // �T�[�r�X���̌v�Z
    double service_completion_rate = (double)sum_completed_service / sum_queue;

    // ���ʂ̏o��
    printf("�V�~�����[�V��������T = %g �܂ł̋q�̓�������sum_q = %d\n\n"
           "�V�~�����[�V��������T = %g �܂ł�ATM�@�ݒu�䐔3 ��ŃT�[�r�X���I�������q�̑���fsq = %d\n\n"
           "�����q�ɑ΂���T�[�r�X��( �T�[�r�X���I�������q�̑���/ �q�̓�������) act_ro = %lf\n\n",
           SIMULATION_TIME, sum_queue, SIMULATION_TIME, sum_completed_service, service_completion_rate);
    fprintf(fp, "�V�~�����[�V��������T = %g �܂ł̋q�̓�������sum_q = %d\n\n"
                "�V�~�����[�V��������T = %g �܂ł�ATM�@�ݒu�䐔3 ��ŃT�[�r�X���I�������q�̑���fsq = %d\n\n"
                "�����q�ɑ΂���T�[�r�X��( �T�[�r�X���I�������q�̑���/ �q�̓�������) act_ro = %lf\n\n",
            SIMULATION_TIME, sum_queue, SIMULATION_TIME, sum_completed_service, service_completion_rate);

    // ���������
    free_NULLclear(completion_time);
    // �t�@�C���N���[�Y
    fclose(fp);

    return 0;
}