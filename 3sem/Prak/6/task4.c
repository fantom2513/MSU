#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <string.h>
int main(void)
{
    enum
    {
        SEC_IN_DAY = 86400,
        START_YEAR = 1900,
        THURSDAY_NUMBER = 4,
        SUMMER_TIME = -1
    };
    int year;
    scanf("%d", &year);

    struct tm *time;
    struct tm temp = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    temp.tm_mday = 1;
    temp.tm_isdst = SUMMER_TIME;
    time = &temp;
    time->tm_year = year - START_YEAR;
    mktime(time);

    int current_month = 0;
    int number_of_thursday = 0;

    while (time->tm_year == year - START_YEAR) {
        if (current_month != time->tm_mon) {
            number_of_thursday = 0;
            current_month++;
        }
        if (time->tm_wday == THURSDAY_NUMBER) {
            number_of_thursday++;
        }

        if (time->tm_wday == THURSDAY_NUMBER && time->tm_mday % 3 != 0
                && number_of_thursday % 2 == 0) {
            printf("%d %d\n", time->tm_mon + 1, time->tm_mday);
        }
        time->tm_mday++;
        mktime(time);
    }

    return 0;
}