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
#include <ctype.h>
#include <signal.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <readline/readline.h>
#include <readline/history.h>

#define normal          0       //一般命令
#define out_redirect_1  1       //输出重定向('>'新建)
#define out_redirect_2  2       //输出重定向('>>'追加)
#define in_redirect     3       //输入重定向
#define have_pipe       4       //管道命令

void handler_sigint(int signo);                 //信号处理函数
void my_err(const char *err_string, int line);  //错误处理函数
void get_pwd(char *pwd);                        //获取当前工作目录
void print_shell(void);                         //打印shell提示符
void save_input(char *buf);                     //保存输入的命令
void history(void); 							//记录历史命令
void draw_input(char *buf, int *argcount, char arglist[][256]);     //提取输入命令
void do_cmd(int argcount, char arglist[][256]);                     //处理输入命令
int find_cmd(char *cmd);                                            //查找命令中的可执行程序
void hpsh(void);                                                    //shell处理

int main(int argc, char *argv[])
{
    //char **arg = NULL;

    signal(SIGINT,handler_sigint);
    
    //signal(SIGINT,SIG_DFL);

    hpsh();
    
    exit(0);
}


//信号处理函数
void handler_sigint(int signo)
{
    //printf("\n");
    //print_shell();
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
    } else {
        strcpy(pwd,buf);
    }
}

/*
//输出shell提示符
void print_shell(void)
{
    char pwd[256];
    get_pwd(pwd);
    //printf("\033[01;32mhp@lenovo\033[0m:\033[01;34m%s\033[0m$ ",pwd);
}
*/

//shell处理
void hpsh(void)
{
    int i;
    char *buf = (char *)malloc(256);
    char arglist[10][256];
    int argcount = 0;

    if (buf == NULL) {
        my_err("malloc",__LINE__);   
    }
	while (1) {
		memset(buf,0,256);
		//print_shell();
		save_input(buf);
		if (strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0) {
		    break;
		}
		if (strcmp(buf,"") == 0 ) {
		    continue;
		}
		for (i=0; i<10; i++) {
		    arglist[i][0] = '\0';
		}
		argcount = 0;
		draw_input(buf, &argcount, arglist);
		do_cmd(argcount,arglist);
	}

    free(buf);
}

//保存输入的命令
void save_input(char *buf)
{
    int len = 0;
    char ch;
    int fd;
    char str[500];
    char *tmp;
    char pwd[256];
    char computer[256];

    struct passwd *pw;
    struct utsname uts;

    pw = getpwuid(getuid());

    if (gethostname(computer,255) != 0 || uname(&uts) < 0) {
        fprintf(stderr,"无法获取主机信息\n");
        exit(1);
    }

    get_pwd(pwd);

    sprintf(str,"\033[01;32m%s@%s\033[0m:\033[01;34m%s\033[0m$ ",pw->pw_name,uts.nodename,pwd);
    tmp = (char *)malloc(sizeof(256));
    memset(tmp,0,sizeof(tmp));
    tmp = readline(str);
    strcpy(buf,tmp);
    add_history(buf);
    free(tmp);
   
    fd = open("/tmp/history",O_CREAT|O_RDWR|O_APPEND,0644);
    if (fd < 0) {
        perror("open");
    }
    if (strlen(buf) != 0) {
        write(fd,buf,len);
        write(fd,"\n",1);
    }

    close(fd);
}

void history(void)
{
	int i = 0, ret, j;
    FILE *fp;
    char history[2000][20];

    fp = fopen("/tmp/history", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(0);
    }
    
    while ( fgets(history[i++],20,fp) ) ;
    fclose(fp);
    for (j=0; j<i-1; j++) {
        printf("    %d    %s",j+1,history[j]);
    }
}
//提取输入命令
void draw_input(char *buf, int *argcount, char arglist[][256])
{
    int i = 0, j = 0;

    while (buf[i] != '\0') {
        //if ( buf[i] != ' ' && (ispunct(buf[i]) == 0) ) {
        //if ( buf[i] != ' ' && (ispunct(buf[i]) == 0 || buf[i] == '-') ) {
        if ( buf[i] != ' ' ) {
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
    
    //printf("%s\n",arglist[0]);
    //printf("%s\n",arglist[1]);
    //printf("%s\n",arglist[2]);    
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
    char pwd[256];

    if (strcmp(arglist[0],"ls") == 0) {
        strcpy(arglist[argcount++],"--color");
    }

    for (i=0; i<argcount; i++) {
        arg[i] = (char *)arglist[i];
    }
    arg[i] = NULL;
    
    if (strcmp(arg[0],"history") == 0) {
        history();
        return;
    }

    if ( strcmp(arg[0],"cd") == 0 ) {
        if (arg[1] == NULL || (strcmp(arg[1],"~") == 0) ) {
            if (chdir("/home/hp") == 0) {
                return;
            } else {
                perror("chdir");
                return;
            }
        }
        if (arg[2] != NULL) {
            printf("wrong command\n");
        } else if (chdir(arg[1]) == 0) {
            return;
        } else {
            perror("chdir");
            return;
        }
    }

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
            other = out_redirect_1;
            if (arg[i+1] == NULL) {
                flag++;
            }
        }

        if (strcmp(arg[i],">>") == 0) {
            flag++;
            other = out_redirect_2;
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

    if (other == out_redirect_1) {
        for (i=0; arg[i] != NULL; i++) {
            if (strcmp(arg[i],">") == 0) {
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }

    if (other == out_redirect_2) {
        for (i=0; arg[i] != NULL; i++) {
            if (strcmp(arg[i],">>") == 0) {
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
            dup2(fd,1);
            execvp(arg[0],arg);
            close(fd);
            exit(0);
        }
        break;
    case 2:
        if (pid == 0) {
            if ( !(find_cmd(arg[0])) ) {
                printf("%s : command not found\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_APPEND|O_WRONLY,0644);
            dup2(fd,1);
            execvp(arg[0],arg);
            close(fd);
            exit(0);
        }
        break;
    case 3:
        if (pid == 0) {
            if ( !(find_cmd(arg[0])) ) {
                printf("%s : command not found\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_RDONLY);
            dup2(fd,0);
            execvp(arg[0],arg);
            close(fd);
            exit(0);
        }
        break;
    case 4:
        if (pid == 0) {
            int pid2;
            int status2;
            int fd2;

            if ((pid2 = fork()) < 0) {
                my_err("fork",__LINE__);
            } else if (pid2 == 0) {
                if ( !(find_cmd(arg[0])) ) {
                    printf("%s : command not found\n",arg[0]);
                    exit(0);
                }
                fd2 = open("/tmp/temp",O_WRONLY|O_CREAT|O_TRUNC,0644);
                dup2(fd2,1);
                execvp(arg[0],arg);
                exit(0);
            }
            
            if (waitpid(pid2,&status2,WNOHANG) == -1) {
                //my_err("waitpid",__LINE__);
                printf("%d: wait for child process error\n",__LINE__);
            }

            
            if ( !(find_cmd(argnext[0])) ) {
                printf("%s : command not found\n",argnext[0]);
                exit(0);
            }
            fd2 = open("/tmp/temp",O_RDONLY);
            dup2(fd2,0);

            execvp(argnext[0],argnext);
            
            if ( remove("/tmp/temp") ) {
                my_err("remove",__LINE__);
            }
            
            close(fd);
            exit(0);
        }
        break;
    default:
        break;
    }

    //如果命令中有&，表示后台执行，父进程直接返回，不等待子进程结束
    if (background == 1) {
        printf("[1] %d\n",pid);
        return;
    }

    //父进程等待子进程结束
    if (waitpid(pid,&status,0) == -1) {
        printf("%d: wait for child process error\n",__LINE__);
        //my_err("waitpid",__LINE__);
    }
    /*
    else if (background == 1) {
        printf("[1]+ 已完成         ");
        for (i=0; arg[i] != NULL; i++) {
            printf("%s ",arg[i]);
        }
        printf("\n");
    }
    */
    
}

//查找命令中的可执行程序
int find_cmd(char *cmd)
{
    DIR *dir;
    struct dirent *dirp;
    char *path[] = {"./","/bin","/usr/bin",NULL};

    //使当前目录下的程序可以运行
    if (strncmp(cmd,"./",2) == 0) {
        cmd = cmd + 2;
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

