#include <stdio.h>
int main()
{
int x;
int summon = 0;
int disqualify = 1;
int reject = 2;
while(scanf("%d", &x) == 1) {
int result =x>5?summon:disqualify;
if(result == 0) {
printf("summon\n");
} else if(result == 1) {
printf("disqualify\n");
} else if(result == 2) {
printf("reject\n");
}
}
return 0;
}