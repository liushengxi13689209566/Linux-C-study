/*************************************************************************
	> File Name: mutex_frist.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月24日 星期一 16时15分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

int x = 10;
pthread_mutex_t test;
void *thread1(void *arg)
{
    pthread_mutex_lock(&test) ;

    int n = 100;
    while(n--)
    {
        x++;
        //printf("%d\t",x);
    }
    printf("\n");
    pthread_mutex_unlock(&test);   
}

void *thread2(void *arg)
{
    pthread_mutex_lock(&test) ;

    int n = 100;
    while(n--)
    {
        x++;
        //printf("%d\t",x);
    }
    pthread_mutex_unlock(&test);   
}

int main(void)
{
    pthread_mutex_init(&test,NULL);
    pthread_t thid1,thid2; 
    pthread_create(&thid1 ,NULL,thread1,NULL); 
    pthread_create(&thid2 ,NULL,thread1,NULL); 
    sleep(5);
    printf("********************************************%d\n",x);
} 
   
