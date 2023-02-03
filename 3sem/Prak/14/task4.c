#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <string.h>
int modul(int x, int count)
{
    return (x % count + count) % count;
}
int main(int argc, char *argv[])
{
    enum
    {
        BASE = 10,
        KEY = 0xba
    };
    int nproc = strtol(argv[1], NULL, BASE);
    int semid = semget(KEY, nproc, 0600 | IPC_CREAT | IPC_EXCL);
    int value;
    if (semid < 0) {
        fprintf(stderr, "semget erorr %s\n", strerror(errno));
        return 1;
    }
    semctl(semid, 0, SETVAL, 1);
    for (int i = 0;i < nproc;i++) {
        if (fork() == 0) {
            setbuf(stdin, NULL);
            setbuf(stdout, NULL);
            while (1) {
                struct sembuf b1[] = {
                    {.sem_num = i,-1,0}
                };
                int res = semop(semid, b1, sizeof(b1) / sizeof(b1[0]));
                if (res == -1) {
                    break;
                }
                if (scanf("%d", &value) != 1) {
                    semctl(semid, 0, IPC_RMID);
                    _exit(0);
                }
                printf("%d %d\n", i, value);

                int next = modul(value, nproc);
                struct sembuf b2[] = {
                    {.sem_num = next,1,0}
                };
                res = semop(semid, b2, sizeof(b2) / sizeof(b2[0]));
                if (res == -1) {
                    break;;
                }
            }
            _exit(0);
        }
    }

    while ((wait(NULL)) > 0) {}
    semctl(semid, 0, IPC_RMID);
    return 0;
}