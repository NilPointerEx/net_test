#include "test_epoll.h"
#include <sys/socket.h>
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
	
	//Argument Checking
	if(argc<4)
	{
		perror("TestEpoll Server Argument Invalid\n");
		exit(1);
	}
	int port = atoi(argv[3]);

	//Begin Epoll 
	int svr_fd = SocketBind(IP_SERVER, port);
    listen(svr_fd, LISTEN_ENQ);
	DoEpoll(svr_fd);
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

int TestEpoll::SocketBind(const char *ip, int port)
{
	int svr_fd = 0;
	sockaddr_in svr_addr;

	if(-1==(svr_fd =socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("Socket Error!\n");
		exit(1);
	}
	SetNonBlocking(svr_fd);
	bzero(&svr_addr, sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &(svr_addr.sin_addr));
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
	int nfd = 0;
	char buf[BUF_SIZE] = {0};
	int	ep_fd = epoll_create(MAX_EVENTS);
	AddEvent(ep_fd, svr_fd, EPOLLIN | EPOLLET);	
    while(1) {
        nfd = epoll_wait(ep_fd, events, MAX_EVENTS, INFINITE);
		HandleEvents(ep_fd, events, nfd, svr_fd, buf);
    }
	close(ep_fd);
}

void TestEpoll::HandleEvents(int ep_fd, epoll_event *events, int nfd, int svr_fd, char *buf)
{
	int i;
	int fd;

	if(nfd<0)
	{
		perror("epoll_wait Error!\n");
		exit(1);
	}

	for(i=0;i<nfd;++i)
	{
		fd = events[i].data.fd;
		if((fd==svr_fd) && (events[i].events & EPOLLIN))
		{
			DoAccept(ep_fd, fd);
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
	sockaddr_in conn_addr;
	//************Rememver to assign sizeof(sockaddr_in) to addrlen, or you will get wrong conn_addr from accept function*************************//
	socklen_t addrlen = sizeof(sockaddr_in);	
	int conn_fd;
	
	while((conn_fd = accept(fd, (sockaddr*)&conn_addr, &addrlen))>0)
	{
		SetNonBlocking(conn_fd);
		printf("New Connection with : %s:%d \n", inet_ntoa(conn_addr.sin_addr), ntohs(conn_addr.sin_port));
		AddEvent(ep_fd, conn_fd, EPOLLIN | EPOLLET);
	}
	if(-1==conn_fd)
	{
		if(errno!=EAGAIN && errno!=ECONNABORTED && errno!=EPROTO && errno!=EINTR)
		{
			perror("Accept Error!\n");
		}
	}
}

void TestEpoll::DoRead(int ep_fd, int fd, char *buf)
{
	int nread = 0;
	int n = 0;
	
	while((nread = read(fd, buf+n, BUF_SIZE-1-n))>0)
	{
		n += nread;	
	}

	if(n>0)
	{
		buf[n] = '\0';
		printf("Receive Message : %s\n", buf);
	}

	if(0==nread)
	{
		printf("Client Disconneted!\n");
		close(fd);
		DeleteEvent(ep_fd, fd, EPOLLIN);
	}
	else if(nread<0 && errno!=EAGAIN)
	{
		perror("Read Error!\n");
		close(fd);
		DeleteEvent(ep_fd, fd, EPOLLIN);
	}
	else
	{
		ModifyEvent(ep_fd, fd, EPOLLOUT | EPOLLET);
	}
}

void TestEpoll::DoWrite(int ep_fd, int fd, char *buf)
{
	int nwrite;
	int nsize = strlen(buf);
	int n = 0;

	while(n<nsize)
	{
		nwrite = write(fd, buf+n, nsize-n);
		
		if(nwrite>0)
		{
			n += nwrite;
			if(n==nsize)
			{
				ModifyEvent(ep_fd, fd, EPOLLIN);
			}
		}
		else if(0==nwrite)
		{
			printf("Client Disconneted!\n");
			close(fd);
			DeleteEvent(ep_fd, fd, EPOLLOUT);
			break;
		}
		else if(nwrite<0)
		{
			if(errno!=EAGAIN)
			{
				perror("Write Error!\n");
				close(fd);
				DeleteEvent(ep_fd, fd, EPOLLOUT);
			}
			break;
		}
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












