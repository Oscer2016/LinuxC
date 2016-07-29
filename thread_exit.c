#include <stdio.h>  
#include <pthread.h>  
#include <stdlib.h>  
#include <unistd.h>

pthread_t       tid1, tid2;  
void            *tret;  
  
   
  
void  *thr_fn1(void *arg)  
{  
    sleep(1);//睡眠一秒，等待TID2结束。  
    pthread_join(tid2, &tret);//tid1一直阻赛，等到tid2的退出，获得TID2的退出码  
    printf("thread 2 exit code %d\n", (int)tret);  
    printf("thread 1 returning\n");  
    return((void *)2);  
}  
  
void  *thr_fn2(void *arg)  
{       
    printf("thread 2 exiting\n");  
    pthread_exit((void *)3);  
}  
  
int main(void)  
{  
    int     err;  
  
    err = pthread_create(&tid1, NULL, thr_fn1, NULL);  
    if (err != 0)  
        printf("can't create thread 1\n");  
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);  
    if (err != 0)  
        printf("can't create thread 2\n");  
    err = pthread_join(tid1, &tret);//主线程一直阻赛，等待TID1的返回。  
    if (err != 0)  
        printf("can't join with thread 1\n");  
    printf("thread 1 exit code %d\n", (int)tret);  
      //err = pthread_join(tid2, &tret);  
    //if (err != 0)  
    //    printf("can't join with thread 2\n");  
//    printf("thread 2 exit code %d\n", (int)tret);  
    exit(0);  
}   
