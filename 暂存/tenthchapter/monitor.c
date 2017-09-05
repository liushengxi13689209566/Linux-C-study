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
int main(int argc,char **argv)
{
    int fd[2]; //1 写     一血
    pid_t pid ;
    int status ;
    if(argc <  2)
    {
        printf("Wrong Param !! \n");
        exit(-1);
    }
    if(pipe(fd)) //在fork 之前调用pipe 必须！！！我就坑在这里！！ 
    {
        printf("Create pipe is failed !! \n");
        exit(-1);
    }
    pid = fork() ;
    switch(pid)
    {
        case 0:   
            printf("mobioeteoiittjnmpp");
            /*close(0) ; //关闭标准输入，复制管道输出端到标准输入；
            dup(fd[0]);*/
            dup2(0,fd[0]);
            if(execvp("./111",argv)< 0)
            {
                perror("execvp wrong !!\n");
                exit(-1);
            }
            exit(0);
        default:
            close(fd[0]); //关闭读通道
            write(fd[1],argv[1],strlen(argv[1]) );
            break;
    }
            wait(&status);
            exit(0);
}
