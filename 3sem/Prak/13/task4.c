#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <math.h>
#include <dlfcn.h>
int main(int argc, char *argv[])
{
    enum { BASE = 10 };
    char *name = "lib.c";
    char *out_name = "lib.so";
    double left = strtod(argv[1], NULL);
    double right = strtod(argv[2], NULL);
    int n = strtol(argv[3], NULL, BASE);
    int fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);

    dprintf(fd, "#include <stdio.h>\n#include <stdlib.h>\n#include <math.h>\n"
        "double f(double x)\n"
        "{\n"
        "return %s;\n"
        "}\n", argv[4]);
    close(fd);
    if (fork() == 0) {
        execlp("gcc", "gcc", "-shared", "-o", out_name, "-fPIC", name, "-lm", NULL);
    }
    wait(NULL);
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "./%s", out_name);
    void *handle = dlopen(path, RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL) {
        fprintf(stderr, "ldopen erorr: %s\n", dlerror());
        return -1;
    }
    double (*func)(double) = dlsym(handle, "f");
    double square = 0;
    double dx = (right - left) / (double) n;
    for (int i = 0;i < n;i++) {
        double xi = left + (double) i * dx;
        square += func(xi) * dx;
    }
    printf("%.10g\n", square);
    dlclose(handle);

    return 0;
}