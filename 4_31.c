/*************************************************************************
	> File Name: 4_31.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月08日 星期五 09时59分21秒
 ************************************************************************/

#include <stdio.h>
#define MAX 255
int main(void){

    unsigned char a[MAX], i;
    
    for (i=0; i<=MAX; i++){
        a[i] = i;
        //printf("%d ",a[i]);
    }
    //上一个循环是死循环，所以不会执行本循
    for (i=0; i<=MAX; i++){
        printf("%d ",a[i]);
    }

    printf("\n");
    return 0;
}
