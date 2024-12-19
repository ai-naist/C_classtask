// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task10_bonus3.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>

const double UOM = 1.0; // ����P�� : Unit of Measure �� ��

// �|�C���^�ƌ^���w�肵�ă������̊m�ۂƏ��������s���}�N��
#define GetArray(ptr, type, N)                                                  \
	{                                                                           \
		ptr = (type *)calloc((N), sizeof(type));                                \
		if (ptr == NULL)                                                        \
		{                                                                       \
			printf("%s �^�̔z�� %s �̃��������m�ۂł��܂���B\n", #type, #ptr); \
			exit(EXIT_FAILURE);                                                 \
		}                                                                       \
	}

// �������J����������NULL�N���A����}�N��
#define free_null(ptr) \
	{                  \
		free(ptr);     \
		ptr = NULL;    \
	}

FILE *fp; // CSV�o�͗p

// switch-case �̕���p
enum PRN_Type
{
	UniformRN = 1,
	NormalRN,
	ExpRN,
	PoissonRN
};

// �v���g�^�C�v�錾
inline double Uni(const int);
inline double Normal(const char *);
void InputAB(double *, double *);
void InputMuSig(double *, double *);
void Generate_U_RN(const int, const double, const double, double *);
void Generate_N_RN(const int, const double, const double, double *);
void Generate_Exp_RN(const int, const double, double *);
void Generate_Poisson_RN(const int, const double, double *);
void CulcData(const int, double *, double *, double *, double *, double *, double *, double *);
void OutputData(const int, const int, const double, const double, const double, const double, const double,
				double *, double *, double *, double *, double *, double *, double *);
void OutputFreq(const int, const int, const double, const double *, const double *, const double *, int *, int *, double *, double *);
void CreateRN(const int, double *, double *, double *, double *, double *, double *, int *);

int main(void)
{
	srand((unsigned int)time(NULL));
	//srand(123); // ���쌟�ؗp

	// fp �I�[�v�� a���[�h
	if (fopen_s(&fp, "Inoue_Akihiro_task10_bonus3.csv", "a") != 0)
		exit(EXIT_FAILURE);

	int N; // �����̐�����
	do
	{
		printf("�����̐����� N �� �����l�Ŏw�肵�ĉ����� ---> ");
		scanf_s("%d", &N);
	} while (N % 2 == 1); // �����w��

	double *x;
	GetArray(x, double, N);

	double a, b;	   // ��l�����͈̔�
	double mu, sigma;  // ���K�����̏��������i�^�l�j
	double lambda;	   // ���ۂ̕��ϔ�����
	int choice;		   // �����̌^�i 1 : ��l����	2 : ���K���� �j
	bool check = true; // �����̌^�I�����[�v�p

	// �����̌^��I�����Đ���
	CreateRN(N, &a, &b, &mu, &sigma, &lambda, x, &choice);

	double xmax = -DBL_MAX; // �ő�l
	double xmin = DBL_MAX;	// �ŏ��l
	double sum = 0;			// �a
	double avx = 0;			// ����
	double vx = 0;			// ���U
	double sx = 0;			// �W���΍�

	// �����̃f�[�^���v�Z
	CulcData(N, &xmax, &xmin, &sum, &avx, &vx, &sx, x);

	// �����̌^�ŕ��򂵂ă^�C�g���ƁA�����̃f�[�^���o��
	OutputData(N, choice, a, b, mu, sigma, lambda, &xmax, &xmin, &sum, &avx, &vx, &sx, x);

	int k; // ���̐�
	printf("\n���̐� k �� �����l �� �w�肵�ĉ����� ---> ");
	scanf_s("%d", &k);

	// ���̋�ԕ� h �̐ݒ�
	double h = ceil((xmax - xmin) / (double)k);

	double *x_interval; // ���̋�Ԓl
	GetArray(x_interval, double, k + 1);
	x_interval[0] = xmin - (UOM / 2);		   // �f�[�^��Ԃ̉����l�ݒ�
	for (int i = 1; i < k + 1; i++)			   //
		x_interval[i] = x_interval[i - 1] + h; // �e���̃f�[�^��Ԓl�̐ݒ�

	double *x_midval; // ��Ԃ̐^�񒆂̒l
	GetArray(x_midval, double, k);
	for (int i = 0; i < k; i++)
		x_midval[i] = (x_interval[i] + x_interval[i + 1]) / 2;

	int *freq;			  // �x��
	int *cum_freq;		  // �ݐϓx��
	double *rel_freq;	  // ���Γx��
	double *cum_rel_freq; // �ݐϑ��Γx��

	GetArray(freq, int, k);
	GetArray(cum_freq, int, k);
	GetArray(rel_freq, double, k);
	GetArray(cum_rel_freq, double, k);

	// ���̕\���Ɠx���e�[�u���̏o��
	OutputFreq(N, k, h, x, x_interval, x_midval, freq, cum_freq, rel_freq, cum_rel_freq);

	// �t�@�C���N���[�Y
	fclose(fp);
	// ���������
	free_null(x);
	free_null(x_interval);
	free_null(x_midval);
	free_null(freq);
	free_null(rel_freq);
	free_null(cum_freq);
	free_null(cum_rel_freq);

	return 0;
}

// ��l�����̌v�Z
inline double Uni(const int d)
{
	return ((double)rand() + d) / ((double)RAND_MAX + d);
}

// ���K���������̌v�Z
inline double Normal(const char *tri)
{
	if (strcmp(tri, "sin") == 0)
		return sqrt(-2.0 * log(Uni(1))) * sin(2.0 * M_PI * Uni(1));
	else if (strcmp(tri, "cos") == 0)
		return sqrt(-2.0 * log(Uni(1))) * cos(2.0 * M_PI * Uni(1));
	else
		exit(EXIT_FAILURE);
}

// �w�����������̌v�Z
inline double ExpRand(const double lambda)
{
	return (-1.0 / (lambda)) * log(Uni(1));
}

// �͈�[a,b]�̓���
void InputAB(double *p_a, double *p_b)
{
	do
	{
		do
		{
			printf("\n�����^��l�����͈̔� [ a , b ] ���w�肵�ĉ�����\n"
				   "a ---> ");
			scanf_s("%lf", p_a);
		} while (*p_a < 1.0);
		printf("b ---> ");
		scanf_s("%lf", p_b);
	} while (*p_a > *p_b); // 1.0 �� a �� b �̏����w�����
}

// ���� �� �� �W���΍� �� �̓���
void InputMuSig(double *p_mu, double *p_sigma)
{
	do
	{
		printf("\n���K�����̕��� �� �� �W���΍� �� ���w�肵�ĉ�����\n"
			   "�� ---> ");
		scanf_s("%lf", p_mu);
		printf("�� ---> ");
		scanf_s("%lf", p_sigma);
	} while ((*p_mu - 3 * (*p_sigma)) <= 0); // �� > 3�� �̏����w�����
}

void InputExpLambda(double *p_lambda)
{
	printf("\n�w�������̐����ɑ΂��鎖�ۂ̕��ϔ����� lambda ���w�肵�Ă�������\n"
		   "lambda ---> ");
	scanf_s("%lf", p_lambda);
}

void InputPoissonLambda(double *p_lambda)
{
	printf("\n�|�A�\�������̐����ɑ΂��鎖�ۂ̕��ϔ����� lambda ���w�肵�Ă�������\n"
		   "lambda ---> ");
	scanf_s("%lf", p_lambda);
}

// ��l�����𐶐�
void Generate_U_RN(const int N, const double a, const double b, double *x)
{
	// �͈�[a,b]�̎����^��l������ N ����
	for (int i = 0; i < N; i++)
		x[i] = a + (b - a) * Uni(0);
}

// ���K�����𐶐�
void Generate_N_RN(const int N, const double mu, const double sigma, double *x)
{
	// ���� �� �� �W���΍� �� �̐��K���z�ɏ]�����K���� (�{�b�N�X�E�~�����[�@)�� N ����
	for (int i = 0; i < N; i = i + 2)
	{
		x[i] = mu + sigma * Normal("cos");
		x[i + 1] = mu + sigma * Normal("sin");
	}
}

// �w�������𐶐�
void Generate_Exp_RN(const int N, const double lambda, double *x)
{
	for (int i = 0; i < N; i++)
	{
		x[i] = ExpRand(lambda);
	}
}

// �|�A�\�������𐶐�
void Generate_Poisson_RN(const int N, const double lambda, double *x)
{
	for (int i = 0; i < N; i++)
	{
		double sum_ti = 0.0;
		int j = 0;
		for (; sum_ti < 1; j++)
			sum_ti += ExpRand(lambda);

		x[i] = --j;
	}
}

// �����̃f�[�^���v�Z
void CulcData(const int N, double *pmax, double *pmin, double *psum, double *pavx, double *pvx, double *psx, double *x)
{
	for (int i = 0; i < N; i++)
	{
		// �a
		*psum += x[i];
		// �ő�l
		if (*pmax < x[i])
			*pmax = x[i];
		// �ŏ��l
		if (*pmin > x[i])
			*pmin = x[i];
	}
	// ���ϒl
	*pavx = *psum / N;
	// ���U
	for (int i = 0; i < N; i++)
		*pvx += pow((x[i] - *pavx), 2);
	*pvx = *pvx / N;
	// �W���΍�
	*psx = sqrt(*pvx);
}

// �����̌^�ŕ��򂵂ă^�C�g���ƁA�����̃f�[�^�e�[�u�����o��
void OutputData(const int N, const int choice, const double a, const double b, const double mu, const double sigma, const double lambda,
				double *pmax, double *pmin, double *psum, double *pavx, double *pvx, double *psx, double *x)
{
	switch (choice)
	{
	case UniformRN:
		printf("\n�����^��l�����f�[�^�̓��v��������\n"
			   "\n�f�[�^�͈�\ta\tb\n"
			   "\t\t%g\t%g\n\n",
			   a, b);
		fprintf(fp, "�����^��l�����f�[�^�̓��v��������\n"
					"\n�f�[�^�͈�,a,b\n"
					",%g,%g\n\n",
				a, b);
		break;

	case NormalRN:
		printf("\n���K�����f�[�^�̓��v��������\n"
			   "\n���K���z\t����\t�W���΍�\n"
			   "�^�̒l\t\t%g\t%g\n\n",
			   mu, sigma);
		fprintf(fp, "���K�����f�[�^�̓��v��������\n"
					"\n���K���z,����,�W���΍�\n"
					"�^�̒l,%g,%g\n\n",
				mu, sigma);
		break;

	case ExpRN:
		printf("\n�w�������f�[�^�̓��v��������\n"
			   "\n���ۂ̕��ϔ�����\t%g\n"
			   "���ۂ̕��ϔ����Ԋu\t%g\n",
			   lambda, 1 / lambda);
		fprintf(fp, "\n�w�������f�[�^�̓��v��������\n"
					"\n���ۂ̕��ϔ�����,%g\n"
					"���ۂ̕��ϔ����Ԋu,%g\n",
				lambda, 1 / lambda);
		break;

	case PoissonRN:
		printf("\n�|�A�\�������f�[�^�̓��v��������\n"
			   "\n���ۂ̕��ϔ�����\t%g\n",
			   lambda);
		fprintf(fp, "\n�|�A�\�������f�[�^�̓��v��������\n"
					"\n���ۂ̕��ϔ�����,%g\n",
				lambda);
		break;
	}

	// �f�[�^���e�[�u��
	printf("�f�[�^��\t\t%d\n"
		   "�f�[�^�̕���\t\t%lf\n"
		   "�f�[�^�̕s�Ε��U\t%lf\n"
		   "�f�[�^�̕W���΍�\t%lf\n"
		   "�f�[�^�̍ő�l\t\t%lf\n"
		   "�f�[�^�̍ŏ��l\t\t%lf\n",
		   N, *pavx, *pvx, *psx, *pmax, *pmin);
	fprintf(fp, "�f�[�^��,%d\n"
				"�f�[�^�̕���,%lf\n"
				"�f�[�^�̕s�Ε��U,%lf\n"
				"�f�[�^�̕W���΍�,%lf\n"
				"�f�[�^�̍ő�l,%lf\n"
				"�f�[�^�̍ŏ��l,%lf\n",
			N, *pavx, *pvx, *psx, *pmax, *pmin);
}

// �x���e�[�u���̏o��
void OutputFreq(const int N, const int k, const double h, const double *x, const double *x_interval, const double *x_midval,
				int *freq, int *cum_freq, double *rel_freq, double *cum_rel_freq)
{
	// ���̕\���Ɠx���e�[�u���̃^�C�g��
	printf("\n���̐�\t\t%d\n"
		   "���̋�ԕ�\t%g\n"
		   "\n�f�[�^���\t\t\t���Ԃ̒l\t�x��\t�ݐϓx��\t���Γx��\t�ݐϑ��Γx��\n",
		   k, h);
	fprintf(fp, "\n���̐�,%d\n"
				"���̋�ԕ�,%g\n"
				"\n�f�[�^���,���Ԃ̒l,�x��,�ݐϓx��,���Γx��,�ݐϑ��Γx��\n",
			k, h);

	int temp_freq = 0;			// �ݐϓx���̈ꎞ�L��
	for (int i = 0; i < k; i++) // ���̍X�V
	{
		for (int j = 0; j < N; j++) // �f�[�^�̌���
		{
			if ((x_interval[i] <= x[j]) && (x[j] < x_interval[i + 1]))
				freq[i]++; // ���݂̋��ɂ��鐔�l���J�E���g�i�x���j
		}
		cum_freq[i] = temp_freq + freq[i];				   // �ݐϓx��
		rel_freq[i] = (double)freq[i] / (double)N;		   // ���Γx���̎Z�o
		cum_rel_freq[i] = (double)cum_freq[i] / (double)N; // �ݐϑ��Γx���̎Z�o
		temp_freq = cum_freq[i];						   // �ݐϓx���̍X�V�p

		// �x���e�[�u���̏o��
		printf("%lf �| %lf\t%lf\t%d\t%d\t\t%lf\t%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
		fprintf(fp, "%lf �| %lf,%lf,%d,%d,%lf,%lf\n", x_interval[i], x_interval[i + 1], x_midval[i], freq[i], cum_freq[i], rel_freq[i], cum_rel_freq[i]);
	}
	// �݌v�̏o��
	printf("\t\t\t\t\t\t�݌v\t%d\t\t�݌v\t\t%g\n", cum_freq[k - 1], cum_rel_freq[k - 1]);
	fprintf(fp, ",,�݌v,%d,�݌v,%g\n\n", cum_freq[k - 1], cum_rel_freq[k - 1]);
}

// �����̌^��I�����Đ���
void CreateRN(const int N, double *p_a, double *p_b, double *p_mu, double *p_sigma, double *p_lambda, double *x, int *pchoice)
{
	bool check = true;
	do
	{
		printf("\n1 : �͈�[a,b]�̎����^��l�����̐���\n"			  // Uniform Random Number
			   "\n2 : ���� �� �� �W���΍� �� �̐��K�����̐���\n"		  // Normal Random Number
			   "\n3 : ���ۂ̕��ϔ������ԊԊu 1 / lambda �̎w������\n" // Exponential Random Number
			   "\n4 : ���ۂ̕��ϔ����� lambda �̃|�A�\������\n"		  // Poisson Random Number
			   "\n�������闐���̑I��ԍ��� 1 �` 4 ��� 1 ���͉�����. ---> ");
		scanf_s("%d", pchoice);

		// �����̌^�ŏ������򂵂āA�[����������
		switch (*pchoice)
		{
		case UniformRN:
			InputAB(p_a, p_b);
			Generate_U_RN(N, *p_a, *p_b, x);
			check = false;
			break;

		case NormalRN:
			InputMuSig(p_mu, p_sigma);
			Generate_N_RN(N, *p_mu, *p_sigma, x);
			check = false;
			break;

		case ExpRN:
			InputExpLambda(p_lambda);
			Generate_Exp_RN(N, *p_lambda, x);
			check = false;
			break;

		case PoissonRN:
			InputPoissonLambda(p_lambda);
			Generate_Poisson_RN(N, *p_lambda, x);
			check = false;
			break;

		default:
			printf("\n�I��ԍ��Ɍ�肪����܂��D�ēx�C�I��ԍ�����͂��Ȃ����ĉ������D\n");
		}
	} while (check);
}