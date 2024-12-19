// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task3-1.cpp
#include<stdio.h>
#include<stdlib.h> // EOF�����ɕK�v
#define _USE_MATH_DEFINES
#include<math.h>

const int N_Max = 100; // �萔

// ���ϒl�v�Z�֐�
double AvgFunc(int N_Data, double sum)
{
	return sum / N_Data;
}

// �ő�l
double MaxFunc(int N_Data, double* array)
{
	double max = array[0]; // �z��̐擪�̒l�ŏ�����

	for (int i = 1; i < N_Data; i++)
	{
		if (array[i] > max)
			max = array[i];
	}

	return max;
}

// �ŏ��l
double MinFunc(int N_Data, double* array)
{
	double min = array[0]; // �z��̐擪�̒l�ŏ�����

	for (int i = 1; i < N_Data; i++)
	{
		if (array[i] < min)
			min = array[i];
	}

	return min;
}

// ���U
double VarFunc(int N_Data, double avg, double* array)
{
	double var = 0;

	for (int i = 0; i < N_Data; i++)
	{
		var += (avg - array[i]) * (avg - array[i]);
	}

	return var / (N_Data - 1);
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
	if (fp1 == NULL) // �G���[����
		return 1;

	// fp2���������݃��[�h�ŃI�[�v��
	fopen_s(&fp2, "Inoue_Akihiro_task3-1.csv", "w");
	if (fp2 == NULL) // �G���[����
		return 1;

	printf("No.\t\tx\t\ty\n");
	fprintf(fp2, "No.,x,y\n"); // csv�ɏ�������



	// csv����Z���P�ʂœǂݍ���
	int i = 0;
	while ((fscanf_s(fp1, "%lf,%lf", &x[i], &y[i])) != EOF) // EOF�̓t�@�C���̏I�[
	{

		printf("%d\t%lf\t%lf\n", i + 1, x[i], y[i]);
		fprintf(fp2, "%d,%lf,%lf\n", i + 1, x[i], y[i]); // csv�ɏ�������

		// x,y���ꂼ��̍��v
		sum_x += x[i];
		sum_y += y[i];

		i++;
	}

	fclose(fp1); // �t�@�C���N���[�Y

	N_Data = i; // �f�[�^��

	printf("�f�[�^��\t%d\t\t%d\n", N_Data, N_Data); // �f�[�^���̕\��
	fprintf(fp2, "�f�[�^��,%d,%d\n", N_Data, N_Data); // csv�Ƀf�[�^���̏�������

	double max_x = MaxFunc(N_Data, x), min_x = MinFunc(N_Data, x), max_y = MaxFunc(N_Data, y), min_y = MinFunc(N_Data, y);

	printf("�ő�\t%lf\t%lf\n", max_x, max_y); // �ő�̕\��
	fprintf(fp2, "�ő�,%lf,%lf\n", max_x, max_y); // csv�ɍő�̏�������

	printf("�ŏ�\t%lf\t%lf\n", min_x, min_y); // �ŏ��̕\��
	fprintf(fp2, "�ŏ�,%lf,%lf\n", min_x, min_y); // csv�ɍŏ��̏�������

	printf("�͈�\t%lf\t%lf\n", max_x - min_x, max_y - min_y); // �͈͂̕\��
	fprintf(fp2, "�͈�,%lf,%lf\n", max_x - min_x, max_y - min_y); // csv�ɔ͈͂̏�������

	double avg_x = AvgFunc(N_Data, sum_x), avg_y = AvgFunc(N_Data, sum_y);

	printf("����\t%lf\t%lf\n", avg_x, avg_y); // ���ς̕\��
	fprintf(fp2, "����,%lf,%lf\n", avg_x, avg_y); // csv�ɕ��ς̏�������

	double var_x = VarFunc(N_Data, avg_x, x), var_y = VarFunc(N_Data, avg_y, y);

	printf("���U\t%lf\t%lf\n", var_x, var_y); // ���U�̕\��
	fprintf(fp2, "���U,%lf,%lf\n", var_x, var_y); // csv�ɕ��U�̏�������

	printf("�W���΍�\t%lf\t%lf\n", sqrt(var_x), sqrt(var_y)); // �W���΍��̕\��
	fprintf(fp2, "�W���΍�,%lf,%lf\n", sqrt(var_x), sqrt(var_y)); // csv�ɕW���΍��̏�������


	fclose(fp2); //�t�@�C���N���[�Y

	return 0;
}