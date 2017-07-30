/*************************************************************************
	> File Name: execve_2.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月25日 星期二 21时49分33秒
 ************************************************************************/
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc,char **argv ,char **environ)
{
    pid_t pid ;
    int stat_val ;
    char *a= "50" ;
    char *b= "10" ;
    char *str[3] = { a,b, NULL};
    int  n;
    pid=fork() ;
    switch(pid)
    {
        case 0: execve("test",str,environ) ; exit(0);
        case  -1:printf("ERROR !!\n"); exit(-1);
        default : while(*environ) 
                  {
                      printf("%s\n",*environ);
                      *environ++;
                  }break;
    }
    wait(&n);
    printf("----------------%d\n",n);
    exit(0);
}

