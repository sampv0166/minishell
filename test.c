#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int increment_i(int *i)
{
    *i = *i + 1;
    return (*i);
}

int main(void)
{
    int i;
    i =  1;

    printf("%d\n", i);
    increment_i(&i);
    printf("%d\n", i);
    return 0;
}