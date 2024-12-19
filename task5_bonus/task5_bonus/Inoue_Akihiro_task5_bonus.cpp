// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task5_bonus.cpp

#include <stdio.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <time.h> // clock�֐�

// ����`������ f(x) �̒�`
#define f(x) (log(x) - cos(x))
// f(x)�̈�K���֐�
#define D_f(x) ((1 / (x)) + sin(x))

FILE *fp; // FILE�|�C���^

int main(void)
{
	// fp���������݃��[�h�ŃI�[�v��
	fopen_s(&fp, "Inoue_Akihiro_task5_bonus.csv", "w");
	if (fp == NULL) // �G���[����
		return 1;

	clock_t start = clock(); // �T���J�n�����̎擾

	// �^�C�g���̏o��
	printf("n\tx_n+1\tx_n\tf(x_n)\tf'(x_n)\tx_n+1 - x_n\n"); // cmd
	fprintf(fp, "n,x_n+1,x_n,f(x_n),f'(x_n),x_n+1 - x_n\n"); // csv

	const double x0 = 0.001;	// �T���J�n�_
	const double eps = 0.00001; // ��������萔
	double xn, xn1, y, Dy, w;	// x:�ϐ� y:�֐��l Dy:�ꎟ���W�� w:�ߎ����̑��΍�
	int n = 1;					// ������

	// �T���J�n�_�̏�����
	xn = x0;

	// �j���[�g���@�Ŋ֐�f(x)�̋ߎ�����T�����鏈��
	do
	{
		y = f(xn);
		Dy = D_f(xn);
		xn1 = xn - (y / Dy);
		w = fabs(xn1 - xn);

		// �o�߂̏o��
		printf("%d\t%.8f\t%.8f\t%.8f\t%.8f\t%.8f\n", n, xn1, xn, y, Dy, w); // cmd
		fprintf(fp, "%d,%.8f,%.8f,%.8f,%.8f,%.8f\n", n, xn1, xn, y, Dy, w); // csv

		w = w / xn;
		xn = xn1;	   // �T���_�̍X�V
		n++;		   // �񐔂̃J�E���g
	} while (w > eps); // �ߎ����̑��΍�����������萔�������Ƃ��ɏ����𔲂���

	// �֐���f(x)�Ƌߎ����̏o��
	printf("\nf(x) = log(x) - cos(x) = 0\n\n"
		   "�j���[�g���@�ɂ��ߎ����F%.8f\n\n",
		   xn1); // cmd
	fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
				"�j���[�g���@�ɂ��ߎ����F%.8f\n\n",
			xn1); // csv

	clock_t end = clock(); // �T���I�������̎擾

	// �����o�ߎ��Ԃ̏o��
	printf("��������\t%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC);	  // cmd
	fprintf(fp, "��������,%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

	fclose(fp); // �t�@�C���N���[�Y
	return 0;
}