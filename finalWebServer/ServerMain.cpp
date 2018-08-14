#include "http_conn.h"
using namespace std;
int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        cout << "usage : " << basename(argv[0]) << "   ip_address    port_number   " << endl;
        return 1;
    }
    const char *ip = argv[1];
    const int port = atoi(argv[2]);
    try
    {
        WebServer my(ip, port);
    }
    catch (const char *&str)
    {
        printf("错误号码 errrno == %d \n" ,errno);
        perror(str); //  str + 错误信息 
    }
    catch (...)
    {
        cout << " 其他错误！！！" << endl;
    }
    return 0;
}
