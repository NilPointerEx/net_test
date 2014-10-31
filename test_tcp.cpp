#include "test_tcp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

void TestTcp::Test(int argc, char ** argv)
{
	printf("TestTcp::Test!\n");
	if(argc<3)
	{
		printf("TestTcp Invalid Args!\n");
		return;
	}
	if(0 == strcmp("client", argv[2]))
	{
		BeginClien(argc, argv);
	}
	else if(0 == strcmp("server", argv[2]))
	{
		BeginServer(argc, argv);
	}
	else
	{
		printf("TestTcp Invalid Args!\n");
	}
}

void TestTcp::BeginClien(int argc, char ** argv)
{
	printf("TestTcp::BeginClien!\n");
	int skfd = 0;
	sockaddr_in server_addr;
	in_addr addr;
	int port = 0;
	char buf[1024] = {0};

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

	//if(-1 == (bind(skfd, (sockaddr*)&server_addr, sizeof(sockaddr))))
	//{
	//	printf("Bind Error\n");
	//}

	//if(-1 == listen(skfd, 4))
	//{
	//	printf("Listen Error\n");
	//}

}
