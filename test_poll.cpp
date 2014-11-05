#include "test_poll.h"
#include "common.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void TestPoll::Test(int argc, char ** argv)
{
	printf("TestPoll::Test!\n");

	if(argc<3)
	{
		printf("TestPoll Invalid Args!\n");
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
		printf("TestPoll Invalid Args!\n");
	}
}

void TestPoll::BeginServer(int argc, char ** argv)
{
	printf("TestPoll BeginServer\n");

	//参数检查
	if(argc<4)
	{
		perror("TestPoll Server Argument Invalid\n");
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

	//do_poll
	pollfd client_fds[OPEN_MAX];
	int client_fd;
	int i = 0;
	int maxi = 0;
	int nready = 0;
	int nread = 0;
	char buf[BUF_SIZE];

	sockaddr_in client_addr;
	socklen_t clientaddr_len;
	//Initialize client_fds
	client_fds[0].fd = svr_fd;
	client_fds[0].events = POLLIN;
	for(i=1;i<OPEN_MAX;++i)
	{
		client_fds[i].fd = -1;
	}
	
	while(1)
	{
		nready = poll(client_fds, maxi+1, INFINITE);

		if(-1==nready)
		{
			perror("Poll Error!\n");
			exit(1);
		}

		if(client_fds[0].revents & POLLIN)
		{
			//New Connection
			clientaddr_len = sizeof(sockaddr_in);
			if(-1 == (client_fd = accept(svr_fd, (sockaddr*)&client_addr, &clientaddr_len)))
			{
				if(EINTR==errno)
				{
					continue;
				}
				else
				{
					perror("Accept Error!\n");
					exit(1);
				}
			}
			printf("New Connection with :	%s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

			//Add to list
			for(i=1;i<OPEN_MAX;++i)
			{
				if(-1 == client_fds[i].fd)
				{
					client_fds[i].fd = client_fd;
					client_fds[i].events = POLLIN;
					break;
				}
			}
			
			if(OPEN_MAX==i)
			{
				perror("Too Many Connections!\n");
				exit(1);
			}

			maxi = MAX(maxi, i);

			if(--nready<=0)
			{
				continue;
			}

		}

		//hancle read events
		for(i=1;i<=maxi;++i)
		{
			if(client_fds[i].fd>0 && client_fds[i].revents&POLLIN)
			{
				nread = read(client_fds[i].fd, buf, BUF_SIZE);
				if(nread<=0)
				{
					close(client_fds[i].fd);
					client_fds[i].fd = -1;
					printf("Client Disconnected!\n");
					continue;
				}
				buf[nread] = '\0';
				printf("Receive Message : %s\n", buf);

				write(client_fds[i].fd, buf, nread);
			}
		}
	}
}

void TestPoll::BeginClient(int argc, char ** argv)
{
	printf("TestPoll BeginClient!\n");

	//参数检查
	if(argc<5)
	{
		perror("TestPoll Client Argument Invalid\n");
		exit(1);
	}
	in_addr svr_addr_in;
	inet_pton(AF_INET, argv[3], &svr_addr_in);
	int port = atoi(argv[4]);

	//socket
	int client_fd;
	if(-1==(client_fd=socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("Socket Error!\n");
		exit(1);
	}

	//connect
	sockaddr_in svr_addr;
	bzero(&svr_addr, sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr = svr_addr_in;
	svr_addr.sin_port = htons(port);
	if(-1 == connect(client_fd, (sockaddr*)&svr_addr, sizeof(svr_addr)))
	{
		perror("Connect Fail!\n");
		exit(1);
	}

	//do_poll
	pollfd client_fds[2];
	client_fds[0].fd = client_fd;
	client_fds[0].events = POLLIN;
	client_fds[1].fd = STDIN_FILENO;
	client_fds[1].events = POLLIN;
	int nfd = 2;
	int nready;
	int nread;
	char buf[BUF_SIZE] = {0};
	
	while(1)
	{
		nready = poll(client_fds, nfd, INFINITE);
		if(-1==nready)
		{
			perror("Poll Error!\n");
			exit(1);
		}

		if(client_fds[0].revents & POLLIN)
		{
			nread = read(client_fds[0].fd, buf, BUF_SIZE);
			if(nread<=0)
			{
				printf("Server Disconnected!\n");
				close(client_fds[0].fd);
				client_fds[0].fd = -1;
				continue;
			}

			write(STDIN_FILENO, buf, nread);
		}

		if(client_fds[1].revents & POLLIN)
		{
			nread = read(client_fds[1].fd, buf, BUF_SIZE);
			if(nread<=0)
			{
				client_fds[1].fd = -1;
				continue;
			}
			write(client_fd, buf, nread);
		}
	}
}
