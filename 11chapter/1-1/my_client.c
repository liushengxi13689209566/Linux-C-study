/*************************************************************************
	> File Name: my_client.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月08日 星期二 10时52分46秒
 ************************************************************************/

#include"myhead.h"
#define N 0
#define Y 1
void input_buf(int conn_fd,const char *string)
{
    char input_buf[1287] ;
    char recv_buf[128] ;
    int flag ;
    do
    {
        printf("%s :",string);
        fgets(input_buf,128,stdin); //从键盘读入用户名和密码
        input_buf[strlen(input_buf)] = '\0';
        if(send(conn_fd,input_buf,strlen(input_buf),0) < 0)  myerror("client send ",__LINE__);
        if(recv(conn_fd,recv_buf,sizeof(recv_buf),0) < 0)  myerror("user recv",__LINE__);
        if(recv_buf[0] == '1') flag = 1 ;
        else  {printf("sorry ,you is  wrong !! try again @@ \n") ; flag= 0 ;}
    }while(flag ==  0); //条件为假退出
}
int main(void)
{
    int   i ;
    int ret ;
    int conn_fd ;
    struct sockaddr_in  serve_addr ;
    char recv_buf[128];
    char send_buf[128] ; //发送数据
    memset(&serve_addr,0,sizeof(struct sockaddr_in)) ;
    serve_addr.sin_family =AF_INET ; //TCP 
    serve_addr.sin_port = htons(5288) ; //TCP 
    serve_addr.sin_addr.s_addr= inet_addr("127.0.0.1") ; //直接设置为本地IP
    conn_fd = socket(AF_INET,SOCK_STREAM ,0 );
    if(conn_fd < 0)  myerror("client socket ",__LINE__);

    if(connect(conn_fd,(struct sockaddr *)&serve_addr,sizeof(struct sockaddr))   < 0)
        myerror("client connect ",__LINE__);

    input_buf(conn_fd,"username");
    input_buf(conn_fd,"passwd");

    ret =recv(conn_fd,recv_buf,sizeof(recv_buf),0 ); //没有接受到数据就一直等待
    if(ret < 0)   myerror("recv",__LINE__);
    recv_buf[ret]='\0';
    printf("%s\n",recv_buf); //welcome to my server !!
    while(1)
    {
        memset(send_buf,0,sizeof(send_buf));
        printf("你想聊点什么呐？？： ");
        scanf("%s",send_buf);
        memset(recv_buf,0,sizeof(recv_buf));
        send(conn_fd,send_buf,sizeof(send_buf),0);
        recv(conn_fd,recv_buf,sizeof(recv_buf),0);
        printf("the recv is %s \n",recv_buf);
    }
    close(conn_fd);
    return 0 ;
}
