/*************************************************************************
	> File Name: myshell.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月25日 星期一 22时58分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

#define normal          0       //一般命令
#define out_redirect    1       //输出重定向
#define in_redirect     2       //输入重定向
#define have_pipe       3       //管道命令

void my_err(const char *err_string, int line);  //错误处理函数
void get_pwd(char *pwd);                        //获取当前工作目录
void print_shell();                             //打印shell提示符
void save_input(char *buf);                     //保存输入的命令
void draw_input(char *buf, int *argcount, char arglist[][256]);     //提取输入命令
void do_cmd(int argcount, char arglist[][256]);                     //处理输入命令
int find_cmd(char *cmd);                                            //查找命令中的可执行程序

int main(int argc, char *argv[])
{
    int i;
    char arglist[10][256];
    int argcount = 0;
    char **arg = NULL;
    char *buf = (char *)malloc(256);

    if (buf == NULL) {
        my_err("malloc",__LINE__);   
    }
    
    while (1) {
        memset(buf,0,256);
        print_shell();
        save_input(buf);
        
        if (strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0) {
            break;
        }
        if (strcmp(buf,"") == 0) {
            continue;
        }
        for (i=0; i<10; i++) {
            arglist[i][0] = '\0';
        }
        argcount = 0;
        draw_input(buf, &argcount, arglist);
        do_cmd(argcount,arglist);
    }

    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }

    exit(0);
}

//错误处理函数
void my_err(const char *err_string, int line)
{
    fprintf(stderr,"line: %d ",line);
    perror(err_string);
    exit(1);
}

//获取当前工作目录
void get_pwd(char *pwd)
{
    int i, j = 0;
    char buf[256];

    getcwd(buf,256);

    if (strncmp(buf,"/home/hp",8) == 0) {
        pwd[j++] = '~';
        for (i=8; buf[i] != '\0'; i++,j++) {
            pwd[j] = buf[i];
        }
        pwd[j] = '\0';
    }
}

//输出shell提示符
void print_shell()
{
    char pwd[256];
    get_pwd(pwd);
    printf("\033[01;32mhp@lenovo\033[0m:\033[01;34m%s\033[0m$ ",pwd);
}

//保存输入的命令
void save_input(char *buf)
{
    int len = 0;
    char ch;

    while (len < 256 && ((ch = getchar()) != '\n')) {
        buf[len++] = ch;
    }

    //命令过长，退出程序
    if (len == 256) {
        printf("command is too long...\n");
        exit(-1);
    }

    buf[len] = '\0';
    /*
    int i;
    for (i=0; buf[i]!='\0'; i++){
        printf("%c\n",buf[i]);
    }
    for (i=0; buf[i]!='\0'; i++){
        printf("%d\n",buf[i]);
    }
    */
}

//提取输入命令
void draw_input(char *buf, int *argcount, char arglist[][256])
{
    int i = 0, j = 0;

    while (buf[i] != '\0') {
        if (buf[i] != ' ') {
            arglist[*argcount][j++] = buf[i++];           
        } else {
            while (buf[++i] == ' '){
                continue;
            }
            arglist[*argcount][j] = '\0';
            (*argcount)++;
            j = 0;
        }
    }
    arglist[(*argcount)++][j] = '\0';
    /*
    printf("%s\n",arglist[0]);
    printf("%s\n",arglist[1]);
    printf("%s\n",arglist[2]);
    */
}

//处理输入命令
void do_cmd(int argcount, char arglist[][256])
{
    int flag = 0;
    int background = 0;     //标识命令中是否有后台运行标识符&
    int other = 0;          //用于指示命令中是否有>,<,|
    int status;
    int i;
    int fd;
    char *argnext[argcount+1];
    char *arg[argcount+1];
    char *file;
    pid_t pid;

    for (i=0; i<argcount; i++) {
        arg[i] = (char *)arglist[i];
    }
    arg[i] = NULL;
    
    for (i=0; i<argcount; i++) {
        if (strncmp(arg[i],"&",1) == 0) {
            if (i == argcount-1) {
                background = 1;
                arg[argcount-1] = NULL;
                break;
            } else {
                printf("wrong command\n");
                exit(1);
            }
        }
    }

    for (i=0; arg[i] != NULL; i++) {
        if (strcmp(arg[i],">") == 0) {
            flag++;
            other = out_redirect;
            if (arg[i+1] == NULL) {
                flag++;
            }
        }

        if (strcmp(arg[i],"<") == 0) {
            flag++;
            other = in_redirect;
            if (i == 0) {
                flag++;
            }
        }

        if (strcmp(arg[i],"|") == 0) {
            flag++;
            other = have_pipe;
            if (arg[i+1] == NULL) {
                flag++;
            }
            if (i == 0) {
                flag++;
            }
        }
    }

    if (flag > 1) {
        printf("wrong command\n");
        exit(0);
    }

    if (other == out_redirect) {
        for (i=0; arg[i] != NULL; i++) {
            if (strcmp(arg[i],">") == 0) {
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }

    if (other == in_redirect) {
        for (i=0; arg[i] != NULL; i++) {
            if (strcmp(arg[i],"<") == 0) {
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }

    if (other == have_pipe) {
        for (i=0; arg[i] != NULL; i++) {
            if (strcmp(arg[i],"|") == 0) {
                arg[i] = NULL;
                int j;
                for (j=i+1; arg[j] != NULL; j++) {
                    argnext[j-i-1] = arg[j];
                }
                argnext[j-i-1] = arg[j];
                break;
            }
        }
    }

    if ((pid = fork()) < 0) {
        my_err("fork",__LINE__);
    }

    switch (other) {
    case 0:
        if (pid == 0) {
            if ( !(find_cmd(arg[0])) ) {
                printf("%s : command not found\n",arg[0]);
                exit(0);
            }
            execvp(arg[0],arg);
            exit(0);
        }
        break;
    case 1:
        if (pid == 0) {
            if ( !(find_cmd(arg[0])) ) {
                printf("%s : command not found\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
            printf("%d\n",fd);
            dup2(fd,1);
            execvp(arg[0],arg);
            exit(0);
        }
        break;
    case 2:
        if (pid == 0) {
            if ( !(find_cmd(arg[0])) ) {
                printf("%s : command not found\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_RDONLY);
            dup2(fd,0);
            execvp(arg[0],arg);
            exit(0);
        }
        break;
    case 3:
        if (pid == 0) {
            int pid2;
            int status2;
            int fd2;

            if ((pid = fork()) < 0) {
                my_err("fork",__LINE__);
            } else if (pid2 == 0) {
                if ( !(find_cmd(arg[0])) ) {
                    printf("%s : command not found\n",arg[0]);
                    exit(0);
                }
                fd2 = open("/tmp/youdonotkownfile",O_WRONLY|O_CREAT|O_TRUNC,0644);
                dup2(fd2,1);
                execvp(arg[0],arg);
                exit(0);
            }
            if (waitpid(pid2,&status2,0) == -1) {
                //my_err("waitpid",__LINE__);
                printf("wait for child process error\n");
            }
            if ( !(find_cmd(argnext[0])) ) {
                printf("%s : command not found\n",argnext[0]);
                exit(0);
            }
            fd2 = open("/tmp/youdonotkownfile",O_RDONLY);
            dup2(fd2,0);
            execvp(argnext[0],argnext);

            if ( remove("/tmp/youdonotkownfile") ) {
                my_err("remove",__LINE__);
            }
            exit(0);
        }
        break;
    default:
        break;
    }

    //如果命令中有&，表示后台执行，父进程直接返回，不等待子进程结束
    if (background == 1) {
        printf("[process id %d]\n",pid);
        return;
    }

    //父进程等待子进程结束
    if (waitpid(pid,&status,0) == -1){
        printf("wait for child process error\n");
        //my_err("waitpid",__LINE__);
    }
}
    

//查找命令中的可执行程序
int find_cmd(char *cmd)
{
    DIR *dir;
    struct dirent *dirp;
    char *path[] = {"./","/bin","/usr/bin",NULL};

    //使当前目录下的程序可以运行
    if (strncmp(cmd,"./",2) == 0) {
        cmd += 2;
    }

    //分别在当前目录，/bin和/usr/bin目录查找要执行的程序
    int i = 0;
    while (path[i] != NULL) {
        if ((dir = opendir(path[i])) == NULL) {
            my_err("opendir",__LINE__);
        }
        while ((dirp = readdir(dir)) != NULL) {
            if (strcmp(dirp->d_name,cmd) == 0) {
                closedir(dir);
                return 1;
            }    
        }
        closedir(dir);
        i++;
    }
    return 0;
}

