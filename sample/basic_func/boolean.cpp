#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    bool B = true;
    int A = 0;
    A = B + B;
    printf("%d\n", A);
    return 0;
}