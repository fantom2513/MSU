#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
void
work(int fdin, int fdout, int max_value, int number)
{
    int i = 0;
    FILE *fdr = fdopen(fdin, "r");
    FILE *fdw = fdopen(fdout, "w");
    while (i < max_value) {
        fscanf(fdr, "%d", &i);
        if (max_value == 1 && number == 2) {
            break;
        }
        if (i >= max_value) {
            break;
        }
        printf("%d %d\n", number, i);
        fflush(stdout);
        i++;
        fprintf(fdw, "%d\n", i);
        fflush(fdw);
    }
    fclose(fdr);
    fclose(fdw);
}
int main(int argc, char *argv[])
{
    enum { BASE = 10 };
    int max_value = strtol(argv[1], NULL, BASE);
    int fd1_2[2];
    int fd2_1[2];
    pipe(fd1_2);
    pipe(fd2_1);
    if ((fork()) == 0) {
        int pid1 = 1;
        close(fd1_2[0]);
        close(fd2_1[1]);
        work(fd2_1[0], fd1_2[1], max_value, pid1);
        _exit(0);
    }

    if ((fork()) == 0) {
        int pid2 = 2;
        close(fd1_2[1]);
        close(fd2_1[0]);
        work(fd1_2[0], fd2_1[1], max_value, pid2);
        _exit(0);
    }
    FILE *in = fdopen(fd2_1[1], "w");
    int value = 1;
    fprintf(in, "%d\n", value);
    fflush(in);
    close(fd1_2[0]);
    close(fd2_1[1]);
    close(fd1_2[1]);
    close(fd2_1[0]);
    while (wait(NULL) > 0) {}

    printf("Done\n");
    return 0;
}