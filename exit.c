#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>


int main()
{

    pid_t result;
    result = fork();
    if(result<0)
    perror("fork");
    if(result == 0)
    {
        printf("This is _exit test\n");
        printf("This is the content in the buffer000");
        _exit(0);
    }
    else
    {
        printf("This is exit test\n");
        printf("This is the content in the buffer");
        exit(0);
    }

    return 0;
}
