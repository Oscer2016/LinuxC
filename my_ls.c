#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>
#include <grp.h>
#include <pwd.h>
#include <dirent.h>
#include <errno.h>

#define MAXROWLEN 80

void my_err(const char *err_string, int line); 
void get_filenames(int flag, char *path);
void display_inode(struct stat buf,char *name);
void display_attribute(struct stat buf,char *name);
void display_single(char *name);
void display(int flag, char *pathname);

long sum_size = 0, s;
int count = 0;			//保存文件数
int g_leave_len = MAXROWLEN;
int g_maxlen = 0;

void my_err(const char *err_string, int line) 
{
    fprintf(stderr,"line:%d",line);
    perror(err_string);
    exit(1);
}

void get_filenames(int flag, char *path)
{
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;
	int i, j, k, len = strlen(path);
	
    char filenames[256][PATH_MAX+1], temp[PATH_MAX+1], name[256][PATH_MAX+1];

    dir = opendir(path);
    if (dir == NULL) {
        my_err("opendir",__LINE__);
    }
    while ((ptr = readdir(dir)) != NULL) {
        if (g_maxlen < strlen(ptr->d_name)) {
            g_maxlen = strlen(ptr->d_name);
        }
        count++;
    }
    closedir(dir);

    if (count > 256) {
        my_err("too many files under this dir",__LINE__);
    }

   
    dir = opendir(path);
    for (i=0; i<count; i++) {
        if ((ptr = readdir(dir)) == NULL) {
            my_err("readdir",__LINE__);
        }
        strncpy(filenames[i],path,len);
        filenames[i][len] = '\0';
        strcat(filenames[i],ptr->d_name);
        filenames[i][len+strlen(ptr->d_name)] = '\0';
    }
    
    for (i=0; i<count-1; i++)
        for (j=0; j<count-i-1; j++) {
            if (strcmp(filenames[j],filenames[j+1]) > 0) {
                strcpy(temp,filenames[j+1]);
                strcpy(filenames[j+1],filenames[j]);
                strcpy(filenames[j],temp);
            }
        }

    for (i=0; i<count; i++) {
        if (stat(filenames[i],&buf) == -1) {
            my_err("stat",__LINE__);
        }
        sum_size += buf.st_blocks;
    }
    
    closedir(dir);
    
    s = sizeof(filenames)/sizeof(filenames[0]);
    /*
    switch (flag) {
    case 5:
    case 6:
    case 7:
    	for (i=0; i<(s+1)/2; i++) {
		    strcpy(temp,filenames[i]);
		    strcpy(filenames[i],filenames[s-1]);
		    strcpy(filenames[s-1],temp);
    	}
    }
    */

    /*
    for (i=0; i<s; i++) {
    	for (j=0; j<strlen(filenames[i]); j++) {
		    if (filenames[i][j] == '/' || filenames[i][j] == '.') {
		        k = 0;
		        continue;
		    }
	    	name[i][k++] = filenames[i][j];
	    }
	    name[i][k] = '\0';
    }
    
    */
    
	switch (flag) {
	case 0:
	case 1:
	case 4:
	case 5:
		for (i=0; i<count; i++) {
			display(flag,filenames[i]);
		}
		break;

	case 2:
	case 3:
    case 6:
	case 7:
    case 10:
		printf("总用量  %ld\n",sum_size); 
		for (i=0; i<count; i++) {
			display(flag,filenames[i]);
		}
		break;
    case 8:
        /*
        for (i=0; i<(s+1)/2; i++) {
		    strcpy(temp,filenames[i]);
		    strcpy(filenames[i],filenames[s-1]);
		    strcpy(filenames[s-1],temp);
    	}
        for (i=0; i<count; i++) {
            display(flag,filenames[i]);
        }
        */
        
        for (i=s-1, k=0; i>=0; i--,k++) {
            printf("%s\t",filenames[i]);
           // if (k%5==0)
                //printf("\n");
        }
        //printf("\n");
        break;
        
	/*
	case 4:
	case 5:
		for (i=0; i<count; i++) {
			display(flag_param,filenames[i]);
		}
		break;

	case 7:
	case 8:
		printf("总用量  %ld\n",sum_size); 
		for (i=0; i<count; i++) {
			display(flag_param,filenames[i]);
		}
		break;
	*/   
	default:
		break;
	}
}

void display_inode(struct stat buf,char *name)
{
    printf("%d ",buf.st_ino);
}

void display_attribute(struct stat buf,char *name)
{
    struct passwd *psd;
    struct group *grp;
    char buf_time[32];

    if (S_ISLNK(buf.st_mode)) {
        printf("l");
    } else if (S_ISREG(buf.st_mode)) {
        printf("-");
    } else if (S_ISDIR(buf.st_mode)) {
        printf("d");
    } else if (S_ISCHR(buf.st_mode)) {
        printf("c");
    } else if (S_ISBLK(buf.st_mode)) {
        printf("b");
    } else if (S_ISFIFO(buf.st_mode)) {
        printf("f");
    } else if (S_ISSOCK(buf.st_mode)) {
        printf("s");
    } 

    if (buf.st_mode & S_IRUSR) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IWUSR) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IXUSR) {
        printf("x");
    } else {
        printf("-");
    }

    if (buf.st_mode & S_IRGRP) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IWGRP) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IXGRP) {
        printf("x");
    } else {
        printf("-");
    }

    if (buf.st_mode & S_IROTH) {
        printf("r");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IWOTH) {
        printf("w");
    } else {
        printf("-");
    }
    if (buf.st_mode & S_IXOTH) {
        printf("x");
    } else {
        printf("-");
    }
    printf("  ");

    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);

    printf("%4d ",buf.st_nlink);
    printf("%-8s",psd->pw_name);
    printf("%-8s",grp->gr_name);
    printf("%-8d",buf.st_size);
    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time) - 1] = '\0';
    printf("  %s",buf_time);
}

void display_single(char *name)
{
    int i, len;
    
    if (g_leave_len < g_maxlen) {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }

    len = strlen(name);
    len = g_maxlen - len;
    printf("%-s",name);
    
    for (i=0; i<len; i++) {
        printf(" ");
    }
    printf("  ");

    g_leave_len -= (g_maxlen + 2);
    
}

void display(int flag, char *pathname)
{
    int i, j;
    struct stat buf;
    char name[NAME_MAX + 1];

    for (i=0, j=0; i<strlen(pathname); i++) {
        if (pathname[i] == '/') {
            j = 0;
            continue;
        }
        name[j++] = pathname[i];
    }
    name[j] = '\0';

    if (lstat(pathname,&buf) == -1) {
        my_err("lstat",__LINE__);
    }

    switch (flag) {

    case 0:
        if (name[0] != '.') {
            display_single(name);
        }
        break;

    case 1:
        display_single(name);
        break;

    case 2:
        if (name[0] != '.') {
            display_attribute(buf,name);
            printf("  %-s\n",name);
        }
        break;

    case 3:
        display_attribute(buf,name);
        printf("  %-s\n",name);
        break;
    case 4:
        if (name[0] != '.') {
            display_inode(buf,name);
            display_single(name);
        }
        break;
    case 5:
        display_inode(buf,name);
        display_single(name);
        break;
    case 6:
        if (name[0] != '.') {
            display_inode(buf,name);
            display_attribute(buf,name);
        }
        break;
    case 7:
        display_inode(buf,name);
        display_attribute(buf,name);
        break;
    case 8:
        /*
        for (i=count-1; i>=0; i--) {
            printf("%s\t",name[i]);
        }	
        break;
        */
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    int i, j, k, num;
    char path[PATH_MAX+1];
    char param[32];
    int flag_param = 0;
    struct stat buf;

    j = 0;
    num = 0;
    for (i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            for (k=1; k<strlen(argv[i]); k++,j++) {
                param[j] = argv[i][k];
            }
            num++;
        }
    }

    for (i=0; i<j; i++) {
        if (param[i] == 'a') {
            flag_param |= 1;
            continue;
        } else if (param[i] == 'l') {
            flag_param |= 2;
            continue;
        } else if (param[i] == 'i') {
            flag_param |= 4;
            continue;
        } else if (param[i] == 'r') {
            flag_param |= 8;
            continue;
        } else {
            printf("my_ls: invalid option -%c\n", param[i]);
            exit(1);
        }
    }
    param[j] = '\0';

    //如果没有输入文件名或目录，显示当前目录
    if ((num + 1) == argc) {
        strcpy(path,"./");
        path[2] = '\0';
        get_filenames(flag_param,path);
        return 0;
    }
    
    i=1;
    do {
        if (argv[i][0] == '-') {
            i++;
            continue;
        } else {
            strcpy(path,argv[i]);
            if (stat(path,&buf) == -1) {
                my_err("stat",__LINE__);
            }
            if (S_ISDIR(buf.st_mode)) {
                if (path[strlen(argv[i]) -1] != '/') {
                    path[strlen(argv[i])] = '/';
                    path[strlen(argv[i]) + 1] = '\0';
                } else {
                    path[strlen(argv[i])] = '\0';
                }
                get_filenames(flag_param,path);         
                i++;
            } else {
                display(flag_param,path);
                i++;
            }
        }
    } while (i<argc);

    return 0;
}

