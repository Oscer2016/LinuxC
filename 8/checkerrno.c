/*************************************************************************
	> File Name: checkerrno.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月28日 星期四 11时34分18秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    FILE *stream;
    char *filename = "test";

    errno = 0;

    stream = fopen(filename, "r");
    if (stream  == NULL) {
        printf("open files %s failed, errno is %d\n",filename,errno);
    } else {
        printf("open file %s successfully\n",filename);
    }
}

