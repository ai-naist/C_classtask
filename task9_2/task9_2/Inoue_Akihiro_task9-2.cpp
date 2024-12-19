// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task9-2.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdbool.h>

const double UOM = 1.0; // ����P�� : Unit of Measure �� ��

// �|�C���^�ƌ^���w�肵�ă������̊m�ۂƏ��������s���}�N��
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
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

FILE *fp; // CSV�o�͗p

// switch-case �̕���p
enum PRN_Type
{
    UniformRN = 1,
    NormalRN
};

int main(void)
{
    srand((unsigned int)time(NULL));
    //srand(123); // ���쌟�ؗp

    // fp �I�[�v�� w���[�h
    if (fopen_s(&fp, "Inoue_Akihiro_task9-2.csv", "w") != 0)
        exit(EXIT_FAILURE); // �G���[����

    int N; // ����������
    printf("�����̐����� N �� �����l�Ŏw�肵�ĉ�����---- > ");
    scanf_s("%d", &N);

    double *x;
    get_array(x, double, N);

    double a, b;       // ��l�����͈̔�
    double mu, sigma;  // ���K�����̏��������i�^�l�j
    int choice;        // �����̌^�i 1 : ��l����   2 : ���K���� �j
    bool check = true; // �����̌^�I�����[�v�p

    do
    {
        printf("\n1 : �͈�[a,b]�̎����^��l�����̐���\n"       // Uniform Random Number
               "\n2 : ���� �� �� �W���΍� �� �̐��K�����̐���\n" // Normal Random Number
               "\n�������闐���̑I��ԍ��� 1 �� 2 ��� 1 ���͉�����. ---> ");
        scanf_s("%d", &choice);

        // �����̌^�ŏ������򂵂āA�[����������
        switch (choice)
        {
        case UniformRN:
            do
            {
                do
                {
                    printf("\n�����^��l�����͈̔� [ a , b ] ���w�肵�ĉ�����\n"
                           "a ---> ");
                    scanf_s("%lf", &a);
                } while (a < 1.0);
                printf("b ---> ");
                scanf_s("%lf", &b);
            } while (a > b); // 1.0 �� a �� b �̏����w�����

            // �͈�[a,b]�̎����^��l������ N ����
            for (int i = 0; i < N; i++)
                x[i] = a + (b - a) * ((double)rand() / (double)RAND_MAX);
            check = false;
            break;

        case NormalRN:
            do
            {
                printf("\n���K�����̕��� �� �� �W���΍� �� ���w�肵�ĉ�����\n"
                       "�� ---> ");
                scanf_s("%lf", &mu);
                printf("�� ---> ");
                scanf_s("%lf", &sigma);
            } while ((mu - 3 * sigma) <= 0); // �� > 3�� �̏����w�����

            // ���� �� �� �W���΍� �� �̐��K���z�ɏ]�����K���� (�{�b�N�X�E�~�����[�@)�� N ����
            for (int i = 0; i < N; i = i + 2)
            {
                double r1 = ((double)rand() + 1) / ((double)RAND_MAX + 1);
                double r2 = ((double)rand() + 1) / ((double)RAND_MAX + 1);
                x[i] = mu + sigma * sqrt(-2.0 * log(r1)) * cos(2.0 * M_PI * r2);
                x[i + 1] = mu + sigma * sqrt(-2.0 * log(r1)) * sin(2.0 * M_PI * r2);
            }
            check = false;
            break;

        default:
            printf("\n�I��ԍ��Ɍ�肪����܂��D�ēx�C�I��ԍ�����͂��Ȃ����ĉ������D\n");
        }
    } while (check);

    double xmax = -DBL_MAX;
    double xmin = DBL_MAX;
    double sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += x[i];     // �a
        if (xmax < x[i]) //
            xmax = x[i]; // �ő�l
        if (xmin > x[i]) //
            xmin = x[i]; // �ŏ��l
    }
    double avx = sum / N; // ���ϒl
    double vx = 0;
    for (int i = 0; i < N; i++)
        vx += pow((x[i] - avx), 2);
    vx = vx / N;          // ���U
    double sx = sqrt(vx); // �W���΍�

    // �����̌^�ŕ��򂵂ă^�C�g���ƁA�f�[�^�̏����������o��
    switch (choice)
    {
    case UniformRN:
        printf("\n�����^��l�����f�[�^�̓��v��������\n"
               "\n�f�[�^�͈�\ta\tb\n"
               "\t\t%g\t%g\n\n",
               a, b);
        fprintf(fp, "�����^��l�����f�[�^�̓��v��������\n"
                    "\n�f�[�^�͈�,a,b\n"
                    ",%g,%g\n\n",
                a, b);
        break;

    case NormalRN:
        printf("\n���K�����f�[�^�̓��v��������\n"
               "\n���K���z\t����\t�W���΍�\n"
               "�^�̒l\t\t%g\t%g\n\n",
               mu, sigma);
        fprintf(fp, "���K�����f�[�^�̓��v��������\n"
                    "\n���K���z,����,�W���΍�\n"
                    "�^�̒l,%g,%g\n\n",
                mu, sigma);
        break;
    }

    // �f�[�^���e�[�u��
    printf("�f�[�^��\t\t%d\n"
           "�f�[�^�̕���\t\t%lf\n"
           "�f�[�^�̕s�Ε��U\t%lf\n"
           "�f�[�^�̕W���΍�\t%lf\n"
           "�f�[�^�̍ő�l\t\t%lf\n"
           "�f�[�^�̍ŏ��l\t\t%lf\n",
           N, avx, vx, sx, xmax, xmin);
    fprintf(fp, "�f�[�^��,%d\n"
                "�f�[�^�̕���,%lf\n"
                "�f�[�^�̕s�Ε��U,%lf\n"
                "�f�[�^�̕W���΍�,%lf\n"
                "�f�[�^�̍ő�l,%lf\n"
                "�f�[�^�̍ŏ��l,%lf\n",
            N, avx, vx, sx, xmax, xmin);

    int k; // ���̐�
    printf("\n���̐� k �� �����l �� �w�肵�ĉ�����---- > ");
    scanf_s("%d", &k);

    double h = ceil((xmax - xmin) / (double)k); // ���̋�ԕ� h �̐ݒ�

    double *x_interval; // ���̋�Ԓl
    get_array(x_interval, double, k + 1);
    x_interval[0] = xmin - (UOM / 2);          // �f�[�^��Ԃ̉����l�ݒ�
    for (int i = 1; i < k + 1; i++)            //
        x_interval[i] = x_interval[i - 1] + h; // �e���̃f�[�^��Ԓl�̐ݒ�

    double *x_midval; // ��Ԃ̐^�񒆂̒l
    get_array(x_midval, double, k);
    for (int i = 0; i < k; i++)
        x_midval[i] = (x_interval[i] + x_interval[i + 1]) / 2;

    int *freq;            // �x��
    int *cum_freq;        // �ݐϓx��
    double *rel_freq;     // ���Γx��
    double *cum_rel_freq; // �ݐϑ��Γx��
    // �z��̏�����
    get_array(freq, int, k);
    get_array(cum_freq, int, k);
    get_array(rel_freq, double, k);
    get_array(cum_rel_freq, double, k);

    // ���̕\���Ɠx���e�[�u���̃^�C�g��
    printf("\n���̐�\t\t%d\n"
           "���̋�ԕ�\t%g\n"
           "\n�f�[�^���\t\t\t���Ԃ̒l\t�x��\t�ݐϓx��\t���Γx��\t�ݐϑ��Γx��\n",
           k, h);
    fprintf(fp, "\n���̐�,%d\n"
                "���̋�ԕ�,%g\n"
                "\n�f�[�^���,���Ԃ̒l,�x��,�ݐϓx��,���Γx��,�ݐϑ��Γx��\n",
            k, h);

    int temp_freq = 0;          // �ݐϓx���̈ꎞ�L��
    for (int i = 0; i < k; i++) // ���̍X�V
    {
        for (int j = 0; j < N; j++) // �f�[�^�̌���
        {
            if ((x_interval[i] <= x[j]) && (x[j] < x_interval[i + 1]))
                freq[i]++; // ���݂̋��ɂ��鐔�l���J�E���g�i�x���j
        }
        cum_freq[i] = temp_freq + freq[i];                 // �ݐϓx��
        rel_freq[i] = (double)freq[i] / (double)N;         // ���Γx���̎Z�o
        cum_rel_freq[i] = (double)cum_freq[i] / (double)N; // �ݐϑ��Γx���̎Z�o
        temp_freq = cum_freq[i];                           // �ݐϓx���̍X�V�p

        // �x���e�[�u���̏o��
        printf("%lf �| %lf\t%lf\t%d\t%d\t\t%lf\t%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
        fprintf(fp, "%lf �| %lf,%lf,%d,%d,%lf,%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
    }

    // �݌v�̏o��
    printf("\t\t\t\t\t\t�݌v\t%d\t\t�݌v\t\t%lf\n", cum_freq[k - 1], cum_rel_freq[k - 1]);
    fprintf(fp, ",,�݌v,%d,�݌v,%lf\n", cum_freq[k - 1], cum_rel_freq[k - 1]);

    // �t�@�C���N���[�Y
    fclose(fp);
    // ���������
    free_null(x);
    free_null(x_interval);
    free_null(x_midval);
    free_null(freq);
    free_null(rel_freq);
    free_null(cum_freq);
    free_null(cum_rel_freq);

    return 0;
}