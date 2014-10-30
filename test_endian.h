#include <stdio.h>

class TestEndian
{
public:
	static void Test(int argc, char ** argv)
	{
		long x = 0x11223344;
		char *c = (char *)&x; 

		if(0x11==*c)
		{
			printf("Big Endian\n");
		}
		else
		{
			printf("Little Endian\n");
		}
	}
};
