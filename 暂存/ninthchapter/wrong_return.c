/*************************************************************************
	> File Name: wrong_return.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月01日 星期二 08时55分35秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<setjmp.h>
jmp_buf env ;
void fun1(int signo)
{
    printf("SIGRTMIN + 15\n");
    longjmp(env,10);

}
void fun2(int signo)
{
    printf("SIGTRMAX -15 \n");
    longjmp(env,20);
}
int main(void)
{
    switch(setjmp(env))
    {
        case 0: break;
        case 10:printf("fun1    \n"); break;
        case 20:printf("fun2     \n");break ;
    }
    signal(SIGRTMIN+ 15,fun1);
    signal(SIGRTMAX -9,fun2);
    while(1)
          ;
    return 0;
}

