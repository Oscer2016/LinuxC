/*************************************************************************
	> File Name: 4_36.c
	> Author: hepan
	> Mail: hepansos@gmail.com
	> Created Time: 2016年07月09日 星期六 11时06分31秒
 ************************************************************************/

#include <stdio.h>

//递归判断数组是否递增
int fun(int a[], int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return (a[n-1] >= a[n-2]);
    return ( fun(a, n-1) && (a[n-1] >= a[n-2]) );
}

int main(void)
{
    int a[] = {1,2,3,4,5,6};
    int b[] = {1,2,3,5,4,6};

    if ( fun(a,sizeof(a)/sizeof(a[0])) == 1 )
        printf("a: ok\n");
    else
        printf("a: no\n");

    if ( fun(b,sizeof(b)/sizeof(b[0])) == 1 )
        printf("b: ok\n");
    else
        printf("b: no\n");

    return 0;
}
