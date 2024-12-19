//�w�Дԍ��F1201201034
//�|�[�^��ID�Fseb01034
//�����F�}������
//�v���O�������Fkasahara_genya_exam6.cpp
# include<stdio.h> // �t�@�C�����̓��o�͑���̂��߂̕W�����o�̓w�b�_�[�t�@�C���̓Ǎ���
#include<stdlib.h> // EOF �̏������ł��邽�߂̕W�����C�u�����w�b�_�[�t�@�C���̓Ǎ���
# define _USE_MATH_DEFINES // ���l���Z�萔(�~������) �� ��`
# include<math.h> //���l���Z�萔����`���ꂽ�w�b�_�t�@�C���̓Ǎ���
#include<time.h> // �������Ԃ��v�鏈�����s�����߂̃w�b�_�[�t�@�C���̓ǂݍ���
// #define �𗘗p���āA���̒T���Ԋu ��x �� 0.001 �ɐݒ肷��v���O�������쐬
#define delta_x 0.001
// �����t���֐��`���}�N���𗘗p�����C����`������ f(x) �̒�`�E�쐬
#define f(x) (log(x)-cos(x))
// ����`�������̋ߎ����̒T�����ʂ��t�@�C���o�͂��邽�߂̃t�@�C���|�C���^�̒�`
FILE* fp;

// �ċA�֐��Ăяo���𗘗p��������֐�(�l�n���E�߂�l����)�̒�`(�v���g�^�C�v�錾)
// ������(���͏��)�̒�` double x1, int n
double direct_recursion(double x1, int n);

int main(void){
	//�������Ԃ��v�邽�߂̎��ԕϐ��̒�`
	clock_t start, end;
	//�����J�n���O�̎��Ԃ�ۑ�
	start = clock();

	double a;
	double x1; // ����^�������̉��̋ߎ������i�[���邽�߂̎����^�ϐ���`
	int n; // ������
	// Step 1 : ���̒T���J�n�_ a �� 0.001 �� �ݒ�
	a = 0.001;

	// step 2 - start -
	x1 = a; // x1 �� a �� ������
	n = 1;// ������ n �� 1 �ɏ�����
    // step 2 - end -
	// ���͏��ƂȂ�������Ƃ��āAx1, n �̒l��l�n���Ŏ���֐� direct_recursion �� �Ăяo��
	x1 = direct_recursion(x1, n); // (�G)�Ɏ���������͂��Ă��������B

	// step 5 - ���s���ʂ�csv�t�@�C���ւ̃t�@�C���o�͂̏���
	// Open for write (csv�t�@�C���ɒǋL�����݃��[�h�ŕۑ����A�t�@�C���o�͂���t�@�C���I�[�v������)
	fopen_s(&fp, "kasahara_genya_exam6.csv", "a");
	// step 5 - �T�����ʂ�PC ��ʏ�ɕ\��
	printf("\nf(x)=log(x)-cos(x)=0\n\n");
	printf("���ڒT���@�ɂ��ߎ����F%.8lf\n\n", x1);
	// �T������ �� csv �t�@�C���֏o��(�ǋL�����݃��[�h�ɐݒ肵��csv �t�@�C��)
	fprintf(fp, "\nf(x)=log(x)-cos(x)=0\n\n");
	fprintf(fp, "���ڒT���@�ɂ��ߎ����F%.8lf\n\n", x1);
	
	// �S�Ă̏����I������̎��Ԃ�ۑ�
	end = clock();
	
	// �T����������(�b)�� PC ��ʕ\��
	printf("�������ԁF%lf�b\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	// �T����������(�b)�� csv �t�@�C���֏o��(�ǋL�����݃��[�h�ɐݒ肵��csv �t�@�C��)
	fprintf(fp, "�������ԁF%lf�b\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	// FILE�|�C���^ fp �ŃI�[�v�������t�@�C�����N���[�Y����
	fclose(fp);
	return(0);
}
//step3�`step4������֐���
double direct_recursion(double x1, int n)//������x1�Ɣ�����n
{
	fopen_s(&fp, "kasahara_genya_exam6.csv", "a");//�t�@�C�����I�[�v��
	double x2, y1, y2;
	//�����t���֐��`���}�N���𗘗p����x1�ɑ΂���֐��ly1���v�Z
	y1 = f(x1);
	//x2�̎Z�o
	x2 = x1 + delta_x;
	//�����t���֐��`���}�N���𗘗p����x2�ɑ΂���֐��ly2���v�Z
	y2 = f(x2);

	if (n == 1) {
		printf("������n\tx1\tf(x1)\n");//�r���o�ߕ\���^�C�g����PC��ʕ\��
		printf("%d\t%.8lf\t%.8lf\n", n, x1, f(x1));//n=1�̎��̂��ꂼ��̒l��PC��ʕ\��
		fprintf(fp, "������n,x1,y1\n");//�r���o�ߕ\���^�C�g�����t�@�C���o��
		fprintf(fp, "%d,%.8lf,%.8lf\n", n, x1, y1);//n=1�̎��̂��ꂼ��̒l��PC��ʕ\��
	}
	else {
		printf("%d\t%.8lf\t%.8lf\n", n, x1, y1);//�T���r���o�߂̒l��PC��ʕ\��
		fprintf(fp, "%d,%.8lf,%.8lf\n", n, x1, y1);//�T���r���o�߂̒l���t�@�C���o��
	}
	x1 = x2;//x1��x2�X�V
	n++;//n���X�V
	if (y1 * y2 <= 0) //�ߎ���x1�̒T�������̌J��Ԃ����[�v�̒E�o����
	{
		fclose(fp);//�t�@�C�����N���[�Y
		x1 = x1 - delta_x;//�]���ȃ�x��x1��������Đ������ߎ���x1�ɋ��߂Ȃ���
		return x1;//����`�������̋ߎ���x1�̒l������֐��Ăяo���� main �֐��ɖ߂�
	}
	else //x1�����`�������̋ߎ����Ƃ��Ĕ���ł��Ȃ������ꍇ
	{
		fclose(fp);//�t�@�C�����N���[�Y
		return direct_recursion(x1, n);//���݂�x1��n���������Ƃ��āA�ċA�֐��Ăяo���ɖ߂�A����`�������̋ߎ����̒T���𑱂���
	}
}