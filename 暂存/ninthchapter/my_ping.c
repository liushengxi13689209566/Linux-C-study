/*************************************************************************
	> File Name: my_ping.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 16时20分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
void fun(int signo)
{
    printf("liushengxi  zui shuai !!! \n");
    alarm(1) ; //一秒发一个SIGALRM 信号
}
int main(void)
{
    signal(SIGALRM,fun);
    raise(SIGALRM); //先触发一个SIGALRM 信号  
    while(1)
        ;
    return 0;
}
