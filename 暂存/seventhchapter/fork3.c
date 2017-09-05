/*************************************************************************
	> File Name: fork2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月23日 星期五 10时03分54秒
 ************************************************************************/
#include<stdlib.h>
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
            while(1)
            {
                printf("PID: %d  PPID : %d \n",getpid(),getppid());
                sleep(3);
            }
        case -1:
            printf("creat P id failed \n");
            exit(-1);
        default:
            printf("I 'm PPprogress,PPID :%d\n",getpid());//父进程执行
            exit(0);//父进程退出
    }
}
