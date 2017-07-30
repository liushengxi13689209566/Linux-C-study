/*************************************************************************
	> File Name: my_chmod.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月06日 星期二 20时57分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char **argv)
{
    int mode ;
    int mode_u ;
    int mode_g ;
    int mode_o ;
    char *path ;
    if(argc < 3)
    {
        printf("Your input is wrong !!\n"); //判断输入参数的个数
        exit(0) ;
    }
    mode= atoi(argv[1]) ;//参数一定是当作字符处理的
    if(mode > 777 || mode < 0)
    {
        printf("Your input is wrong !!\n") ;
        exit(0) ;
    }
    mode_u = mode /100 ;
    mode_g = mode /10 % 10 ;
    mode_o = mode %10 ;
    mode = mode_u*8*8 + mode_g*8 +mode_o ;//转换为八进制
    path = argv[2] ;
    if( chmod(path,mode)== -1) //调用chmod 这个函数
    {
        printf("chmod error !!\n") ;
        exit (0) ;
    }
    return 0;

}
