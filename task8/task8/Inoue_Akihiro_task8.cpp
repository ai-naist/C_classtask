// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task8.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>

// 2�s�s�ԋ������Z�o����}�N��
#define distance_func(xi, xj, yi, yj) (sqrt(pow((xi) - (xj), 2) + pow((yi) - (yj), 2)))

// �������J����������NULL�N���A����}�N��
#define free_null(ptr) \
    {                  \
        free(ptr);     \
        ptr = NULL;    \
    }

// �t�@�C���|�C���^
FILE *fp1, *fp2, *fp3; // fp1:�������������s�s���W�̈ꎟ�ۑ��p�@fp2:�s�s���W�̓ǂݍ��ݗp�@fp3:���ʏo�͗p

// x���W��y���W���\���̂Œ�`
typedef struct
{
    int num;  // �s�s�ԍ�
    double x; // x���W
    double y; // y���W
} CityInfo_t;

int main(void)
{
    // ��1 �s�s�̍��W�͈�[a,b]���w��@���͈̔͂�N�̍��W�𗐐��Ŏ擾�@�擾�������W�� citydata_info.csv �ɏo��
    double a, b;
    int N;
    // a,b,N �̓���
    printf("�K��s�s�̈ʒu���W x ���W�� y ���W�͈̔�( ���� a , ��� b )�̐ݒ�ɂ���\n"
           "�͈� �̉��� a ���w�肵�ĉ������B --- > ");
    scanf_s("%lf", &a);
    printf("�͈� �̏�� b ���w�肵�ĉ������B --- > ");
    scanf_s("%lf", &b);
    do
    {
        printf("�K��s�s�� N ���w�肵�ĉ�����. �B--- > ");
        scanf_s("%d", &N);
    } while ((N <= 0) || (N > INT_MAX)); // �s���Ȓl�̉��

    // fp1���������݃��[�h�ŃI�[�v��
    if (fopen_s(&fp1, "citydata_info.csv", "w") != 0)
        exit(EXIT_FAILURE); // �G���[����

    srand((unsigned int)time(NULL)); // �V�[�h�ltime(NULL)�ŗ����n��̐���
    //srand(123); // ���쌟�ؗp

    for (int n = 1; n <= N; n++)
    {
        //�@���W(x,y)��[a,b]�ł̗����ɒu�������Ď擾
        double x_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);
        double y_point = a + (b - a) * ((double)rand() / (double)RAND_MAX);

        // citydata_info.csv �ɏo��
        fprintf(fp1, "%d,%lf,%lf\n", n, x_point, y_point);
    }
    fclose(fp1); // �t�@�C���N���[�Y
    // ��1 �����

    // ��2 �\���̔z��� citydata_info.csv ����ǂݍ��񂾒l�ŏ��������@�����o�̒l�� Inoue_Akihiro_task8.csv �ɏo��
    CityInfo_t *cityinfodata;                                       // �\���̌^�z��̐擪�v�f�ւ̃|�C���^
    cityinfodata = (CityInfo_t *)calloc(N + 1, sizeof(CityInfo_t)); // �������̊m��(�|�C���^���w���A�h���X��[0]�`[N+1]�܂Ŋ��蓖�Ă�)
    /*  calloc(��,�������T�C�Y) �� �w�肵���T�C�Y�Ŋm�ۂ����������̐擪�A�h���X��void�^�ւ̃|�C���^�ŕԂ��A���蓖�Ă�ꂽ�v�f��0�N���A����
        (CityInfo_t *) ��typedef���ꂽ�\���̌^�ւ̃|�C���^�ɃL���X�g���ĕԂ��Ă���
        �|�C���^ cityinfodata �Ɋ��蓖�Ă�ꂽ�A�h���X���w�肷�邱�ƂŔz��Ƃ��Ĉ�����   */
    if (cityinfodata == NULL)
    {
        // �G���[����
        printf("�\���̌^�z��̃��������m�ۂł��܂���B\n");
        exit(EXIT_FAILURE);
    }

    // fp2��ǂݎ�胂�[�h�ŃI�[�v��
    if (fopen_s(&fp2, "citydata_info.csv", "r") != 0)
        exit(EXIT_FAILURE); // �G���[����

    // fp3���������݃��[�h�ŃI�[�v��
    if (fopen_s(&fp3, "Inoue_Akihiro_task8.csv", "w") != 0)
        exit(EXIT_FAILURE); // �G���[����

    // �^�C�g���̏o��
    printf("\n�s�s�ԍ�\tx���W\t\ty���W\n");
    fprintf(fp3, "�s�s�ԍ�,x���W,y���W\n");

    // �����o�̒l(�s�s�ԍ��Ax���W�Ay���W)�� citydata_info.csv ����ǂݍ��݁A Inoue_Akihiro_task8.csv �ɏ�������
    int n = 1;
    while ((fscanf_s(fp2, "%d,%lf,%lf", &cityinfodata[n].num, &cityinfodata[n].x, &cityinfodata[n].y)) != EOF)
    {
        // �ǂݍ��񂾃����o���o��
        printf("%d\t\t%lf\t%lf\n", cityinfodata[n].num, cityinfodata[n].x, cityinfodata[n].y);
        fprintf(fp3, "%d,%lf,%lf\n", cityinfodata[n].num, cityinfodata[n].x, cityinfodata[n].y);
        n++;
    }
    fclose(fp2); // �t�@�C���N���[�Y
    // ��2 �����

    // ��3 �s�s�ԍ��ƖK�⏇���ԍ�����������z����`
    // �z�� z[�s�s�ԍ�] = ���̓s�s�̖K�⏇���ԍ�(�S�̂ŉ��ԖڂɖK�₷��s�s��)�@�����l0�͂��̓s�s�����K���\��
    int *z;                                // �z��̐擪�v�f�ւ̃|�C���^
    z = (int *)calloc(N + 1, sizeof(int)); // �������̊m��(�A�h���X�̊��蓖��)
    if (z == NULL)
    {
        // �G���[����
        printf("�ꎟ���z�� z �̃��������m�ۂł��܂���B\n");
        exit(EXIT_FAILURE);
    }

    // �z�� zz[�K�⏇���ԍ�] = �s�s�ԍ��@�����l0�͂��̏����ԍ��ŖK�₷��s�s�������\��
    int *zz;                                // �z��̐擪�v�f�ւ̃|�C���^
    zz = (int *)calloc(N + 1, sizeof(int)); // �������̊m��(�A�h���X�̊��蓖��)
    if (zz == NULL)
    {
        // �G���[����
        printf("�ꎟ���z�� zz �̃��������m�ۂł��܂���B\n");
        exit(EXIT_FAILURE);
    }
    // ��3 �����

    // ��4 �o���s�s����͂Ŏ擾�@�ŋߗז@�Ōo�H�T���@�T���o�߂̏o�́@�T�����Ԃ̌v��
    // �o���s�s�����
    int start;
    do
    {
        printf("\n�ŏ��̏o���s�s start ��s�s�ԍ� 1 �` %d ���w�肵�ĉ������B---> ", N);
        scanf_s("%d", &start);
    } while ((start <= 0) || (start > N)); // �s���Ȓl�̉��

    // �T�����Ԍv���̊J�n
    clock_t begin = clock();

    int i;     // ���݂̓s�s�ԍ�
    i = start; // �o���s�s�ԍ� start �ŏ�����

    double dij;                 // 2�s�s�ԋ���
    double totaldistance = 0.0; // ���ړ�����

    int k = 1; // �K�⏇��
    z[i] = k;  // �s�s�ɑΉ����鏇��
    zz[k] = i; // �����ɑΉ�����s�s

    int next = 0;

    // ���ʃ^�C�g���̏o��
    printf("\nk\ti\tnext\tmin\t\ttdis\n");
    fprintf(fp3, "\nk,i,next,min,tdis\n");

    // �ŋߗז@�ɂ��ŒZ�ړ������̒T��
    for (k = 2; k <= N; k++) // �T�������ł��߂��s�s�����̖K��s�s�ɍX�V
    {
        double min = DBL_MAX; // �ŒZ�ړ������̃�����{���x���������_���̍ő�l�ŏ�����

        for (int j = 1; j <= N; j++) // ���ݓs�s����ł��߂��s�s��T��
        {
            if (z[j] == 0)
            {
                // 2�s�s�ԋ���
                dij = distance_func(cityinfodata[i].x, cityinfodata[j].x, cityinfodata[i].y, cityinfodata[j].y);

                if (dij < min)
                {
                    min = dij;
                    next = j; // �s�s�ԍ��̃���
                }
            }
        }

        z[next] = k;  // ���̖K��s�s�̌���
        zz[k] = next; // �����ɑΉ�����s�s

        totaldistance += min;

        // �r�����ʂ̏o��
        printf("%d\t%d\t%d\t%lf\t%lf\n", k, i, next, min, totaldistance);
        fprintf(fp3, "%d,%d,%d,%lf,%lf\n", k, i, next, min, totaldistance);

        i = next; // ���ݓs�s�̍X�V
    }

    // �ŏI���B�s�s����o���s�s�֖߂鋗���̌v�Z
    dij = distance_func(cityinfodata[i].x, cityinfodata[start].x, cityinfodata[i].y, cityinfodata[start].y);
    totaldistance += dij;

    // �r�����ʂ̏o��
    printf("\t%d\t%d\t%lf\t%lf\n", i, start, dij, totaldistance);
    fprintf(fp3, ",%d,%d,%lf,%lf\n", i, start, dij, totaldistance);

    // �T�����Ԍv���̏I���
    clock_t end = clock();
    // ��4 �����

    // ��5 �T�����ʂƒT���������Ԃ̏o��
    // �s�s�ԍ�����
    printf("\n�s�s�ԍ�\t�K�⏇��\n");
    fprintf(fp3, "\n�s�s�ԍ�,�K�⏇��\n");
    for (int l = 1; l <= N; l++)
    {
        printf("%d\t\t%d\n", l, z[l]);
        fprintf(fp3, "%d,%d\n", l, z[l]);
    }

    // �K�⏇������
    printf("\n�K�⏇��\t�s�s�ԍ�\n");
    fprintf(fp3, "\n�K�⏇��,�s�s�ԍ�\n");
    for (int l = 1; l <= N; l++)
    {
        printf("%d\t\t%d\n", l, zz[l]);
        fprintf(fp3, "%d,%d\n", l, zz[l]);
    }

    // ���ړ������̏o��
    printf("\n���ړ�����\t%lf\n", totaldistance);
    fprintf(fp3, "\n���ړ�����,%lf\n", totaldistance);

    // �����o�ߎ��Ԃ̏o��
    printf("\n�T����������\t%lf �b\n", ((double)end - (double)begin) / CLOCKS_PER_SEC);
    fprintf(fp3, "\n�T����������,%lf �b\n", ((double)end - (double)begin) / CLOCKS_PER_SEC);

    fclose(fp3); // �t�@�C���N���[�Y
    // ��5 �����

    // ���������
    free_null(cityinfodata);
    free_null(z);
    free_null(zz);

    return 0;
}
