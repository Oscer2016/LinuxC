#include <stdio.h>
int main(void)
{
    int a, b, c, d, e;
    for (a=1; a<=5; a++)
    {
        for (b=1; b<=5; b++)
        {
            if (b==a)   continue;
            for (c=1; c<=5; c++)
            {
                if (c==a || c==b)
                    continue;
                for(d=1; d<=5; d++)
                {
                    if (d==a || d==b || d==c)
                        continue;
                    e=15-a-b-c-d;
                    if ( ((a==3) != (b==1)) && ((b==2) != (e==4)) && ((c==1) != (d==2)) && ((c==5) != (d==3)) && ((a==1) != (e==4)) )
                        printf("A=%d,B=%d,C=%d,D=%d,E=%d.\n",a,b,c,d,e);
                }
            }
        }
    }
    return 0;
}

