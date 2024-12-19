//�w�Дԍ��@1201201038
//�|�[�^��ID�@seb01038
//�����@���c�S��
//�v���O�������@kamata_yuusei_task10.cpp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

FILE *fp;

int main(void)
{

	fopen_s(&fp, "kamata_yuusei_task10.csv", "a");

	double ramda = 0.4;
	double myu = 0.2;
	int s = 3;
	double T = 0.0;
	double delta_t = 0.0;

	printf("�V�~�����[�V��������T�������l�œ��͂��Ă��������B��");
	scanf_s("%.2f", &T);
	printf("\n���Ԃ̍���delta_t�������l�œ��͂��Ă��������B��");
	scanf_s("%.2f", &delta_t);

	printf("�q�̕��ϓ����� ramda = %.1f\nATM�@1�䓖����̕��σT�[�r�X�� myu = %.1f\nATM�@�̐ݒu�䐔 s = %d\n", ramda, myu, s);
	fprintf(fp, "�q�̕��ϓ����� ramda = %.1f\nATM�@1�䓖����̕��σT�[�r�X�� myu = %.1f\nATM�@�̐ݒu�䐔 s %d\n", ramda, myu, s);

	int q = 0;	   //�q�̓����̗L�����m�F����ϐ��̒�`
	int sum_q = 0; // �q�̓����l�����J�E���g����ϐ��̒�`

	srand((unsigned int)time(NULL));

	double u, ca, ca_time; // ���z�֐��l�C�q�̓������ԊԊu�Ƌq�̓������Ԃ��i�[����ϐ��̒�`

	u = (double)(rand() + 1) / (double)(RAND_MAX + 1);

	ca = (-1.0 / ramda) * log(u);

	ca_time = ca;

	int *sv; // ATM�@s ��̋󂫏󋵂��L�^����ꎟ���z��sv �̒�`��0 �ɏ�����

	sv = (int *)malloc((s + 1) * sizeof(int));

	int win;

	for (win = 0; win < (s + 1); win++)
	{ //�ꎟ���z��sv [s] �̒�`-- AT M�@s �䂪�S�ċ󂫂Ƃ���0  �ɏ����ݒ�
		sv[win] = 0;
	}

	int sq = 0; // �q�̃T�[�r�X�����̊����L�����`�F�b�N����ϐ���`��0�ɏ�����

	double st_win; //�q�����蓖�Ă�ꂽ�eATM�@�̃T�[�r�X���Ԃ��i�[����ϐ��̒�`

	double *stime; //�q�����蓖�Ă�ꂽ�eATM�@�̃T�[�r�X�I�����Ԃ��i�[����z��̒�`�Ə�����

	stime = (double *)malloc((s + 1) * sizeof(double));

	for (win = 0; win < (s + 1); win++)
	{ //
		stime[win] = 0;
	}

	int fsq = 0;

	double t; //  ���݂̃V�~�����[�V�������Ԃ��i�[����ϐ��̒�`

	for (t = 0.0; t <= T; t = t + delta_t)
	{

		if (t >= ca_time)
		{
			q = 1;
			sum_q = sum_q + 1;

			u = (double)(rand() + 1) / (double)(RAND_MAX + 1);

			ca = (-1.0 / ramda) * log(u);

			ca_time = ca + t;
		}

		for (win = 1; win < (s + 1); win++)
		{
			if (q = 1)
			{
				if (sv[win] = 0)
				{

					sv[win] = 1;
					sq = 1;
					q = 0;

					u = (double)(rand() + 1) / (double)(RAND_MAX + 1);

					st_win = (-1.0 / myu) * log(u);

					stime[win] = st_win + t; //�q�����蓖�Ă�ꂽATM�@win �̃T�[�r�X�I�����Ԃ̎Z�o
				}
			}

			if (sq = 1)
			{
				if (stime[win] <= t + delta_t)
				{

					sv[win] = 0;

					stime[win] = 0.0;

					sq = 0;

					fsq = fsq + 1;
				}
			}
		}
	}

	double act_ro;

	act_ro = sum_q / fsq;

	printf("\n\n�V�~�����[�V�������� T = %.1f�܂ł̋q�̓������� sum_q = %d\n\n�V�~�����[�V��������T = %.1f �܂ł�ATM�@�ݒu�䐔�R��ŃT�[�r�X���I�������q�̑��� fsq = %d\n\n", T, sum_q, T, fsq);
	fprintf(fp, "\n\n�V�~�����[�V�������� T = %.1f�܂ł̋q�̓������� sum_q = %d\n\n�V�~�����[�V��������T = %.1f �܂ł�ATM�@�ݒu�䐔�R��ŃT�[�r�X���I�������q�̑��� fsq = %d\n\n", T, sum_q, T, fsq);

	printf("�����q�ɑ΂���T�[�r�X�� act_ro= %lf\n\n", act_ro);
	fprintf(fp, "�����q�ɑ΂���T�[�r�X�� act_ro= %lf\n\n", act_ro);

	free(sv);
	free(stime);

	return (0);
}