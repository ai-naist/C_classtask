#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void)
{
	int i;
	do
	{
		scanf_s("%d", &i);
		if (i <= 0)
			printf("•s³‚È’l\n");
	} while ((i <= 0) || (i > INT_MAX));

	printf("%d", i);
	return 0;
}