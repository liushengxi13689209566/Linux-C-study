/*************************************************************************
	> File Name: my_create.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月06日 星期二 21时16分38秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
int main()
{
    int fd ;//文件描述符，其实就是文件指针
    //if((fd=open("example_62.c" ,O_CREAT | O_EXCL ,S_IRUSR | S_IWUSR )) == -1) { //O_CREAT:文件不存在时，创建。O_EXCL:检查文件是否存在，不存在时创建，存在时，打开文件出错。S_IWUSR和S_IRUSR 表示新建的文件的权限（用|或运算）
    if((fd=creat("example_62.c" , S_IWUSR ))== -1){
    perror("open") ;//先输出open ，再输出错误原因
//    printf("open: %s  with error :%d\n",strerror(errno),errno) ;  //error :错误号码。strerror ：将错误号码转换为错误信息
    exit(1) ;
    }
    else 
    {
        printf("creat file success !!\n") ;
    }
    printf("------------------------------%d\n",fd);
    close(fd) ;
    return 0;
}

