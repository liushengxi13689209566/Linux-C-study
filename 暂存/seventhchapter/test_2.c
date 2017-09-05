#include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include<sys/types.h>
 #include<string.h>
 #include<fcntl.h>
 #include<sys/wait.h>
 #include<sys/stat.h>
 #include<dirent.h>
 #include<readline/readline.h>
 #include<readline/history.h>
 #include<signal.h>

 #define   normal 0
 #define   out_direct     1
 #define   int_redirect   2
 #define   pipe           3
 
 
 void explain_input(char buf[],int *argcount,char arglist[100][256]);
 void do_cmd(int argcount ,char arglist[100][256]);
 int find_cmd(char *cmd) ;
  
 int main(void)
 {
     int i ;
     int argcount = 0; //待执行命令的参数个数
     char arglist[100][256]; //存放命令

     struct stat temp ;//判断是否是目录或文件
     time_t now ;     
     char  *line ; 
     signal(SIGINT,SIG_IGN);
     char  str[520]; //存放输入的命令
     while(1)
     { 
         memset(str,0,sizeof(str));
         time(&now);
         strcpy(str ,"\e[1;31m ");
         strcat(str ,ctime(&now));
         strcat(str ,"\e[0m \e[1;32mMyshell $$ \e[0m\0 ");
         for(i= 0; i< 100 ;i++)
             arglist[i][0]='\0';
         argcount = 0;
         line=readline(str);
         if(*line)
             add_history(line);
         explain_input(line,&argcount,arglist);
         if(strcmp(arglist[0],"exit") == 0 || strcmp(arglist[0],"logout") == 0 )
             break;
         if(strcmp(arglist[0],"cd") == 0) //实现cd 命令
         {
             if(*arglist[1] == '-' || *arglist[1] == '~' || *arglist[1] == '\0')
                chdir("/home/liushengxi/");
             else 
             {
                 if(lstat(arglist[1],&temp) < 0)
                 {
                     printf("lstat error !!! \n");
                     continue ;
                 }
                if(S_ISREG(temp.st_mode))
                 {
                     printf("Sorry ,It's a file !!\n");
                     continue ;
                 }
                 else  if(arglist[1][strlen(arglist[1])-1] != '/')
                            strcat(arglist[1] ,"/\0") ;
                  chdir(arglist[1]) ;
             }
             continue ;
         }
         do_cmd(argcount,arglist); //处理命令
     }
     return 0;
 }



 void explain_input(char *line,int *argcount,char arglist[100][256])  //没问题
 {
     int i,j= 0,k = 0;
     for(i= 0;i< strlen(line)- 1 ;i++)   //i=strlen -2   "china\n\0"
     {
         if(line[i] !=' ')
         {   if(i != strlen(line)-2)
                     arglist[j][k++ ]= line[i];
             else
             {
                  arglist[j][k++]=line[i];
                  arglist[j][k]='\0';
             } 
         }
         else if ( line[i+ 1] != ' ') 
         {
             arglist[j++][k]='\0';
             k= 0;
             if (arglist[j-1][0] == '\0')    j= j-1;
         }
     }
     *argcount= j + 1 ; //arglist 等价于argc,j 就是数组个数,老铁，为什么加一就是对的？？？？
 }
 

