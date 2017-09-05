/*************************************************************************
	> File Name: test_select.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月07日 星期一 17时38分52秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
void display(const char *str)
{
    int second ;
    second = time((time_t *)NULL );
    printf("%s : %d \n",str,second);
}
int main(void)
{
    fd_set readfds ;
    struct timeval timeout ;
    int ret ;
    FD_ZERO(&readfds); //清空文件集
    FD_SET(0,&readfds); //加入文件集
    while(1)
    {
    timeout.tv_sec= 10;
    timeout.tv_usec= 0;
        display("****************************************before select ");
        ret = select(1,&readfds,NULL,NULL,&timeout); //1 加入一个文件
        display("------------------after select ");
        switch(ret)
        {
            case 0:
            printf("No data \n");
            exit(0);
            break;
            case -1:
            perror("select");
            exit(-1);
            break;
            default:
            getchar();
            printf("Data is accept now \n");
        }
    }
    return 0;
}

