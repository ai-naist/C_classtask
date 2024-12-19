// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task3-2.cpp
#include<stdio.h>
#include<stdlib.h> // EOF�����ɕK�v
#define _USE_MATH_DEFINES
#include<math.h>

const int N_Max = 100; // �萔(�f�[�^�ǂݍ��ݗp�z��̑傫��)

// BMI
double BMIFunc(double height, double weight)
{
	return weight / height / height * 10000;
}

// ����
double AvgFunc(int N_Data, double sum)
{
	return sum / N_Data;
}

// ���U�ƕ��ς��������f�[�^�̃J�E���g
double VarFunc(int N_Data, double avg, double* array, double* pN_ex_avg)
{
	double var = 0;
	int N_ex_avg = 0;

	for (int i = 0; i < N_Data; i++)
	{
		var += (avg - array[i]) * (avg - array[i]); // ����2��a

		if ((avg - array[i]) < 0)
			N_ex_avg++; // ���ς��������f�[�^�̃J�E���g

	}

	*pN_ex_avg = N_ex_avg;

	return var / (N_Data - 1);
}

// �̌^�ʊ������J�E���g���A�󂯎�����z��̒l������������
void getDivArray(int div[5],int N_Data, double avg, double* bmi)
{
	for (int i = 0; i < N_Data; i++)
	{
		if (bmi[i] < 18.5)
			div[0]++;
		else if ((bmi[i] >= 18.5) && (bmi[i] < 20))
			div[1]++;
		else if ((bmi[i] >= 20) && (bmi[i] < 25))
			div[2]++;
		else if ((bmi[i] >= 25) && (bmi[i] < 30))
			div[3]++;
		else
			div[4]++;
	}
}


FILE* fp1;
FILE* fp2;

int main(void)
{
	double height[N_Max] = { 0 }, weight[N_Max] = { 0 }, bmi[N_Max] = { 0 }; // �z���0�ŏ�����
	double sum_height = 0, sum_weight = 0, sum_bmi = 0; // ���v�l�̃���

	int N_Data; // �f�[�^��

	// fp1��ǂݎ�胂�[�h�ŃI�[�v��
	fopen_s(&fp1, "healthdata.csv", "r");
	if (fp1 == NULL) // �G���[����
		return 1;

	// fp2���������݃��[�h�ŃI�[�v��
	fopen_s(&fp2, "Inoue_Akihiro_task3-2.csv", "w");
	if (fp2 == NULL) // �G���[����
		return 1;

	printf("����No.\t\t\t�g��\t�̏d\tBMI\n"); // �^�C�g���̕\��
	fprintf(fp2, "����No.,�g��,�̏d,BMI\n"); // csv�ɏ�������



	// csv����Z���P�ʂœǂݍ���
	int i = 0;
	while ((fscanf_s(fp1, "%lf,%lf", &height[i], &weight[i])) != EOF) // EOF�̓t�@�C���̏I�[
	{

		bmi[i] = BMIFunc(height[i], weight[i]);

		printf("%d\t\t\t%.2f\t%.2f\t%.2f\n", i + 1, height[i], weight[i], bmi[i]); // �e�f�[�^�̕\��
		fprintf(fp2, "%d,%.2f,%.2f,%.2f\n", i + 1, height[i], weight[i], bmi[i]); // csv�ɏ�������

		// �e�f�[�^���ꂼ��̍��v
		sum_height += height[i];
		sum_weight += weight[i];
		sum_bmi += bmi[i];

		i++;
	}

	fclose(fp1); // �t�@�C���N���[�Y

	N_Data = i; // �f�[�^��

	printf("�f�[�^��\t\t%d\t%d\t%d\n", N_Data, N_Data,N_Data); // �f�[�^���̕\��
	fprintf(fp2, "�f�[�^��,%d,%d,%d\n", N_Data, N_Data,N_Data); // csv�Ƀf�[�^���̏�������

	// ���ς���
	double avg_height = AvgFunc(N_Data, sum_height), avg_weight = AvgFunc(N_Data, sum_weight), avg_bmi = AvgFunc(N_Data, sum_bmi);

	printf("����\t\t\t%.2f\t%.2f\t%.2f\n", avg_height, avg_weight,avg_bmi); // ���ς̕\��
	fprintf(fp2, "����,%.2f,%.2f,%.2f\n", avg_height, avg_weight,avg_bmi); // csv�ɕ��ς̏�������

	double hei_ex_avg, wei_ex_avg, bmi_ex_avg; // ���ς��������f�[�^�p�̕ϐ�

	// ���U����
	double var_height = VarFunc(N_Data, avg_height, height, &hei_ex_avg), var_weight = VarFunc(N_Data, avg_weight, weight, &wei_ex_avg), var_bmi = VarFunc(N_Data, avg_bmi, bmi, &bmi_ex_avg);

	printf("�W���΍�\t\t%.2f\t%.2f\t%.2f\n", sqrt(var_height), sqrt(var_weight),sqrt(var_bmi)); // �W���΍��̕\��
	fprintf(fp2, "�W���΍�,%.2f,%.2f,%.2f\n", sqrt(var_height), sqrt(var_weight),sqrt(var_bmi)); // csv�ɕW���΍��̏�������

	printf("���ς�����������(��)\t%.2f\t%.2f\t%.2f\n", hei_ex_avg/N_Data*100,wei_ex_avg/N_Data*100,bmi_ex_avg/N_Data*100); // ���ς������������̕\��
	fprintf(fp2, "���ς�����������(��),%.2f,%.2f,%.2f\n", hei_ex_avg / N_Data * 100, wei_ex_avg / N_Data * 100, bmi_ex_avg / N_Data * 100); // csv�ɕ��ς������������̏�������

	int div[5] = { 0 }; // �z��v�f 0:�����߂� 1:���e�̌^ 2:�K�� 3:����C�� 4:����߂� �ɑΉ�����
	char pattern[6][100] = { "���������̊���(��)","���e�̌^�̊���(��)","�K���̊i�̊���(��)","����C���̊���(��)","���肷���̊���(��)" ,"�����̍��v(��)"};
	// 2�����z�񏑎� char array[��][����]

	getDivArray(div, N_Data, avg_bmi, bmi); // �z��div�Ƀ|�C���^�n��
	
	double sum_rate = 0; // ���v�����̃���

	for (i = 0; i < 5; i++)
	{
		double div_rate = div[i]; // ���������_���ɕϊ�
		div_rate = div_rate / N_Data * 100;


		printf("%s\t\t\t%.2f\n", pattern[i], div_rate); // �̌^�ʊ����̕\��
		fprintf(fp2, "%s,,,%.2f\n", pattern[i], div_rate); // csv�ɑ̌^�ʊ����̏�������

		sum_rate += div_rate;
	}

	printf("%s\t\t\t\t%.f\n", pattern[i], sum_rate); // ���v�����̕\��
	fprintf(fp2, "%s,,,%.f\n", pattern[i], sum_rate); // csv�ɍ��v�����̏�������


	fclose(fp2); //�t�@�C���N���[�Y

	return 0;
}