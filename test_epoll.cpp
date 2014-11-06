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
#include <fcntl.h>

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

	sockaddr_in svr_addr;
	int port = atoi(argv[3]);
	
	//socket
	int svr_fd = 0;
	if(-1==(svr_fd =socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("Socket Error!\n");
		exit(1);
	}
	SetNonBlocking(svr_fd);
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

int TestEpoll::SocketBind(const char *ip, int port)
{
	int svr_fd = 0;
	sockaddr_in svr_addr;

	if(-1==(svr_fd =socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("Socket Error!\n");
		exit(1);
	}
	//SetNonBlocking(svr_fd);
	bzero(&svr_addr, sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	//inet_pton(AF_INET, ip, &(svr_addr.sin_addr));
	svr_addr.sin_addr.s_addr = htons(INADDR_ANY);
	svr_addr.sin_port = htons(port);
	if(-1==(bind(svr_fd, (sockaddr*)&svr_addr, sizeof(svr_addr))))
	{
		perror("Bind Error!\n");
		exit(1);
	}
	return svr_fd;
}

void TestEpoll::DoEpoll(int svr_fd)
{
	epoll_event events[MAX_EVENTS];
	int ret = 0;
	char buf[BUF_SIZE] = {0};
	int	ep_fd = epoll_create(MAX_EVENTS);
	AddEvent(ep_fd, svr_fd, EPOLLIN);	
	while(1)
	{
		ret = epoll_wait(ep_fd, events, MAX_EVENTS, INFINITE);
		HandleEvents(ep_fd, events, ret, svr_fd, buf);
	}
	close(ep_fd);
}

void TestEpoll::HandleEvents(int ep_fd, epoll_event *events, int num, int svr_fd, char *buf)
{
	int i;
	int fd;

	if(num<0)
	{
		perror("epoll_wait Error!\n");
		exit(1);
	}

	for(i=0;i<num;++i)
	{
		fd = events[i].data.fd;
		if((fd==svr_fd) && (events[i].events & EPOLLIN))
		{
			sockaddr_in cliaddr;
			socklen_t cliaddrlen;	
			int client_fd;

			while((client_fd = accept(fd, (sockaddr*)&cliaddr, &cliaddrlen))>0)
			{
				SetNonBlocking(client_fd);
				printf("New Connection with : %s:%d \n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
				AddEvent(ep_fd, client_fd, EPOLLIN);
			}
			if(-1==client_fd)
			{
				perror("Accept Error!\n");
			}
		}
		else if(events[i].events & EPOLLIN)
		{
			DoRead(ep_fd, fd, buf);
		}
		else if(events[i].events & EPOLLOUT)
		{
			DoWrite(ep_fd, fd, buf);
		}
		else
		{
			perror("Unhandled Event!\n");
		}
	}
}

void TestEpoll::DoAccept(int ep_fd, int fd)
{
			sockaddr_in cliaddr;
			socklen_t cliaddrlen;	
			int client_fd;

			while((client_fd = accept(fd, (sockaddr*)&cliaddr, &cliaddrlen))>0)
			{
				SetNonBlocking(client_fd);
				printf("New Connection with : %s:%d \n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
				AddEvent(ep_fd, client_fd, EPOLLIN);
			}
			if(-1==client_fd)
			{
				perror("Accept Error!\n");
			}
}

void TestEpoll::DoRead(int ep_fd, int fd, char *buf)
{
	int nread;
	nread = read(fd, buf, BUF_SIZE);
	if(nread<0)
	{
		perror("Read Error!\n");
		close(fd);
		DeleteEvent(ep_fd, fd, EPOLLIN);
	}
	else if(0==nread)
	{
		printf("Client Disconneted!\n");
		close(fd);
		DeleteEvent(ep_fd, fd, EPOLLIN);
	}
	else
	{
		buf[nread] = '\0';
		printf("Receive Message : %s\n", buf);
		ModifyEvent(ep_fd, fd, EPOLLOUT);
	}
}

void TestEpoll::DoWrite(int ep_fd, int fd, char *buf)
{
	int nwrite;
	nwrite = write(fd, buf, strlen(buf));
	if(nwrite<0)
	{
		perror("Write Error!\n");
		close(fd);
		DeleteEvent(ep_fd, fd, EPOLLOUT);
	}
	else
	{
		ModifyEvent(ep_fd, fd, EPOLLIN);
	}
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

void TestEpoll::SetNonBlocking(int fd)
{
	int opts;
	opts = fcntl(fd, F_GETFL);
	if(opts<0)
	{
		perror("F_GETFL Error!\n");
		exit(1);
	}
	opts = opts | O_NONBLOCK;
	if(fcntl(fd, F_SETFL, opts)<0)
	{
		perror("F_SETFL Error!\n");
		exit(1);
	}
}












