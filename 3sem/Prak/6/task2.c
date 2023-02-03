#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    long long sum = 0;
    DIR *dir = opendir(argv[1]);
    char buff[PATH_MAX];
    struct dirent *input = readdir(dir);
    while (input != NULL) {
        int size = strlen(input->d_name);
        int res = snprintf(buff, sizeof(buff), "%s/%s", argv[1], input->d_name);
        if (res <= sizeof(buff)) {
            struct stat st;
            int exist = stat(buff, &st);

            char *template = ".exe";
            int len_template = strlen(template);
            if (exist == 0 && S_ISREG(st.st_mode) && !access(buff, X_OK)
                && size >= sizeof(template) && !strcmp(&input->d_name[size - len_template], template)) {
                sum++;
            }
            input = readdir(dir);
        }
    }
    printf("%lld\n", sum);
    closedir(dir);
}