/*************************************************************************
	> File Name: compete.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月25日 星期一 17时09分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void charatatime(char *);

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
    } else if (pid == 0) {
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
    }

    exit(0);
}

static void charatatime(char *str) 
{
    char *ptr;
    int c;

    setbuf(stdout,NULL);
    for (ptr=str; (c = *ptr++) != 0;) {
        putc(c,stdout);
    }
}
