#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    enum
    {
        BASE = 16,
        SIZE = 65536,
        MASK = 0x1FF,
        SHIFT = 9
    };
    struct stat st;
    int res = lstat(argv[1], &st);
    if (res < 0) {
        fprintf(stderr, "lstat erorr\n");
        return 1;
    }
    if (st.st_size != SIZE) {
        fprintf(stderr, "wrong file size\n");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Open erorr\n");
        return 1;
    }
    unsigned short begining = strtol(argv[2], NULL, BASE);
    char *src = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (src < 0) {
        fprintf(stderr, "mmap erorr\n");
        return 1;
    }
    unsigned short virt_addr, physical_addr;
    while ((scanf("%hx", &virt_addr)) != EOF) {
        physical_addr = *(short *) &src[begining + 2 * (virt_addr >> SHIFT)] | (virt_addr & MASK);
        printf("%hu\n", *(short *) (src + physical_addr));
    }
    if (munmap(src, SIZE) == -1) {
        fprintf(stderr, "munmap erorr\n");
        return 1;
    }
    close(fd);
    return 0;
}