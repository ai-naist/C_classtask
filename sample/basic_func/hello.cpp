#include <stdio.h>

/**/ void out_f(/**/ const char *);

int main(void)
{
    char *str = "hello world";
    out_f(str);
    return 0;
}

void out_f(const char /**/ *str)
{
    printf("%s\n", str);
}