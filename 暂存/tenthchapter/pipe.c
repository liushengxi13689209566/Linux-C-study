/*************************************************************************
	> File Name: pipe.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月02日 星期三 17时59分45秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
int read_pipe(int fd0)
{
    char str[520];
    read(fd0,str,522);
    printf("the %s  is from pipe\n ",str);
}
int write_pipe(int fd1)
{
    char *p="刘生玺是不是最帅滴？？？？" ;
    write(fd1,p,strlen(p)+ 1);
    printf("write is OK !! \n");
}
int main(void)
{
    int fd[2]; //1 写     一血
    pid_t pid ;
    int status ;
    if(pipe(fd)) //在fork 之前调用pipe 必须！！！我就坑在这里！！ 
    {
        printf("Create pipe is failed !! \n");
        exit(-1);
    }
    pid=fork();
    switch(pid)
    {
        case 0:    
            close(fd[1]); //读的时候关闭写通道
            read_pipe(fd[0]);
            exit(0);
        default:
            close(fd[0]); //写的时候关闭读通道
            write_pipe(fd[1]);
            waitpid(pid ,&status,0);
            exit(0);
    }
    return 0;
}

