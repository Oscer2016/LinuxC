/*************************************************************************
	> File Name: oncerun.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月27日 星期三 22时01分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void) 
{
    printf("Function run is running in thread %lu\n",pthread_self());
}

void *thread1(void *arg)
{
    pthread_t thid = pthread_self();
    printf("1Current thread's ID is %lu\n",thid);
    pthread_once(&once,run);
    printf("thread1 ends\n");
}

void *thread2(void *arg)
{
    pthread_t thid  = pthread_self();
    printf("2Current thread's ID is %lu\n",thid);
    //pthread_once(&once, run);
    printf("thread2 ends\n");
}

int main(void)
{
    pthread_t thid1, thid2;

    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(1);
    printf("main thread exit!\n");

    exit(0);
}
