/*************************************************************************
	> File Name: procread.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月04日 星期五 08时57分06秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>

#define FIFO_NAME "myfifo"
#define SIZE  1024
int myerror(const char *err_str ,int line )
{
    fprintf(stderr,"at line :%d ",line);
    perror(err_str );
    exit(-1);
}
int main(void)
{
    int fd ;
    char buf[SIZE];
    fd = open(FIFO_NAME,O_RDONLY) ;
    if(fd < 0)  myerror("open by O_RDONLY",__LINE__);
    read(fd ,buf,SIZE);
    printf("read from FIFO : %s\n",buf);
    close(fd);
    exit(-0);
}
