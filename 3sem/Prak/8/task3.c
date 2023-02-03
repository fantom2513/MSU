#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    enum { BASE = 10 };

    int rows = strtol(argv[2], NULL, BASE);
    int cols = strtol(argv[3], NULL, BASE);
    int out_fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
    int size,
        tmp;
    if (__builtin_mul_overflow(cols, rows, &tmp)) {
        fprintf(stderr, "overflow");
        return 1;
    }
    if (__builtin_mul_overflow(tmp, sizeof(int), &size)) {
        fprintf(stderr, "overflow");
        return 1;
    }
    ftruncate(out_fd, size);
    int *dest = mmap(NULL, size, PROT_WRITE, MAP_SHARED, out_fd, 0);
    if (dest == MAP_FAILED) {
        fprintf(stderr, "map failed");
        return 1;
    }
    int value = 1;
    int i = 0,
        j = 0;
    int col_begin = 0,
        col_end = 0,
        row_begin = 0,
        row_end = 0;
    while (value <= rows * cols) {
        dest[i * cols + j] = value;

        if (i == row_begin && j < cols - col_end - 1) {
            j++;
        } else if (j == cols - col_end - 1 && i < rows - row_end - 1) {
            i++;
        } else if (i == rows - row_end - 1 && j > col_begin) {
            j--;
        } else {
            i--;
        }
        if ((i == row_begin + 1) && (j == col_begin) && (col_begin != cols - col_end - 1)) {
            col_begin++;
            col_end++;
            row_begin++;
            row_end++;
        }
        value++;
    }
    close(out_fd);
    if(munmap(dest, size)==-1){
        fprintf(stderr, "munmap failed");
        return 1;
    }


    return 0;
}