#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
volatile sig_atomic_t flag;
void
work(int max_value, FILE *fdw, FILE *fdr, int number)
{
    int value;
    sigset_t s2;
    sigemptyset(&s2);
    int pidtokill;
    printf(":%d 3\n", number);
    if (number == 1) {
        while (!flag) {
            sigsuspend(&s2);
        }
        flag = 0;
        fscanf(fdr, "%d", &pidtokill);
        fprintf(fdw, "%d\n", getpid());
        printf("| %d\n", pidtokill);
        kill(pidtokill, SIGUSR1);
        while (!flag) {
            sigsuspend(&s2);
        }
        flag = 0;
    } else if (number == 2) {
        kill(pidtokill, SIGUSR1);
        while (!flag) {
            sigsuspend(&s2);
        }
        flag = 0;
        fscanf(fdr, "%d", &pidtokill);
        kill(pidtokill, SIGUSR1);
    }
    printf("{ %d %d %d\n", number, pidtokill, getpid());
    printf(":%d 4\n", number);
    while (1) {
        printf(":%d 5\n", number);
        while (!flag) {
            sigsuspend(&s2);
        }
        flag = 0;
        printf(":%d 6\n", number);
        fscanf(fdr, "%d", &value);
        printf(":%d 7\n", number);
        if (value >= max_value) {
            fprintf(fdw, "%d\n", value);
            kill(pidtokill, SIGUSR1);
            break;
        }
        printf("%d %d\n", number, value);
        fflush(stdout);

        value++;

        fprintf(fdw, "%d\n", value);
        fflush(fdw);
        printf(":%d 8\n", number);
        kill(pidtokill, SIGUSR1);
        printf(":%d 9\n", number);
    }
    fclose(fdw);
    fclose(fdr);
    _exit(0);

}
void handler(int s)
{
    flag = 1;
}

int main(int argc, char *argv[])
{
    enum { BASE = 10 };
    int value, number = 1;
    sigset_t s1;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s1, NULL);
    sigset_t s2;
    sigemptyset(&s2);
    int fd[2];
    int pid[2];

    pipe(fd);
    FILE *fdr = fdopen(fd[0], "r");
    FILE *fdw = fdopen(fd[1], "w");
    sigaction(SIGUSR1, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    printf(": 1\n");
    int max_value = strtol(argv[1], NULL, BASE);
    pid[0] = fork();
    if (pid[0] == 0) {

        number = 1;
        printf(":%d 2\n", number);
        work(max_value, fdw, fdr, number);
    } else {
        pid[1] = fork();
        if (pid[1] == 0) {
            number = 2;
            printf(":%d 2\n", number);
            work(max_value, fdw, fdr, number);
        } else {
            value = 1;
            fprintf(fdw, "%d\n", pid[1]);
            fprintf(fdw, "%d\n", value);
            fflush(fdw);
            kill(pid[0], SIGUSR1);
            //kill(pid[0], SIGUSR1);
            fclose(fdw);
            fclose(fdr);
            wait(NULL);
            wait(NULL);
            printf("Done\n");
            return 0;
        }
    }

}