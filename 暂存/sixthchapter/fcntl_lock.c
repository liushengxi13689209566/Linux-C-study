/*************************************************************************
	> File Name: fcntl_lock.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月15日 星期四 15时38分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
void my_err(const char *err_string ,int line )
{
    fprintf(stderr,"line:%d " ,line) ; //fprintf()函数根据指定的格式(format)向输出流(stream)写入数据,把后面的写到前面
    perror(err_string) ; //先输出err_string ,再输出错误原因
    exit(1) ;
}
int lock_set(int fd ,struct flock *lock)
{
    if(fcntl(fd,F_SETLK,lock)== 0)//F_SETLK 读锁与写锁设置，无锁时，释放锁
    {
        if(lock->l_type == F_RDLCK)
            printf("R 锁 pid :%d\n",getpid());
        if(lock->l_type == F_WRLCK)
            printf("W 锁 pid :%d\n",getpid());
        if(lock->l_type == F_UNLCK)
            printf("释放 锁 pid :%d\n",getpid());
    }
    else 
    {
        perror("lock failed \n")   ;
        return  -1;
    }
    return 0;
}
int lock_test(int fd,struct flock *lock)
{
    if(fcntl(fd,F_GETLK,lock)== 0) //F_GETLK 能设置锁，则修改l_type为F_UNLCK
     {   if(lock->l_type==F_UNLCK)
            {
                printf("The lock can be set \n");
                return 0;
            }
         else if(lock->l_type==F_RDLCK)
                printf("can't be set ,is R 锁 pid :%d\n",lock->l_pid);
               else if(lock->l_type==F_WRLCK)
                printf("can't be set ,is R 锁 pid :%d\n",lock->l_pid);
                return -2;  
     }
    else 
    {
        perror("get locks failed \n");
        return -1;
    }
}
int main(void)
{
    int fd;
    int ret;
    struct flock lock;
    char read_buf[32];
    if((fd =open("example_65.c",O_RDWR | O_CREAT |O_TRUNC ,S_IRWXU))== -1)  //O_RDWR 可读写 O_CREAT 创建 O_TRUNC 文件清空
        my_err("open",__LINE__) ;
    if(write(fd,"test lock",10)!= 10)
        my_err("write",__LINE__);
    memset(&lock,0,sizeof(struct flock));
    lock.l_start= SEEK_SET ;//整个文件区域
    lock.l_whence= 0;
    lock.l_len= 0;
    lock.l_type=F_RDLCK;//读锁
    if(lock_test(fd,&lock)== 0)
    {
        lock.l_type=F_RDLCK;
        lock_set(fd,&lock);
    }
    lseek(fd,0,SEEK_SET);//移动文件指针到开头
    if((ret=read(fd,read_buf,10))< 0)//读出数据,ret==10
        my_err("read",__LINE__);
    read_buf[ret]='\0';//read_buf[10]='\0'
    printf("%s\n",read_buf);
    getchar();
    lock.l_type=F_WRLCK;//写锁
    if(lock_test(fd,&lock)== 0)
    {
        lock.l_type=F_WRLCK;
        lock_set(fd,&lock);
    }
    lock.l_type=F_UNLCK;
    lock_set(fd,&lock);
    close(fd);
    return 0;
}


