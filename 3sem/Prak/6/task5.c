#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};
enum
{
    USER_SHIFT = 6,
    GROUP_SHIFT = 3,
    MASK = 0x7
};
static int
check_rights(int access, int st_mode, int shift)
{
    int reqired_rules = (st_mode & (access << shift)) >> shift;
    return access == reqired_rules;
}
static int
find_gid(const struct Task *task, const struct stat *stb)
{
    for (int i = 0; i < task->gid_count; i++) {
        if (task->gids[i] == stb->st_gid) {
            return 1;
        }
    }
    return 0;
}
int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (task->uid == 0) {
        return 1;
    }

    if (task->uid == stb->st_uid) {
        return check_rights(access, stb->st_mode, USER_SHIFT);
    }

    if (find_gid(task, stb)) {
        return check_rights(access, stb->st_mode, GROUP_SHIFT);
    }
    return check_rights(access, stb->st_mode, 0);
}