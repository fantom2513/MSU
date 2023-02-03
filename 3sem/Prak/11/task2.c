#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
int main()
{
    int fd[2];
    int tmp;
    long long sum = 0;
    pipe(fd);
    if (fork() == 0) {
        close(fd[1]);
        if (fork() == 0) {
            int x;
            while (read(fd[0], &x, sizeof(tmp))) {
                sum += x;
            }

            printf("%lld\n", sum);
            fflush(stdout);
            close(fd[0]);
            close(fd[1]);
            _exit(0);
        } else {
            wait(NULL);
            _exit(0);
        }
    } else {
        close(fd[0]);
        while (scanf("%d", &tmp) != EOF) {
            write(fd[1], &tmp, sizeof(tmp));
        }
        close(fd[1]);
        wait(NULL);
        return 0;
    }
}