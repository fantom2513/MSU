#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int grandson_pid;
    int son_pid=fork();
    if(son_pid==0) {
        grandson_pid=fork();
        if(grandson_pid==0) {
            printf("3 ");
            fflush(stdout);
            _exit(0);
        }
        wait(&grandson_pid);
        printf("2 ");
        fflush(stdout);
        _exit(0);
    }
    wait(&son_pid);
    printf("1\n");
    return 0;
}