/*************************************************************************
	> File Name: ctrlpocess.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月03日 星期四 16时15分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
int main(int argc,char **argv )
{
    int n ;
    char buf[1204];
    while(1)
    {
        n= read(0,buf,1204);  //从标准输入设备中读取 字节 
        if(n > 0 )
        {
            buf[n]= '\0';
            printf("********************buf == %s\n",buf);
            if(strcmp(buf,"exit") == 0 )
            {
                printf("exit is running !!\n");
                sleep(1);
                exit(0);
            }
            if(strcmp(buf,"getpid") == 0)
            {
                printf("xiangdemei!! \n");
                sleep(1);
                exit(0);
            }
        }
    }
}
