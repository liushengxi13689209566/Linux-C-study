/*************************************************************************
	> File Name: shareman.h
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月06日 星期日 16时00分01秒
 ************************************************************************/

#ifndef _SHAREMAN_H
#define _SHAREMAN_H
#endif
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
#include<sys/shm.h>
#define SHM_SIZE 1024
union semun{
    int val ;
    struct semid_ds *buf;
    unsigned short *array;
};
int myerror(const char *err_str ,int line )
{
    fprintf(stderr,"at line :%d ",line);
    perror(err_str );
    exit(-1);
}
int create_sem(const char *pathname,int pro_id,int members ,int init_val)//创建信号量
{
    key_t msgkey ;
    int i ,sid ;
    union semun semopts ;  //信号集控制共用体
    msgkey=ftok(pathname,pro_id); //根据两个参数生成唯一的键值
    if(msgkey < 0)  myerror("ftok",__LINE__);
    if(segmget(msgkey ,members,IPC_CREATE | 0666) < 0) myerror("segmget",__LINE__) ;//members 所创建的信号集包含的信号个数
    semopts.val=init_val;
    for(i = 0;i< members ;i++)
    {
        semctl(sid,i ,SETVAL ,semopts);  //sid 为信号集标示符，i 标示特定信号 ， SETVAL 设置某个信号的值为val ,也就是init_val
    }
    return sid ;
}
int open_sem(const char *pathname ,int pro_id)
{
    key_t msgkey ;
    int sid  ;
    msgkey=ftok(pathname,pro_id); //根据两个参数生成唯一的键值
    if(msgkey < 0)  myerror("ftok",__LINE__);
    sid = segmget(msgkey ,0 ,IPC_CREATE | 0666)   // 0 表示只打开信号集
    if(sid < 0)          myerror("segmget",__LINE__) ;
    return sid ;
}
int sem_p(int semid ,int i) //semid 信号集标示符 
{
    struct sembuf buf =  {0 ,-1,IPC_NOWAIT}; //信号操作 
    if(i < 0)   myerror("p 操作",__LINE__);
    buf.sem_num = i ; //确定哪一个信号
    if(semop(semid,&buf ,1) < 0)  myerror("semop",__LINE__); //1 代表操作一个信号
    return 0;
}
int sem_v(int semid ,int i) //semid 信号集标示符 
{
    struct sembuf buf =  {0 ,+ 1,IPC_NOWAIT}; //信号操作 
    if(i < 0)   myerror("p 操作",__LINE__);
    buf.sem_num = i ; //确定哪一个信号
    if(semop(semid,&buf ,1) < 0)  myerror("semop",__LINE__); //1 代表操作一个信号
    return 0;
}
int sem_delete(int semid)
{
    return (semctl(semid,0,.IPC_RMID)) ; //IPC_RMID  将信号集从内存中删除
}
int wait_sem(int semid ,int i) //等待信号为1
{
    while(semctl(semid ,i ,GETVAL ,1000) == 0) // GETVAL 返回信号集中 i 的值，第三个参数无用
    {
        sleep(1);
    }
    return 1;
}
int create_shm(char *pathname ,int pro_id,size_t size)
{
    key_t shmkey ;
    int sid ;
    shmkey= ftok(pathname ,pro_id);
    if(shmkey <  0)   myerror("shmkey ",__LINE__ );
    sid= shmget(shmkey ,size ,IPC_CREATE | 0666);// 创建size 大小的共享内存区
    if(sid < 0)    myerror("shmget",__LINE__);
    return sid ;//返回共享内存区的标示符
}



