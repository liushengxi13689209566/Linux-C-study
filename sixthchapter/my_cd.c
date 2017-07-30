/*************************************************************************
	> File Name: my_cd.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月18日 星期日 15时50分36秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<linux/limits.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
void my_err(const char *err_string ,int line )
{
    fprintf(stderr,"line:%d " ,line) ; //fprintf()函数根据指定的格式(format)向输出流(stream)写入数据,把后面的写到前面
    perror(err_string) ; //先输出err_string ,再输出错误原因
    exit(1) ;
}
int main(int argc,char **argv)
{
    char buf[PATH_MAX + 1];
    int fd ;
    if(argc < 2)
    {
        printf("You input is wrong !!\n");
        exit(1);
    }
    if(chdir(argv[1]) < 0)
        my_err("chdir",__LINE__);
    if(getcwd(buf ,512) < 0)
        my_err("getcwd",__LINE__);
    printf("%s\n",buf);
    if((fd=open("temp",O_CREAT | O_RDWR ,S_IRUSR  | S_IWUSR))< 0)//temp file 
    {
        my_err("open",__LINE__);
    }
    return 0;
}

