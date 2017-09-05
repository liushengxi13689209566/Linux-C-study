/*************************************************************************
	> File Name: myhead.h
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月08日 星期二 08时24分02秒
 ************************************************************************/

#ifndef _MYHEAD_H //防止重复包含该头文件
#define _MYHEAD_H
#endif
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
void myerror(const char *str ,int line)
{
    perror(str);
    printf("at %d \n",line);
    exit(1);
}

