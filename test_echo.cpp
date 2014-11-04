#include "test_echo.h"
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

void TestEcho::Test(int argc, char ** argv)
{
	printf("TestEcho::Test!\n");

	if(argc<3)
	{
		printf("TestEcho Invalid Args!\n");
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
		printf("TestEcho Invalid Args!\n");
	}
}

void TestEcho::BeginServer(int argc, char ** argv)
{
	printf("TestEcho BeginServer\n");

	int svr_fd = -1;
	sockaddr_in svr_addr;
	int port = 0;

	if(argc<4)
	{
		printf("TestEcho Server Invalid Args!\n");
		exit(1);
	}

	port = atoi(argv[3]);

	if(-1 ==(svr_fd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("Socket Error!\n");
		exit(1);
	}

	bzero(&svr_addr, sizeof(svr_addr));
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	svr_addr.sin_port = htons(port);

	if(-1 == bind(svr_fd, (sockaddr*)&svr_addr, sizeof(sockaddr)))
	{
		perror("Bind Error!\n");
		exit(1);
	}

	if(-1 == listen(svr_fd, LISTEN_ENQ))
	{
		perror("Listen Error!\n");
		exit(1);
	}

	int i = 0;
	int client_fd;
	sockaddr_in client_addr;
	int client_fds[FD_SETSIZE];
	fd_set rset, allset;
	int maxfd = 0;
	int maxi = -1;
	int nready = 0;
	char buf[BUF_SIZE] = {0};

	//Initialize
	for(i=0;i<FD_SETSIZE;++i)
	{
		client_fds[i] = -1;
	}
	FD_ZERO(&allset);
	FD_SET(svr_fd, &allset);
	maxfd = svr_fd;

	socklen_t cliaddrlen;
	while(1)
	{
		printf("=========================================================================\n");
		rset = allset;
		nready = select(maxfd+1, &rset, nullptr, nullptr, nullptr);

		if(nready<0)	
		{
			perror("Select Error!\n");
			exit(1);
		}

		if(FD_ISSET(svr_fd, &rset))
		{
			cliaddrlen = sizeof(client_addr);
			if(-1 == (client_fd = accept(svr_fd, (sockaddr*)&client_addr, &cliaddrlen)))
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

			printf("New Connection with : %s:%d \n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

			for(i=0;i<FD_SETSIZE;++i)
			{
				if(-1 == client_fds[i])
				{
					client_fds[i] = client_fd;
					break;
				}
			}
			if(FD_SETSIZE == i)
			{
				perror("Too Many Connections!\n");
				exit(1);
			}
			FD_SET(client_fd, &allset);
			maxfd = MAX(maxfd, client_fd); 
			maxi = MAX(maxi, i);
			if(--nready <= 0)
			{
				continue;

			}
		}

		int nread = 0;
		bzero(&buf, BUF_SIZE); 
		for(i=0;i<=maxi;++i)	
		{
			if(client_fds[i]>0 && FD_ISSET(client_fds[i], &rset))
			{
				nread = read(client_fds[i], buf, BUF_SIZE);
				if(nread<=0)
				{
					printf("Client Disconnectd!\n");
					close(client_fds[i]);
					FD_CLR(client_fds[i], &allset);
					client_fds[i] = -1;
					continue;
				}
				printf("Read Message : %s\n", buf);
				write(client_fds[i], buf, nread);
			}
		}
	}
}

void TestEcho::BeginClient(int argc, char ** argv)
{
	printf("TestEcho BeginClient\n");
}
