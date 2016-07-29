#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void clean_fun1(void * arg)
{
    printf("this is clean fun1\n");
}
void clean_fun2(void * arg)
{
    printf("this is clean fun2\n");
}
void * thread_fun(void * arg)
{
    pthread_cleanup_push(clean_fun1,NULL);
    pthread_cleanup_push(clean_fun2,NULL);
    sleep(100);
    //这里要注意,如果将sleep(100);换成while(1);的话,程序会一直暂停.push和pop要成对出现.
    //因为while(1);运行的太快,线程不接受cancel信号
    //while(1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return NULL;
}

int main(void)
{
    pthread_t tid1;
    int err;
    err=pthread_create(&tid1,NULL,thread_fun,NULL);
    if(err!=0)
    {
        perror("pthread_create");
        exit(0);
    }
    sleep(3);
    //printf("test\n");
    err=pthread_cancel(tid1);
    if(err!=0)
    {
        perror("cancel error");
        exit(0);
    }
    
    err=pthread_join(tid1,NULL);
    
    if(err!=0)
    {
        perror("pthread_join  error");
        exit(0);
    }         
    return 0;
}

