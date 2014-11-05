#include "test_epoll.h"
#include "common.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>

void TestEpoll::Test(int argc, char ** argv)
{
	printf("TestEpoll::Test!\n");

	if(argc<3)
	{
		printf("TestEpoll Invalid Args!\n");
		return;
	}
	if(0 == strcmp("client", argv[2]))
	{
		BeginClient(argc, argv);
	}
	else if(0 == strcmp("server", argv[2]))
	{
		BeginServer(argc, argv);
	}
	else
	{
		printf("TestEpoll Invalid Args!\n");
	}
}

void TestEpoll::BeginServer(int argc, char ** argv)
{
	printf("TestEpoll BeginServer\n");
	
	//参数检查
	if(argc<4)
	{
		perror("TestEpoll Server Argument Invalid\n");
		exit(1);
	}

	int port = atoi(argv[3]);
	
	//socket
	int svr_fd = 0;
	if(-1==(svr_fd =socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("Socket Error!\n");
		exit(1);
	}
	
	//bind
	sockaddr_in svr_addr;
	bzero(&svr_addr, sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	svr_addr.sin_port = htons(port);
	if(-1==(bind(svr_fd, (sockaddr*)&svr_addr, sizeof(svr_addr))))
	{
		perror("Bind Error!\n");
		exit(1);
	}

	//listen
	listen(svr_fd, LISTEN_ENQ);

	//do_epoll
	DoEpoll(svr_fd);
}

void TestEpoll::DoEpoll(int svr_fd)
{
	epoll_event events[EPOLL_EVENTS];
	int ret = 0;
	char buf[BUF_SIZE] = {0};
	int	ep_fd = epoll_create(FDSIZE);
	AddEvent(ep_fd, svr_fd, EPOLLIN);	
	while(1)
	{
		ret = epoll_wait(ep_fd, events, EPOLL_EVENTS, INFINITE);
		HandleEvents(ep_fd, events, ret, svr_fd, buf);
	}
	close(ep_fd);
}

void TestEpoll::HandleEvents(int ep_fd, epoll_event *events, int num, int svr_fd, char *buf)
{

}

void TestEpoll::AddEvent(int efd, int fd, int evt)
{
	epoll_event ep_evt;
	ep_evt.events = evt;
	ep_evt.data.fd = fd;
	epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ep_evt);
}

void TestEpoll::ModifyEvent(int efd, int fd, int evt)
{
	epoll_event ep_evt;
	ep_evt.events = evt;
	ep_evt.data.fd = fd;
	epoll_ctl(efd, EPOLL_CTL_MOD, fd, &ep_evt);
}

void TestEpoll::DeleteEvent(int efd, int fd, int evt)
{
	epoll_event ep_evt;
	ep_evt.events = evt;
	ep_evt.data.fd = fd;
	epoll_ctl(efd, EPOLL_CTL_DEL, fd, &ep_evt);
}

void TestEpoll::BeginClient(int argc, char ** argv)
{
	printf("TestEpoll BeginClient!\n");
}
