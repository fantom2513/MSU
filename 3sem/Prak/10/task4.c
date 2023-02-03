/*
Кинули игнор за нарушение условия, но код рабочий
*/
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
    enum { SIZE = 8 };
    char path[PATH_MAX];

    char *env = getenv("XDG_RUNTIME_DIR");
    if(env==NULL){
        env = getenv("TMPDIR");
        if(env == NULL){
            env="/tmp";
        }
    }
    char name[SIZE] = "mul";

    int fd_name = open("/dev/urandom", O_WRONLY);
    read(fd_name, &name, SIZE);
    close(fd_name);

    snprintf(path, sizeof(path), "%s/%s", env, name);
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0755);

    dprintf(fd, "#! /usr/bin/python3\nimport os\nprint(");
    for (int i = 1; i < argc - 1;i++) {
        dprintf(fd, "%s*", argv[i]);
    }
    dprintf(fd, "%s)\nos.remove(\"%s\")", argv[argc - 1], path);

    close(fd);
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork erorr");
        return 0;
    } else if (pid == 0) {
        execlp(path, path, NULL);
        fprintf(stderr, "exec eror\n");
    } else {
        wait(NULL);
        return 0;
    }
}