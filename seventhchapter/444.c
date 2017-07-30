/*************************************************************************
	> File Name: test.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月15日 星期六 19时03分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
int main(void)
{
    char buf[256];
    char arglist[100][256];
    int i,j= 0,k= 0;
    fgets(buf,255,stdin); //会把换行符读入
    for(i= 0;i< strlen(buf) ;i++) //i=strlen -  1 
    {
        if(buf[i] !=' ')
        {   if(i!=strlen(buf)-1)
                    arglist[j][k++ ]= buf[i];
            else
            {
                 arglist[j][k++]=buf[i];
                 arglist[j][k]='\0';
            } 
        }
        else if ( buf[i+ 1] != ' ') 
        {
            arglist[j++][k]='\0';
            k= 0;
        }
    }
    printf("-----------%d\n",j);
    printf("arglist[%d]==%s\n",j-1 ,arglist[j-1]);
    for(i= 0;i< j;i++)
        printf("%s\t",arglist[i]);
    
}
