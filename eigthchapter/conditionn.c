/*************************************************************************
	> File Name: conditionn.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月25日 星期二 08时38分01秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t mutex ;
pthread_cond_t cond ;
void *thread1( void *arg )
{
    pthread_cleanup_push(pthread_mutex_unlock ,&mutex); //退出时会执行它，用以清除资源（它又会指向一个函数：pthread_mutex_t_unlock）
    while(1)
    {
        printf("thread1 is running !! \n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond ,&mutex); //阻塞等待条件变量被设置为1
        printf("thread 1 is apply the conditionn !! \n");
        pthread_mutex_unlock(&mutex);
        sleep(4);
    }
    pthread_cleanup_pop(0);
}
void *thread2( void *arg )
{
    while(1)
    {
        printf("thread2 is running !! \n");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond ,&mutex); //阻塞等待条件变量被设置为1
        printf("thread2 is apply the conditionn !! \n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
int main(void)
{
    pthread_t tid1 ,tid2 ;
    printf("520520505201505205020502220500\n");
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&tid1 ,NULL,(void *)thread1 ,NULL);
    pthread_create(&tid2 ,NULL,(void *)thread2 ,NULL);
    do
    {
        pthread_cond_signal(&cond); //循环设置条件变量为1
    }while(1);
    sleep(50);
    pthread_exit(0);
}


