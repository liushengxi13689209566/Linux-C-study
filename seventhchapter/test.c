/*************************************************************************
	> File Name: test.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月15日 星期六 19时03分22秒
 ************************************************************************/
#include<stdio.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
int main()
{
    char *line;
    char arglist[100][256];
    int i,j= 0,k= 0 ;
    int temp ;
    char *str="liushengxi$$";
//    fgets(buf,255,stdin);  //会把换行符读入
    line=readline(str);
    if(*line)
       add_history(line);
    printf("*****************************line == %s\n",line);
    temp=strlen(line);
    for(i= 0;i< temp ;i++)   //i=strlen -2   "china\n\0"
    {
        if(line[i] !=' ')
        {   if(i != (temp - 1))
                    arglist[j][k++ ]= line[i];
            else
            {
                 arglist[j][k++]=line[i];
                 arglist[j][k]='\0';
            } 
        }
        else if ( line[i+ 1] != ' '&&line[i+ 1] != 0 ) 
        {
            arglist[j++][k]='\0';
            k= 0;
            if (arglist[j-1][0] == '\0') j = j-1;
        }
    }
          j++ ;
    printf("-------------------------j==%d \n",j);
    for(i= 0;i<j;i++)
        printf("arglist[%d]== %s\n",i,arglist[i]);
  ``
}
