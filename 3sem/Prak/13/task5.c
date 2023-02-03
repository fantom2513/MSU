#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
volatile sig_atomic_t value = -1;
volatile sig_atomic_t recive_flag = 0;
enum
{
    ZERO = 0,
    ONE = 1,
    MASK = 0x1,
    END = -2
};
void
handler1(int sig)
{
    if (sig == SIGUSR1) {
        value = ZERO;
    }
    if (sig == SIGUSR2) {
        value = ONE;
    }
    if (sig == SIGIO) {
        value = END;
    }
}
void
handler2(int sig)
{
    if (sig == SIGALRM) {
        recive_flag = 1;
    }
}
int main(int argc, char *argv[])
{
    struct sigaction s1, s2;
    s1.sa_handler = handler1;
    s1.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &s1, NULL);
    sigaction(SIGUSR2, &s1, NULL);
    sigaction(SIGIO, &s1, NULL);
    s2.sa_handler = handler1;
    s2.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &s2, NULL);
    sigset_t sa;
    sigemptyset(&sa);
    int pipes[20];
    pipe(pipes);
    pid_t pid1, pid2;
    if ((pid1 = fork()) == 0) {
        int brother_pid, count;
        char buff;
        close(pipes[1]);
        read(pipes[0], &brother_pid, sizeof(brother_pid));
        printf("|1 %d\n", brother_pid);
        count = 0;
        while (value != END) {
            while (value < 0) {
                sigsuspend(&sa);
            }
            if (value != -1) {
                kill(brother_pid, SIGALRM);
            }
            buff = buff | (value << count);
            count++;
            if (count == CHAR_BIT) {
                count = 0;
                putchar(buff);
                buff = 0;
            }
            value = -1;
        }
        close(pipes[0]);
    } else {
        if ((pid2 = fork()) == 0) {
            int fd = open(argv[1], O_RDONLY);
            char buff;
            int brother_pid;
            printf("|2 %d\n", pid1);
            while (read(fd, &buff, sizeof(buff)) == sizeof(buff)) {
                printf("%c",buff);
                for (int i = 0;i < CHAR_BIT; i++) {
                    if (buff & (MASK << i)) {
                        kill(brother_pid, SIGUSR2);
                    } else {
                        kill(brother_pid, SIGUSR1);
                    }
                }
                while (!recive_flag) {
                    sigsuspend(&sa);
                }
            }
            kill(pid1, SIGIO);
            close(fd);
        } else {
            printf("|3 %d %d\n", pid1, pid2);
            write(pipes[1], &pid2, sizeof(pid2));
            close(pipes[0]);
            close(pipes[1]);

            wait(NULL);
            wait(NULL);
        }
    }
}