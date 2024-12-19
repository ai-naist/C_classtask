#include <stdio.h>
int main(void)
{
    int S = 3747;
    printf("%d\n", (S - S % 3600) / 3600);
    return 0;
}