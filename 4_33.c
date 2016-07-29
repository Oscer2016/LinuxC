/*************************************************************************
	> File Name: 4_33.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月09日 星期六 10时53分43秒
 ************************************************************************/

#include <stdio.h>

void reverse(char *p)
{
    if (*p == '\0')
        return;
    reverse(p+1);
    printf("%c",*p);
}

int main(void)
{
    char s[6] = "hello";

    reverse(s);
    printf("\n");

    return 0;
}
