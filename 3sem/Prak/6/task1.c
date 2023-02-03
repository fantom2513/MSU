#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    enum
    {
        MKSEC_IN_SEC = 1000000,
        BASE = 10
    };
    struct timeval start_time;
    start_time.tv_sec = strtol(argv[1], NULL, BASE);
    start_time.tv_usec = strtol(argv[2], NULL, BASE);

    double lambd = strtod(argv[3], NULL);
    long number_of_events = strtol(argv[4], NULL, BASE);
    unsigned int start_value = strtoul(argv[5], NULL, BASE);

    srand(start_value);

    for (int i = 0; i < number_of_events; i++) {
        double random_value = (-1.0) * log((double) rand() / RAND_MAX) / lambd;
        start_time.tv_usec += floor(random_value);
        if (start_time.tv_usec >= MKSEC_IN_SEC) {
            start_time.tv_sec += start_time.tv_usec / MKSEC_IN_SEC;
            start_time.tv_usec %= MKSEC_IN_SEC;
        }
        printf("%ld %ld\n", start_time.tv_sec, start_time.tv_usec);
    }
}