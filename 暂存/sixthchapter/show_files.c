/*************************************************************************
	> File Name: show_files.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月18日 星期日 16时15分25秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int my_readir(const char *path)
{
    DIR *dir;
    struct dirent *ptr;
    if(   (dir=opendir(path))  == NULL  )
    {
        perror("opendir");
        return -1;
    }
    while( ( ptr=readdir(dir) )  != NULL )
        printf("%s\n",ptr->d_name);
    closedir(dir);
    return 0;
}
int main(int argc ,char **argv)
{
    if(argc < 2)
    {
        printf("you input is wrong !!\n");
        exit(1);
    }
    if(my_readir(argv[1])  < 0)
    exit(1);
    return 0;
}
