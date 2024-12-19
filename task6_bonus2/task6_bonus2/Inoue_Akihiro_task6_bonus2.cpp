// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task6_bonus2.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <time.h> // clock�֐�

// ����`������ f(x) �̒�`
#define f(x) (log(x) - cos(x))
// f(x)�̈�K���֐�
#define D_f(x) ((1 / (x)) + sin(x))

double newton_recursion(double, const double, int);

FILE *fp; // FILE�|�C���^

int main(void)
{
    // fp���������݃��[�h�ŃI�[�v�����t�@�C����������
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus2.csv", "w");
    if (fp == NULL) // �G���[����
        exit(EXIT_FAILURE);
    fclose(fp); // �t�@�C���N���[�Y

    clock_t start = clock(); // �T���J�n�����̎擾

    const double x0 = 0.001;    // �T���J�n�_
    const double eps = 0.00001; // ��������萔
    double xn, xn1;             // x:�ϐ�
    int n = 1;                  // ������

    // �T���J�n�_�̏�����
    xn = x0;

    // �j���[�g���@�Ŋ֐�f(x)�̋ߎ�����T�����鏈��
    xn1 = newton_recursion(xn, eps, n);

    // fp��ǉ��������݃��[�h�Ńt�@�C���I�[�v��
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus2.csv", "a");
    if (fp == NULL) // �G���[����
        exit(EXIT_FAILURE);

    // �֐���f(x)�Ƌߎ����̏o��
    printf("\nf(x) = log(x) - cos(x) = 0\n\n"
           "�j���[�g���@�ɂ��ߎ����F%.8f\n\n",
           xn1); // cmd
    fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
                "�j���[�g���@�ɂ��ߎ����F%.8f\n\n",
            xn1); // csv

    clock_t end = clock(); // �T���I�������̎擾

    // �����o�ߎ��Ԃ̏o��
    printf("��������\t%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC);     // cmd
    fprintf(fp, "��������,%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

    fclose(fp); // �t�@�C���N���[�Y
    return 0;
}

double newton_recursion(double xn, const double eps, int n)
{
    // fp��ǉ��������݃��[�h�Ńt�@�C���I�[�v��
    fopen_s(&fp, "Inoue_Akihiro_task6_bonus2.csv", "a");
    if (fp == NULL) // �G���[����
        exit(EXIT_FAILURE);

    if (n == 1)
    {
        // �^�C�g���̏o��
        printf("n\tx_n+1\t\tx_n\t\tf(x_n)\t\tf'(x_n)\t\tx_n+1 - x_n\n"); // cmd
        fprintf(fp, "n,x_n+1,x_n,f(x_n),f'(x_n),x_n+1 - x_n\n"); // csv
    }

    double y = f(xn);           // y:�֐��l
    double Dy = D_f(xn);        // Dy:�ꎟ���W��
    double xn1 = xn - (y / Dy); // �ߎ���
    double w = fabs(xn1 - xn);  // w:�ߎ����̍�

    // �o�߂̏o��
    printf("%d\t%.8f\t%.8f\t%.8f\t%.8f\t%.8f\n", n, xn1, xn, y, Dy, w); // cmd
    fprintf(fp, "%d,%.8f,%.8f,%.8f,%.8f,%.8f\n", n, xn1, xn, y, Dy, w); // csv

    w = w / xn;
    xn = xn1; // �T���_�̍X�V

    // �T����ԕ��ɂ��ċA����
    // �x�[�X�P�[�X
    if (w < eps)
    {
        fclose(fp); // �t�@�C���N���[�Y
        return xn1;
    }
    // �ċA�X�e�b�v
    else
    {
        n++;        // �񐔂̃J�E���g
        fclose(fp); // �t�@�C���N���[�Y
        return newton_recursion(xn, eps, n);
    }
}