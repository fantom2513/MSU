#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int
execute_command(const char *name)
{
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork erorr\n");
        return 0;
    } else if (pid == 0) {
        execlp(name, name, NULL);
        _exit(1);
    } else {
        int status;
        wait(&status);
        return WIFEXITED(status) && (WEXITSTATUS(status) == 0);
    }
}
int main(int argc, char *argv[])
{
    return !((execute_command(argv[1]) || execute_command(argv[2])) && execute_command(argv[3]));
}