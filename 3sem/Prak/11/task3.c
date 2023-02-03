#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>
int main()
{
    int fd[2];
    pipe(fd);
    struct tm *times;
    time_t t;
    if (fork() == 0) {
        if (fork() == 0) {
            if (fork() == 0) {
                t = time(NULL);
                for (int i = 0;i < 3;i++) {
                    write(fd[1], &t, sizeof(t));
                }
                _exit(0);
            } else {
                read(fd[0], &t, sizeof(t));
                close(fd[0]);
                close(fd[1]);
                times = localtime(&t);
                wait(NULL);
                printf("D:%02d\n", times->tm_mday);
                fflush(stdout);
                _exit(0);
            }
        } else {
            read(fd[0], &t, sizeof(t));
            close(fd[0]);
            close(fd[1]);
            times = localtime(&t);
            wait(NULL);
            printf("M:%d\n", times->tm_mon + 1);
            fflush(stdout);
            _exit(0);
        }
    } else {
        read(fd[0], &t, sizeof(t));
        close(fd[0]);
        close(fd[1]);
        times = localtime(&t);
        wait(NULL);
        printf("Y:%d\n", times->tm_year + 1900);
        fflush(stdout);
        return 0;
    }
}