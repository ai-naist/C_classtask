#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES

double f(double x)
{
  return 4 / (1 + x * x);
}

// シンプソン則（区間[a,b]をn分割）による近似積分計算 
double simpsons_rule(double a, double b, int n)
{
  double h;
  int i;
  double value = 0;

  h = (b - a) / (2 * n);
  for (i = 0; i <= 2 * n; i++)
  {
    if (i == 0 || i == 2 * n)
      value += f(a + i * h); // 始点X_0か、終点X_2nの場合
    else if (i % 2 == 1)
      value += 4 * f(a + i * h); // X_n奇数の場合
    else
      value += 2 * f(a + i * h); // X_n偶数の場合
  }
  value = value * h / 3;
  return value;
}

int main(void)
{
  printf("Analytical solution : %.15f\n", M_PI); // M_PIは円周率の値を返す関数
  printf("Numerical solution  : %.15f\n", simpsons_rule(0, 1, 4));
  return 0;
}