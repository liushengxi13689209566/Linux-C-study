/*************************************************************************
	> File Name: test_setitimer.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 16时35分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
void fun(int signo)
{
    switch(signo)
    {
        case SIGALRM :printf("+++++++++++++++++++++++++++++++++++++SIGALRM\n"); break;
        case SIGPROF :printf("------SIGPROF \n") ;break;
        default:break;
    }
}
int main(void)
{
    struct itimerval value ;
    signal(SIGALRM,fun);
    signal(SIGPROF,fun);
    value.it_value.tv_sec=  1;   //第一次一秒触发信号
    value.it_value.tv_usec=  0;   //
    value.it_interval.tv_sec=  5;  //第二次2 秒触发信号 
    value.it_interval.tv_usec=  1;// 
    setitimer(ITIMER_REAL,&value ,NULL); //
    setitimer(ITIMER_PROF,&value ,NULL); //
    while(1)
          ;
    return 0;
}

