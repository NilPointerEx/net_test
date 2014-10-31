#include "test_tcp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

void TestTcp::Test(int argc, char ** argv)
{
	printf("TestTcp::Test!\n");
	//if(argc<3)
	//{
	//	printf("TestTcp Invalid Args!\n");
	//	return;
	//}
	//if(0 == strcmp("client", argv[2]))
	//{
	//	BeginClien(argc, argv);
	//}
	//else if(0 == strcmp("server", argv[2]))
	//{
	//	BeginServer(argc, argv);
	//}
	//else
	//{
	//	printf("TestTcp Invalid Args!\n");
	//}
}

void TestTcp::BeginClien(int argc, char ** argv)
{
	printf("TestTcp::BeginClien!\n");
	int skfd = 0;
	sockaddr_in server_addr;
	in_addr addr;
	int port = 0;
	char buf[BUF_SIZE] = {0};

	if(-1 == (skfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		printf("Socket Error!\n");
		return;
	}

	if(argc<5)
	{
		printf("TestTcp CLient Invalid Args!\n");
		return;
	}

	
	inet_aton(argv[3], &addr);
	port = atoi(argv[4]);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr = addr;
	
	if(-1 == (connect(skfd, (sockaddr*)&server_addr, sizeof(sockaddr))))
	{
		printf("Connect Error!\n");
		return;
	}

	while(1)
	{
		int addrlen = 0;
		printf("Input Send Message :");
		gets(buf);
		printf("\nSendMessage : %s\n", buf);
	}
}

void TestTcp::BeginServer(int argc, char ** argv)
{
	printf("TestTcp::BeginServer!\n");

	//int server_fd = 0;
	//int client_fd = 0;
	//sockaddr_in server_addr;
	//int port = 0;
	//char buf[BUF_SIZE] = {0};

	//if(argc<4)
	//{
	//	printf("TestTcp Server Invalid Args!\n");
	//	return;
	//}

	//port = atoi(argv[3]);

	//if(-1 == (server_fd = socket(AF_INET, SOCK_STREAM, 0)))
	//{
	//	printf("Socket Error!\n");
	//	return;
	//}
	//
	//bzero(&server_addr, sizeof(sockaddr_in));
	//server_addr.sin_family = AF_INET;
	//server_addr.sin_port = htons(port);
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

	//if(-1 == (bind(server_fd, (sockaddr*)&server_addr, sizeof(sockaddr))))
	//{
	//	printf("Bind Error\n");
	//}

	//if(-1 == listen(server_fd, 4))
	//{
	//	printf("Listen Error\n");
	//}

	//while(1)
	//{
	//	printf("Waiting for client....");
	//	if(-1 == (client_fd = accept(server_fd, nullptr, nullptr)))
	//	{
	//		perror("Accept Error");
	//		exit(1);
	//	}

	//	if(-1 == (read(client_fd, buf, BUF_SIZE)))
	//	{
	//		perror("Read Error!");
	//	}
	//	printf("Message Received : %s \n", buf);

	//	close(client_fd);
	//}
}


















