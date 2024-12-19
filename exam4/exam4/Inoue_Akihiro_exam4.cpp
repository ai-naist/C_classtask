// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam4.cpp

#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES // ���l���Z�萔

// �֐��`���}�N����p���Ċ֐��� f(x0)���`����
#define f(x0) (7.0 * pow((x0), 4.0) - 5.0 * pow((x0), 3.0) + 3.0 * (x0))
// ���� #define �}�N����(������,...) (�u����̎�)


// �֐��� f(x0)���`����֐�
double f_x(double x0)
{
	// �������s���֐��̑��
	double fx0 = 7.0 * pow(x0, 4.0) - 5.0 * pow(x0, 3.0) + 3.0 * x0;
	return fx0;
}

// �o�͂̋L�q���}�N���ŏ�������
#define cout(x) printf("\t%lf", (x))
#define fout(x) fprintf(fp,",%lf",(x))

FILE* fp; // �t�@�C���|�C���^�̐錾

int main(void)
{
	// fp���������݃��[�h�ŃI�[�v��
	fopen_s(&fp,"Inoue_Akihiro_exam4.csv", "w");
	if (fp == NULL) // �G���[����
		return 1;

	double x0; // �֐����ɑ������ϐ�
	const double h = 0.01; // x0�̔����Ԋu

	double u[5], m[5]; // u:����֐�  m:�֐��`���}�N�� �ɑΉ����� 0:x0  1:fx0  2:h  3:dfdx0  4:d2fdx02 �����ꂼ��i�[����
	u[2] = h;
	m[2] = h;

	// �^�C�g�����R���\�[���ɏo��
	printf("f(x0) = 7.0 * x0^4 - 5.0 * x0^3 + 3.0 * x0\n\n");
	printf("choice : u:����֐��𗘗p�Am:�������֐��`���}�N���𗘗p\n\n");
	printf("choice\tx0\t\tfx0\t\th\t\tdfdx0\t\td2fdx02\t\n");

	// �^�C�g����csv�ɏ�������
	fprintf(fp, "f(x0) = 7.0 * x0^4 - 5.0 * x0^3 + 3.0 * x0\n\n");
	fprintf(fp, "choice : u:����֐��𗘗p�Am:�������֐��`���}�N���𗘗p\n\n");
	fprintf(fp, "choice,x0,fx0,h,dfdx0,d2fdx02\n");

	// �֐�����ψ� 1.99 <= x <= 2.01 �͈̔͂� 0.01 ���Ƃɕω�������
	for (x0 = 1.99; x0 <= 2.01; x0 += h) {

		u[0] = x0;
		m[0] = x0;

		// ���݂� x0 �ł� �֐� f(x) ���Z�o
		u[1] = f_x(x0); // ����֐�
		m[1] = f(x0); // �}�N��

		// ���݂� x0 �ł� �֐� f(x) �� 1�����W���̎Z�o
		u[3] = (f_x(x0 + h) - f_x(x0 - h)) / (2.0 * h); // ����֐�
		m[3] = (f(x0 + h) - f(x0 - h)) / (2.0 * h); // �}�N��

		// ���݂� x0 �ł� �֐� f(x) �� 2�����W���̎Z�o
		u[4] = (f_x(x0 + h) - 2.0 * f_x(x0) + f_x(x0 - h)) / pow(h, 2.0); // ����֐�
		m[4] = (f(x0 + h) - 2.0 * f(x0) + f(x0 - h)) / pow(h, 2.0); // �}�N��

		// ����֐��𗘗p�����ꍇ��choice�̑I�𕶎�, x0, fx0, h, dfdx0, d2fdx02 �̒l���R���\�[���ɏo��
		printf("u");
		for (int i=0; i < 5; i++)
			cout(u[i]);
		printf("\n");
		// �������֐��}�N���𗘗p�����ꍇ��choice�̑I�𕶎�, x0, fx0, h, dfdx0, d2fdx02 �̒l���R���\�[���ɏo��
		printf("m");
		for (int i=0; i < 5; i++)
			cout(m[i]);
		printf("\n");

		// ����֐��𗘗p�����ꍇ��choice�̑I�𕶎�,x0, fx0, h, dfdx0, d2fdx02 �̒l��csv�t�@�C���o��
		fprintf(fp, "u");
		for (int i=0; i < 5; i++)
			fout(u[i]);
		fprintf(fp,"\n");
		// �������֐��}�N���𗘗p�����ꍇ��choice�̑I�𕶎�,x0, fx0, h, dfdx0, d2fdx02 �̒l��csv�t�@�C���o��
		fprintf(fp, "m");
		for (int i=0; i < 5; i++)
			fout(m[i]);
		fprintf(fp,"\n");
	}
	fclose(fp); // �t�@�C���N���[�Y

	return 0;
}