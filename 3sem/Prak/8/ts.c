#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
int main()
{
    char a[3];
    a[0]=3;
    a[1]=0;
    a[2]=1;
    printf("%u\n", *(short*)(a+1));

}