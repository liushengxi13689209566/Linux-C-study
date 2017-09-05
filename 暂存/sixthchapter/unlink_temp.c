/*************************************************************************
	> File Name: unlink_temp.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月17日 星期六 22时35分50秒
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
    int fd;
    char buf[32];
    if((fd=open("temp",O_CREAT | O_RDWR ,S_IRUSR  | S_IWUSR))< 0)//temp file 
    {
        my_err("open",__LINE__);
    }
    if(unlink("temp")< 0)
    {
        my_err("unlink",__LINE__);
    }
    printf("file unlinked !!\n");
    if(write(fd,"liushengxi",11)< 0)
        my_err("write",__LINE__);
    if(lseek(fd,0,SEEK_SET) < 0)
        my_err("lseek",__LINE__);
    if(read(fd,buf,11) < 0 )
        my_err("read",__LINE__);
    return 0;
}

