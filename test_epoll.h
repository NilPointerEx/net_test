#include <sys/epoll.h>

class TestEpoll
{
public:
	static void Test(int argc, char ** argv);

private:
	static const int BUF_SIZE = 1024;
	static const int LISTEN_ENQ = 5;
	static const int INFINITE = -1;
	static const int EPOLL_EVENTS = 1000;
	static const int FDSIZE = 100;

	static void BeginClient(int argc, char ** argv);
	static void BeginServer(int argc, char ** argv);
	
	static void DoEpoll(int svr_fd);
	static void HandleEvents(int ep_fd, epoll_event *events, int num, int svr_fd, char *buf);

	static void DoAccept();
	static void DoRead();
	static void DoWrite();
	static void AddEvent(int efd, int fd, int evt);
	static void ModifyEvent(int efd, int fd, int evt);
	static void DeleteEvent(int efd, int fd, int evt);
};
