/*************************************************************************
	> File Name: fork3.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月23日 星期六 00时16分24秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    
    pid = fork();
    switch (pid) {
    case 0:
        while (1) {
            printf("A background process , PID: %d, ParentID: %d\n",getpid(),getppid());
            sleep(3);
        }
    case -1:
        perror("Process creation failed\n");
        exit(-1);
    default:
        printf("I am parent process,my pid is %d\n",getpid());
    }

    return 0;
}
