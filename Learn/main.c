#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main()
{

    int var = 10;
    int *ip;

    ip = &var;
    printf("var address: %p \n",&var);
    printf("ip value: %p \n",ip);
    printf("ip address: %p \n",&ip);
    printf("ip address value: %p \n",*ip);

    return 0;
}
