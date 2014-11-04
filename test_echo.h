
class TestEcho
{
public:
	static void Test(int argc, char ** argv);

private:
	static const int BUF_SIZE = 1024;
	static const int LISTEN_ENQ = 5;

	static void BeginClient(int argc, char ** argv);
	static void BeginServer(int argc, char ** argv);
};
