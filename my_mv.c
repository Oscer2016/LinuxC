/*************************************************************************
	> File Name: my_mv.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月19日 星期二 00时01分29秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    //检查参数个数的合法性
    if (argc < 3) {
        printf("my_mv <old file> <new file>\n");
        exit(0);
    }

    if (rename(argv[1],argv[2]) < 0) {
        perror("rename");
        exit(1);
    }

    return 0;
}
