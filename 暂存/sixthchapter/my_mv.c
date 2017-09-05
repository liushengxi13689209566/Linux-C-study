/*************************************************************************
	> File Name: my_mv.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月16日 星期五 18时05分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main(int argc ,char **argv)
{
    if(argc < 3)
    {
        printf("input is wrong !! Like :mv oldpath newpath\n");
        exit(1);
    }
    if(rename(argv[1],argv[2]) <  0 )
    {
        printf("%s, %s\n", argv[1], argv[2]);
        perror("rename : ");
        exit(1);
    }
    return 0;
}
