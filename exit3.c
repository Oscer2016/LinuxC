/*************************************************************************
	> File Name: exit3.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月25日 星期一 16时08分58秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "exit2.c"
int main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("fork");
    } else if (pid == 0) {
        exit(7);
    }

    if (wait(&status) != pid) {
        perror("wait");
    } 
    pr_exit(status);

    if ((pid = fork()) < 0) {
        perror("fork");
    } else if (pid == 0) {
        abort();
    }

    if (wait(&status) != pid) {
        perror("wait");
    }
    pr_exit(status);

    if ((pid = fork()) < 0) {
        perror("fork");
    } else if (pid == 0) {
        status /= 0;
    }

    if (wait(&status) != pid) {
        perror("wait");
    }

    exit(0);
}
