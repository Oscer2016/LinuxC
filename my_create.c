/*************************************************************************
	> File Name: my_create.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月18日 星期一 09时07分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    extern int errno;
    int fd;
    //if ((fd = open("example_62.c", O_CREAT|O_EXCL, S_IRUSR|S_IWUSR)) == -1){
    if ((fd = open("example_62.c", S_IRWXU)) == -1){
        //perror("open");
        printf("open:%s with errno:%d\n",strerror(errno),errno);
        exit(1);        
    }else{
        printf("create file success\n");
    }

    close(fd);
    return 0;
}
