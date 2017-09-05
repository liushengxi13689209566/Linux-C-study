/*************************************************************************
	> File Name: exec.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月15日 星期六 10时28分52秒
 ************************************************************************/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char **argv,char **environ)
{
    pid_t pid ;
    int i;
    pid=fork();
    switch(pid)
    {
        case -1:printf("ERROR !!\n");
                exit(-1);
        case 0:printf("chaild is running \n");
        printf("pid == %d\tppid ==  %d \n",getpid(),getppid());
        execve("111",argv,environ);
        exit(0);
        default:
        printf("Parents is running !!\n");
        break;
    }
 
    exit(0);
}


