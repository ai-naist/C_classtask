// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam2-1.cpp

# include<stdio.h>
# define _USE_MATH_DEFINES // ���l���Z�萔�̒�`
# include<math.h>

FILE* fp; // FILE�|�C���^�@fp�͊���̊֐���

int main(void) {

	// Open for write
	// FILE�|�C���^fp �� "�t�@�C����.�g���q" �� "�t�@�C�������݃��[�h" �̏���^����
	//�t�@�C�������݂��Ȃ��Ƃ��̓\�[�X�Ɠ����f�B���N�g���ɐV�K�쐬�����
	fopen_s(&fp, "Inoue_Akihiro_exam2-1.csv", "w");

	double x1 = 1.73;
	double y1 = log(2 * x1); // x1 �ɑ΂��� log(2*x1) �̎Z�o�l�� �ϐ� y1 �ɑ��

	//CUI�ł̕\��
	printf("x1 log(2x1)\n");
	printf("%.2lf %.8lf\n", x1, y1);

	//csv�t�@�C���ւ̑���
	fprintf(fp, "x1,log(2x1)\n"); // �\�^�C�g����csv�t�@�C���֏㏑���ۑ�
	fprintf(fp, "%.2lf,%.8lf\n", x1, y1); // x1 �� y1 �� �f�[�^��csv�t�@�C���֏㏑���ۑ�

	fclose(fp); //�t�@�C�������

	return 0;
}
