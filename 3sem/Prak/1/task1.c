#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int v,t,pos=0;
    scanf("%d%d",&v,&t);
    if(t)
    {
        if(v>=0)
            pos=(v*t)%109;
        else
            pos=(109+(v*t)%109)%109;
        printf("%d",pos);
    }
    else
        printf("%d",pos);

    return 0;
}