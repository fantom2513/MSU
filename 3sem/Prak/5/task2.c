#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    enum { BASE = 8 };
    const char mask[] = "rwxrwxrwx";

    int temp,
        access_rules;
    int size = sizeof(mask) - 1;
    char ans[sizeof(mask)]={0};
    for (int i = 1; i < argc; i++) {
        access_rules = strtol(argv[i], NULL, BASE);
        for (int j = 0; j < size; j++) {
            temp = access_rules & (0x1 << (size - j - 1));
            if (temp == 0) {
                ans[j] = '-';
            } else {
                ans[j] = mask[j];
            }
        }
        printf("%s\n", ans);
    }
}