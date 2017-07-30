/*************************************************************************
	> File Name: 1-1获取文件属性.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月15日 星期四 22时09分42秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
int main(int argc ,char **argv)
{
    struct stat buf ;//struct stat 本身就有的结构体（保存文件状态信息）
    if(argc !=  2)
    {
        printf("You input is wrong \n");
        exit(0);
    }
    if(stat(argv[1],&buf)< 0)//获取文件属性，保存在buf 中
    {
        perror("stat :");
        exit(1);
    }
    printf("st_mode is : %o\n",buf.st_mode);

    if(S_ISREG(buf.st_mode))//POSIX 标准
        printf("-    ");
    else if(S_ISDIR(buf.st_mode))
        printf("d    ");

    if(buf.st_mode & S_IRUSR) //与对应的权限取与运算即可
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWUSR)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXUSR )
        printf("x");
    else printf("-");

    if(buf.st_mode & S_IRGRP)
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWGRP)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXGRP )
        printf("x");
    else printf("-");

    if(buf.st_mode & S_IROTH)
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWOTH)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXOTH)
        printf("x");
    else printf("-");
    printf("\n");



    printf("size is : %d\n",buf.st_size);
    return 0;


}  
