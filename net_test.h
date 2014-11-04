#include "common.h"
#include "test_ip.h"
#include "test_hostname.h"
#include "test_endian.h"
#include "test_tcp.h"
#include "test_echo.h"
#include <string>
#include <stdio.h>
#include <map>
using namespace std;

class NetTest
{
public:
	void Test(string key, int argc, char** argv)
	{
		auto iter = map_fun.find(key); 
		if(iter!=map_fun.end())
		{
			(iter->second)(argc, argv);
		}
		else
		{
			printf("Function Not Found!\n");
		}
	}

private:
	typedef void(*TestFun)(int argc, char** argv);
	typedef map<string, TestFun> TestFunMap;
	TestFunMap map_fun;

	void RegistTestFun(string key, TestFun fun)
	{
		map_fun.insert(make_pair(key,fun)); 
	}

DECLARE_SINGLETON(NetTest);
};

NetTest::NetTest()
{
	RegistTestFun("ip", TestIP::Test); 
	RegistTestFun("hostname", TestHostname::Test); 
	RegistTestFun("endian", TestEndian::Test); 
	RegistTestFun("tcp", TestTcp::Test); 
	RegistTestFun("echo", TestEcho::Test); 
}

NetTest::~NetTest()
{
}
