#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int
mysys(const char *str)
{
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            return 128 + WTERMSIG(status);
        } else {
            return WEXITSTATUS(status);
        }
    }
}