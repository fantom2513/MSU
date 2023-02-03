#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
void
run(char file_name[])
{
    FILE *in = fopen(file_name, "r");
    char name[PATH_MAX];
    fscanf(in, "%4096s", name);
    fclose(in);
    execlp(name, name, NULL);
    _exit(1);
}
int main(int argc, char *argv[])
{
    enum { BASE = 10 };
    int n = strtol(argv[1], NULL, BASE);
    for (int i = 0;i < n;i++) {
        pid_t pid = fork();
        if (pid == 0) {
            run(argv[i+2]);
        }
    }
    int count = 0;
    int status;
    while (wait(&status) > 0) {
        count += WIFEXITED(status) && (WEXITSTATUS(status) == 0);
    }
    for (int i = n;i < argc - 2;i++) {
        pid_t pid = fork();
        if (pid == 0) {
            run(argv[i+2]);
        } else {
            wait(&status);
            count += WIFEXITED(status) && (WEXITSTATUS(status) == 0);
            
        }
    }
    printf("%d\n", count);
    return 0;
}