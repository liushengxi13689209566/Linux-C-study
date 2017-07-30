/*************************************************************************
	> File Name: env.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月15日 星期六 10时00分48秒
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>
int main(int argc,char **argv,char **envp)
{
    int i ;
    while(*envp)
    {
        printf("%s\n",*envp);
        *envp++;
    }
    return 0;
}
