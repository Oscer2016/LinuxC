/*************************************************************************
	> File Name: test_address.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年08月01日 星期一 11时29分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    char buffer[32];
    int ret = 0;
    int host = 0;
    int network = 0;
    unsigned int address = 0;
    struct in_addr in;

    in.s_addr = 0;

    //输入一个以'.'分隔的字符串形式的IP地址
    printf("please input your ip address: ");
    fgets(buffer,31,stdin);
    buffer[31] = '\0';

    //示例使用inet_aton()函数
    if ((ret = inet_aton(buffer,&in)) == 0) {
        printf("inet_aton: \tinvalid address\n");
    } else {
        printf("inet_aton:\t0x%x\n",in.s_addr);
    }

    //示例使用inet_addr()函数
    if ((address = inet_addr(buffer)) == INADDR_NONE) {
        printf("inet_addr: invalid address\n");
    } else {
        printf("inet_addr:\t0x%lx\n",address);
    }

    //示例使用inet_network()函数
    if ((address = inet_network(buffer)) == -1) {
        printf("inet_network: invalid address\n");
    } else {
        printf("inet_network:\t0x%lx\n",address);
    }

    //示例使用inet_ntoa()函数
    if (inet_ntoa(in) == NULL) {
        printf("inet_ntoa: invalid address\n");
    } else {
        printf("inet_ntoa:\t%s\n",inet_ntoa(in));
    }

    //示例使用inet_lnaof()与inet_netof()函数
    host = inet_lnaof(in);
    network = inet_netof(in);

    printf("inet_lnaof:\t0x%x\n",host);
    printf("inet_netof:\t0x%x\n",network);

    in = inet_makeaddr(network,host);
    printf("inet_makeaddr:0x%x\n",in.s_addr);

    return 0;
}
