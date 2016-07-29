/*************************************************************************
	> File Name: createthread.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月27日 星期三 20时26分23秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *thread(void *arg)
{
    pthread_t newthid;
    pthread_t pthread_self();
    printf("this is a new thread, thread ID = %lu\n",newthid);
    return NULL;
}

int main(void)
{
    pthread_t thid;

    printf("main thread, ID is %lu\n",pthread_self());   //打印主线程的ID
    if (pthread_create(&thid, NULL, (void *)thread, NULL) != 0) {
        printf("thread creation failed\n");
        exit(1);
    }
    sleep(1);
    exit(0);
}
