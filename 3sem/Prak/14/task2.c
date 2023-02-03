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
void
operation(int *data, int ind1, int ind2, int value)
{
    if (ind1 != ind2) {
        int tmp1 = data[ind1] - value;
        int tmp2 = data[ind2] + value;

        data[ind1] = tmp1;
        data[ind2] = tmp2;
    }
}
int main(int argc, char *argv[])
{
    enum { BASE = 10 };
    int count = strtol(argv[1], NULL, BASE);
    key_t key = strtol(argv[2], NULL, BASE);
    int nproc = strtol(argv[3], NULL, BASE);
    int iter_count =strtol(argv[4], NULL, BASE);
    long long max_value = strtoll(argv[3], NULL, BASE);
    int semid = semget(key, nproc, 0600 | IPC_CREAT | IPC_EXCL);
    if (semid < 0) {
        fprintf(stderr, "semget erorr\n");
        exit(1);
    }
    long long *val = mmap(NULL, sizeof(val), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    int *send = mmap(NULL, sizeof(send), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    (*val) = 0;
    (*send) = 0;
    for (int i = 1;i <= nproc;i++) {
        if (fork() == 0) {
            while (1) {
                struct sembuf b1[] = {
                    {.sem_num = i - 1,-1,0}
                };
                int res = semop(semid, b1, sizeof(b1) / sizeof(b1[0]));
                if (res == -1) {
                    break;
                }
                printf("%d %lld %d\n", i, *val, *send);
                fflush(stdout);
                (*val)++;
                if ((*val) > max_value) {
                    semctl(semid, 0, IPC_RMID);
                    break;
                }
                (*send) = i;
                int next = (((*val) % nproc) * ((*val) % nproc) * ((*val) % nproc) * ((*val) % nproc)) % nproc;
                struct sembuf b2[] = {
                    {.sem_num = next,1,0}
                };
                res = semop(semid, b2, sizeof(b2) / sizeof(b2[0]));
                if (res == -1) {
                    break;
                }
            }
            _exit(0);
        }
    }
    semctl(semid, 0, SETVAL, 1);
    while ((wait(NULL)) > 0) {}
    munmap(val, sizeof(val));
    munmap(send, sizeof(send));
    return 0;
}