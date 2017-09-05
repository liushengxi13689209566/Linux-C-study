/*************************************************************************
	> File Name: procwrite.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月04日 星期五 08时36分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    char buf[SIZE]= "liushengxizuishuai!!";
    umask(0);
    if(mkfifo(FIFO_NAME,S_IFIFO | 0666)    < 0)  //创建管道文件
         myerror("mkfifo",__LINE__);
    fd = open (FIFO_NAME,O_WRONLY );
    if(fd < 0)    myerror("open by O_WRONLY ",__LINE__);
    write(fd ,buf ,strlen(buf)+ 1);
    close(fd);
    exit(0);

}
