
class TestPoll
{
public:
	static void Test(int argc, char ** argv);

private:
	static const int BUF_SIZE = 1024;
	static const int LISTEN_ENQ = 5;
	static const int OPEN_MAX = 1000;
	static const int INFINITE = -1;

	static void BeginClient(int argc, char ** argv);
	static void BeginServer(int argc, char ** argv);
};
