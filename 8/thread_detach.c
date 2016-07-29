#include<pthread.h>
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

void print_message_function( void *ptr );

int main (void)
{
	pthread_t thread1;
    void *ret;
	while(1)
	{
		pthread_create(&thread1,NULL,(void *)&print_message_function,NULL);
		printf("%lu\n",thread1);
        pthread_join(thread1,&ret);
	}
    printf("%d\n",(int)ret);
	exit (0);
}
void  print_message_function( void *ptr )
{ 
  	pthread_detach(pthread_self());
    static int g;
    printf("%d\n", g++);
    pthread_exit((void *)0) ;
}
