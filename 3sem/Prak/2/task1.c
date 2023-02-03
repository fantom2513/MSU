#include <stdio.h>
#include <string.h>
#include <stdlib.h>
enum { STR_SIZE = 129 };
int main(void)
{
    char str1[STR_SIZE], str2[STR_SIZE], str3[STR_SIZE];
    scanf("%s\n%s\n%s", str1, str2, str3);
    printf("[Host:%s,Login:%s,Password:%s]\n", str1, str2, str3);
}