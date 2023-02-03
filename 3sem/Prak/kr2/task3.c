#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    struct stat st;
    int fd = open(argv[1], O_RDONLY);
    uint64_t min = (uint64_t) strtoull(argv[2], NULL, 10);
    stat(argv[1], &st);
    long long size = st.st_size / sizeof(uint64_t);
    uint64_t *value = calloc(size, sizeof(uint64_t));
    for (int i = 0; i < size;i++) {
        read(fd, &value[i], sizeof(uint64_t));
    }
    close(fd);
    fd = open(argv[1], O_WRONLY | O_TRUNC);
    for (int i = 0;i < size;i++) {
        if (value[i] >= min) {
            write(fd,&value[i],sizeof(uint64_t));
        }
    }
    close(fd);
    return 0;
}