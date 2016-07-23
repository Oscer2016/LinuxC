/*************************************************************************
	> File Name: diffork.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月23日 星期六 09时37分33秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int globVar = 5;

int main(void)
{
    pid_t pid;
    int var = 1, i;
    
    printf("fork is different with vfork \n");

    pid = vfork();
    //pid = fork();
    switch (pid) {
    case 0:
        i = 3; 
        while(i-- > 0) {
            printf("Child process is running\n");
            globVar++;
            var++;
            sleep(1);
        }
        printf("%d %d\n",getpid(),getppid());
        printf("Child's globVar = %d, var = %d\n",globVar,var);
        //break;
        exit(0);
    case -1:
        perror("Process creation failed\n");
        exit(0);
    default:
        i = 5;
        while (i-- > 0) {
            printf("Parent process is running\n");
            globVar++;
            var++;
            sleep(1);
        }
        printf("%d %d\n",getpid(),getppid());
        printf("Parent's globVar = %d, var = %d\n",globVar,var);
        exit(0);
    }

    return 0;
}
