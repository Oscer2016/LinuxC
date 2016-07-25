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
char buf[] = "a write to stdout\n";

int main(void)
{
    int var;
    pid_t pid;
    var = 88;
    
    if (write(STDOUT_FILENO,buf,sizeof(buf)-1)) {
        perror("write");
    }
    
    printf("before fork\n");
    if ((pid = fork()) < 0) {
        perror("fork");
    } else if (pid == 0) {
        glob++;
        var++;
    } else {
        sleep(2);
        //;
    }

    printf("pid = %d,glob = %d,var = %d\n",getpid(),glob,var);
    exit(0);
}
