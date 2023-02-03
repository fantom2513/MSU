#include <string.h>
const char mask[] = "rwxrwxrwx";
int
parse_rwx_permissions(const char *str)
{

    if (str == NULL) {
        return -1;
    }
    unsigned int ans = 0;
    int size_of_mask = sizeof(mask) - 1;
    unsigned int size = strlen(str);
    if (size != size_of_mask) {
        return -1;
    }

    int i = 0;
    while (str[i] != '\0') {

        if (str[i] == mask[i]) {
            ans += 0x1 << (size_of_mask - i - 1);
        } else if (str[i] != '-') {
            return -1;
        }
        i++;
    }
    return ans;
}