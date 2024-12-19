// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_exam3.cpp
#include<stdio.h>
 #include<stdlib.h> // EOF�����ɕK�v
 #define _USE_MATH_DEFINES
 #include<math.h>

const int N_Max = 100; // �萔

//���ϒl�v�Z�֐�
double AvgFunc(int N_Data, double sum_x, double sum_y, double* p_x)
{
	*p_x = sum_x / N_Data;
	return sum_y / N_Data;
}

FILE* fp1;
FILE* fp2;

int main(void)
{
	double x[N_Max] = { 0 }, y[N_Max] = { 0 }; // �z��x,y��0�ŏ�����
	double sum_x = 0, sum_y = 0; // ���v�l�̃���

	int N_Data;

	// fp1��ǂݎ�胂�[�h�ŃI�[�v��
	fopen_s(&fp1, "data3.csv", "r");
	if (fp1 == NULL) //�G���[����
		return 1;

	// fp2���������݃��[�h�ŃI�[�v��
	fopen_s(&fp2, "Inoue_Akihiro_exam3.csv", "w");
	if (fp2 == NULL) //�G���[����
		return 1;

	printf("No.\t\tx\t\ty\n");
	fprintf(fp2, "No.,x,y\n"); // csv�ɏ�������



	// csv����Z���P�ʂœǂݍ���
	int i = 0;
	while ((fscanf_s(fp1, "%lf,%lf", &x[i], &y[i])) != EOF) // EOF�̓t�@�C���̏I�[
	{

		printf("%d\t%lf\t%lf\n", i+1, x[i], y[i]);
		fprintf(fp2, "%d,%lf,%lf\n", i+1, x[i], y[i]); // csv�ɏ�������

		//x,y���ꂼ��̍��v
		sum_x += x[i];
		sum_y += y[i];

		i++;
	}

	fclose(fp1); // �t�@�C���N���[�Y

	N_Data = i; //�f�[�^��

	printf("�f�[�^��\t%d\t\t%d\n", N_Data, N_Data); // �f�[�^���̕\��
	fprintf(fp2, "�f�[�^��,%d,%d\n", N_Data, N_Data); // csv�Ƀf�[�^���̏�������

	double avg_x,avg_y = AvgFunc(N_Data, sum_x, sum_y, &avg_x);

	printf("����\t%lf\t%lf\n", avg_x, avg_y); // ���ς̕\��
	fprintf(fp2, "����,%lf,%lf\n", avg_x, avg_y); // csv�ɕ��ς̏�������


	fclose(fp2); //�t�@�C���N���[�Y

	return 0;
}