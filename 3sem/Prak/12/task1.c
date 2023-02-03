#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
static  int count = 0;
void
handler(int s)
{
    if (count == 5){
        _exit(0);
    } else {
        printf("%d\n",count);
        fflush(stdout);
        count++;
    }
}
int main()
{
    sigaction(SIGHUP, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    printf("%d\n",getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
}