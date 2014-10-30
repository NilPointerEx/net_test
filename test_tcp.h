#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TestTcp
{
public:
	static void Test(int argc, char ** argv)
	{
		printf("TestTcp::Test!\n");
	}

private:
};
