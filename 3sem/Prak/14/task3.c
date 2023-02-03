#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <string.h>
struct Buf
{
    long mtype;
    long long x[2];
};

int main(int argc, char *argv[])
{
    enum { BASE = 10 };
    key_t key = strtol(argv[1], NULL, BASE);
    int nproc = strtol(argv[2], NULL, BASE);
    long long value1 = strtoll(argv[3], NULL, BASE);
    long long value2 = strtoll(argv[4], NULL, BASE);
    long long max_value = strtoll(argv[5], NULL, BASE);

    int id = msgget(key, 0600 | IPC_CREAT | IPC_EXCL);
    if (id < 0) {
        fprintf(stderr, "msgget erorr %s\n", strerror(errno));
        return 1;
    }

    pid_t *pid = calloc(nproc, sizeof(pid_t));

    struct Buf start = {
            .mtype = 1,
            .x = {value1, value2}
    };

    msgsnd(id, &start, sizeof(start.x), 0);

    for (int i = 0;i < nproc;i++) {

        if ((pid[i] = fork()) < 0) {

            for (int j = 0;j < i;j++) {
                kill(pid[j], SIGKILL);
            }
            free(pid);
            while (wait(NULL) > 0) {}
            msgctl(id, IPC_RMID, 0);

            return 1;
        } else if (pid[i] == 0) {
            free(pid);
            while (1) {

                long long x3;
                struct Buf message;
                if (msgrcv(id, &message, sizeof(message.x), (long) i + 1, 0) == -1) {
                    break;
                }

                x3 = message.x[0] + message.x[1];
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                if (x3 > max_value) {
                    msgctl(id, IPC_RMID, 0);
                    break;
                }
                message.mtype = x3 % nproc + 1;
                message.x[0] = message.x[1];
                message.x[1] = x3;
                msgsnd(id, &message, sizeof(message.x), 0);
            }
            _exit(0);
        }

    }
    free(pid);
    while (wait(NULL) > 0) {}
    return 0;
}