/*************************************************************************
	> File Name: fork7.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月25日 星期一 16时27分53秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        perror("fork");
    } else if (pid == 0) {  //first child
        if ((pid = fork()) < 0) {
            perror("fork");
        } else if (pid > 0) {
            exit(0);        //parent from second fork == first child
        } 
        /*
         * We're the second child;our parent becomes init as soon 
         * as our real parent calls exit() in the statement above.
         * Here's where we'd continue executing,knowing that when we're done, init will reap our status.
         */
        
        //sleep(2);
        printf("second child,parent pid = %d\n",getpid());
        exit(0);
    
    }

    if (waitpid(pid,NULL,0) != pid) { //wait for first child
        perror("waitpid");     
    } 

    /*
     * We're the parent (the original process);we continue executing,
     * knowing that we're not the parent of the second chilid.
     */
    exit(0);
}
