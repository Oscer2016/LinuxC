/*************************************************************************
	> File Name: fork.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月21日 星期四 23时30分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("Process Creation Study\n");
    pid = fork();

    switch(pid) {
    case 0:
        printf("Child process is running,Curpid is %d,ParentPid is %d\n",pid,getppid());
        break;
    case -1:
        printf("Process creation failed\n");
        break;
    default:
        printf("Parent process is running,ChildPid is %d,ParentPid is %d\n",pid,getpid());
        break;
    }
    exit(0);
}
