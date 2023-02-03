#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main()
{
    enum { SIZE = 256 };
    unsigned int array[SIZE];
    int count = 0;
    unsigned int max = 0;
    while (scanf("%u", &array[count]) == 1) {

        if (array[count] > max) {
            max = array[count];
        }
        count++;
    };
    if (max == 0) {
        return 0;
    }
    for (int i = count-1;i >= 0;i--) {
        if (array[i] > 0) {
            if ((max % array[i]) == 0) {
                printf("%u\n", array[i]);
            }
        }
    }
    return 0;
}