/*************************************************************************
	> File Name: 4_40.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月14日 星期四 10时53分15秒
 ************************************************************************/

#include <stdio.h>
char *Strcpy(char *dest, char *src)
{
    if ( (dest == NULL) || (src == NULL) )
    {
        printf("arg wrong\n");
        return NULL;
    }
    char *ret_string = dest;
    while ( (*dest++ = *src++) != '\0' ) ;
    *dest = '\0';
    return ret_string;
}
int main(void)
{
    char a[] = "helloworld";
    char b[] = "hello";
    printf("%s\n",Strcpy(a,b));
    return 0;
}
