#include "net_test.h"

int main(int argc, char** argv)
{
	if(argc<2)
	{
		printf("Argument Invalid!\n");
		return -1;
	}
	NetTest *test = nullptr;
	test = NetTest::GetInstance();
	test->Test(argv[1], argc, argv);
}
