#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int input,
        first_number;
    int father = 1;
    int erorr_flag = 0;
    if (scanf("%d", &first_number) == EOF) {
        return 0;
    }
    while (1) {

        int new_pid = fork();
        if (new_pid == -1) {
            _exit(1);
        }
        if (new_pid == 0) {
            if (scanf("%d", &input) != 1) {
                _exit(0);
            }
            father = 0;
        } else {
            wait(&new_pid);
            WIFEXITED(new_pid);
            if (WEXITSTATUS(new_pid) == 1 && father == 0) {
                _exit(1);
            }
            if (WEXITSTATUS(new_pid) == 1 && father == 1) {
                printf("-1\n");
                erorr_flag = 1;
                break;
            }
            if (father) {
                break;
            }
            printf("%d\n", input);
            fflush(stdout);
            _exit(0);
        }
    }
    if (!erorr_flag) {
        printf("%d\n", first_number);
    }
    return 0;
}