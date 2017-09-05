/*************************************************************************
	> File Name: reader.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月06日 星期日 16时54分51秒
 ************************************************************************/
#include"shareman.h"
int main(void)
{
    int semid ,shmid ;
    char *shmaddr ;
    char write_size[SHM_SIZE ];
    shmsid =create_shm("."."m",SHM_SIZE); // .代表当前目录，m 就是109 
    if(shmid < 0)  myerror("create_shm ",__LINE__);
    shmaddr = shmat(shmid,NULL ,0 ) ; //使用共享内存前，必须将其附加到进程的地址空间， 0 代表默认
    if(shmaddr == (char *)-1) myerror("shmat",__LINE__);
    semid=create_sem(".",'s',1,1);  //打开信号集
    if(semid < 0)   myerro("open_sem",__LINE__);
    while(1)
    {
        wait_sem(semid ,0); //等待信号为一
        sem_p(semid,0);
        printf("writer :");
        fgets(write_size,1024,stdin);
        int len = strlen(write_size)
        printf("%s\n",shmaddr);
        sleep(10);
        sem_v(semid ,0);
        slepp(10);
    }
}
