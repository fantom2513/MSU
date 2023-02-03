#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    enum { BASE = 10 };
    long long sum_positve = 0,
        sum_negative = 0;
    long int temp;
    for (int i = 1; i < argc;i++) {
        temp = strtol(argv[i], NULL, BASE);
        if (temp >= 0) {
            sum_positve += temp;
        } else {
            sum_negative += temp;
        }

    }
    printf("%lld\n%lld\n", sum_positve, sum_negative);
    return 0;
}