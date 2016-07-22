/*************************************************************************
	> File Name: my_chown.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月20日 星期三 15时26分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv)
{
    int i, j = 0, k = 0;
    char uid[15], gid[15];
    struct stat buf;
    struct passwd *psd;
    struct group *grp;
    //检查参数个数的合法性
    if (argc < 3) {
        printf("my_chown <uid:gid> <file name>\n");
        exit(1);
    }

    //获取uid
    for (i=0; i<strlen(argv[1]); i++) {
        if (argv[1][i] != ':') {
            uid[j++] = argv[1][i];
        } else {
            uid[j] = '\0';
            break;
        }
    }

    //获取gid
    for (i++; i<strlen(argv[1]); i++) {
        gid[k++] = argv[1][i];
    }
    gid[k] = '\0';

    //改变文件所有者
    psd = getpwnam(uid);
    grp = getgrnam(gid);

    if (chown(argv[2],psd->pw_uid,grp->gr_gid) < 0) {
        perror("chown");
        exit(1);
    }

    return 0;
}
