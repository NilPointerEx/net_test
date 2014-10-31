
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TestString
{
public:
	static void Test(int argc, char ** argv)
	{
		printf("TestString::Test!\n");
	}

private:
};
