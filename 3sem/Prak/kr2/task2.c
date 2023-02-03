#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
int main(int argc, char *argv[])
{
    enum
    {
        BUFF_SIZE = 16,
        BASE = 16
    };
    char buff[BUFF_SIZE];
    strncpy(buff,argv[1],16);
    printf("%16s\n",buff);
    long long val1_high = strtoull(argv[1], NULL, BASE);
    strncpy(buff,argv[1]+16,16);
    printf("%16s\n",buff);
    long long val1_low = strtoull(argv[1], &argv[1] + 16, BASE);
    strncpy(buff,argv[1],16);
    long long val2_low = strtoull(argv[2], NULL, BASE);
    strncpy(buff,argv[1],16);
    long long val2_high = strtoull(argv[2], &argv[2] + 16, BASE);
    long long sub_low;
    printf("%s\n", (argv[1] + 16));
    printf("%lld %lld %lld %lld\n", val1_low, val1_high, val2_low, val2_high);
    /*if (__builtin_smulll_overflow(val1_low, val2_low, &sub_low)){
        val1_high--;
        val1_low
    }*/

}