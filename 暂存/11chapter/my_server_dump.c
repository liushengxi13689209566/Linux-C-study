/*************************************************************************
	> File Name: my_server.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月08日 星期二 08时49分52秒
 ************************************************************************/
#include"myhead.h"
#define SERV_PORT 5240
#define LISTENQ  12
#define USERNAME  0
#define PASSWD    1
typedef struct userinfo{
    char username[52] ;
    char passwd[52];
}user ;
user users[4]={
    {"linux","linux"},
    {"lili","1234"},
    {"lala","1234"},
    {"papa","papapa"},
}; //全局结构体数组
void setnonblocking(int sock)    //设置非阻塞属性
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}
int  find(const char *name)
{
    int i ;
    if(name == NULL)
    {
        printf("in find ,no name\n");
        return -2;
    }
    for(i= 0;i< 4;i++ )
    {
        if( !strcmp(users[i].username,name) )  return i ; //返回下标，到时候直接利用下标找密码
    }
    return -1;
}
void send_data(int conn_fd ,const char *string)
{
    if(send(conn_fd,string,strlen(string),0) < 0)
       myerror("send",__LINE__);
}
int main(void)
{
    int sock_fd ,conn_fd, epfd ,nfds ;
    int flag_recv = USERNAME ;
    int ret ;
    int name_num ;
    pid_t pid  ;
    int flag = 0 ;
    char recv_buf[128]; //接受数据
    char send_buf[128]; //发送数据
    struct sockaddr_in cli_addr ,serve_addr ;
    int cli_len ;

    sock_fd = socket(AF_INET,SOCK_STREAM ,0); //创建套接字
    if(sock_fd < 0) myerror("socket",__LINE__);

  //  setnonblocking(sock_fd);   //设置为非阻塞方式

    memset(&serve_addr,0,sizeof(struct sockaddr_in)) ;
    serve_addr.sin_family =AF_INET ; //TCP 
    serve_addr.sin_port = htons(SERV_PORT) ; //TCP 
    serve_addr.sin_addr.s_addr= htonl(INADDR_ANY) ; //直接设置为本地IP
    if(bind(sock_fd,(struct sockaddr *)&serve_addr,sizeof(struct sockaddr_in)) <   0 )//绑定套接字
    myerror("bind ",__LINE__);
    if(listen(sock_fd,LISTENQ) < 0) //转换为监听套接字
    myerror("listen",__LINE__);
    cli_len =sizeof(struct sockaddr_in);
    while(1)
    {
           struct epoll_event ev ,events[20];
           epfd= epoll_create(256); //
           conn_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&cli_len); //阻塞等待下一个数据
           if(conn_fd < 0)  myerror("accept",__LINE__);
           printf("accept a new information from %s \n",inet_ntoa(cli_addr.sin_addr)); //这一句成功！！
           pid= fork();
           if(pid < 0)
               myerror("fork",__LINE__);
           if(pid ==  0 )
           { 
               while(flag ==  0) //flag == 0 时表示未登录成功，需要登录及验证
               {
                   ret = recv(conn_fd,recv_buf,sizeof(recv_buf),0);  //没有接受到数据就一直阻塞
                   if(ret < 0)   myerror("recv",__LINE__);
                   recv_buf[ret-1] ='\0'; //将接受到的换行符转换为'\0'
                   if(flag_recv == USERNAME )
                   {
                       name_num = find(recv_buf);
                       switch(name_num)
                       {
                           case -1:send_data(conn_fd,"0"); break;
                           default:send_data(conn_fd,"1");flag_recv=PASSWD ; break ;
                       }
                   }
                   else if(flag_recv  ==  PASSWD )
                   {
                       if(  !strcmp(users[name_num].passwd,recv_buf)    )
                       {
                           send_data(conn_fd,"1");
                           printf("%s login  \n",users[name_num].username);
                           send_data(conn_fd,"welcome to my server !!! @ liushengxi,It;'s we talk ~~~'\n");
                           ev.data.fd=conn_fd; //把ev 中保存的fd 放入事件表中
                           epoll_ctl(epfd,EPOLL_CTL_ADD,conn_fd,&ev);
                           flag =  1 ;  //跳出while循环时，一定是登录成功了
                       }
                       else send_data(conn_fd,"0");
                   }
               }
               int i ;
               while(1)
               {
                   nfds= epoll_wait(epfd,events,20,500);
                   for(i =  0 ; i <  nfds  ; i++ )
                   {
                       if(events[i].events&EPOLLIN)
                       {
                           memset(recv_buf,0,sizeof(recv_buf));
                           recv(conn_fd,recv_buf,sizeof(recv_buf),0);
                           printf("------------------------%s\n",recv_buf);
                           if(strcmp(recv_buf,"exit") == 0) { printf("left\n");   break;   }
                           send_data(conn_fd,recv_buf);
                       }
                   }
               }
               close(sock_fd);
               close(conn_fd);
               exit(0); //子进程结束
           }
           else close(conn_fd); //进程间的数据是copy 型的
    }
    return 0;
}
