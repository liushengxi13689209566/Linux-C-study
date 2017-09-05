/*************************************************************************
	> File Name: test_address.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月07日 星期一 11时32分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(void)
{
    char buf[32];
    int ret= 0 ;
    unsigned int address = 0 ;
    struct in_addr in ;
    in.s_addr = 0 ;
    printf("Please input you ip address :");
    fgets(buf,32,stdin);
    ret =inet_aton(buf,&in);
    if(ret == 0)
        printf("invalid address !! \n");
    else printf("ip address is : 0x%x\n",in.s_addr);
    return 0;

}
