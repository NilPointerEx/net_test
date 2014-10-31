class TestTcp
{
public:
	static void Test(int argc, char ** argv);

private:
	static const int BUF_SIZE = 1024;

	static void BeginClien(int argc, char ** argv);
	static void BeginServer(int argc, char ** argv);
};
