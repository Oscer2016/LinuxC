/*************************************************************************
	> File Name: getpid.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月24日 星期日 22时09分18秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    if ((pid = fork()) == -1) {
        printf("fork error!\n");
        exit(1);
    }

    if (pid == 0) {
        printf("getpid return %d\n",getpid());
    }

    exit(0);
}
