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
#include <malloc.h>
void
destroy(pid_t *pids, int max)
{
    for (int i = 0;i < max;i++) {
        kill(pids[i], SIGKILL);
        int status;
        waitpid(pids[i], &status, 0);
    }
}
int main(int argc, char *argv[])
{
    int fd_array[2];
    int pipedes[2];

    fd_array[0] = dup(0);
    fd_array[1] = dup(1);

    pid_t *pid = (pid_t *) malloc((argc - 1) * sizeof(pid_t));
    //close(2);
    for (int i = 1;i < argc; i++) {
        if (i == argc - 1) {
            pipedes[0] = dup(0);
            pipedes[1] = dup(1);
        } else {
            if (pipe(pipedes) < 0) {
                destroy(pid, i - 1);
                free(pid);
                return 1;
            }
        }

        pid[i-1] = fork();
        if (pid[i-1] == 0) {
            dup2(fd_array[0], 0);
            dup2(pipedes[1], 1);

            close(fd_array[0]);
            close(fd_array[1]);
            close(pipedes[0]);
            close(pipedes[1]);

            execlp(argv[i], argv[i], NULL);
            _exit(1);
        } else if (pid[i-1] < 0) {
            destroy(pid, i - 1);
            free(pid);
            return 1;
        }
        close(fd_array[0]);
        close(fd_array[1]);

        fd_array[0] = pipedes[0];
        fd_array[1] = pipedes[1];
    }

    close(fd_array[0]);
    close(fd_array[1]);
    close(pipedes[0]);
    close(pipedes[1]);
    free(pid);
    while ((wait(NULL)) > 0) {}
    return 0;
}