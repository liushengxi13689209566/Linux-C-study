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

pthread_mutex_t text;
int  x = 520  ;
void *thread1()
{
    int temp ;
    pthread_mutex_lock(&text) ;
    temp = x;
   // sleep(1);
//    pthread_mutex_unlock(&x);   

    printf("temp == %d\n",temp);
//    pthread_mutex_unlock(&x);    
}
int main(void)
{
    pthread_t thid1; 
    pthread_create(&thid1 ,NULL,thread1,NULL); 
    sleep(5);
    printf("********************************************%d\n",x);
} 
   
