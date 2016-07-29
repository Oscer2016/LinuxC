/*************************************************************************
	> File Name: my_touch.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月19日 星期二 09时27分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>

#define     PARAM_NONE  0   //无参数
#define     PARAM_T     1   //-t更改新建文件的时间

int main(int argc, char **argv)
{
	int i, j, k, num;
    char param[20];                 //保存命令行参数，不包含目标文件名
    int flag_param = PARAM_NONE;    //参数种类，即是否有-t选项
    int fd;
    struct stat statbuf;
    struct utimbuf timebuf;

    //命令行参数解析
    j = 0;
    k = 1;
    for (i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            for (j=0; j<strlen(argv[i]); ) {
                param[j++] = argv[i][k++];  //获取'-'后的参数保存到数组param中
            }
    	}
    }
    
    //只支持-t选项，如果含有其他选项就报错
    for (i=0; i<j-1; i++) {
        if (param[i] == 't') {
            flag_param |= PARAM_T;
            continue;
        } else {
            printf("my_touch: invalid option -%c\n",param[i]);
            exit(1);
        }
    }
    param[j] = '\0';

    //创建空文件
    if ((fd = open(argv[argc-1],O_EXCL|O_CREAT,S_IRWXU)) < 0) {
        perror("open");
        exit(1);
    }

    close(fd);

    //改变修改时间
    if (flag_param) {

        timebuf.modtime = atoi(argv[argc-2]);
        timebuf.actime = atoi(argv[argc-2]);

        if (utime(argv[argc-1], &timebuf) < 0) {

            perror("utime");
            exit(1);
        }   
    }


    /*
    i = 1;
    do {
        if (argv[i][0] == '-') {
            i++;
            continue;
        }
    } while (i < argc);
    */
}
    
        

