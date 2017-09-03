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
 
typedef struct {
    char pre[500];
    char now[500];
}WW ;
 void explain_input(char buf[],int *argcount,char arglist[100][256]);
 void do_cmd(int argcount ,char arglist[100][256]);
 int find_cmd(char *cmd) ;
int solve_cd(char arglist[100][256],WW *p);
  
 int main(void)
 {
     int i ;
     int argcount = 0; //待执行命令的参数个数
     char arglist[100][256]; //存放命令
     struct stat temp ;//判断是否是目录或文件
     time_t now ;     
     WW *p ;
     p=(WW *)malloc(sizeof(WW));
     memset(p->pre,0,sizeof(p->pre));
     memset(p->now,0,sizeof(p->now));
     int status_love ;
     char  *line  = NULL; 
     line = (char *) malloc(sizeof(char)*255);
     pid_t pid_love ;
     signal(SIGINT,SIG_IGN);
     char  str[520]; //存放输入的命令
     char dir[500] ;
     memset(dir,0,sizeof(dir));
     while(1)
     { 
         memset(str,0,sizeof(str));
         memset(line, 0, sizeof(line));
         time(&now);
         strcpy(str ,"\e[1;31m ");
         strcat(str ,ctime(&now));
         strcat(str ,"\e[0m \e[1;32mMyshell $$ \e[0m\0 ");
         memset(arglist, 0, sizeof(char)*100*256);
         argcount = 0;
         line=readline(str);
         if(*line)
             add_history(line);
         explain_input(line,&argcount,arglist);   //argcount 就是数组的 个数
         if(strlen(arglist[0]) == 0)      continue ;
         if((strcmp(arglist[0],"exit") == 0 || strcmp(arglist[0],"logout") == 0) && (strlen(arglist[1]) == 0 ))
             break;
         if(strcmp(arglist[0],"love") == 0)
         {
             pid_love=fork();
             switch(pid_love)
             {
                 case -1:   printf("fork pid_love  ERROR !!!\n") ;return 0;
                 case 0 :   execvp("//home/liushengxi/linux&&C/seventhchapter/love",NULL); exit(0);
                 default :if(waitpid(pid_love ,&status_love,0)< 0)
                         {
                            printf("waitpid is  ERROR !!!\n");
                            return  0;
                         }
                         break;
             }
             continue;
         }
         if(solve_cd(arglist,p) == 0)
             continue;
         do_cmd(argcount,arglist); //处理命令
     }
     return 0;
 }
int solve_cd(char arglist[100][256],WW *p)
{ 
    struct stat temp;
    if(strcmp(arglist[0],"cd") == 0) //实现cd 命令
    {
             if(*arglist[1] == '-')
             {
                 if(strlen(p->pre) == 0)
                 {
                     printf("OLDPWD 未设定\n");
                     return 0;
                 }
                 else { chdir(p->pre);   strcpy(p->pre,p->now); getcwd(p->now, 500);  return 0 ;}
             }
             if( *arglist[1] == '~' || *arglist[1] == '\0')
              {   getcwd(p->pre, 500) ;   chdir("/home/liushengxi/"); getcwd(p->now,500); return 0;}
             else 
             {
                 if(lstat(arglist[1],&temp) < 0)
                 {
                     printf("lstat error !!! \n");
                     return 0 ;
                 }
                if(S_ISREG(temp.st_mode))
                 {
                     printf("Sorry ,It's a file !!\n");
                     return  0 ;
                 }
                 else {  //目录
                         if(arglist[1][strlen(arglist[1])-1] != '/')
                               strcat(arglist[1] ,"/\0") ; //判断目录
                        getcwd(p->pre,500);
                        chdir(arglist[1]) ;
                        getcwd(p->now,500);
                    }
                return 0;
            }
    }
}
 void explain_input(char *line,int *argcount,char arglist[100][256])  //没问题
 {
     int i,j= 0,k = 0;
     int temp=strlen(line) ;
     for(i= 0;i<  temp ;i++)   //i=strlen -2   "china\n\0"
     {
         if(line[i] !=' ')
         {   if(i !=  (temp - 1))
                     arglist[j][k++ ]= line[i];
             else
             {
                  arglist[j][k++]=line[i];
                  arglist[j][k]='\0';
             } 
         }
         else if ( (line[i+ 1] != ' ') && (line[i+ 1] != 0) )
         {
             arglist[j++][k]='\0';
             k= 0;
             if (arglist[j-1][0] == '\0')    j= j-1;
         }
     }
     *argcount= j + 1 ;
     arglist[*argcount][0]= '\0';
 }
  
 
 void do_cmd(int argcount ,char arglist[100][256])
 {
     int flag= 0;   //判断命令的正确性
     int how= 0 ;   //命令格式
     int background = 0;//判断后台运行
     int i,j,next= 0;
     int fd, status ;
     char *arg[argcount+ 8]; //指针数组
     char *file ;
     pid_t pid ;
     int temp ;
     for(i= 0;i< argcount ;i++)
     {
         arg[i] =(char *)arglist[i];
     }
     arg[argcount]=NULL ;
     for(i= 0;arg[i] ;i++)//遍历指针数组
     {
         if((*arg[i] ==  '&') && (arg[i + 1] != NULL))    //ls & -l 
         {
             printf("Wrong command !!\n");
             exit(-1);
         }
         else if((*arg[i] == '&') && (arg[i + 1] == NULL ) )
         {
             background= 1;
             arg[i]=NULL;
             break;
         }
     } 
     for(i= 0;arg[i] ;i++)
     {
         if((*arg[i] == '>') && (arg[i + 1] == NULL))
         {
             printf("Wrong command !!\n");
             return  ;
         }
         else if((*arg[i]== '>') && (arg[i + 1] != NULL ) )
         {
             how=out_direct ;
             flag++ ;
             break;
         }
     }
 
     for(i= 0;arg[i] ;i++)
     {
         if((*arg[i] == '<') && (arg[i + 1] == NULL))
         {
             printf("Wrong command !!\n");
             exit(-1);
         }
         else if((*arg[i]== '<') && (arg[i + 1] != NULL ) )
         {
             how= int_redirect;
             flag++ ;
             break;
         }
     }
     for(i= 0;arg[i] ;i++)
     {
         if((*arg[i] == '|') &&  (arg[i + 1] == NULL))
         {
             printf("Wrong command !!\n");
             exit(-1);
         }
         else if((*arg[i]== '|') && (arg[i + 1] != NULL ) )
         {
             how=pipe ;
             break;
         }
     }
    int a[100]={0};  //处理管道参数
    int t= 0;
    int pid2,fd2 ;
    int k= 1;
    for(i= 0;arg[i] ;i++)
    {
        if(*arg[i] == '|')
        {
            arg[i]=NULL ;
            a[k++]= i+ 1;
        }
    }
    if(flag > 1)
    {
        printf("Wrong command !! \n");
        exit(-1);
    }
     switch(how)
     {
         case out_direct:for(i= 0 ;arg[i];i++) //> 
                         {
                             if(*arg[i] == '>')
                             {
                                 file=arg[i+ 1];
                                 arg[i]=NULL ;
                             }
                         }
                         break;
         case int_redirect:for(i= 0 ;arg[i];i++)
                         {
                             if(*arg[i] == '<')
                             {
                                 file=arg[i+ 1];
                                 arg[i]=NULL ;
                             }
                         }
                         break;
     }
     pid=fork();
     if(pid < 0)
     {
         printf("creat process failed !! \n");
         exit(-1);
     }
     switch(how)
     {
         case 0:if(pid == 0)   //第一次fork    ls 
                {
                    if(!(find_cmd(arg[0])))
                    {
                        printf("the cmd is not find !!\n");
                        exit(-1);
                    }
                    if(( strcmp(arg[0],"ls") == 0) || (strcmp(arg[0],"grep") == 0 ) ||( strcmp(arg[0],"egrep")== 0))
                    {
                        for(i = 0;arg[i] ;i++)    ;
                                 arg[i]= "--color=auto";
                                 arg[i + 1]=NULL ;
                    }
                    execvp(arg[0],&arg[0]) ;  // arg 传参
                    exit(0);   //退出子进程
                }
               break;
         case 1:if(pid == 0)  // ls > 111 
                {
                    if(!(find_cmd(arg[0])))
                    {
                        printf("the cmd is not find !!\n");
                        exit(-1);
                    }
                  fd=open(file,O_RDWR |O_CREAT |O_TRUNC,0644);  //创建file 文件
                  dup2(fd ,1);// 1   标准输出
                  execvp(arg[0],arg) ;
                  exit(0); //退出子进程
                }
               break;
         case 2:if(pid == 0) //ls  < 
                {
                    if(!(find_cmd(arg[0])))
                    {
                        printf("the cmd is not find !!\n");
                        exit(-1);
                    }
                   fd=open(file,O_RDONLY) ;
                   dup2(fd ,0); //标准输入 0
                   execvp(arg[0],arg) ;
                   exit(0); //退出子进程
                }
               break;
         case 3:
            if(pid == 0)  //子进程
            {
                for(i=  0 ;i< k ;i++)
                {
                    if(pid2=fork()< 0)  {printf("fork is failed !! \n") ;return ; }
                    if(pid2== 0)
                    {
                        if(!(find_cmd(arg[a[t]])))
                        {
                            printf("The cmd is noy find !! \n");
                            exit(0);
                        }
                        printf("child i=%d\n",i);
                        exit(0);
                        if(i == 0)
                        {
                            printf("**********%s\n",arg[a[t]]);
                            fd2=open("/tmp/just_a_test",O_RDWR |O_CREAT |O_TRUNC,0644);
                            dup2(fd2,1);
                            execvp(arg[a[t]],arg);
                            exit(0);
                        }
                        else 
                        {
                            fd2=open("/tmp/just_a_test",O_RDWR);
                            dup2(fd2,0); //标准输入 0
                            execvp(arg[a[t]],&arg[a[t]]) ;
                            dup2(fd2,1); //标准输出   1
                            exit(0);
                        }
                        t++ ;
                    }
                    else    //pid2> 0
                    {
                        fd2=open("/tmp/just",O_RDWR);
                        dup2(fd2,1);
                        printf("par i=%d\n",i);
                        if(waitpid(pid2 ,&status, 0) < 0 ) //子进程等待子子进程的执行
                        {
                            printf("waitpid is failed !! \n");
                            exit(-1);
                        }
                        close(fd2);
                    }
                }
            }
            break;
           default :break;
     }
     if(background == 1)
         return ;
     if(waitpid(pid ,&status, 0) == -1 )
     {
         printf("waitpid is failed !! \n");
         exit(-1);
     }
 }


 int find_cmd(char *cmd)   //没问题 
 {
     DIR *dir ;
    int i= 0 ;
    struct dirent *dirp ;
    char *path[]={"/bin","/usr/bin",NULL};
    while(path[i])
    {
        if((dir=opendir(path[i])) == NULL)
        {
            printf("opendir is failed !! \n");
            exit(-1);
        }
        while((dirp=readdir(dir)) ) 
        {
            if(strcmp(dirp->d_name,cmd) == 0)
            {
                closedir(dir);
                return 1;
             }
         }
         closedir(dir);
         i++ ;
     }
     return 0;
 }
