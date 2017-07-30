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
typedef struct {
    int a;
    int b;
}TT ;
void *creat_pthread(void *arg)
{
    TT *p = (TT *)arg;
    pthread_t newthid ;
    int i;
    newthid=pthread_self() ;
    printf("the new  pthread ID is %u \n",newthid) ;
    for(i= 0 ;i< (p->a)  ; i++ )
       printf("---------------------------%d\n",i );
    return NULL ;
}
int main(void)
{
    TT *p = (TT *)malloc(sizeof(TT)) ;
    pthread_t thid ; 
    int n  ,i;
    p->a= 100 ;
    p->b= 30 ; 
    printf("%d %d\n",p->a,p->b);
    printf("the main  pthread ID is %u \n",pthread_self()) ;
    if(pthread_create(&thid ,NULL ,creat_pthread ,(void *)p) != 0)
    {
        printf("creat pthread is failed !! \n");
        exit(-1);
    }
    for(i= 0;i<  100;i++)
        printf("+++++++++++++++++++++++%d\n",i);
    sleep(5);
    exit(0);
}
