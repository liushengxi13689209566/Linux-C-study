/*************************************************************************
	> File Name: my_kill.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 10时11分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc ,char **argv) //kill -s 2 **** // kill ****
{
    int i ,j ;
    pid_t pid ;
    char str[520]; //保存命令行输入
    int signum = SIGTERM ;
    if(argc <  2 || argc > 4 )
    {
        printf("Wrong commend !! \n");
        exit(-1);
    }

    if(argc == 2)
    {
        pid = atoi(argv[1]) ; 
    }

    if(argc == 4)
    {
        signum =  atoi(argv[2]) ;
        pid = atoi(argv[3]) ;
    }

    if(kill(pid,signum) < 0)
    {
        printf("Kill error !!! \n");
        exit(-1);
    }
}

