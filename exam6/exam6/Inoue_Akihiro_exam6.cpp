// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam6.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <time.h> // clock�֐�

// ����`������ f(x) �̒�`
#define f(x) (log(x) - cos(x))

// �v���g�^�C�v�錾
double direct_recursion(double, const double, int);

FILE *fp; // FILE�|�C���^

int main(void)
{
	// fp���������݃��[�h�ŃI�[�v�����t�@�C����������
	fopen_s(&fp, "Inoue_Akihiro_exam6.csv", "w");
	if (fp == NULL) // �G���[����
		exit(EXIT_FAILURE);
	fclose(fp); // �t�@�C���N���[�Y

	clock_t start = clock(); // �T���J�n�����̎擾

	const double delta_x = 0.001; // �T���Ԋu
	const double a = 0.001;		  // �T���J�n�_
	double x1;					  // �T���_
	int n = 1;					  // ������
	x1 = a;						  // �T���_���J�n�_�ŏ�����

	// ���ڒT���@�Ŋ֐�f(x)�̋ߎ������ċA�Ăяo���ɂ�郋�[�v�ŒT�����鏈��
	x1 = direct_recursion(x1, delta_x, n);

	// fp��ǉ��������݃��[�h�Ńt�@�C���I�[�v��
	fopen_s(&fp, "Inoue_Akihiro_exam6.csv", "a");
	if (fp == NULL) // �G���[����
		exit(EXIT_FAILURE);

	// �֐���f(x)�Ƌߎ����̏o��
	printf("\nf(x) = log(x) - cos(x) = 0\n\n"
		   "���ڒT���@�ɂ��ߎ����F%lf\n\n",
		   x1); // cmd
	fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
				"���ڒT���@�ɂ��ߎ����F%lf\n\n",
			x1); // csv

	clock_t end = clock(); // �T���I�������̎擾

	// �����o�ߎ��Ԃ̏o��
	printf("��������\t%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC);	  // cmd
	fprintf(fp, "��������,%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

	fclose(fp); // �t�@�C���N���[�Y
	return 0;
}

double direct_recursion(double x1, const double delta_x, int n)
{
	// fp��ǉ��������݃��[�h�Ńt�@�C���I�[�v��
	fopen_s(&fp, "Inoue_Akihiro_exam6.csv", "a");
	if (fp == NULL) // �G���[����
		exit(EXIT_FAILURE);

	double y1 = f(x1);
	double x2 = x1 + delta_x;
	double y2 = f(x2);

	if (n == 1)
	{
		// �^�C�g���̏o��
		printf("������n\tx1\tf(x1)\n");	 // cmd
		fprintf(fp, "������n,x1,f(x1)\n"); // csv
	}

	// �o�߂̏o��
	printf("%d\t\t%.3f\t%.8f\n", n, x1, y1);  // cmd
	fprintf(fp, "%d,%.3f,%.8f\n", n, x1, y1); // csv

	// y1��y2�̕����ω�������
	// �x�[�X�P�[�X(�ٕ����̂Ƃ�)
	if (y1 * y2 <= 0)
	{
		fclose(fp); // �t�@�C���N���[�Y
		return x1;
	}
	// �ċA�X�e�b�v(�������̂Ƃ�)
	else
	{
		x1 = x2;	// �T���_��i�߂�
		n++;		// �񐔂̃J�E���g
		fclose(fp); // �t�@�C���N���[�Y
		return direct_recursion(x1, delta_x, n);
	}
}