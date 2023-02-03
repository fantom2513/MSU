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
    enum
    {
        SIZE = 4,
        SHIFT = 20,
        NEW_CHAR_BIT = 12
    };
    int masks[4] =
    {0x00f00000, 0x000ff000,
    0x00000f00, 0x000000ff};
    int temp;
    char buff[SIZE] = {0};
    int out_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (out_fd < 0) {
        fprintf(stderr, "Open erorr\n");
        return 1;
    }
    while (scanf("%d", &temp) > 0) {
        buff[0] = (temp & masks[0]) >> (CHAR_BIT + NEW_CHAR_BIT);
        buff[1] = (temp & masks[1]) >> NEW_CHAR_BIT;
        buff[2] = (temp & masks[2]) >> CHAR_BIT;
        buff[3] = (temp & masks[3]);
        if (write(out_fd, buff, SIZE) != sizeof(buff)) {
            fprintf(stderr, "Write erorr\n");
            return 1;
        }
    }
    close(out_fd);
    return 0;

}