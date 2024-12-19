// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task4_bonus.cpp

#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES // ���l���Z�萔

// �֐��`���}�N����p���Ĕ�ϕ��֐� f(x)���`����
#define f(x) (4.0/(1.0+pow((x),2.0)))

FILE* fp; // �t�@�C���|�C���^�̐錾

int main(void)
{
	// fp���������݃��[�h�ŃI�[�v��
	fopen_s(&fp, "Inoue_Akihiro_task4_bonus.csv", "w");
	if (fp == NULL) // �G���[����
		return 1;

	int n = 400; // ��ԕ�����(�����l) n �̎w��
	double a = 0, b = 1; // �ϕ����[a,b]�̎w��
	double S; // �ϕ��l
	double h = (b - a) / (2.0 * n); // ��ԕ�

	// �^�C�g���̏o��
	printf("�V���v�\�����ɂ�鐔�l�v�Z\n");
	fprintf(fp, "�V���v�\�����ɂ�鐔�l�v�Z\n");

	// ��ϕ��֐� f(x)�̕\��
	printf("��ϕ��֐� f(x) = 4.0 / ( 1.0 + x*x )\n");
	fprintf(fp, "��ϕ��֐�,f(x) = 4.0 / ( 1.0 + x*x )\n");

	// �ϕ����[a,b]�̕\��
	printf("�ϕ����[a�Cb]) a=%.2f b=%.2f\n", a, b);
	fprintf(fp, "�ϕ����[a�Cb],a=%.2f,b=%.2f\n", a, b);

	// ��ԕ�����(�����l) n �̕\��
	printf("���l�ϕ��̋�ԕ����� n=%d\n", n);
	fprintf(fp, "���l�ϕ��̋�ԕ�����,n=%d\n", n);

	// �V���v�\�����ɂ�鐔�l�ϕ��̏���
	S = f(a) + f(b);
	for (int i = 1; i < n; i++)
		S += 4.0 * f(a + (2.0 * i - 1.0) * h) + 2.0 * f(a + 2.0 * i * h);

	S += 4.0 * f(a + (2.0 * n - 1.0) * h);
	S = (S * h) / 3.0;

	// ���ʂ̏o��
	printf("f(x)�̐ϕ��̋ߎ��l T = %.15f\n", S);
	fprintf(fp, "f(x)�̐ϕ��̋ߎ��l,T = %.15f\n", S);

	fclose(fp); // �t�@�C���N���[�Y

	return 0;
}