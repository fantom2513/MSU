#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    pid_t pid_cmd3, pid;

    if ((pid = fork()) == 0) {
        if (fork() == 0) {
            int fd1 = open(argv[4], O_RDONLY);
            dup2(fd1, 0);
            dup2(fd[1], 1);

            close(fd[1]);
            close(fd1);
            close(fd[0]);

            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else {
            close(fd[0]);
            int status;
            wait(&status);
            status = WIFEXITED(status) && (WEXITSTATUS(status) == 0);

            if (status != 0) {
                if (fork() == 0) {
                    dup2(fd[1], 1);

                    close(fd[0]);
                    close(fd[1]);
                    execlp(argv[2], argv[2], NULL);
                    _exit(1);
                } else {
                    close(fd[1]);
                    close(fd[0]);
                    wait(NULL);
                }
            }
        }
        _exit(0);
    }

    if ((pid_cmd3 = fork()) == 0) {
        int fd2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(fd[0], 0);
        dup2(fd2, 1);

        close(fd[1]);
        close(fd[0]);
        close(fd2);

        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    int status;

    waitpid(pid, &status, 0);
    waitpid(pid_cmd3, &status, 0);
    return 0;
}
