
/*************************************************************************
	> File Name: right_return.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 09时34分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<setjmp.h>
int flag = 0;
jmp_buf env ;
void fun1(int signo)
{
    if(flag == 0)
    return ;
    printf("SIGRTMAX - 9  \n");
    sleep(1);
    printf("after sleep !! \n");
    sleep(20);
    siglongjmp(env ,100);  //信号不会丢失
}
int main(void)
{
    switch(sigsetjmp(env,10000)) //第二个参数只要非零即可
    {
        case  0:flag= 1 ;break;
        case 100:printf("fun1 !!! \n");break;
    }
        signal(SIGRTMAX- 9 ,fun1);
    while(1)
       ;
    return 0;
}


