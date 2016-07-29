#include <stdio.h>
int main(void)
{
    int i;
    for (i=7; ; i+=7)
        if (i%2==1 && i%3==2 && i%5==4 && i%6==5)
            break;
    printf("这条阶梯共有 %d 阶 .\n",i);

    return 0;
}
