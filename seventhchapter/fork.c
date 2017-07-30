/*************************************************************************
	> File Name: fork2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月23日 星期五 10时03分54秒
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(void)
{
    pid_t pid;
    pid=fork();
    switch(pid)
    {
        case 0://子进程执行
            printf("PID: %d  PPID : %d \n",getpid(),getppid());
            break;     
        case -1:
            printf("creat P id failed \n");
        break;
        default:
            printf("I 'm PPprogress,PPID :%d\n",getpid());//父进程执行
        break;
    }
    return 0;
}
