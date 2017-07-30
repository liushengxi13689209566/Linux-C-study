/*************************************************************************
	> File Name: execve.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月25日 星期二 21时47分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc,char *argv[] ,char *environ[])
{
    int i;
    int  t ;
    t= atoi(argv[1]);
    for(i= 0 ;i< t ;i++)
        printf("-----------------l55555555555555555555555555555555555\n") ;
    return 0;
}

