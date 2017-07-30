/*************************************************************************
	> File Name: errshow.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月25日 星期二 09时49分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
FILE* open_file(char *filename)
{
    FILE *stream ;
    stream=fopen(filename ,"rw+");
    if(!stream)
    {
        printf("can not open the %s :reason is :%s \n",filename ,strerror(errno));
        exit(-1);
    }
    else return stream ;
}
int main(void)
{
    char *filename="test";
    open_file(filename);
    return 0;

}
