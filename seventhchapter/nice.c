/*************************************************************************
	> File Name: nice.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月26日 星期三 09时10分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/resource.h>
int main(void)
{
    pid_t pid ;
    int n ;
    int stat_val  = 0 ;
    int  old ,new ;
    pid=fork();
    switch(pid)
    {
        case 0:
        printf("I m child process ,PID = %d ,PPID = %d \n",getpid() ,getppid() );
        old =getpriority(PRIO_PROCESS,0);
        printf("old priority is %d \n",old);
        new =nice(2);
        printf("new priority is %d \n",new);
        exit(0) ;
        case -1:printf("ERROR!!!\n");exit(-1);
        default :printf("I m parents process ,PID = %d ,PPID = %d \n",getpid() ,getppid() );
                break  ;
    }
    wait(&n);
    exit(0);

}
