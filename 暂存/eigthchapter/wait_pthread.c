/*************************************************************************
	> File Name: creat_pthread.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月18日 星期二 15时56分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int *creat_pthread(int *n  )
{
    pthread_t newthid ;
    int i;
    newthid=pthread_self() ;
    printf("the new  pthread ID is %d \n",newthid) ;
    for(i= 0 ;i< *n ;i++)
       printf("------------------------%d\n",i );
    pthread_exit((void *)-100);
}
int main(void)
{
    pthread_t thid ; 
    int n  ,i;
    int status ;
    printf("main pthread ID is %d \n",pthread_self());
    printf("please input  the   n :  ");
    scanf("%d",&n);
    if(pthread_create(&thid ,NULL ,(void *)creat_pthread ,&n) != 0)
    {
        printf("creat pthread is failed !! \n");
        exit(-1);
    }
    pthread_join(thid,(void *)&status);
    printf("the new pthread's exit number is %d \n",status);
    exit(0);
}
