// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task4.cpp

#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES // ���l���Z�萔

// �֐��`���}�N����p���Ĕ�ϕ��֐� f(x)���`����
#define f(x) (4.0/(1.0+pow((x),2.0)))
// ���� #define �}�N����(������,...) (�u����̎�)


FILE* fp; // �t�@�C���|�C���^�̐錾

int main(void)
{
	// fp���������݃��[�h�ŃI�[�v��
	fopen_s(&fp, "Inoue_Akihiro_task4.csv", "w");
	if (fp == NULL) // �G���[����
		return 1;

	int n = 400; // ��ԕ�����(�����l) n �̎w��
	double a = 0, b = 1;	// �ϕ����[a,b]�̎w��
	double T; // �ϕ��l
	double h = (b - a) / n; // ��ԕ�

	// �^�C�g���̏o��
	printf("��`���ɂ�鐔�l�v�Z\n");
	fprintf(fp, "��`���ɂ�鐔�l�v�Z\n");

	// ��ϕ��֐� f(x)�̕\��
	printf("��ϕ��֐� f(x) = 4.0 / ( 1.0 + x*x )\n");
	fprintf(fp,"��ϕ��֐�,f(x) = 4.0 / ( 1.0 + x*x )\n");

	// �ϕ����[a,b]�̕\��
	printf("�ϕ����[a�Cb]) a=%.2f b=%.2f\n",a,b);
	fprintf(fp, "�ϕ����[a�Cb],a=%.2f,b=%.2f\n",a,b);

	// ��ԕ�����(�����l) n �̕\��
	printf("���l�ϕ��̋�ԕ����� n=%d\n", n);
	fprintf(fp,"���l�ϕ��̋�ԕ�����,n=%d\n", n);

	// ��`���ɂ�鐔�l�ϕ��̏���
	T = (f(a) + f(b)) / 2.0;
	for (int i = 1; i < n; i++)
		T += f(a + i * h);

	T = h * T;

	// ���ʂ̏o��
	printf("f(x)�̐ϕ��̋ߎ��l T = %.10f\n", T);
	fprintf(fp,"f(x)�̐ϕ��̋ߎ��l,T = %.10f\n", T);

	fclose(fp); // �t�@�C���N���[�Y

	return 0;
}