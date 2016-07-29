/*************************************************************************
	> File Name: errshow.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月28日 星期四 11时41分24秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

FILE *open_file(char *filename)
{
    FILE *stream;
    errno = 0;

    stream = fopen(filename, "r");
    if (stream == NULL) {
        printf("can not open the file %s. reason: %s\n",filename,strerror(errno));
        exit(-1);
    } else {
        return stream;
    }
}

int main(void)
{
    char *filename = "test";

    open_file(filename);
    return 0;
}
