/*************************************************************************
	> File Name: jointhread.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月28日 星期四 09时22分56秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void assisthread(void *arg)
{
    printf("I am helping to do some jobs\n");
    sleep(2);
    pthread_exit(0);
}

int main(void)
{
    pthread_t assistthid;
    int status;
    
    pthread_create(&assistthid, NULL, (void *)assisthread, NULL);
    pthread_join(assistthid, (void *)&status);
    printf("assistthread's exit is caused %d\n",status);

    return 0;
}
