// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task5.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <time.h> // clock�֐�

// ����`������ f(x) �̒�`
#define f(x) (log(x) - cos(x))

double bisection_recursion(double, double, const double, int);

FILE *fp; // FILE�|�C���^

int main(void)
{
    // fp���������݃��[�h�ŃI�[�v�����t�@�C����������
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus1.csv", "w");
    if (fp == NULL) // �G���[����
        exit(EXIT_FAILURE);
    fclose(fp); // �t�@�C���N���[�Y

    clock_t start = clock(); // �T���J�n�����̎擾

    const double a = 0.001, b = 3.0; // �T���J�n�_
    const double eps = 0.00001;      // ��������萔
    double x, xL, xH;                // x:�ϐ�
    int n = 1;                       // ������

    // �T����ԂƊ֐��l�̏�����
    xL = a;
    xH = b;

    // 2���@�Ŋ֐�f(x)�̋ߎ�����T�����鏈��
    x = bisection_recursion(xL, xH, eps, n);

    // fp��ǉ��������݃��[�h�Ńt�@�C���I�[�v��
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus1.csv", "a");
    if (fp == NULL) // �G���[����
        exit(EXIT_FAILURE);

    // �֐���f(x)�Ƌߎ����̏o��
    printf("\nf(x) = log(x) - cos(x) = 0\n\n"
           "2���@�Fa = %lf  b = %lf\n"
           "2���@�ɂ��ߎ����F%.8f\n\n",
           a, b, x); // cmd
    fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
                "2���@�Fa = %lf  b = %lf\n"
                "2���@�ɂ��ߎ����F%.8f\n\n",
            a, b, x); // csv

    clock_t end = clock(); // �T���I�������̎擾

    // �����o�ߎ��Ԃ̏o��
    printf("��������\t%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC);     // cmd
    fprintf(fp, "��������,%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

    fclose(fp); // �t�@�C���N���[�Y
    return 0;
}

double bisection_recursion(double xL, double xH, const double eps, int n)
{
    // fp��ǉ��������݃��[�h�Ńt�@�C���I�[�v��
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus1.csv", "a");
    if (fp == NULL) // �G���[����
        exit(EXIT_FAILURE);

    if (n == 1)
    {
        // �^�C�g���̏o��
        printf("������n\tx\t\tf(x)\n");  // cmd
        fprintf(fp, "������n,x,f(x)\n"); // csv
    }

    double yL = f(xL);
    double yH = f(xH);
    double w = fabs(xH - xL);       // �T����
    double x = x = (xH + xL) / 2.0; // ���_
    double y = f(x);

    // ���̑��ݏꏊ�Ŕ��肵�A�T����ԂƊ֐��l���X�V����
    if (yL * y < 0)
    { // �����������ɑ���
        xH = x;
        yH = y;
    }
    else if (yH * y < 0)
    { // �����E�����ɑ���
        xL = x;
        yL = y;
    }
    else
        w = 0; // ���_�̊֐��l��0�̂Ƃ�

    // �o�߂̏o��
    printf("%d\t\t%.8f\t%.8f\n", n, x, y);  // cmd
    fprintf(fp, "%d,%.8f,%.8f\n", n, x, y); // csv

    // �T����ԕ��ɂ��ċA����
    // �x�[�X�P�[�X
    if (w < eps)
    {
        fclose(fp); // �t�@�C���N���[�Y
        return x;
    }
    // �ċA�X�e�b�v
    else
    {
        n++;        // �񐔂̃J�E���g
        fclose(fp); // �t�@�C���N���[�Y
        return bisection_recursion(xL, xH, eps, n);
    }
}