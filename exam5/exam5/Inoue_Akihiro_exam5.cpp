// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam5.cpp

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>
#include <time.h> // clock�֐�

// ����`������ f(x) �̒�`
#define f(x) (log(x)-cos(x))

FILE* fp; // FILE�|�C���^

int main(void)
{
	// fp���������݃��[�h�ŃI�[�v��
	fopen_s(&fp, "Inoue_Akihiro_exam5.csv", "w");
	if (fp == NULL) // �G���[����
		return 1;

	clock_t start = clock(); // �T���J�n�����̎擾

	// �^�C�g���̏o��
	printf("������n\tx1\tf(x1)\n"); // cmd
	fprintf(fp, "������n,x1,f(x1)\n"); // csv

	double a=0.001; // �T���J�n�_
	const double delta_x = 0.001; // �T���Ԋu
	double x1, x2, y1, y2; // x:�ϐ��@y:�֐��l
	int n = 1; // ������

	x1 = a; // x1�̏�����

	// ���ڒT���@�Ŋ֐�f(x)�̋ߎ�����T�����鏈��
	do {
		y1 = f(x1);

		x2 = x1 + delta_x;
		y2 = f(x2);

		// �o�߂̏o��
		printf("%d\t%.3f\t%lf\n",n,x1,y1); // cmd
		fprintf(fp, "%d,%.3f,%lf\n", n, x1, y1); // csv

		x1 = x2; // �T���_��i�߂�
		n++; // �񐔂̃J�E���g
		
	} while ((y1 * y2) > 0); // �֐��l�̕����ω��ŏ����𔲂���

	x1 = x2 - delta_x; // �ߎ���(�X�V�����T���_����O�ɖ߂�)

	// �֐���f(x)�Ƌߎ����̏o��
	printf("\nf(x) = log(x) - cos(x) = 0\n\n"
		"���ڒT���@�ɂ��ߎ����F%lf\n\n", x1); // cmd
	fprintf(fp, "\nf(x) = log(x) - cos(x) = 0\n\n"
		"���ڒT���@�ɂ��ߎ����F%lf\n\n", x1); // csv

	clock_t end = clock(); // �T���I�������̎擾

	// �����o�ߎ��Ԃ̏o��
	printf("��������\t%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // cmd
	fprintf(fp, "��������,%lf �b\n", ((double)end - (double)start) / CLOCKS_PER_SEC); // csv

	fclose(fp); // �t�@�C���N���[�Y
	return 0;
}