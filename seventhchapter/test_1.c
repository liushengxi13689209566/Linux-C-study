/*************************************************************************
	> File Name: test_1.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月29日 星期六 17时28分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
    int i= 10;
    pid_t pid  ;
    int s;
//    pid=fork();
    pid= fork();
    switch(pid){
        case 0: i+ 10 ;  return 0 ;
        default:waitpid(pid,&s,0);
        printf("%d\n",i);
    }
}
