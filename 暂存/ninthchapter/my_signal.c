/*************************************************************************
	> File Name: my_signal.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月31日 星期一 16时29分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
void test1(int signo)
{
    printf("SIGINT\n") ;
}
void test2(int signo)
{
    printf("SIGQUIT\n") ;
}
int main(void)
{
    signal(SIGINT,test1) ;
    signal(SIGQUIT,test2);
    while(1)
        ;
    return 0;
}

