/*************************************************************************
	> File Name: test_umask.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月18日 星期一 22时48分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    umask(0);   //不屏蔽任何权限
    if (creat("example_681.test",S_IRWXU|S_IRWXG|S_IRWXO) < 0) {
        perror("creat");
        exit(1);
    }

    umask(S_IRWXO);     //屏蔽其他用户的所有权限
    if (creat("example_682.test",S_IRWXU|S_IRWXG|S_IRWXO) < 0) {
        perror("creat");
        exit(1);
    }

    return 0;
}
