/*************************************************************************
	> File Name: test_umask.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月16日 星期五 17时33分01秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
int main(void)
{
    umask(0);//不屏蔽任何权限
    if(creat("example_681",S_IRWXU | S_IRWXO |S_IRWXG) < 0)
    {
        perror("creat :");
        exit(1);
    }
    umask(S_IRWXO);  //屏蔽其他用户的所有权限
    if(creat("example_682",S_IRWXU | S_IRWXO |S_IRWXG) < 0)
    {
        perror("creat :");
        exit(2);
    }
    return 0;
}
