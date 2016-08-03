/*************************************************************************
	> File Name: server2.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年08月02日 星期二 14时45分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT        8888            //侦听端口地址
#define BACKLOG     5               //侦听队列长度

struct message {
    //struct in_addr sin_addr;
    //unsigned short sin_port;
    int sock_fd;
    //struct message *next;
}info[5];

/* 服务器对客户端的处理 */
void process_conn_server1(void *sc)
{
    ssize_t size = 0;
    char buffer[1024];

    for(;;){
        /* 从套接字中读取数据放到缓冲区buffer中 */
        size = read(info[0].sock_fd, buffer, 1024);   
        //printf("%s\n",buffer);
        buffer[size] = '\0';
        if(size == 0){/* 没有数据 */
            return; 
        }
        //gets(buffer);
        /* 构建响应字符，为接收到客户端字节的数量 */

        write(info[1].sock_fd, buffer, strlen(buffer));/* 发给客户端 */
    }   
}

/* 服务器对客户端的处理 */
void process_conn_server2(void *sc)
{
    ssize_t size = 0;
    char buffer[1024];

    for(;;){
        /* 从套接字中读取数据放到缓冲区buffer中 */
        size = read(info[1].sock_fd, buffer, 1024);   
        //printf("%s\n",buffer);

        if(size == 0){/* 没有数据 */
            return; 
        }
        buffer[size] = '\0';
        //gets(buffer);
        /* 构建响应字符，为接收到客户端字节的数量 */
        write(info[0].sock_fd, buffer, strlen(buffer));/* 发给客户端 */
    }   
}

int main(int argc, char *argv[])
{
    int ss, sc;         //ss为服务器的socket描述符，sc为客户端的socket描述符
    struct sockaddr_in server_addr;     //服务器地址结构
    struct sockaddr_in client_addr;     //客户端地址结构
    int err;                            //返回值
    pid_t pid;                          //分叉的进行ID
    pthread_t thid1, thid2;
    char msg[127];
    int i = 0;
    int n = 1;

    //建立一个流式套接字
    ss = socket(AF_INET, SOCK_STREAM, 0);
    if (ss < 0) {
        printf("soccket error");
        return -1;
    }

    //设置服务器地址
    bzero(&server_addr, sizeof(server_addr));   //清零
    server_addr.sin_family = AF_INET;           //协议族
    inet_aton("192.168.30.105",&server_addr.sin_addr);    //本机地址
    server_addr.sin_port = htons(PORT);                 //服务器端口

    //绑定地址结构到套接字描述符
    err = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (err < 0) {
        printf("bind error\n");
        return -1;
    }

    //设置侦听
    err = listen(ss, BACKLOG);
    if (err < 0) {
        printf("listen error\n");
        return -1;
    }
    
    for (; ;) {
        socklen_t addrlen = sizeof(struct sockaddr);

        sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
        //接收客户端连接
        write(sc, "welcome", 7);
        if (sc < 0) {
            continue;
        } 
        info[i++].sock_fd = sc;

        if (n) {
            n--;
		    pthread_create(&thid1, NULL, (void *)&process_conn_server1, NULL);
        } else {
		    pthread_create(&thid2, NULL, (void *)&process_conn_server2, NULL);    
        }
        
        /*
        //send(sc, "hello world", 12, 0);
        //建立一个新的进程处理到来的连接
        pid = fork();
        if (pid == 0) {
            close(ss);
            process_conn_server(sc);      //处理连接 
        } else {
            close(sc);
        }
        */
    }
}

