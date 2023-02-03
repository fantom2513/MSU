#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
volatile int last = 0;
volatile sig_atomic_t count = 0;
void
handler(int sig)
{
    if (sig == SIGINT) {
        if (count == 3) {
            _exit(0);
        }
        printf("%d\n", last);
        fflush(stdout);
        count++;
    }
    if (sig == SIGTERM) {
        _exit(0);
    }
}
int
prime(int low, int high)
{
    int isprime = 1;
    if (low < 2) {
        low = 2;
    }
    for (int i = low;i < high;i++) {
        for (int j = 2;j * j < i;j++) {
            int res;
            if (__builtin_smul_overflow(j, j, &res)) {
                return 0;
            }
            if (i % j == 0) {
                isprime = 0;
                break;
            }
        }
        if (isprime) {
            last = i;
        }
        isprime = 1;
    }
    return 1;
}

int main()
{
    int low, high;
    scanf("%d%d", &low, &high);
    struct sigaction s;
    s.sa_handler = handler;
    s.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);
    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    prime(low, high);
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    printf("-1\n");
    return 0;
}