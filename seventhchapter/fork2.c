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
    int i;
    pid=fork();
    switch(pid)
    {
        case 0:
          for(i= 0 ;i< 50 ;i++) 
            printf("*****************************子进程\n");
            break;
        case -1:
            printf("creat P id failed \n");
            break;
        default:
          for(i= 0 ;i< 50 ;i++) 
            printf("+++++++++++++++++++++++++++++++++++++++父进程哦！！\n");
            break ;
    }
  
    return 0;
}
