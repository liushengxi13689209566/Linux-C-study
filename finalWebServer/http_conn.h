/*************************************************************************
	> File Name: http_conn.h
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年08月09日 星期四 08时16分37秒
 ************************************************************************/

#ifndef _HTTP_CONN_H
#define _HTTP_CONN_H
#include <iostream>
#include <sys/wait.h>
#include <fstream>
#include <vector>
#include <string>
#include <libgen.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/sendfile.h>
#include <error.h>
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <sys/stat.h>
#include "ThreadPool.h"
const int BUFFER_SIZE = 4096;
const int CHAR_MAX_SIZE = 1024;
const char PATH_404[512] = "/home/Shengxi-Liu/TestWeb/finalWebServer/HTML/404.html" ;
const std::string PATH_501 = "/home/Shengxi-Liu/TestWeb/finalWebServer/HTML/501.html";
const std::string PATH_666 = "/home/Shengxi-Liu/TestWeb/finalWebServer/HTML/666.html";
const std::string ROOT_PATH = "/home/Shengxi-Liu/TestWeb/finalWebServer";
const std::string PATH_404_PNG = "/home/Shengxi-Liu/TestWeb/finalWebServer/Picture/404.png";
const std::string PATH_ICO = "/home/Shengxi-Liu/TestWeb/finalWebServer/Picture/666.ico";
const int MAX_EVENT_NUMBER = 1024;
const int LISTENQ = 1024;
class WebServer
{
  public:
	WebServer(const char *ip, const int port);
	~WebServer();

  private:
	int listenfd;
	int epollfd;

	static void addfd(int epollfd, int fd, bool oneshot);
	static int setnonblocking(int fd);


	int start(const char *ip, const int port);
	static int worker(int fd, int epollfd); //线程函数
	static int close_conn(int fd, int epollfd);
	static int reponse_GET(std::string filename, const int fd);
	static int not_found(const int fd);
	static int make_headers(const int statue, const int fd, std::string filename);
	static int send_file(const int fd, const char* filename);



























	static int reponse_POST(std::string filename, std::string dat, const int fd);
	static int reponse_noKnow(const int fd);

	static std::string Analysis_POST(std::string recv_buffer);
};
#endif
