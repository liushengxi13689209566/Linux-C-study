/*************************************************************************
	> File Name: my_rwl.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月07日 星期三 22时11分29秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
/* 妈的，反正就是注意各种的括号就是了，如：fd=open,write 函数等。。。。巨坑*/
void my_err(const char *err_string ,int line )
{
    fprintf(stderr,"line:%d " ,line) ; //fprintf()函数根据指定的格式(format)向输出流(stream)写入数据,把后面的写到前面
    perror(err_string) ;//先输出err_string ,再输出错误原因
    exit(1) ;
}
int  my_read(int fd) //读数据函数
{
    int len ;
    int ret ;
    int i ;
    char read_buf[64] ;
    if((lseek( fd , 0 ,SEEK_END))== -1) //移动文件指针到结尾
        my_err("lseek",__LINE__) ; //__LINE__  预编译器内置宏，表示行数
    if((len=lseek(fd,0,SEEK_CUR)) ==  -1 ) //求相对于文件开头的偏移量，用于表明文件开始处到文件当前位置的字节数 len
        my_err("lseek",__LINE__) ; 
    if((lseek(fd,0,SEEK_SET)) ==  -1 ) //移动文件指针到开头 
        my_err("lseek",__LINE__) ; 
    printf(" 字节数是 ： %d \n",len) ;
    if((ret = read(fd,read_buf,len)) < 0) //成功时返回实际读到的字节数，失败返回 -1
        my_err("read",__LINE__ ) ;
    for(i= 0 ;i< len ;i++)
        printf("%c",read_buf[i]) ;
    printf("\n") ;
    return  ret ;
}
int main(void)
{
    int fd ;
    char write_buf[32]="Hello Word !!" ;
    if((fd=creat("example_63.c",S_IRWXU))==  -1) //S_IRWXU                     可读，可写，可执行creat函数的返回值就是如果成功返回一个只写的文件描述符，主意“只写”的，失败返回-1；
   //if((fd =open("example_63.c",O_RDWR | O_CREAT |O_TRUNC ,S_IRWXU))== -1) //O_RDWR 可读写 O_CREAT 创建 O_TRUNC 文件清空
        my_err("open",__LINE__) ;
    else{
        printf("Creat file success !!\n") ;
    }
    if(write(fd,write_buf,strlen(write_buf)) != strlen(write_buf) ) //写入文件，write 的返回值是实际写入的字节数
        my_err("write",__LINE__) ;
    my_read(fd) ; //读出数据
    printf("/*--------------------------------------------*/\n") ;
    if(lseek(fd,10,SEEK_END)== -1) //从文件结尾处向后移动10位
    my_err("lseek",__LINE__) ; //_LINE_  预编译器内置宏，表示行数
    if(write(fd,write_buf,strlen(write_buf)) != strlen(write_buf) ) //写入文件，write 的返回值是实际写入的字节数
        my_err("write",__LINE__) ;
    my_read(fd) ;
    close(fd) ; //关闭文件
    return  0;
}
