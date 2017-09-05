/*************************************************************************
	> File Name: tsd.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月24日 星期一 14时39分24秒
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
pthread_key_t key ;//键
void *thread2(int *arg) //是函数，但返回一个指针，即指针函数
{
    int tsd = 10  ;
    int  i;
    printf("thread2 %d is running !!\n",pthread_self() );
    pthread_setspecific(key,(void *)tsd );
    for(i= 0 ;i< 10 ;i++)
        printf("%d\t",*arg);
    printf("\nthread2 %d   : the key is %d \n",pthread_self(),pthread_getspecific(key) );
}
void *thread1(void *arg)
{
    int tsd = 520  ;
    pthread_t thid2 ;
    int T = 5;
    printf("thread1  %d is running !!\n",pthread_self() );
    pthread_setspecific(key,(void *)tsd);
    pthread_create(&thid2,NULL,thread2,&T);
    sleep(1); //等待thread2 结束
    printf("\nthread1 %d   : the key is %d \n",pthread_self(),pthread_getspecific(key) );
}
int main(void)
{
    pthread_t thid1;
    printf("main thread !!\n");
    pthread_key_create(&key,NULL);
    pthread_create(&thid1,NULL,thread1,NULL);
    sleep(3);
    pthread_key_delete(key);
    printf("main thread exit \n");
    return 0;
}
