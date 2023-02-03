#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int n,
        new_pid;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        new_pid = fork();
        if(new_pid == 0) {
            if(i==n-1) {
                printf("%d\n", i+1);
                fflush(stdout);    
                break;
            }
            printf("%d ", i+1);
            fflush(stdout);
        } else {
            wait(&new_pid);ы
            _exit(0);
        }
    }
    return 0;
}
