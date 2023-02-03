#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
volatile int flag = 0;
enum
{
    ADDITION = 0,
    MULTIPLICATION = 1
};
void
handler(int sig)
{
    if (sig == SIGINT) {
        flag = ADDITION;
    }
    if (sig == SIGQUIT) {
        flag = MULTIPLICATION;
    }
}
int main()
{
    sigaction(SIGQUIT, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGINT, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    unsigned int val = 0;
    unsigned int tmp;
    printf("%d\n", getpid());
    fflush(stdout);
    while ((scanf("%d", &tmp)) == 1) {
        if (flag == MULTIPLICATION) {
            val = val * tmp;
        } else {
            val = val + tmp;
        }
        printf("%d\n", val);
        fflush(stdout);
    }
}