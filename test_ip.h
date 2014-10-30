#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TestIP
{
public:
	static void Test(int argc, char ** argv)
	{
		if(argc<3)
		{
			printf("TestIP Invalid Args!\n");
			return;
		}
		in_addr addr;
		int ret = 0;
		if(ret = inet_aton(argv[2], &addr))
		{
			printf("ret = %d\n", ret);
			printf("addr = %x\n", addr.s_addr);
			char* c = (char *)&addr;
			printf("IP1 = %x.%x.%x.%x\n", (*c)&0xff, *(c+1)&0xff, *(c+2)&0xff, *(c+3)&0xff);
			printf("IP1 = %u.%u.%u.%u\n", (*c)&0xff, *(c+1)&0xff, *(c+2)&0xff, *(c+3)&0xff);
		}
		else
		{
			printf("Invalid!\n");
		}
	}
};
