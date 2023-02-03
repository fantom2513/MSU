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
    char name[NAME_MAX];
    char out_name[NAME_MAX];
    int fd_rand = open("/dev/urandom", O_RDONLY);
    char temp[SIZE];
    read(fd_rand, &temp, SIZE);
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "./%s.out", temp);
    snprintf(out_name, sizeof(out_name), "%s.out", temp);
    snprintf(name, sizeof(name), "%s.c", temp);
    close(fd_rand);

    int fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0755);
    dprintf(fd, "#include <stdio.h>\n"
        "int main()\n"
        "{\n"
        "int x;\n"
        "int summon = 0;\n"
        "int disqualify = 1;\n"
        "int reject = 2;\n"
        "while(scanf(\"%%d\", &x) == 1) {\n"
        "int result =%s;\n"
        "if(result == 0) {\n"
        "printf(\"summon\\n\");\n"
        "} else if(result == 1) {\n"
        "printf(\"disqualify\\n\");\n"
        "} else if(result == 2) {\n"
        "printf(\"reject\\n\");\n"
        "}\n"
        "}\n"
        "return 0;\n"
        "}", argv[1]);
    close(fd);

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork erorr");
        return 0;
    } else if (pid == 0) {
        execlp("gcc", "gcc", name, "-o", out_name, NULL);
        fprintf(stderr, "exec 1 eror\n");
    } else {
        wait(NULL);
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork erorr");
            return 0;
        } else if (pid == 0) {
            execlp(path, path, NULL);
            fprintf(stderr, "exec 2 eror\n");
        } else {
            wait(NULL);
            return 0;
        }
    }
}