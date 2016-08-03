/*************************************************************************
	> File Name: client2.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年08月02日 星期二 15时28分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888

//客户端处理过程
void process_conn_client(int s)
{
    pid_t pid;
    ssize_t size = 0;
    char buffer[1024];          //数据的缓冲区
    
    pid = fork();

    for (; ;) {
        if (pid > 0) {
            memset(buffer, 0, 1024);
            //从标准输入中读取数据放到缓冲区buffer中
            int len = read(s, buffer, 1024);
            buffer[len] = '\0';
            printf("%s\n",buffer);
        } else {
            //读到数据
            memset(buffer, 0, 1024);
            fgets(buffer, 1024, stdin);
            buffer[strlen(buffer)] = '\0';
            write(s, buffer, strlen(buffer));         //发送给服务器
        }
    }
}

int main(int argc, char *argv[])
{
    int s, c; 
    char msg[127];
    pid_t pid;
    struct sockaddr_in server_addr;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("socket error\n");
        return -1;
    }

    //设置服务器地址
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    //将用户输入的字符串类型的IP地址转为整型
    inet_pton(AF_INET, "192.168.30.105", &server_addr.sin_addr);

    //连接服务器
    connect(s, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    process_conn_client(s);         //客户端处理过程
    close(s);                       //关闭连接
    return 0;
}

