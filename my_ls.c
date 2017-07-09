
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<dirent.h>
#include<grp.h>
#include<errno.h>
#include<pwd.h>
#include<string.h>

#define PARAM_NONE 0
#define PARAM_A    1
#define PARAM_L    2
#define MAXROWLEN    80


void my_err(const char *err_string ,int line )
{
    fprintf(stderr,"line:%d " ,line) ; 
    perror(err_string) ; 
    exit(1) ;
}

void display_attribute(struct stat buf,char *name)
{
    char buf_time[32];
    struct passwd *psd;
    struct group *grp;

    if(S_ISREG(buf.st_mode))
        printf("-");
    else if(S_ISDIR(buf.st_mode))
        printf("d");

    if(buf.st_mode & S_IRUSR) //与对应的权限取与运算即可
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWUSR)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXUSR )
        printf("x");
    else printf("-");

    if(buf.st_mode & S_IRGRP)
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWGRP)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXGRP )
        printf("x");
    else printf("-");

    if(buf.st_mode & S_IROTH)
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWOTH)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXOTH)
        printf("x");
    else printf("-");
    printf(".   ");
    
    printf("%4d",buf.st_nlink);

    psd=getpwuid(buf.st_uid);
    grp=getgrgid(buf.st_gid);
    printf("%-8s",psd->pw_name);
    printf("%-8s",grp->gr_name);

    printf("%6d",buf.st_size);

    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time)- 1]='\0';
    printf(" %s",buf_time);
}

void display(int flag_param,char *pathname)///home/liushengxi/test.c   /home/liushengxi/.vimrc
{
    int i,j;
    struct stat buf;
    char name[NAME_MAX + 1];//最长文件名 name 
    for(i= 0,j= 0;i<strlen(pathname);i++)
    {
        if(pathname[i]=='/')
        {
            j= 0;
            continue;
        }
        name[j++]=pathname[i];
    }
    name[j]='\0';

    if(lstat(pathname,&buf) < 0)  //buf 存储文件
        my_err("lstat",__LINE__);
    switch(flag_param)
    {
        case PARAM_NONE:
            if(name[0] != '.')
                printf("%s\n",name);//打印单个文件
            break;
        case PARAM_A:printf("%s\n",name);
                     break;
        case PARAM_L:
                     if(name[0] != '.')
                     {
                         display_attribute(buf,name); //另一个函数
                         printf("%-8s\n",name);
                     }
                     break;
        case PARAM_A+PARAM_L:
                     display_attribute(buf,name);
                     printf("%-8s\n",name);
                     break;
        default:break;
    }
}

void display_dir(int  flag_param,char *path) //path 目录名
{
    DIR *dir;
    struct  dirent  *ptr;
    int count= 0;
    char filename[256][PATH_MAX+ 1],temp[PATH_MAX + 1];
    dir=opendir(path);
    if(dir == NULL)
        my_err("opendir",__LINE__);

    while((ptr=readdir(dir)) != NULL)//目录下的文件名ptr->d_name 
        count++;

    closedir(dir);

    if(count > 256)
        my_err("too many files in the dir ",__LINE__);

    int i,j,len=strlen(path); //路径
    dir=opendir(path);
    for(i= 0;i<count;i++) //一个文件一个文件的打开
    {
        ptr=readdir(dir);
        if(ptr == NULL )
        {
            my_err("readdir",__LINE__);
        }
        strncpy(filename[i],path,len);//把目录名考到filename中
        filename[i][len]='\0';

        strcat(filename[i],ptr->d_name);//把文件名考到filename中

        filename[i][len+strlen(ptr->d_name)]='\0';
    }
    for(i= 0;i< count- 1;i++)
    {
        for(j= 0;j< count -1 -i ;j++)
        {
            if(strcmp(filename[j],filename[j + 1]) > 0 )//
            {
                strcpy(temp,filename[j+ 1]);
                strcpy(filename[j + 1],filename[j]);
                strcpy(filename[j],temp);
            }
        }
    }
    for(i= 0;i< count; i++)
        display(flag_param,filename[i]);
    closedir(dir);
   
}

// ls 
// ls  -a 
// ls  -l
// ls -al 
// ls -l /home
// ls -a /home/
//ls 文件
//ls -l 文件名

int main(int argc,char **argv)  
{
    int i,j,k,num;
    char path[PATH_MAX+ 1];//路径
    int param[32];//保存命令行参数
    struct stat buf;//文件信息 
    int flag_param=PARAM_NONE;//参数种类
    j= 0;
    num = 0;
    for(i= 1;i<argc;i++) //ls -a -l rgbobn      argc==4;num == 3
    {
        if(argv[i][0] == '-')
        {
            for(k= 1;k <strlen(argv[i]);k++,j++)
                param[j]=argv[i][k];
        }
        num++;
    }

    for(i=  0;i< j;i++)
    {
        if(param[i] == 'a')
        {
            flag_param |= PARAM_A;
            continue;
        }
        else if(param[i]== 'l')
        {
            flag_param |= PARAM_L;
            continue;
        }
        else 
        {
            printf("sorry !! now we agree -al\n");
            exit(1);
        }
    }
    param[j]='\0';
    
    if((num + 1) != argc) //只输入a.out ,即 ls  
    {
        strcpy(path,"./");
        path[2]='\0';
        display_dir(flag_param,path);//parh== './' 
        return 0;
    }
    i= 1;
    do
    {
        if(argv[i][0] == '-')
        {
            i++;
            continue;
        }
        else 
        {
            strcpy(path,argv[i]);
            if(stat(path,&buf)< 0)
                my_err("stat",__LINE__);
            

            if(S_ISDIR(buf.st_mode))// argv[i] 是一个目录
            {
                printf("ISDIR\n");
                if(path[strlen(argv[i])- 1] != '/')
                {
                    path[strlen(argv[i])] ='/';
                    path[strlen(argv[i]+ 1)] ='\0';
                }
                else  path[strlen(argv[i])] ='\0';

                display_dir(flag_param,path);//flag_param ==  0
                i++ ;
            }
            else //arhv[i]是一个文件
            {
                display(flag_param,path);
                i++ ;
            }
        }
    }while(i< argc);
    return 0;
}

