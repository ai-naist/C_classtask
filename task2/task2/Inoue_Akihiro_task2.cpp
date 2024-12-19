// �w�Дԍ� 1201201010
// �|�[�^��ID : seb01010
// ����  ��㖾�_
// �v���O������ : Inoue_Akihiro_task2.cpp

#include <stdio.h>
#define _USE_MATH_DEFINES // ���l���Z�萔
#include <math.h>

// �C�ӂ̕ϐ�x�ɑ΂��āA���l��͌��ʂ�3�Ԃ��֐�
double NumAnaFunc(double x, double* p_y2, double* p_y3)
{
    *p_y2 = cos(x);
    *p_y3 = sin(x);
    return sqrt(x);
}

FILE *fp; // FILE�|�C���^

int main(void)
{

    // FILE�|�C���^fp �� "�t�@�C����.�g���q" �� "�t�@�C�������݃��[�h" �̏���^����
    fopen_s(&fp, "Inoue_Akihiro_task2.csv", "w");

    double x, y1, y2, y3;

    // �R���\�[���ŕ\��
    printf("x sqrt(x) cos(x) sin(x)\n");
    // csv�ɏo��
    fprintf(fp, "x,sqrt(x),cos(x),sin(x)\n");

    for (int i = 0; i <= 10; i++)
    {
        // x��0����pi�܂�pi/10�����݂ŕω�
        x = i * M_PI / 10;

        // y1,y2,y3�Ɋ֐��l����
        y1 = NumAnaFunc(x, &y2, &y3);

        // �R���\�[���ŕ\��
        printf("%lf %lf %lf %lf\n", x, y1, y2, y3);
        // csv�o��
        fprintf(fp, "%lf,%lf,%lf,%lf\n", x, y1, y2, y3);
    }
    fclose(fp); // �t�@�C���N���[�Y

    return 0;
}