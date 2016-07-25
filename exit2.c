/*************************************************************************
	> File Name: exit2.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月25日 星期一 15时45分03秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void pr_exit(int status)
{
    if (WIFEXITED(status)) {
        printf("normal termination,exit status = %d\n",WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal terminationmination,signal number = %d%s\n",WTERMSIG(status),
    

    #ifdef WCOREDUMP
        WCOREDUMP(status) ? "(core file generated)" : "");
    #else
        "");
    #endif
    } else if (WIFSTOPPED(status)) {
            printf("child stopped,signal number = %d\n",WSTOPSIG(status));
        }

}
