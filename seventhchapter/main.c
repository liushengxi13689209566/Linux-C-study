 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include<sys/types.h>
 #include<string.h>
 #include<fcntl.h>
 #include<sys/wait.h>
 #include<sys/stat.h>
 #include<dirent.h>
 
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
     int argcount = 0;
     char arglist[100][256];
     char buf[256+ 1];
     while(1)
     {
         printf("myshell$$ ");
         memset(buf,0,sizeof(buf));
         fgets(buf,256,stdin);
         for(i= 0; i< 100 ;i++)
             arglist[i][0]='\0';
         argcount = 0;
         explain_input(buf,&argcount,arglist);
         if(strcmp(arglist[0],"exit") == 0 || strcmp(arglist[0],"logout") == 0 )
             break;
         if(strcmp(arglist[0],"cd") == 0)
         {
             if(*arglist[1] == '-' || *arglist[1] == '~' || *arglist[1] == '\0')
                chdir("/home/liushengxi/");
             else 
             {
                 if(arglist[1][strlen(arglist[1])-1] != '/')
                      strcat(arglist[1] ,"/\0") ;
                 else   chdir("arglist[1]") ;
             }
             continue ;
         }
     }
     return 0;
 }
 
 
 void explain_input(char buf[],int *argcount,char arglist[100][256])  //没问题
 {
     int i,j= 0,k = 0;
     for(i= 0;i< strlen(buf)- 1 ;i++)   //i=strlen -2   "china\n\0"
     {
         if(buf[i] !=' ')
         {   if(i != strlen(buf)-2)
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
             if (arglist[j-1][0] == '\0')    j= j-1;
         }
     }
     *argcount= j + 1 ; //arglist 等价于argc,j 就是数组个数,老铁，为什么加一就是对的？？？？
 }

