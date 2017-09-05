/*************************************************************************
	> File Name: helloword.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月15日 星期六 10时26分15秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char **argv,char **environ)
{
    int i;
        printf("pid == %d\tppid ==  %d \n",getpid(),getppid());
    for(i= 0;i<argc ;i++)
        printf("%s\n",argv[i]);
    printf("Hello Word !!\n");
    return 0;
}

