#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    enum
    {
        SIZE = 8,
        BASE = 10,
        COUNT = 3
    };
    int number_of_prcess;
    int pid = 1;
    for (int i = 0;i < COUNT;i++) {
        if (pid != 0) {
            number_of_prcess = i;
            pid = fork();
        }
        if (pid == 0) {
            char buff[SIZE];
            if (read(0, buff, sizeof(buff)) != sizeof(buff)) {
                fprintf(stderr, "Read erorr");
                return 0;
            }
            char str[SIZE + 1];
            snprintf(str, sizeof(str), "%s%s", buff, "\0");
            int input = strtol(str, NULL, BASE);
            int square = input * input;
            printf("%d %d\n", number_of_prcess + 1, square);
            fflush(stdout);
            _exit(0);
        }
    }
    for (int i = 0;i < COUNT;i++) {
        wait(NULL);
    }
    return 0;
}
