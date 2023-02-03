#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    unsigned long long sum = 0;
    for (int i = 1; i < argc; i++) {
        struct stat st;
        int file_found = lstat(argv[i], &st);
        if ((st.st_size % 1024 == 0) && S_ISREG(st.st_mode) && file_found == 0 && st.st_nlink == 1) {
            sum += st.st_size;
        }
    }
    printf("%lld\n", sum);
}