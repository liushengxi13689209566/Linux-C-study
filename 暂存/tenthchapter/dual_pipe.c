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
int child_pipe(int fd0 ,int fd1)
{
    char str[520];
    read(fd0,str,522);
    printf("the %s  is from pipe1\n ",str);
    char *p="傻逼！！";
    write(fd1,p,strlen(p)+ 1);
    printf("Child process write is OK !! \n");
}
int parents_pipe(int fd0 ,int fd1)
{
    char *p="刘生玺是不是最帅滴？？？？" ;
    write(fd1,p,strlen(p)+ 1);
    printf("write is OK !! \n");
    char str[500];
    read(fd0,str,520);
    printf("Partents read from pipe  %s \n",str);
}
int main(void)
{
    int pipe1[2]; //1 写     一血
    int pipe2[2]; //
    pid_t pid ;
    int status ;
    if(pipe(pipe1)) //在fork 之前调用pipe 必须！！！我就坑在这里！！ 
    {
        printf("Create pipe is failed !! \n");
        exit(-1);
    }
    if(pipe(pipe2)) //在fork 之前调用pipe 必须！！！我就坑在这里！！ 
    {
        printf("Create pipe is failed !! \n");
        exit(-1);
    }
    pid=fork();
    switch(pid)
    {
        case 0:    
            close(pipe1[0]); //写管道1
            close(pipe2[1]); //读管道2
            child_pipe(pipe2[0],pipe1[1]);
            exit(0);
        default:
            close(pipe1[1]); //读管道1 
            close(pipe2[0]); //写管道2
            parents_pipe(pipe1[0],pipe2[1]);
            waitpid(pid ,&status,0);
            exit(0);
    }
    return 0;
}

