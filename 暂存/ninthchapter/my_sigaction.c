/*************************************************************************
	> File Name: my_sigaction.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 08时31分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
/*在执行一个信号处理程序的过程中将该种信号自动屏蔽掉。所谓“屏蔽”，与将信号忽略是不同的，
 * 它只是将信号暂时“遮盖”一下，一旦屏蔽去掉，已到达的信号又继续得到处理。*/
 int temp =0 ;
 void fun(int signo)
 {
     printf("liushengxi\n");
     sleep(5);
     temp = temp + 10;
     printf("temp ==  %d \n",temp);
 }
 int main(void)
 {
     struct sigaction act ; // struct sigaction 类型用来描述对信号的处理
     act.sa_handler = fun ; // sa_handler 是一个函数指针，其含义与 signal 函数中的信号处理函数类似
     act.sa_flags= SA_NOMASK ; // sa_flags 成员用于指定信号处理的行为
     sigaction(SIGINT , &act ,NULL);
     while(1)
         ;
     return 0;
 }

