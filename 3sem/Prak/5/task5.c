#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    unsigned int min = 1;
    unsigned short value = 0;
    unsigned char temp[sizeof(value)];
    int fd = open(argv[1], O_RDONLY);
    while (read(fd, &temp, sizeof(temp)) > 0) {
        value = temp[1] + (temp[0] << CHAR_BIT);
        if (value % 2 == 0 && (value <= min || min == 1)) {
            min = value;
        }
    }
    if (min != 1) {
        printf("%d\n", min);
    }
}