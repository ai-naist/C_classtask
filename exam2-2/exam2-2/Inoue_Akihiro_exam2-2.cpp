// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam2-2.cpp

# include<stdio.h>
# define _USE_MATH_DEFINES // ���l���Z�萔
# include<math.h>

FILE* fp; // FILE�|�C���^

int main(void) {

	// FILE�|�C���^fp �� "�t�@�C����.�g���q" �� "�t�@�C�������݃��[�h" �̏���^����
	fopen_s(&fp, "Inoue_Akihiro_exam2-2.csv", "w");

	double x, y;

	//�R���\�[���ŕ\��
	printf("x (5x)^0.3\n");
	//csv�ɏo��
	fprintf(fp, "x,(5x)^0.3\n");

	for (x = 0.5; x <= 10.5; x += 1.0) { // x �� 0.5 <= x <= 10.5 �͈̔͂� ���� 1.0�ŕω�������
		y = pow(5.0 * x, 0.3); //�ׂ��� a^b  ���� double pow(double a, double b);

		//�R���\�[���ŕ\��
		printf("%.1lf %lf\n", x, y);
		//csv�o��
		fprintf(fp, "%.1lf,%lf\n", x, y);

	}
	fclose(fp); //�t�@�C�����N���[�Y����

	return 0;
}