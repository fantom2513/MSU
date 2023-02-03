#include <stdio.h>
int main()
{
    int x;
    while (scanf("%d", &x) == 1) {
        printf("%s\n", x > 5 ? "summon" : "disqualify");
    }
    return 0;
}