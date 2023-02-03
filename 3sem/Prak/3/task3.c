#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main(int argc, char *argv[])
{
    enum
    {
        ROUND = 10000,
    };
    const double percent = 100.0;
    double currency_rate = strtod(argv[1], NULL);
    for (int i = 2; i < argc;i++) {
        double course_change = strtod(argv[i], NULL);
        currency_rate = round(currency_rate * ((percent + course_change) * percent)) / ROUND;
    }
    printf("%.4lf\n", currency_rate);
    return 0;
}
