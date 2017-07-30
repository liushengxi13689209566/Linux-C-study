/*************************************************************************
	> File Name: test_wait.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月15日 星期六 10时57分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void)
{
    int i,j;

    i=  wait(&j) ;
    printf("i== %d \n",i);
    return 0;

}
