/*********************************************mZ***************************
	> File Name: fcntl_access.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月13日 星期二 22时47分50秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void my_err(const char *err_string ,int line )
{
    fprintf(stderr,"line:%d " ,line) ; //fprintf()函数根据指定的格式(format)向输出流(stream)写入数据,把后面的写到前面
    perror(err_string) ; //先输出err_string ,再输出错误原因
    exit(1) ;
}

int main(void)
{
    int ret;
    int access_mode;
    int fd;
    if((fd =open("example_64.c",O_RDWR | O_CREAT |O_TRUNC ,S_IRWXU))== -1)  //O_RDWR 可读写 O_CREAT 创建 O_TRUNC 文件清空
        my_err("open",__LINE__) ;

    if((ret=fcntl(fd,F_SETFL,O_APPEND)) < 0 ) //fcntl 改变文件属性,F_SETFL  设置文件打开方式 O_APPEND  追加方式打开
       my_err("fcntl",__LINE__);

    if((ret=fcntl(fd,F_GETFL,0)) < 0 )  //获取文件打开方式
       my_err("fcntl",__LINE__);

    access_mode=ret &O_ACCMODE;

    if(access_mode==O_RDONLY)
        printf("read only\n");
    else if(access_mode==O_WRONLY)
        printf("write only\n");
    else if(access_mode==O_RDWR)
        printf("read + write !!\n");

    if(ret & O_APPEND){
        printf(" ,A");
    }
    if(ret & O_NONBLOCK){
        printf(" ,N");
    }
    if(ret & O_SYNC){
        printf(" ,S");
    }
    printf("\n");
    return 0;
}
