/*************************************************************************
	> File Name: fork5.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月25日 星期一 14时56分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int glob = 6;

int main(void)
{
    int var;
    pid_t pid;
    var = 88;
    
    printf("before vfork\n");
    if ((pid = vfork()) < 0) {
        perror("fork");
    } else if (pid == 0) {
        glob++;
        var++;
        _exit(0);
        //exit(0);
    }

    printf("pid = %d,glob = %d,var = %d\n",getpid(),glob,var);
    exit(0);
}
