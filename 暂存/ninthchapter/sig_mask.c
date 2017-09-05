/*************************************************************************
	> File Name: sig_mask.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 17时22分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
void my_error(const chat *str ,int line )
{
    perror(str);
    printf("at  %d \n",line);
    exit(0);
}
int fun(int signo)
{
    printf("****************************************SIGINT\n");
}
int main(void)
{
    
}
