#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class TestHostname
{
public:
	static void Test(int argc, char ** argv)
	{
		if(argc<3)
		{
			printf("TestHostname Invalid Args!\n");
			return;
		}
		printf("In test_hostname.Test");
		hostent *host;
		int ret = 0;
		if(host = gethostbyname(argv[2]))
		{
			printf("name = %s\n", host->h_name);
			printf("aliases = %s\n", host->h_aliases);
			printf("addtype = %d\n", host->h_addrtype);
		}
		else
		{
			printf("Invalid!\n");
		}
	}
};
