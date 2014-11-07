#include <sys/epoll.h>

#define BUF_SIZE 1024
#define LISTEN_ENQ 5
#define INFINITE -1
#define MAX_EVENTS 1000
#define IP_SERVER "0.0.0.0"

class TestEpoll
{
public:
	static void Test(int argc, char ** argv);
	static void BeginClient(int argc, char ** argv);
	static void BeginServer(int argc, char ** argv);

private:
	static int SocketBind(const char *ip, int port);
	static void DoEpoll(int svr_fd);
	
	//epoll used
	static void HandleEvents(int ep_fd, epoll_event *events, int num, int svr_fd, char *buf);
	static void DoAccept(int ep_fd, int fd);
	static void DoRead(int ep_fd, int fd, char *buf);
	static void DoWrite(int ep_fd, int fd, char *buf);
	static void AddEvent(int efd, int fd, int evt);
	static void ModifyEvent(int efd, int fd, int evt);
	static void DeleteEvent(int efd, int fd, int evt);
	//socket util
	static void  SetNonBlocking(int fd);
};
