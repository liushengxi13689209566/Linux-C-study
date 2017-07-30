/*************************************************************************
	> File Name: daemn.c
	> Author: 
	> Mail: 
	> Created Time: 2017年06月26日 星期一 11时57分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>
#include<syslog.h>
#include<unistd.h>
#include<sys/param.h>
#include<signal.h>
int init_daemon(void)
{
    int pid;
    int i;

    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);

    pid=fork() ;
    if(pid > 0)
        exit(0);
    else if(pid < 0)
        return -1;

    setsid();
 
/*申请一个控制终端只能是一个进程组组长，那么可以让它fork后自己再退出，子进程做剩下的事。
    所以执行过你所说的这些步骤后，
    下一步还应该调用一次fork()，父进程退出，
    子进程关闭继承于父进程打开的文件，
    修改自己的工作目录，
    然后正式成为一个daemon进程。*/
    if(pid > 0)
        exit(0);
    else if(pid < 0)
        return -1;
    for(i= 0;i< NOFILE ;close(i++));
    chdir("/");
    umask(0);
    signal(SIGCHLD,SIG_IGN);
    return 0;
}
int main(void)
{
    time_t now ;
    init_daemon();
    return 0;
}
