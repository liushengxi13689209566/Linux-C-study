#include "ThreadPool.h"
#include "http_conn.h"
using namespace std;
WebServer::WebServer(const char *ip, const int port)
{
	start(ip, port);
}
WebServer::~WebServer()
{
	close(listenfd);
	close(epollfd);
}
int WebServer::setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}
void WebServer::addfd(int epollfd, int fd, bool oneshot)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
	if (oneshot)
	{
		event.events |= EPOLLONESHOT;
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}
int WebServer::start(const char *ip, const int port)
{
	signal(SIGPIPE, SIG_IGN); // 忽略 SIGPIPE 信号

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
		throw "WebServer socket fun error ";
	int optval = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (int *)&optval, sizeof(int));

	struct sockaddr_in ServerAddress;
	bzero(&ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &ServerAddress.sin_addr);
	ServerAddress.sin_port = htons(port);

	int ret = bind(listenfd, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
	if (ret < 0)
		throw "WebServer bind fun error ";
	ret = listen(listenfd, LISTENQ); //1024
	if (ret < 0)
		throw "WebServer listen fun error ";

	epoll_event events[MAX_EVENT_NUMBER];
	epollfd = epoll_create(LISTENQ); //LISTENQ = 1024
	if (epollfd < 0)
		throw "WebServer epoll_create fun error ";

	addfd(epollfd, listenfd, false);

	ThreadPool pool(40); //核数的两倍

	while (true)
	{
		int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		/*当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数返回时，该系统调用可能会返回一个EINTR错误*/
		if ((number < 0) && (errno != EINTR))
		{
			throw "epoll failure ";
		}
		for (int i = 0; i < number; i++)
		{
			int socketfd = events[i].data.fd;
			if (socketfd == listenfd)
			{
				struct sockaddr_in client_address;
				socklen_t client_length = sizeof(client_address);
				int conn_fd = accept(listenfd, (struct sockaddr *)&client_address, &client_length);
				if (conn_fd < 0)
				{
					cout << "errno == " << errno << endl;
					continue; //重启 accept
				}
				addfd(epollfd, conn_fd, true);
			}
			else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
			{
				/*如果有异常，直接关闭客户端连接*/
				close_conn(socketfd, epollfd);
			}
			else if (events[i].events & EPOLLIN)
			{
				/*同一个进程下 ，线程共享epollfd,conn_fd */
				auto result = pool.commit(WebServer::worker, socketfd, epollfd);
				cout << " 线程返回值是 ：" << result.get() << endl;
			}
			else
				throw "Epoll other error ";
		}
	}
	return 0;
}
int WebServer::close_conn(int fd, int epollfd)
{
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
	close(fd);
}
int WebServer::worker(int fd, int epollfd)
{
	char recv_buffer[BUFFER_SIZE] = {0};
	while (true)
	{
		bzero(recv_buffer, BUFFER_SIZE);
		int size = recv(fd, recv_buffer, BUFFER_SIZE - 1, 0);
		/*因为是非阻塞套接字，所以没有数据可以读取时，返回EAGAIN。
		由于信号的缘故，返回-1,并将errno设置为EINTR，recv函数可以重启，所以我们重启它即可*/
		if (size < 0)
		{
			/*if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				//reset_oneshot(fd, epollfd);
				cout << "一个线程读取完毕，关闭套接字" << endl;
				break;
			}*/
			break;
		}
		else if (size == 0)
		{
			cout << "   client have been closed !!!! " << endl;
			break;
		}
		else
		{
			recv_buffer[size] = 0;
			string temp_buffer = recv_buffer;
			stringstream ss{temp_buffer};
			string method, filename;
			ss >> method >> filename;
			if (method == "GET")
			{
				reponse_GET(filename, fd);
				break;
			}
			else if (method == "POST")
			{
				/*目前先忽略*/
				break;
			}
			else
			{
				//response_noKnow(fd);
				break;
			}
		}
	}
	close(fd);
	return 0; //成功返回 0
}
int WebServer::reponse_GET(string filename, const int fd)
{
	string file = ROOT_PATH;
	if (filename == "/")
		file += "/index.html";
	else
		file += filename;

	if (filename.find("404.png") != string::npos)
		file = PATH_404_PNG;
	if (filename.find("666.ico") != string::npos)
		file = PATH_ICO;

	auto realFile = file.c_str();

	struct stat filestat;
	int ret = stat(realFile, &filestat);
	if (ret < 0 || S_ISDIR(filestat.st_mode)) // not dir
	{
		cout << "not found " << endl;
		not_found(fd);
		return 0;
	}
	//只要从这里下来，所请求的文件就一定会存在
	make_headers(200, fd, file);
	send_file(fd, realFile);
	return 0;
}
/*发送404.html 页面 */
int WebServer::not_found(const int fd)
{
	make_headers(404, fd, ".html");
	send_file(fd, PATH_404);
	return 0;
}
int WebServer::make_headers(const int statue, const int fd, string filename)
{
	char buf[CHAR_MAX_SIZE] = {0};
	bzero(buf, sizeof(buf));
	/* 先发送 http 状 态 行 */
	sprintf(buf, "HTTP/1.1  %d  OK\r\n", statue);
	int ret = send(fd, buf, strlen(buf), 0);
	if (ret < 0){
		close(fd);
		return 0;
		throw " send header error ";
	}
	if (filename.find(".html") != string::npos)
		sprintf(buf, "Content-Type: text/html\r\n;charset=utf-8\r\n\r\n");
	if (filename.find(".jpg") != string::npos)
		sprintf(buf, "Content-Type: image/jpg\r\n;charset=utf-8\r\n\r\n");
	if (filename.find(".png") != string::npos)
		sprintf(buf, "Content-Type: image/png\r\n;charset=utf-8\r\n\r\n");
	if (filename.find(".ico") != string::npos)
		sprintf(buf, "Content-Type: image/x-icon\r\n;charset=utf-8\r\n\r\n");
	if (filename.find(".mp3") != string::npos)
		sprintf(buf, "Content-Type: audio/mp3\r\n;charset=utf-8\r\n\r\n");
	if (filename.find(".mp4") != string::npos)
		sprintf(buf, "Content-Type: video/mpeg4\r\n;charset=utf-8\r\n\r\n");

	ret = send(fd, buf, strlen(buf), 0);
	if (ret < 0){
		close(fd);
		return 0;
		throw " send  header error ";
	}
	return 0;
}
/*简单的向客户端发送已经验证过且存在的文件*/
int WebServer::send_file(const int fd, const char *realFile)
{
	int filefd = open(realFile, O_RDONLY);
	if (filefd < 0)
		throw " open error  ";
	struct stat filestat;
	int ret = stat(realFile, &filestat);
	if (ret < 0)
		throw " stat error ";

	cout << "file's size == " <<  filestat.st_size << endl;

	int sum = 0;
	while (sum < filestat.st_size)
	{
		off_t t = sum;
		int n = sendfile(fd, filefd, &t, filestat.st_size);
		cout << " n == " << n << endl;
		cout << " errno == " << errno << endl ;
		perror("sendfile");
		if (n < 0)
		{
			//Connection reset by peer[连接被对端重置]
			// if ( errno == EAGAIN || errno == EINTR ) //EINTR即errno为4,
			// {
			// 	continue ;
			// }
			// else
			// {
				close(fd);
				close(filefd);
				return 0;
				break;
			//}
		}
		else
		{
			sum += n;
		}
	}
	close(filefd);

	return 0;
}