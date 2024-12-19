//学籍番号　1201201038
//ポータルID　seb01038
//氏名　鎌田祐誠
//プログラム名　kamata_yuusei_exam4.cpp


# include<stdio.h>
# define _USE_MATH_DEFINES
# include<math.h>

#define f(x0) ( 7.0 * pow((x0), 4.0) - 5.0 * pow((x0), 3.0) + 3.0 * (x0))

double f_x(double x0)
{
	double fx0;
 
	fx0 = 7.0 * pow(x0, 4.0) - 5.0 * pow(x0, 3.0) + 3.0 * x0;
	return (fx0);
}
FILE* fp;
int main(void) {

	fopen_s(&fp, "kamata_yuusei_exam4.csv", "w");

	double x0;
	double h = 0.01;
	double fx0u;
	double fx0m;
	double dfdx0u;
	double d2fdx02u;
	double dfdx0m;
	double d2fdx02m;

	printf("f(x0) = 7.0 * x0^4 - 5.0 * x0^3 + 3.0 * x0  \n\n");
	printf("choice :u:自作関数を利用、m：引数つき関数形式マクロを利用\n\n");

	fprintf(fp, "f(x0) = 7.0 * x0^4 - 5.0 * x0^3 + 3.0 * x0  \n\n");
	fprintf(fp, "choice :u:自作関数を利用、m：引数つき関数形式マクロを利用 \n\n");

	printf("choice   x0    fx0      h    dfdx0      d2fdx02\n");
	fprintf(fp, "choice,x0,fx0,h,dfdx0,d2fdx02\n");

	for (x0 = 1.99; x0 <= 2.01; x0 += h) {

		fx0u = f_x(x0);

		fx0m = f(x0);

		dfdx0u = (f_x(x0 + h) - f_x(x0 - h)) / (2.0 * h);

		dfdx0m = (f(x0 + h) - f(x0 - h)) / (2.0 * h);

		d2fdx02u = (f_x(x0 + h) - 2.0 * f_x(x0) + f_x(x0 - h)) / pow(h, 2.0);

		d2fdx02m = (f(x0 + h) - 2.0 * f(x0) + f(x0 - h)) / pow(h, 2.0);

		
		printf("u        %.2f   %.6f      %.2f  %.6f        %.4f\nm        %.2f   %.6f      %.2f  %.6f        %.4f\n", x0, f_x(x0), h, dfdx0u, d2fdx02u, x0, f_x(x0), h, dfdx0u, d2fdx02u);
		fprintf(fp, "u,%.2f,%.6f,%.2f,%.6f,%.4f\nm,%.2f,%.6f,%.2f,%.6f,%.4f\n", x0, f_x(x0), h, dfdx0u, d2fdx02u, x0, f_x(x0), h, dfdx0m, d2fdx02m);
	}
	fclose(fp);

	return(0);
}